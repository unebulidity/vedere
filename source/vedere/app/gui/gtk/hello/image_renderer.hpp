///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2015 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: image_renderer.hpp
///
/// Author: $author$
///   Date: 11/10/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_GTK_HELLO_IMAGE_RENDERER_HPP
#define _VEDERE_APP_GUI_GTK_HELLO_IMAGE_RENDERER_HPP

#include "vedere/app/gui/hello/image_renderer.hpp"
#include "vedere/gui/gtk/drawing_area.hpp"
#include "vedere/base/base.hpp"

namespace vedere {
namespace app {
namespace gui {
namespace gtk {
namespace hello {

enum transformation_mode_t {
    TRANSFORMATION_MODE_NONE,
    TRANSFORMATION_MODE_FAST,
    TRANSFORMATION_MODE_SMOOTH
};
enum aspect_ratio_mode_t {
    ASPECT_RATIO_MODE_IGNORE,
    ASPECT_RATIO_MODE_KEEP
};
typedef cairo_format_t image_format_t;

typedef gui::hello::image_renderert
<image_format_t, CAIRO_FORMAT_ARGB32,
 aspect_ratio_mode_t, ASPECT_RATIO_MODE_IGNORE,
 transformation_mode_t, TRANSFORMATION_MODE_NONE> image_renderer_implements;

typedef gui::hello::image_renderer_extendt
<image_renderer_implements> image_renderer_extends;
///////////////////////////////////////////////////////////////////////
///  Class: image_renderer
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS image_renderer
: virtual public image_renderer_implements, public image_renderer_extends {
public:
    typedef image_renderer_implements Implements;
    typedef image_renderer_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    image_renderer(cairo_t* cr = 0): cr_(cr_) {
    }
    virtual ~image_renderer() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init(cairo_t* cr, size_t width, size_t height) {
        cr_ = cr;
        width_ = width;
        height_ = height;
        return true;
    }
    virtual bool finish() {
        cr_ = 0;
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::render;
    virtual bool render
    (const void* image, size_t image_width, size_t image_height,
     size_t width, size_t height, size_t x, size_t y, cairo_format_t image_format,
     aspect_ratio_mode_t aspect_ratio_mode, transformation_mode_t transformation_mode) {
        if ((cr_) && (image)) {
            cairo_surface_t* surface = 0;
            if ((surface = image_create_from_data
                 ((unsigned char*)image, image_format, image_width, image_height))) {
                cairo_save(cr_);
                switch(aspect_ratio_mode) {
                case ASPECT_RATIO_MODE_IGNORE: {
                    double scale_x = (((double)width)/((double)image_width)),
                           scale_y = (((double)height)/((double)image_height));
                    cairo_translate(cr_, x,y);
                    cairo_scale(cr_, scale_x,scale_y);
                    break; }
                }
                cairo_set_source_surface(cr_, surface, 0,0);
                cairo_paint(cr_);
                cairo_restore(cr_);
                cairo_surface_destroy(surface);
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual cairo_surface_t* image_create_from_data
    (const unsigned char* image, cairo_format_t image_format,
     guint image_width, guint image_height) const {
        if ((image) && (image_width) && (image_height)) {
            cairo_surface_t* surface = 0;

            if ((surface = cairo_image_surface_create
                 (image_format, image_width, image_height))) {
                unsigned char* surface_data = 0;

                cairo_surface_flush(surface);
                if ((surface_data = cairo_image_surface_get_data(surface))) {
                    int surface_stride = cairo_image_surface_get_stride(surface);

                    if (0 < (surface_stride)) {
                        cairo_surface_mark_dirty(surface);
                        if ((image_copy_data
                             (surface, surface_data, image, image_format,
                              image_width, image_height, surface_stride))) {
                            cairo_surface_flush(surface);
                            return surface;
                        }
                    }
                }
                cairo_surface_destroy(surface);
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual cairo_surface_t* image_copy_data
    (cairo_surface_t* surface, unsigned char* surface_data,
     const unsigned char* image, cairo_format_t image_format,
     guint image_width, guint image_height, guint surface_stride) const {
        if (CAIRO_FORMAT_ARGB32 == (image_format)) {
            return image_copy_data_argb32
            (surface, surface_data, image,
             image_width, image_height, surface_stride);
        }
        return 0;
    }
    virtual cairo_surface_t* image_copy_data_argb32
    (cairo_surface_t* surface, unsigned char* surface_data,
     const unsigned char* image, guint image_width, guint image_height,
     guint surface_stride) const {
        if ((surface) && (surface_data) && (surface_stride)
            && (image) && (image_width) && (image_height)) {
            size_t row_size = (image_width * sizeof(uint32_t));

            for (guint row = 0; row < image_height; ++row) {
                memcpy(surface_data, image, row_size);
                surface_data += surface_stride;
                image += row_size;
            }
            return surface;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    cairo_t* cr_;
};

} // namespace hello
} // namespace gtk 
} // namespace gui 
} // namespace app 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_GTK_HELLO_IMAGE_RENDERER_HPP 
