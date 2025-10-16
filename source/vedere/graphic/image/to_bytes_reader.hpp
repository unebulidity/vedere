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
///   File: to_bytes_reader.hpp
///
/// Author: $author$
///   Date: 11/24/2015, 1/14/2021
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_TO_BYTES_READER_HPP
#define _VEDERE_GRAPHIC_IMAGE_TO_BYTES_READER_HPP

#include "vedere/graphic/image/reader.hpp"
#include "vedere/io/logger.hpp"

namespace vedere {
namespace graphic {
namespace image {

typedef implement_base to_bytes_reader_implements;
///////////////////////////////////////////////////////////////////////
///  Class: to_bytes_readert
///////////////////////////////////////////////////////////////////////
template <class TImplements = to_bytes_reader_implements>
class _EXPORT_CLASS to_bytes_readert: virtual public TImplements {
public:
    typedef TImplements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual byte_t* detach_image
    (size_t& image_width, size_t& image_height,
     size_t& image_depth, size_t& image_size) {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual byte_t* alloc_image
    (size_t image_width, size_t image_height,
     size_t image_depth, size_t image_size) {
        return 0;
    }
    virtual void free_image() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef to_bytes_readert<> to_bytes_reader;

///////////////////////////////////////////////////////////////////////
///  Class: to_bytes_reader_extendt
///////////////////////////////////////////////////////////////////////
template <class TImplements, class TExtends>

class _EXPORT_CLASS to_bytes_reader_extendt
: virtual public to_bytes_reader,
  virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    to_bytes_reader_extendt()
    : image_width_(0), image_height_(0),
      image_depth_(0), image_size_(0), bytes_(0) {
    }
    virtual ~to_bytes_reader_extendt() {
        free_image();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual byte_t* detach_image
    (size_t& image_width, size_t& image_height,
     size_t& image_depth, size_t& image_size) {
        byte_t* bytes = bytes_;
        image_size = image_size_;
        image_width = image_width_;
        image_height = image_height_;
        image_depth = image_depth_;
        bytes_ = 0;
        image_width_ = (image_height_ = (image_depth_ = (image_size_ = 0)));
        VEDERE_LOG_MESSAGE_DEBUG("detach_image(): bytes = " << pointer_to_string(bytes) << " size = " << image_size << " width = " << image_width << " height = " << image_height << " depth = " << image_depth << "");
        return bytes;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual byte_t* alloc_image
    (size_t image_width, size_t image_height,
     size_t image_depth, size_t image_size) {
        VEDERE_LOG_MESSAGE_DEBUG("alloc_image(): bytes_ = new byte_t[image_size = " << image_size << "]...");
        if ((bytes_ = new byte_t[image_size])) {
            VEDERE_LOG_MESSAGE_DEBUG("alloc_image(): ...bytes_ = " << pointer_to_string(bytes_) << " = new byte_t[image_size = " << image_size << "]");
            image_width_ = image_width;
            image_height_ = image_height;
            image_depth_ = image_depth;
            image_size_ = image_size;
            memset(bytes_, 255, image_size);
            return bytes_;
        }
        return 0;
    }
    virtual void free_image() {
        image_width_ = (image_height_ = (image_depth_ = (image_size_ = 0)));
        if ((bytes_)) {
            VEDERE_LOG_MESSAGE_DEBUG("free_image(): delete[] bytes_ = " << pointer_to_string(bytes_) << "...");
            delete[] bytes_;
            VEDERE_LOG_MESSAGE_DEBUG("free_image(): ...delete[] bytes_ = " << pointer_to_string(bytes_) << "");
            bytes_ = 0;
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    size_t image_width_, image_height_, image_depth_, image_size_;
    byte_t* bytes_;
};

///////////////////////////////////////////////////////////////////////
///  Class: to_bgra_bytes_readert
///////////////////////////////////////////////////////////////////////
template
<class TImplements, class TReaderExtends,
 class TExtends = image::to_bytes_reader_extendt
 <TImplements, TReaderExtends> >

class _EXPORT_CLASS to_bgra_bytes_readert
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef to_bgra_bytes_readert Derives;

    typedef bool (Derives::*on_image_pixel_t)
    (vedere::graphic::image::pixel_t& pixel, byte_t* pixel_byte, size_t pixel_bytes,
     size_t image_col, size_t image_row, size_t image_plane,
     size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    to_bgra_bytes_readert(): on_image_pixel_(0) {
    }
    virtual ~to_bgra_bytes_readert() {
        VEDERE_LOG_MESSAGE_DEBUG("this->free_image()...");
        this->free_image();
        VEDERE_LOG_MESSAGE_ERROR("...this->free_image()");
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_begin_image
    (size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        size_t image_byte_depth = 0, image_size = 0;

        switch (pixel_value_interpretation) {
        case pixel_value_interpretation_none: {
            if ((1 == image_planes) && (0 == values_per_pixel)
                && ((24 == bits_per_value))) {
                image_byte_depth = 4;
                image_size = (image_height * image_width * image_byte_depth);
                on_image_pixel_ = &Derives::on_rgb_image_pixel;
            } else {
                VEDERE_LOG_MESSAGE_ERROR("...invalid image configuration values_per_pixel = " << values_per_pixel << ", bits_per_value = " << bits_per_value << "");
                return false;
            }
            break; }
        case pixel_value_interpretation_greyscale: {
            if ((1 == image_planes) && (8 == bits_per_value)
                && ((1 == values_per_pixel))) {
                image_byte_depth = 4;
                image_size = (image_height * image_width * image_byte_depth);
                on_image_pixel_ = &Derives::on_greyscale_image_pixel;
            } else {
                VEDERE_LOG_MESSAGE_ERROR("...invalid image configuration values_per_pixel = " << values_per_pixel << ", bits_per_value = " << bits_per_value << "");
                return false;
            }
            break; }
        case pixel_value_interpretation_rgb: {
            if ((1 == image_planes) && (8 == bits_per_value)
                && ((3 == values_per_pixel))) {
                image_byte_depth = 4;
                image_size = (image_height * image_width * image_byte_depth);
                on_image_pixel_ = &Derives::on_rgb_image_pixel;
            } else {
                VEDERE_LOG_MESSAGE_ERROR("...invalid image configuration values_per_pixel = " << values_per_pixel << ", bits_per_value = " << bits_per_value << "");
                return false;
            }
            break; }
        case pixel_value_interpretation_rgba: {
            if ((1 == image_planes) && (8 == bits_per_value)
                && ((4 == values_per_pixel))) {
                image_byte_depth = 4;
                image_size = (image_height * image_width * image_byte_depth);
                on_image_pixel_ = &Derives::on_rgba_image_pixel;
            } else {
                VEDERE_LOG_MESSAGE_ERROR("...invalid image configuration values_per_pixel = " << values_per_pixel << ", bits_per_value = " << bits_per_value << "");
                return false;
            }
            break; }
        case pixel_value_interpretation_bgra: {
            if ((1 == image_planes) && (8 == bits_per_value)
                && ((4 == values_per_pixel))) {
                image_byte_depth = 4;
                image_size = (image_height * image_width * image_byte_depth);
                on_image_pixel_ = &Derives::on_bgra_image_pixel;
            } else {
                VEDERE_LOG_MESSAGE_ERROR("...invalid image configuration values_per_pixel = " << values_per_pixel << ", bits_per_value = " << bits_per_value << "");
                return false;
            }
            break; }
        default:
            VEDERE_LOG_MESSAGE_ERROR("...imvalid pixel_value_interpretation = " << pixel_value_interpretation << "");
            return false;
        }
        this->free_image();
        if ((this->alloc_image(image_width, image_height, image_byte_depth*8, image_size))) {
            return true;
        }
        on_image_pixel_ = 0;
        return false;
    }
    virtual bool on_end_image
    (size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;
        on_image_pixel_ = 0;
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_image_pixel
    (vedere::graphic::image::pixel_t& pixel, byte_t* pixel_byte, size_t pixel_bytes,
     size_t image_col, size_t image_row, size_t image_plane,
     size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = false;
        if ((on_image_pixel_)) {
            success = (this->*on_image_pixel_)
            (pixel, pixel_byte, pixel_bytes, image_col, image_row, image_plane,
             image_width, image_height, image_planes, values_per_pixel,
             bits_per_value, pixel_value_interpretation);
        }
        return success;
    }
    virtual bool on_greyscale_image_pixel
    (vedere::graphic::image::pixel_t& pixel, byte_t* pixel_byte, size_t pixel_bytes,
     size_t image_col, size_t image_row, size_t image_plane,
     size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;
        if ((pixel_byte) && (1 == pixel_bytes)) {
            size_t pixel_offset = ((image_row*image_width)+(image_col))*4;
            if ((this->bytes_) && (this->image_size_ > pixel_offset)) {
                byte_t* byte = this->bytes_ + pixel_offset;
                byte[0] = *pixel_byte;
                byte[1] = *pixel_byte;
                byte[2] = *pixel_byte;
                byte[3] = 255;
                on_bgra_image_pixel_byte(byte);
            }
        } else {
            success = false;
        }
        return success;
    }
    virtual bool on_rgb_image_pixel
    (vedere::graphic::image::pixel_t& pixel, byte_t* pixel_byte, size_t pixel_bytes,
     size_t image_col, size_t image_row, size_t image_plane,
     size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;
        size_t pixel_offset = ((image_row*image_width)+(image_col))*4;
        if ((this->bytes_) && (this->image_size_ > pixel_offset)) {
            byte_t* byte = this->bytes_ + pixel_offset;
            byte[0] = pixel.color_axis(color::space::rgba::axis_blue);
            byte[1] = pixel.color_axis(color::space::rgba::axis_green);
            byte[2] = pixel.color_axis(color::space::rgba::axis_red);
            byte[3] = 255;
            on_bgra_image_pixel_byte(byte);
        }
        return success;
    }
    virtual bool on_rgba_image_pixel
    (vedere::graphic::image::pixel_t& pixel, byte_t* pixel_byte, size_t pixel_bytes,
     size_t image_col, size_t image_row, size_t image_plane,
     size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;
        size_t pixel_offset = ((image_row*image_width)+(image_col))*4;
        if ((this->bytes_) && (this->image_size_ > pixel_offset)) {
            byte_t* byte = this->bytes_ + pixel_offset;
            byte[0] = pixel.color_axis(color::space::rgba::axis_blue);
            byte[1] = pixel.color_axis(color::space::rgba::axis_green);
            byte[2] = pixel.color_axis(color::space::rgba::axis_red);
            byte[3] = pixel.color_axis(color::space::rgba::axis_alpha);
            on_bgra_image_pixel_byte(byte);
        }
        return success;
    }
    virtual bool on_bgra_image_pixel
    (vedere::graphic::image::pixel_t& pixel, byte_t* pixel_byte, size_t pixel_bytes,
     size_t image_col, size_t image_row, size_t image_plane,
     size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;
        size_t pixel_offset = ((image_row*image_width)+(image_col))*4;
        if ((this->bytes_) && (this->image_size_ > pixel_offset)) {
            byte_t* byte = this->bytes_ + pixel_offset;
            byte[0] = pixel.color_axis(color::space::bgra::axis_red);
            byte[1] = pixel.color_axis(color::space::bgra::axis_green);
            byte[2] = pixel.color_axis(color::space::bgra::axis_blue);
            byte[3] = pixel.color_axis(color::space::bgra::axis_alpha);
            on_bgra_image_pixel_byte(byte);
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void on_bgra_image_pixel_byte(byte_t* byte) {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    on_image_pixel_t on_image_pixel_;
};

///////////////////////////////////////////////////////////////////////
///  Class: to_argb_bytes_readert
///////////////////////////////////////////////////////////////////////
template
<class TImplements, class TReaderExtends,
 class TExtends = to_bgra_bytes_readert
 <TImplements, TReaderExtends> >

class _EXPORT_CLASS to_argb_bytes_readert
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    to_argb_bytes_readert() {
    }
    virtual ~to_argb_bytes_readert() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void on_bgra_image_pixel_byte(byte_t* byte) {
        if ((byte)) {
            byte_t temp = byte[0];
            byte[0] = byte[3];
            byte[3] = temp;
            temp = byte[1];
            byte[1] = byte[2];
            byte[2] = temp;
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///  Class: to_rgba_bytes_readert
///////////////////////////////////////////////////////////////////////
template
<class TImplements, class TReaderExtends,
 class TExtends = to_bgra_bytes_readert
 <TImplements, TReaderExtends> >

class _EXPORT_CLASS to_rgba_bytes_readert
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    to_rgba_bytes_readert() {
    }
    virtual ~to_rgba_bytes_readert() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void on_bgra_image_pixel_byte(byte_t* byte) {
        if ((byte)) {
            byte_t blue = byte[0];
            byte[0] = byte[2];
            byte[2] = blue;
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace image
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_TO_BYTES_READER_HPP 
