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
///   Date: 4/2/2016
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_TIFF_LIBTIFF_IMAGE_READER_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_TIFF_LIBTIFF_IMAGE_READER_HPP

#include "vedere/graphic/image/to_bytes_reader.hpp"
#include "vedere/graphic/image/reader.hpp"
#include "lamna/graphic/image/format/tiff/libtiff/reader.hpp"
#include "lamna/graphic/image/format/tiff/libtiff/reader_events.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace tiff {
namespace libtiff {

typedef image::reader image_reader_implement;
typedef lamna::graphic::image::format::tiff::libtiff::reader_events reader_implement;
///////////////////////////////////////////////////////////////////////
///  Class: image_readerimplements
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS image_reader_implements
: virtual public reader_implement,
  virtual public image_reader_implement {
public:
    typedef image_reader_implement Implements;
    typedef reader_implement ReaderImplements;
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

    typedef lamna::graphic::image::format::tiff::libtiff::reader reader_t;

    typedef bool (Derives::*on_TIFFPixel_t)
    (lamna::graphic::image::pixel& pixel,
     byte_t* pixelByte, size_t pixelBytes, size_t imageRow, size_t imageCol,
     size_t imageLength, size_t imageWidth, size_t rowsPerStrip,
     size_t samplesPerPixel, size_t bitsPerSample,
     uint16_t planarConfiguration, uint16_t photometricInterpretation);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    image_readert()
    : reader_(this),
      pixel_value_interpretation_(pixel_value_interpretation_none),
      on_TIFFPixel_(0) {
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
    virtual bool on_8_bit_PLANARCONFIG_CONTIG_PHOTOMETRIC_RGB_TIFFPixel
    (lamna::graphic::image::pixel& pixel,
     byte_t* pixelByte, size_t pixelBytes, size_t imageRow, size_t imageCol,
     size_t imageLength, size_t imageWidth, size_t rowsPerStrip,
     size_t samplesPerPixel, size_t bitsPerSample,
     uint16_t planarConfiguration, uint16_t photometricInterpretation) {
        bool success = true;
        size_t red = pixel.red(), green = pixel.green(), blue = pixel.blue();
        rgba::pixel_t pix(red, green, blue, 255, 255);
        success = this->on_image_pixel
        (pix, pixelByte, pixelBytes,
         imageCol, imageRow, 0, imageWidth, imageLength, 1,
         samplesPerPixel, bitsPerSample, pixel_value_interpretation_);
        return success;
    }
    virtual bool on_8_bit_PLANARCONFIG_CONTIG_PHOTOMETRIC_RGBA_TIFFPixel
    (lamna::graphic::image::pixel& pixel,
     byte_t* pixelByte, size_t pixelBytes, size_t imageRow, size_t imageCol,
     size_t imageLength, size_t imageWidth, size_t rowsPerStrip,
     size_t samplesPerPixel, size_t bitsPerSample,
     uint16_t planarConfiguration, uint16_t photometricInterpretation) {
        bool success = true;
        size_t red = pixel.red(), green = pixel.green(), blue = pixel.blue(), alpha = pixel.alpha();
        rgba::pixel_t pix(red, green, blue, alpha, 255);
        success = this->on_image_pixel
        (pix, pixelByte, pixelBytes,
         imageCol, imageRow, 0, imageWidth, imageLength, 1,
         samplesPerPixel, bitsPerSample, pixel_value_interpretation_);
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_TIFFPixel
    (lamna::graphic::image::pixel& pixel,
     byte_t* pixelByte, size_t pixelBytes, size_t imageRow, size_t imageCol,
     size_t imageLength, size_t imageWidth, size_t rowsPerStrip,
     size_t samplesPerPixel, size_t bitsPerSample,
     uint16_t planarConfiguration, uint16_t photometricInterpretation) {
        bool success = false;
        if ((on_TIFFPixel_)) {
            success = (this->*on_TIFFPixel_)
            (pixel, pixelByte, pixelBytes, imageRow, imageCol,
             imageLength, imageWidth, rowsPerStrip,
             samplesPerPixel, bitsPerSample,
             planarConfiguration, photometricInterpretation);
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_begin_PLANARCONFIG_CONTIG_PHOTOMETRIC_RGB_TIFFImage
    (size_t imageLength, size_t imageWidth,
     size_t rowsPerStrip, size_t samplesPerPixel, size_t bitsPerSample,
     uint16_t planarConfiguration, uint16_t photometricInterpretation) {
        bool success = true;
        switch (samplesPerPixel) {
        case 3:
            switch (bitsPerSample) {
            case 8:
                on_TIFFPixel_ = &Derives::on_8_bit_PLANARCONFIG_CONTIG_PHOTOMETRIC_RGB_TIFFPixel;
                break;
            default:
                VEDERE_LOG_MESSAGE_ERROR("...unimplemented bitsPerSample = " << bitsPerSample << " on on_begin_PLANARCONFIG_CONTIG_PHOTOMETRIC_RGB_TIFFImage(" << imageLength << "," <<  imageWidth << "," <<  rowsPerStrip << "," <<  samplesPerPixel << "," <<  bitsPerSample << "," <<  planarConfiguration << "," <<  photometricInterpretation << ")");
                success = false;
                break;
            } // switch (bitsPerSample)
            if ((success)) {
                success = this->on_begin_image
                (imageWidth, imageLength, 1, samplesPerPixel, bitsPerSample,
                 pixel_value_interpretation_ = pixel_value_interpretation_rgb);
            }
            break;
        case 4:
            switch (bitsPerSample) {
            case 8:
                on_TIFFPixel_ = &Derives::on_8_bit_PLANARCONFIG_CONTIG_PHOTOMETRIC_RGBA_TIFFPixel;
                break;
            default:
                VEDERE_LOG_MESSAGE_ERROR("...unimplemented bitsPerSample = " << bitsPerSample << " on on_begin_PLANARCONFIG_CONTIG_PHOTOMETRIC_RGB_TIFFImage(" << imageLength << "," <<  imageWidth << "," <<  rowsPerStrip << "," <<  samplesPerPixel << "," <<  bitsPerSample << "," <<  planarConfiguration << "," <<  photometricInterpretation << ")");
                success = false;
                break;
            } // switch (bitsPerSample)
            if ((success)) {
                success = this->on_begin_image
                (imageWidth, imageLength, 1, samplesPerPixel, bitsPerSample,
                 pixel_value_interpretation_ = pixel_value_interpretation_rgba);
            }
            break;
        default:
            VEDERE_LOG_MESSAGE_ERROR("...unimplemented samplesPerPixel = " << samplesPerPixel << " on on_begin_PLANARCONFIG_CONTIG_PHOTOMETRIC_RGB_TIFFImage(" << imageLength << "," <<  imageWidth << "," <<  rowsPerStrip << "," <<  samplesPerPixel << "," <<  bitsPerSample << "," <<  planarConfiguration << "," <<  photometricInterpretation << ")");
            success = false;
            break;
        } // switch (samplesPerPixel)
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_begin_TIFFImage
    (size_t imageLength, size_t imageWidth,
     size_t rowsPerStrip, size_t samplesPerPixel, size_t bitsPerSample,
     uint16_t planarConfiguration, uint16_t photometricInterpretation) {
        bool success = true;
        switch (planarConfiguration) {
        case PLANARCONFIG_CONTIG:
            switch (photometricInterpretation) {
            case PHOTOMETRIC_RGB:
                success = on_begin_PLANARCONFIG_CONTIG_PHOTOMETRIC_RGB_TIFFImage
                (imageLength, imageWidth, rowsPerStrip, samplesPerPixel,
                 bitsPerSample, planarConfiguration, photometricInterpretation);
                break;
            default:
                VEDERE_LOG_MESSAGE_ERROR("...unimplemented photometricInterpretation = " << photometricInterpretation << " on on_begin_TIFFImage(" << imageLength << "," <<  imageWidth << "," <<  rowsPerStrip << "," <<  samplesPerPixel << "," <<  bitsPerSample << "," <<  planarConfiguration << "," <<  photometricInterpretation << ")");
                success = false;
                break;
            }
            break;
        default:
            VEDERE_LOG_MESSAGE_ERROR("...unimplemented planarConfiguration = " << planarConfiguration << " on on_begin_TIFFImage(" << imageLength << "," <<  imageWidth << "," <<  rowsPerStrip << "," <<  samplesPerPixel << "," <<  bitsPerSample << "," <<  planarConfiguration << "," <<  photometricInterpretation << ")");
            success = false;
            break;
        }
        return success;
    }
    virtual bool on_end_TIFFImage
    (size_t imageLength, size_t imageWidth,
     size_t rowsPerStrip, size_t samplesPerPixel, size_t bitsPerSample,
     uint16_t planarConfiguration, uint16_t photometricInterpretation) {
        bool success = true;
        success = this->on_end_image
        (imageWidth, imageLength, 1, samplesPerPixel,
         bitsPerSample, pixel_value_interpretation_);
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    reader_t reader_;
    pixel_value_interpretation_t pixel_value_interpretation_;
    on_TIFFPixel_t on_TIFFPixel_;
};
typedef image_readert<> image_reader;

typedef to_bgra_bytes_readert
<image_reader_implements, image_reader> to_bgra_image_reader;

typedef to_rgba_bytes_readert
<image_reader_implements, image_reader> to_rgba_image_reader;

} // namespace libtiff 
} // namespace tiff 
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_TIFF_LIBTIFF_IMAGE_READER_HPP 
