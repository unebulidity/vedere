///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   File: main_window.hpp
///
/// Author: $author$
///   Date: 7/17/2016, 3/15/2024
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_MAIN_WINDOW_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_MAIN_WINDOW_HPP

#include "vedere/graphic/image/format/viewer/image_loader.hpp"
#include "vedere/graphic/image/format/viewer/main.hpp"
#include "vedere/graphic/image/to_bytes_reader.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace viewer {

///////////////////////////////////////////////////////////////////////
///  Class: main_windowt
///////////////////////////////////////////////////////////////////////
template <class TExtends>
class _EXPORT_CLASS main_windowt: public TExtends {
public:
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main_windowt(image_loader* _image_loader = 0, bool _use_opengl = false)
    : image_loader_(_image_loader), use_opengl_(_use_opengl) {
    }
    virtual ~main_windowt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool load_image
    (size_t image_width, size_t image_height,
     size_t image_depth, const char_t* image_file,
     image_format_t image_format = image_format_raw,
     raw_image_format_t raw_image_format = first_raw_image_format) {
        bool success = false;
        switch (image_format) {
        case image_format_raw:
            if ((image_width) && (image_height) && (image_depth)) {
                success = load_raw_image
                (image_width, image_height,
                 image_depth, image_file, raw_image_format);
            } else {
                success = load_image(image_file, image_format);
            }
            break;
        default:
            success = load_image(image_file, image_format);
            break;
        }
        return success;
    }
    virtual bool load_image
    (const char_t* image_file, image_format_t image_format) {
        if ((image_loader_)) {
            return image_loader_->load_image(image_file, image_format);
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool load_raw_image
    (size_t image_width, size_t image_height,
     size_t image_depth, const char_t* image_file,
     raw_image_format_t raw_image_format = first_raw_image_format) {
        if ((image_loader_)) {
            if ((image_loader_->load_raw_image
                 (image_width, image_height, image_depth, image_file, raw_image_format))) {
                return true;
            }
        }
        if ((image_file) && (image_width) && (image_height) && (image_depth)) {
            size_t image_pixel_size = ((image_depth+7)/8),
                   image_size = (image_width*image_height*image_pixel_size);
            FILE* file = 0;

            VEDERE_LOG_MESSAGE_DEBUG("fopen(" << image_file << ", \"rb\")...");
            if ((file = fopen(image_file, "rb"))) {
                xos::io::read::byte_file f(file);
                bool success = false;

                VEDERE_LOG_MESSAGE_DEBUG("...fopen(" << image_file << ", \"rb\")");
                if ((load_image(f, image_size, image_width, image_height))) {
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
            if ((set_image(bytes, image_size, image_width, image_height))) {
                return true;
            } else {
                delete[] bytes;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void* load_image
    (byte_reader& reader, size_t size, size_t width, size_t height) {
        return 0;
    }
    virtual void* set_image
    (byte_t* bytes, size_t size, size_t width, size_t height) {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_use_opengl(bool to = true) {
        use_opengl_ = to;
        return use_opengl_;
    }
    virtual bool use_opengl() const {
        return use_opengl_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    image_loader* image_loader_;
    bool use_opengl_;
};

} // namespace viewer
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_MAIN_WINDOW_HPP 
