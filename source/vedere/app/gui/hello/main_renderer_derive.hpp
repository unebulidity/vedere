///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2018 $organization$
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
///   File: main_renderer_derive.hpp
///
/// Author: $author$
///   Date: 11/22/2018
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_HELLO_MAIN_RENDERER_DERIVE_HPP
#define _VEDERE_APP_GUI_HELLO_MAIN_RENDERER_DERIVE_HPP

#include "vedere/app/gui/hello/main.hpp"
#include "vedere/graphic/image/to_bytes_reader.hpp"

namespace vedere {
namespace app {
namespace gui {
namespace hello {

///////////////////////////////////////////////////////////////////////
///  Class: main_renderer_derivet
///////////////////////////////////////////////////////////////////////
template <class TExtends>
class _EXPORT_CLASS main_renderer_derivet: public TExtends {
public:
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main_renderer_derivet() {
    }
    virtual ~main_renderer_derivet() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool load_image
    (size_t image_width, size_t image_height,
     size_t image_depth, const char_t* image_file,
     gui::hello::image_format_t image_format = gui::hello::image_format_raw) {
        bool success = false;
        switch (image_format) {

        case gui::hello::image_format_jpeg:
            success = load_jpeg_image(image_file);
            break;

        case gui::hello::image_format_tiff:
            success = load_tiff_image(image_file);
            break;

        case gui::hello::image_format_gif:
            success = load_gif_image(image_file);
            break;

        case gui::hello::image_format_png:
            success = load_png_image(image_file);
            break;

        case gui::hello::image_format_bmp:
            success = load_bmp_image(image_file);
            break;

        case gui::hello::image_format_raw:
            if ((image_width) && (image_height) && (image_depth)) {
                success = load_raw_image
                (image_width, image_height, image_depth, image_file);
            } else {
                success = load_raw_image(image_file);
            }
            break;

        default:
            VEDERE_LOG_ERROR("unexpected image_format = " << image_format << "");
            break;
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool load_jpeg_image(const char_t* image_file) {
        return false;
    }
    virtual bool load_tiff_image(const char_t* image_file) {
        return false;
    }
    virtual bool load_gif_image(const char_t* image_file) {
        return false;
    }
    virtual bool load_png_image(const char_t* image_file) {
        return false;
    }
    virtual bool load_bmp_image(const char_t* image_file) {
        return false;
    }
    virtual bool load_raw_image(const char_t* image_file) {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool load_raw_image
    (size_t image_width, size_t image_height,
     size_t image_depth, const char_t* image_file) {
        if ((image_file) && (image_width) && (image_height) && (image_depth)) {
            size_t image_pixel_size = ((image_depth+7)/8),
                   image_size = (image_width*image_height*image_pixel_size);
            FILE* file = 0;
            if ((file = fopen(image_file, "rb"))) {
                xos::io::read::byte_file f(file);
                bool success = false;
                if ((Extends::load_image(f, image_size, image_width, image_height))) {
                    success = true;
                }
                fclose(file);
                return success;
            } else {
                VEDERE_LOG_MESSAGE_ERROR("...failed on fopen(" << image_file << ", \"rb\")");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool load_image(graphic::image::to_bytes_reader& reader) {
        size_t image_width = 0, image_height = 0,
               image_depth = 0, image_size = 0;
        byte_t* bytes = 0;

        if ((bytes = reader.detach_image
             (image_width, image_height, image_depth, image_size))) {
            if ((Extends::set_image(bytes, image_size, image_width, image_height))) {
                return true;
            } else {
                delete[] bytes;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS main_renderer_derivet

} /// namespace hello
} /// namespace gui
} /// namespace app
} /// namespace vedere

#endif /// ndef _VEDERE_APP_GUI_HELLO_MAIN_RENDERER_DERIVE_HPP
