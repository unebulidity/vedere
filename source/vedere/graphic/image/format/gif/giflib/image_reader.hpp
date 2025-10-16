///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2020 $organization$
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
///   Date: 12/8/2020
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_GIF_GIFLIB_IMAGE_READER_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_GIF_GIFLIB_IMAGE_READER_HPP

#include "vedere/graphic/image/format/gif/giflib/reader.hpp"
#include "vedere/graphic/image/to_bytes_reader.hpp"
#include "vedere/graphic/image/reader.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace gif {
namespace giflib {

typedef image::reader image_reader_implement;
typedef reader_events reader_implement;
///////////////////////////////////////////////////////////////////////
///  Class: image_readert_implements
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS image_readert_implements
: virtual public reader_implement,
  virtual public image_reader_implement {
public:
    typedef image_reader_implement Implements;
    typedef reader_implement ReaderImplements;
};
typedef base image_readert_extends;
///////////////////////////////////////////////////////////////////////
///  Class: image_readert
///////////////////////////////////////////////////////////////////////
template <class TImplements = image_readert_implements, class TExtends = image_readert_extends>
class _EXPORT_CLASS image_readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef image_readert Derives;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    image_readert()
    : image_planes_(0), values_per_pixel_(0), bits_per_pixel_value_(0), 
      pixel_value_interpretation_(pixel_value_interpretation_none) {
    }
    virtual ~image_readert() {
    }
private:
    image_readert(const image_readert &copy) {
    }
public:

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool read(const char* filename) {
        giflib::reader reader(this);
        if ((reader.read(filename))) {
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_begin_gif_image
    (size_t height, size_t width, size_t colors, 
     GifWord interlaceType, GifPixelType backgroundPixel, ColorMapObject* colorMap, giflib::file& file) {
        bool success = true;

        if (colorMap) {
            image_planes_ = 1;
            values_per_pixel_ = 3;
            bits_per_pixel_value_ = 8;
            pixel_value_interpretation_ = pixel_value_interpretation_rgb;
        } else {
            success = false;
        }
        if ((success)) {
            VEDERE_LOG_MESSAGE_DEBUG("this->on_begin_image(width = " << width << ", height = " << height << ", image_planes_ = " << image_planes_ << ", values_per_pixel_ = " << values_per_pixel_ << ", bits_per_pixel_value_ = " << bits_per_pixel_value_ << ", pixel_value_interpretation_ = " << pixel_value_interpretation_ << ")...");
            if ((success = this->on_begin_image(width, height, image_planes_, values_per_pixel_, bits_per_pixel_value_, pixel_value_interpretation_))) {
                VEDERE_LOG_MESSAGE_DEBUG("...this->on_begin_image(width = " << width << ", height = " << height << ", image_planes_ = " << image_planes_ << ", values_per_pixel_ = " << values_per_pixel_ << ", bits_per_pixel_value_ = " << bits_per_pixel_value_ << ", pixel_value_interpretation_ = " << pixel_value_interpretation_ << ")");
            } else {
                VEDERE_LOG_MESSAGE_ERROR("...failed on this->on_begin_image(width = " << width << ", height = " << height << ", image_planes_ = " << image_planes_ << ", values_per_pixel_ = " << values_per_pixel_ << ", bits_per_pixel_value_ = " << bits_per_pixel_value_ << ", pixel_value_interpretation_ = " << pixel_value_interpretation_ << ")");
            }
        }
        return success;
    }
    virtual bool on_end_gif_image
    (size_t height, size_t width, size_t colors, 
     GifWord interlaceType, GifPixelType backgroundPixel, ColorMapObject* colorMap, giflib::file& file) {
        bool success = true;

        VEDERE_LOG_MESSAGE_DEBUG("this->on_end_image(width = " << width << ", height = " << height << ", image_planes_ = " << image_planes_ << ", values_per_pixel_ = " << values_per_pixel_ << ", bits_per_pixel_value_ = " << bits_per_pixel_value_ << ", pixel_value_interpretation_ = " << pixel_value_interpretation_ << ")...");
        if ((success = this->on_end_image(width, height, image_planes_, values_per_pixel_, bits_per_pixel_value_, pixel_value_interpretation_))) {
            VEDERE_LOG_MESSAGE_DEBUG("...this->on_end_image(width = " << width << ", height = " << height << ", image_planes_ = " << image_planes_ << ", values_per_pixel_ = " << values_per_pixel_ << ", bits_per_pixel_value_ = " << bits_per_pixel_value_ << ", pixel_value_interpretation_ = " << pixel_value_interpretation_ << ")");
        } else {
            VEDERE_LOG_MESSAGE_ERROR("...failed this->on_end_image(width = " << width << ", height = " << height << ", image_planes_ = " << image_planes_ << ", values_per_pixel_ = " << values_per_pixel_ << ", bits_per_pixel_value_ = " << bits_per_pixel_value_ << ", pixel_value_interpretation_ = " << pixel_value_interpretation_ << ")");
        }
        image_planes_ = 0;
        values_per_pixel_ = 0;
        bits_per_pixel_value_ = 0;
        pixel_value_interpretation_ = pixel_value_interpretation_none;
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_gif_pixel_color
    (GifColorType& color, GifPixelType& pixel, size_t pixelColumn, size_t pixelLine,
     size_t height, size_t width, size_t colors, GifWord interlaceType, GifPixelType backgroundPixel, ColorMapObject* colorMap) {
        bool success = true;
        rgba::pixel_t rgba(color.Red, color.Green, color.Blue);

        VEDERE_LOG_MESSAGE_TRACE("this->on_image_pixel(rgba(color.Red = " << color.Red << ", color.Green = " << color.Green << ", color.Blue = " << color.Blue << "), &pixel, values_per_pixel_, pixelColumn = " << pixelColumn << ", pixelLine = " << pixelLine << ", image_planes_, width, height, image_planes_, values_per_pixel_, bits_per_pixel_value_, pixel_value_interpretation_)...");
        if ((success = this->on_image_pixel(rgba, &pixel, values_per_pixel_, pixelColumn, pixelLine, image_planes_, width, height, image_planes_, values_per_pixel_, bits_per_pixel_value_, pixel_value_interpretation_))) {
            VEDERE_LOG_MESSAGE_TRACE("...this->on_image_pixel(rgba(color.Red = " << color.Red << ", color.Green = " << color.Green << ", color.Blue = " << color.Blue << "), &pixel, values_per_pixel_, pixelColumn = " << pixelColumn << ", pixelLine = " << pixelLine << ", image_planes_, width, height, image_planes_, values_per_pixel_, bits_per_pixel_value_, pixel_value_interpretation_)");
        } else {
            VEDERE_LOG_MESSAGE_ERROR("...failed on this->on_image_pixel(rgba(color.Red = " << color.Red << ", color.Green = " << color.Green << ", color.Blue = " << color.Blue << "), &pixel, values_per_pixel_, pixelColumn = " << pixelColumn << ", pixelLine = " << pixelLine << ", image_planes_, width, height, image_planes_, values_per_pixel_, bits_per_pixel_value_, pixel_value_interpretation_)");
        }
        return success;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    size_t image_planes_, values_per_pixel_, bits_per_pixel_value_;
    pixel_value_interpretation_t pixel_value_interpretation_;
}; /// class _EXPORT_CLASS image_readert
typedef image_readert<> image_reader;

typedef to_bgra_bytes_readert
<image_readert_implements, image_reader> to_bgra_image_reader;

typedef to_rgba_bytes_readert
<image_readert_implements, image_reader> to_rgba_image_reader;

} /// namespace giflib
} /// namespace gif
} /// namespace format
} /// namespace image
} /// namespace graphic
} /// namespace vedere

#endif /// _VEDERE_GRAPHIC_IMAGE_FORMAT_GIF_GIFLIB_IMAGE_READER_HPP
