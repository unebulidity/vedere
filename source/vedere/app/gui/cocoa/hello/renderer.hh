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
///   File: renderer.hh
///
/// Author: $author$
///   Date: 11/8/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_COCOA_HELLO_RENDERER_HH
#define _VEDERE_APP_GUI_COCOA_HELLO_RENDERER_HH

#include "vedere/app/gui/cocoa/hello/image_renderer.hh"
#include "vedere/app/gui/hello/renderer_extend.hpp"
#include "vedere/app/gui/hello/main_renderer_derive.hpp"
#include "vedere/app/gui/hello/main.hpp"
#include "vedere/graphic/image/format/png/libpng/image_reader.hpp"
#include "vedere/graphic/image/format/jpeg/libjpeg/image_reader.hpp"
#include "vedere/graphic/image/format/tiff/libtiff/image_reader.hpp"
#include "vedere/graphic/image/format/gif/giflib/image_reader.hpp"
#include "vedere/graphic/image/format/raw/libraw/image_reader.hpp"
#include "vedere/io/logger.hpp"

namespace vedere {
namespace app {
namespace gui {
namespace cocoa {
namespace hello {

typedef implement_base renderer_implements;
typedef gui::hello::main_renderer_derivet
<gui::hello::renderer_extendt
  <image_renderer::image_format_t,
   image_renderer::image_format_none, 
   image_renderer> > renderer_extends;
///////////////////////////////////////////////////////////////////////
///  Class: renderer
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS renderer
: virtual public renderer_implements, public renderer_extends {
public:
    typedef renderer_implements Implements;
    typedef renderer_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    renderer()
    : image_format_option_(gui::hello::image_format_raw),
      image_transform_option_(gui::hello::image_transform_fast),
      image_width_option_(0), image_height_option_(0), image_depth_option_(0) {
    }
    virtual ~renderer() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init(iCGContextRef context, size_t width, size_t height) {
        return image_renderer_.init(context, width,height);
    }
    virtual bool finish() {
        return image_renderer_.finish();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool resize(size_t width, size_t height) {
        return image_renderer_.resize(width, height);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual image_renderer_t*
    image_renderer(const image_format_t& image_format) const {
        if (!(image_format != image_renderer_.image_format())) {
            return ((image_renderer_t*)&image_renderer_);
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void* load_image_file() {
        if ((load_image
            (image_width_option_, image_height_option_, image_depth_option_,
             image_file_option_.chars(), image_format_option_))) {
            return image_;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool load_png_image(const char_t* image_file) {
        if ((image_file)) {
            graphic::image::format::png::libpng::to_rgba_image_reader reader;
            if ((reader.read(image_file))) {
                if ((this->load_image(reader))) {
                    return true;
                }
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool load_jpeg_image(const char_t* image_file) {
        if ((image_file)) {
            graphic::image::format::jpeg::libjpeg::to_rgba_image_reader reader;
            if ((reader.read(image_file))) {
                if ((this->load_image(reader))) {
                    return true;
                }
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool load_tiff_image(const char_t* image_file) {
        if ((image_file)) {
            graphic::image::format::tiff::libtiff::to_rgba_image_reader reader;
            if ((reader.read(image_file))) {
                if ((this->load_image(reader))) {
                    return true;
                }
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool load_gif_image(const char_t* image_file) {
        if ((image_file)) {
            graphic::image::format::gif::giflib::to_rgba_image_reader reader;
            if ((reader.read(image_file))) {
                if ((this->load_image(reader))) {
                    return true;
                }
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool load_raw_image(const char_t* image_file) {
        if ((image_file)) {
            graphic::image::format::raw::libraw::to_rgba_image_reader reader;
            if ((reader.read(image_file))) {
                if ((this->load_image(reader))) {
                    return true;
                }
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_image_format_option(const char_t* to) {
        if ((to) && (to[0])) {
            VEDERE_LOG_MESSAGE_DEBUG("image_format_option = \"" << to << "\"...");
            if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_RAW_OPTARG_C))
                || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_RAW_OPTARG_S))) {
                VEDERE_LOG_MESSAGE_DEBUG("image_format_option_ = gui::hello::image_format_raw");
                image_format_option_ = gui::hello::image_format_raw;
            } else {
                if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_JPEG_OPTARG_C))
                    || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_JPEG_OPTARG_S))) {
                    VEDERE_LOG_MESSAGE_DEBUG("image_format_option_ = gui::hello::image_format_jpeg");
                    image_format_option_ = gui::hello::image_format_jpeg;
                } else {
                    if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_TIFF_OPTARG_C))
                        || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_TIFF_OPTARG_S))) {
                        VEDERE_LOG_MESSAGE_DEBUG("image_format_option_ = gui::hello::image_format_tiff");
                        image_format_option_ = gui::hello::image_format_tiff;
                    } else {
                        if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_PNG_OPTARG_C))
                            || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_PNG_OPTARG_S))) {
                            VEDERE_LOG_MESSAGE_DEBUG("image_format_option_ = gui::hello::image_format_pmg");
                            image_format_option_ = gui::hello::image_format_png;
                        } else {
                            if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_GIF_OPTARG_C))
                                || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_GIF_OPTARG_S))) {
                                VEDERE_LOG_MESSAGE_DEBUG("image_format_option_ = gui::hello::image_format_gif");
                                image_format_option_ = gui::hello::image_format_gif;
                            } else {
                                if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_BMP_OPTARG_C))
                                    || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_BMP_OPTARG_S))) {
                                    VEDERE_LOG_MESSAGE_DEBUG("image_format_option_ = gui::hello::image_format_bmp");
                                    image_format_option_ = gui::hello::image_format_bmp;
                                } else {
                                }
                            }
                        }
                    }
                }
            }
        }
        return to;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_image_transform_option(const char_t* to) {
        if ((to) && (to[0])) {
            VEDERE_LOG_MESSAGE_DEBUG("image_transform_option = \"" << to << "\"...");
            if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_FAST_OPTARG_C))
                || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_FAST_OPTARG_S))) {
                VEDERE_LOG_MESSAGE_DEBUG("image_transform_option_ = gui::hello::image_transform_fast");
                image_transform_option_ = gui::hello::image_transform_fast;
            } else {
                if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_SMOOTH_OPTARG_C))
                    || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_SMOOTH_OPTARG_S))) {
                    VEDERE_LOG_MESSAGE_DEBUG("image_transform_option_ = gui::hello::image_transform_smooth");
                    image_transform_option_ = gui::hello::image_transform_smooth;
                } else {
                }
            }
        }
        return to;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_image_width_option(const char_t* to) {
        if ((to) && (to[0])) {
            VEDERE_LOG_MESSAGE_DEBUG("image_width_option = \"" << to << "\"...");
            image_width_option_ = chars_t::to_unsigned(to);
        }
        return to;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_image_height_option(const char_t* to) {
        if ((to) && (to[0])) {
            VEDERE_LOG_MESSAGE_DEBUG("image_height_option = \"" << to << "\"...");
            image_height_option_ = chars_t::to_unsigned(to);
        }
        return to;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_image_depth_option(const char_t* to) {
        if ((to) && (to[0])) {
            VEDERE_LOG_MESSAGE_DEBUG("image_depth_option = \"" << to << "\"...");
            image_depth_option_ = chars_t::to_unsigned(to);
        }
        return to;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_image_file_option(const char_t* to) {
        if ((to) && (to[0])) {
            VEDERE_LOG_MESSAGE_DEBUG("image_file_option = \"" << to << "\"...");
            image_file_option_.assign(to);
        }
        return to;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    gui::hello::image_format_t image_format_option_;
    gui::hello::image_transform_t image_transform_option_;
    size_t image_width_option_, image_height_option_, image_depth_option_;
    string image_file_option_;
    hello::image_renderer image_renderer_;
};

} // namespace hello
} // namespace cocoa 
} // namespace gui 
} // namespace app 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_COCOA_HELLO_RENDERER_HH 
