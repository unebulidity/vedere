///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2021 $organization$
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
///   File: image_reader.hpp
///
/// Author: $author$
///   Date: 1/10/2021
///////////////////////////////////////////////////////////////////////
#ifndef VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_BGRA_IMAGE_READER_HPP
#define VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_BGRA_IMAGE_READER_HPP

#include "vedere/graphic/image/format/raw/bgra/reader.hpp"
#include "vedere/graphic/image/to_bytes_reader.hpp"
#include "vedere/graphic/image/reader.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace raw {
namespace bgra {

typedef image::reader image_reader_implement;
typedef reader_events reader_implement;
///////////////////////////////////////////////////////////////////////
///  Class: image_readerimplement
///////////////////////////////////////////////////////////////////////
class EXPORT_CLASS image_reader_implements
: virtual public reader_implement,
  virtual public image_reader_implement {
public:
    typedef image_reader_implement Implements;
    typedef reader_implement ReaderImplements;
}; /// class image_reader_implements

typedef extend image_reader_extends;
///////////////////////////////////////////////////////////////////////
/// class image_readert
///////////////////////////////////////////////////////////////////////
template <class TExtends = image_reader_extends, class TImplements = image_reader_implements>
class EXPORT_CLASS image_readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef image_readert Derives;

    ///////////////////////////////////////////////////////////////////////
    /// constructor / destructor
    ///////////////////////////////////////////////////////////////////////
    image_readert()
     : image_height_(0), image_width_(0), 
       image_planes_(1), values_per_pixel_(4), bits_per_pixel_value_(8),
       bgra_pixel_value_interpretation_(bgra::pixel_value_interpretation_bgra),
       pixel_value_interpretation_(image::pixel_value_interpretation_bgra) {
    }
    virtual ~image_readert() {
    }
private:
    image_readert(const image_readert& copy): Extends(copy) {
    }
public:

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init(size_t image_height, size_t image_width, size_t image_depth) {
        if ((image_height) && (image_width) && (0 < image_depth)  && (5 > image_depth)) {
            if (4 == image_depth) {
                image_height_ = image_height;
                image_width_ = image_width;
                return true;
            }
        }
        return false;
    }
    virtual bool read(const char* filename) {
        bgra::reader reader
        (image_height_, image_width_, values_per_pixel_, 
         bits_per_pixel_value_, bgra_pixel_value_interpretation_, this);
        if ((reader.read(filename))) {
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_begin_bgra_image
    (bgra::file& file, size_t image_height, size_t image_width, 
     size_t values_per_pixel, size_t bits_per_pixel_value,
     bgra::pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = false;

        if ((bgra::pixel_value_interpretation_bgra == pixel_value_interpretation)) {
            pixel_value_interpretation_ = image::pixel_value_interpretation_bgra;
            if ((8 == (bits_per_pixel_value_ = bits_per_pixel_value))) {
                if ((4 == (values_per_pixel_ = values_per_pixel))) {
                    image_planes_ = 1;
                    success = true;
                }
            }
        }
        if ((success)) {
            VEDERE_LOG_MESSAGE_DEBUG("this->on_begin_image(width = " << image_width << ", height = " << image_height << ", image_planes_ = " << image_planes_ << ", values_per_pixel_ = " << values_per_pixel_ << ", bits_per_pixel_value_ = " << bits_per_pixel_value_ << ", pixel_value_interpretation_ = " << pixel_value_interpretation_ << ")...");
            if ((success = this->on_begin_image(image_width, image_height, image_planes_, values_per_pixel_, bits_per_pixel_value_, pixel_value_interpretation_))) {
            } else {
                VEDERE_LOG_MESSAGE_ERROR("...failed on this->on_begin_image(width = " << image_width << ", height = " << image_height << ", image_planes_ = " << image_planes_ << ", values_per_pixel_ = " << values_per_pixel_ << ", bits_per_pixel_value_ = " << bits_per_pixel_value_ << ", pixel_value_interpretation_ = " << pixel_value_interpretation_ << ")");
            }
        }
        return success;
    }
    virtual bool on_end_bgra_image
    (bgra::file& file, size_t image_height, size_t image_width, 
     size_t values_per_pixel, size_t bits_per_pixel_value,
     bgra::pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;

        VEDERE_LOG_MESSAGE_DEBUG("this->on_end_image(width = " << image_width << ", height = " << image_height << ", image_planes_ = " << image_planes_ << ", values_per_pixel_ = " << values_per_pixel_ << ", bits_per_pixel_value_ = " << bits_per_pixel_value_ << ", pixel_value_interpretation_ = " << pixel_value_interpretation_ << ")...");
        if ((success = this->on_end_image(image_width, image_height, image_planes_, values_per_pixel_, bits_per_pixel_value_, pixel_value_interpretation_))) {
        } else {
            VEDERE_LOG_MESSAGE_ERROR("...failed this->on_end_image(width = " << image_width << ", height = " << image_height << ", image_planes_ = " << image_planes_ << ", values_per_pixel_ = " << values_per_pixel_ << ", bits_per_pixel_value_ = " << bits_per_pixel_value_ << ", pixel_value_interpretation_ = " << pixel_value_interpretation_ << ")");
        }
        image_planes_ = 0;
        values_per_pixel_ = 0;
        bits_per_pixel_value_ = 0;
        pixel_value_interpretation_ = image::pixel_value_interpretation_none;
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_bgra_col
    (byte_t* pixels, size_t pixels_length, size_t pixels_col, size_t pixels_line, 
     size_t image_height, size_t image_width, 
     size_t values_per_pixel, size_t bits_per_pixel_value,
     bgra::pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;

        if ((pixels) && (3 < pixels_length)) {
            byte_t red = pixels[2], green = pixels[1], blue = pixels[0];
            rgba::pixel_t rgba(red, green, blue);

            VEDERE_LOG_MESSAGE_TRACE("this->on_image_pixel(rgba(red = " << red << ", green = " << green << ", blue = " << blue << "), pixels, values_per_pixel_, pixels_col = " << pixels_col << ", pixels_line = " << pixels_line << ", image_planes_, image_width, image_height, image_planes_, values_per_pixel_, bits_per_pixel_value_, pixel_value_interpretation_)...");
            if ((success = this->on_image_pixel(rgba, pixels, values_per_pixel_, pixels_col, pixels_line, image_planes_, image_width, image_height, image_planes_, values_per_pixel_, bits_per_pixel_value_, pixel_value_interpretation_))) {
                VEDERE_LOG_MESSAGE_TRACE("...this->on_image_pixel(rgba(red = " << red << ", green = " << green << ", blue = " << blue << "), pixels, values_per_pixel_, pixels_col = " << pixels_col << ", pixels_line = " << pixels_line << ", image_planes_, image_width, image_height, image_planes_, values_per_pixel_, bits_per_pixel_value_, pixel_value_interpretation_)");
            } else {
                VEDERE_LOG_MESSAGE_ERROR("...failed on this->on_image_pixel(rgba(red = " << red << ", green = " << green << ", blue = " << blue << "), pixels, values_per_pixel_, pixels_col = " << pixels_col << ", pixels_line = " << pixels_line << ", image_planes_, image_width, image_height, image_planes_, values_per_pixel_, bits_per_pixel_value_, pixel_value_interpretation_)");
            }
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool bgra_reader_events_all_success() const {
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    size_t image_height_, image_width_, image_planes_, values_per_pixel_, bits_per_pixel_value_;
    bgra::pixel_value_interpretation_t bgra_pixel_value_interpretation_;
    image::pixel_value_interpretation_t pixel_value_interpretation_;
}; /// class image_readert
typedef image_readert<> image_reader;

typedef to_bgra_bytes_readert
<image_reader_implements, image_reader> to_bgra_image_reader;

typedef to_rgba_bytes_readert
<image_reader_implements, image_reader> to_rgba_image_reader;

} /// namespace bgra
} /// namespace raw
} /// namespace format
} /// namespace image
} /// namespace graphic
} /// namespace vedere

#endif /// ndef VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_BGRA_IMAGE_READER_HPP 
