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
///   File: image_reader.hpp
///
/// Author: $author$
///   Date: 11/26/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_BMP_IMPLEMENT_IMAGE_READER_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_BMP_IMPLEMENT_IMAGE_READER_HPP

#include "vedere/graphic/image/format/bmp/implement/reader.hpp"
#include "vedere/graphic/image/to_bytes_reader.hpp"
#include "vedere/graphic/image/reader.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace bmp {
namespace implement {

typedef image::reader image_reader_implement;
typedef reader_events reader_implement;
///////////////////////////////////////////////////////////////////////
///  Class: image_readerimplement
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
<class TImplements = image_reader_implements,
 class TExtends = image_reader_extends>

class _EXPORT_CLASS image_readert
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef image_readert Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    image_readert()
    : samples_per_pixel_(0),
      pixel_value_interpretation_(pixel_value_interpretation_none) {
    }
    virtual ~image_readert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool read(const char* filename) {
        implement::reader reader(this);
        if ((reader.read(filename))) {
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_bmp_pixel
    (RGBQUAD& rgb,
     BYTE& col_byte, TSIZE col_bytes,
     TSIZE col, TSIZE row, TSIZE plane,
     TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        rgba::pixel_t pixel(rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue);
        bool success = this->on_image_pixel
        (pixel, &col_byte, col_bytes, col, rows-row-1,
         plane, cols, rows, planes, samples_per_pixel_,
         bits, pixel_value_interpretation_);
        return success;
    }
    virtual bool on_bmp_pixel
    (RGBTRIPLE& rgb,
     BYTE& col_byte, TSIZE col_bytes,
     TSIZE col, TSIZE row, TSIZE plane,
     TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        rgba::pixel_t pixel(rgb.rgbtRed, rgb.rgbtGreen, rgb.rgbtBlue);
        bool success = this->on_image_pixel
        (pixel, &col_byte, col_bytes, col, rows-row-1,
         plane, cols, rows, planes, samples_per_pixel_,
         bits, pixel_value_interpretation_);
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_begin_bmp_row
    (BYTE& row_byte, TSIZE row_bytes, TSIZE row, TSIZE plane,
     TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        bool success = this->on_begin_image_row
        (&row_byte, row_bytes, rows-row-1,
         plane, cols, rows, planes, samples_per_pixel_,
         bits, pixel_value_interpretation_);
        return success;
    }
    virtual bool on_end_bmp_row
    (BYTE& row_byte, TSIZE row_bytes, TSIZE row, TSIZE plane,
     TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        bool success = this->on_end_image_row
        (&row_byte, row_bytes, rows-row-1,
         plane, cols, rows, planes, samples_per_pixel_,
         bits, pixel_value_interpretation_);
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_begin_bmp_image
    (TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        bool success = this->on_begin_image
        (cols, rows, planes, samples_per_pixel_,
         bits, pixel_value_interpretation_);
        return success;
    }
    virtual bool on_end_bmp_image
    (TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        bool success = this->on_end_image
        (cols, rows, planes, samples_per_pixel_,
         bits, pixel_value_interpretation_);
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    size_t samples_per_pixel_;
    pixel_value_interpretation_t pixel_value_interpretation_;
};
typedef image_readert<> image_reader;

typedef to_bgra_bytes_readert
<image_reader_implements, image_reader> to_bgra_image_reader;

} // namespace implement
} // namespace bmp 
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_BMP_IMPLEMENT_IMAGE_READER_HPP 
