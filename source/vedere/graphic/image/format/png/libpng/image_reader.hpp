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
///   File: image_reader.hpp
///
/// Author: $author$
///   Date: 4/9/2016
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_PNG_LIBPNG_IMAGE_READER_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_PNG_LIBPNG_IMAGE_READER_HPP

#include "lamna/graphic/image/format/png/libpng/png.hpp"
#include "vedere/graphic/image/to_bytes_reader.hpp"
#include "vedere/graphic/image/reader.hpp"
#include "lamna/graphic/image/format/png/libpng/reader.hpp"
#include "lamna/graphic/image/format/png/libpng/reader_events.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace png {
namespace libpng {

typedef image::reader image_reader_implement;
typedef lamna::graphic::image::format::png::libpng::reader_events reader_implement;
///////////////////////////////////////////////////////////////////////
///  Class: image_readerimplements
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS image_reader_implements
: virtual public reader_implement,
  virtual public image_reader_implement {
public:
    typedef image_reader_implement Implements;
    typedef reader_implement ReaderImplements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef base image_reader_extends;
///////////////////////////////////////////////////////////////////////
///  Class: image_readert
///////////////////////////////////////////////////////////////////////
template
<class TImplements = image_reader_implements, class TExtends = image_reader_extends>
class _EXPORT_CLASS image_readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef image_readert Derives;

    typedef lamna::graphic::image::format::png::libpng::reader reader_t;

    typedef bool (Derives::*on_PNGPixel_t)
    (lamna::graphic::image::pixel& pixel,
     byte_t* colByte, size_t colBytes, size_t col, size_t row,
     size_t height, size_t width, size_t bitDepth, size_t colorChannels,
     uint colorType, uint filterType, uint interlaceType, uint compressionType);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    image_readert()
    : reader_(this),
      pixel_value_interpretation_(pixel_value_interpretation_none),
      on_PNGPixel_(0) {
    }
    virtual ~image_readert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Implements::Implements::read;
    virtual bool read(const char* file) {
        if ((file)) {
            if ((reader_.read(file))) {
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_PNGPixel8
    (lamna::graphic::image::pixel& pixel,
     byte_t* colByte, size_t colBytes, size_t col, size_t row,
     size_t height, size_t width, size_t bitDepth, size_t colorChannels,
     uint colorType, uint filterType, uint interlaceType, uint compressionType) {
        size_t red = pixel.red(), green = pixel.green(), blue = pixel.blue();
        rgba::pixel_t pix(red, green, blue, ((byte_t)-1), ((byte_t)-1));
        bool success = this->on_image_pixel
        (pix, colByte, colBytes, col, row, 0, width, height, 1,
         colorChannels, bitDepth, pixel_value_interpretation_);
        return success;
    }
    virtual bool on_PNGPixel16
    (lamna::graphic::image::pixel& pixel,
     byte_t* colByte, size_t colBytes, size_t col, size_t row,
     size_t height, size_t width, size_t bitDepth, size_t colorChannels,
     uint colorType, uint filterType, uint interlaceType, uint compressionType) {
        size_t red = pixel.red(), green = pixel.green(), blue = pixel.blue(), alpha = pixel.alpha();
        rgba::pixel_t pix(red, green, blue, alpha, ((word_t)-1));
        bool success = this->on_image_pixel
        (pix, colByte, colBytes, col, row, 0, width, height, 1,
         colorChannels, bitDepth, pixel_value_interpretation_);
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_begin_PNGImage
    (size_t height, size_t width, size_t bitDepth, size_t colorChannels,
     uint colorType, uint filterType, uint interlaceType, uint compressionType) {
        bool success = true;
        switch (interlaceType) {
        case PNG_INTERLACE_NONE:
            switch (colorType) {
            case PNG_COLOR_TYPE_RGB:
            case PNG_COLOR_TYPE_RGB_ALPHA:
                pixel_value_interpretation_ = (PNG_COLOR_TYPE_RGB_ALPHA != colorType)
                ?(pixel_value_interpretation_rgb):(pixel_value_interpretation_rgba);
                success = this->on_begin_image
                (width, height, 1, colorChannels, bitDepth, pixel_value_interpretation_);
                break;
            default:
                success = false;
                LAMNA_LOG_MESSAGE_ERROR("...implemented colorType = " << colorType << " on_begin_PNGImage(" << height << "," <<  width << "," <<  bitDepth << "," <<  colorChannels << "," <<  colorType << "," <<  filterType << "," <<  interlaceType << "," <<  compressionType << ")");
                break;
            }
            break;
        default:
            success = false;
            LAMNA_LOG_MESSAGE_ERROR("...implemented interlaceType = " << interlaceType << " on_begin_PNGImage(" << height << "," <<  width << "," <<  bitDepth << "," <<  colorChannels << "," <<  colorType << "," <<  filterType << "," <<  interlaceType << "," <<  compressionType << ")");
            break;
        }
        return success;
    }
    virtual bool on_end_PNGImage
    (size_t height, size_t width, size_t bitDepth, size_t colorChannels,
     uint colorType, uint filterType, uint interlaceType, uint compressionType) {
        bool success = this->on_end_image
        (width, height, 1, colorChannels, bitDepth, pixel_value_interpretation_);
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    reader_t reader_;
    pixel_value_interpretation_t pixel_value_interpretation_;
    on_PNGPixel_t on_PNGPixel_;
};
typedef image_readert<> image_reader;

typedef to_bgra_bytes_readert
<image_reader_implements, image_reader> to_bgra_image_reader;

typedef to_argb_bytes_readert
<image_reader_implements, image_reader> to_argb_image_reader;

typedef to_rgba_bytes_readert
<image_reader_implements, image_reader> to_rgba_image_reader;

} // namespace libpng 
} // namespace png 
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_PNG_LIBPNG_IMAGE_READER_HPP 
