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
///   File: image_loader.hpp
///
/// Author: $author$
///   Date: 7/18/2016
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_IMAGE_LOADER_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_IMAGE_LOADER_HPP

#include "vedere/graphic/image/to_bytes_reader.hpp"
#include "vedere/io/logger.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace viewer {

enum image_format_t {
    image_format_raw,
    image_format_png,
    image_format_jpeg,
    image_format_tiff,
    image_format_gif,
    image_format_bmp,
    image_format_pgm,
    image_format_dng,

    next_image_format,
    first_image_format = image_format_raw,
    last_image_format = (next_image_format - 1),
    image_formats = (last_image_format - first_image_format + 1)
};

enum raw_image_format_t {
    raw_image_format_bgra,

    next_raw_image_format,
    first_raw_image_format = raw_image_format_bgra,
    last_raw_image_format = (next_raw_image_format - 1),
    raw_image_formats = (last_raw_image_format - first_raw_image_format + 1)
};

typedef implement_base image_loader_implements;
///////////////////////////////////////////////////////////////////////
///  Class: image_loadert
///////////////////////////////////////////////////////////////////////
template <class TImplements = image_loader_implements>
class _EXPORT_CLASS image_loadert: virtual public TImplements {
public:
    typedef TImplements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool load_raw_image
    (size_t image_width, size_t image_height,
     size_t image_depth, const char_t* image_file,
     raw_image_format_t raw_image_format) {
        image_loadert* forward_to = image_loader_forward_to();
        VEDERE_LOG_MESSAGE_DEBUG("load_raw_image(...," <<  chars_to_string(image_file) << ", " << raw_image_format << ")...");
        if ((forward_to)) {
            return forward_to->load_raw_image(image_width, image_height, image_depth, image_file, raw_image_format);
        }
        VEDERE_LOG_MESSAGE_DEBUG("...load_raw_image(...," <<  chars_to_string(image_file) << ", " << raw_image_format << ")");
        return false;
    }
    virtual bool load_image
    (const char_t* image_file, image_format_t image_format) {
        image_loadert* forward_to = image_loader_forward_to();
        VEDERE_LOG_MESSAGE_DEBUG("load_image(" <<  chars_to_string(image_file) << ", " << image_format << ")...");
        if ((forward_to)) {
            return forward_to->load_image(image_file, image_format);
        }
        VEDERE_LOG_MESSAGE_DEBUG("...load_image(" <<  chars_to_string(image_file) << ", " << image_format << ")");
        return false;
    }
    virtual bool load_image
    (graphic::image::to_bytes_reader& reader) {
        bool success = false;
        image_loadert* forward_to = image_loader_forward_to();
        VEDERE_LOG_MESSAGE_DEBUG("load_image(" <<  pointer_to_string(&reader) << ")...");
        if ((forward_to)) {
            success = forward_to->load_image(reader);
        } else {
            size_t image_width = 0, image_height = 0,
                   image_depth = 0, image_size = 0;
            byte_t* bytes = 0;
            void *image = 0;

            if ((bytes = reader.detach_image
                 (image_width, image_height, image_depth, image_size))) {
                VEDERE_LOG_MESSAGE_DEBUG("load_image(): image = set_image(bytes = " << pointer_to_string(bytes) << " size = " << image_size << " width = " << image_width << " height = " << image_height << ") depth = " << image_depth << "...");
                if ((image = set_image(bytes, image_size, image_width, image_height))) {
                    VEDERE_LOG_MESSAGE_DEBUG("load_image(): ...image = " << pointer_to_string(image) << " = set_image(bytes = " << pointer_to_string(bytes) << " size = " << image_size << " width = " << image_width << " height = " << image_height << ") depth = " << image_depth << "");
                    success = true;
                } else {
                    VEDERE_LOG_MESSAGE_ERROR("load_image(): ...failed on image = " << pointer_to_string(image) << " = set_image(bytes = " << pointer_to_string(bytes) << " size = " << image_size << " width = " << image_width << " height = " << image_height << ") depth = " << image_depth << "...");
                    delete[] bytes;
                }
            } else {
                VEDERE_LOG_MESSAGE_ERROR("...failed on reader.detach_image()");
            }
        }
        VEDERE_LOG_MESSAGE_DEBUG("...load_image(" <<  pointer_to_string(&reader) << ")");
        return success;
    }
    virtual void* set_image
    (byte_t* bytes, size_t size, size_t width, size_t height) {
        image_loadert* forward_to = image_loader_forward_to();
        VEDERE_LOG_MESSAGE_DEBUG("set_image(" << pointer_to_string(bytes) << "," <<  size << "," <<  width << "," <<  height << ")...");
        if ((forward_to)) {
            return forward_to->set_image(bytes, size, width, height);
        }
        VEDERE_LOG_MESSAGE_DEBUG("...set_image(" << pointer_to_string(bytes) << "," <<  size << "," <<  width << "," <<  height << ")");
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual image_loadert* forward_image_loader_to(image_loadert* to) {
        return 0;
    }
    virtual image_loadert* image_loader_forward_to() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef image_loadert<> image_loader;

} // namespace viewer
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_IMAGE_LOADER_HPP 
