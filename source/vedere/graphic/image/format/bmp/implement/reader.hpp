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
///   File: reader.hpp
///
/// Author: $author$
///   Date: 11/25/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_BMP_IMPLEMENT_READER_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_BMP_IMPLEMENT_READER_HPP

#include "vedere/graphic/image/format/bmp/implement/reader_events.hpp"
#include "vedere/io/logger.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace bmp {
namespace implement {

typedef reader_events reader_implements;
typedef base reader_extends;
///////////////////////////////////////////////////////////////////////
///  Class: readert
///////////////////////////////////////////////////////////////////////
template
<class TImplements = reader_implements, class TExtends = reader_extends>

class _EXPORT_CLASS readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef readert Derives;

    typedef bool (Derives::*on_bmp_col_t)
    (BYTE& col_byte, TSIZE col_bytes,
     TSIZE col, TSIZE row, TSIZE plane,
     TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes);

    typedef bool (Derives::*on_bmp_row_t)
    (BYTE& row_byte, TSIZE row_bytes, TSIZE row, TSIZE plane,
     TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    readert(reader_events* bmp_reader_events_forward_to = 0)
    : bmp_reader_events_forward_to_(bmp_reader_events_forward_to),
      on_bmp_row_(0), on_bmp_col_(0),
      rgb_quad_(0), rgb_quads_(0),
      row_byte_(0), row_bytes_(0), row_padded_(0),
      col_bytes_(0), col_shift_(0), col_mask_(0) {
    }
    virtual ~readert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool read(const char* filename) {
        xos::io::read::byte_file file;
        if ((file.open(filename))) {
            bool success = read(file);
            file.close();
            return success;
        }
        return false;
    }
    virtual bool read(byte_reader& reader) {
        size_t count = 0, amount = 0;

        VEDERE_LOG_MESSAGE_DEBUG("bfh_.read(reader)...");
        if ((amount = bfh_.read(reader))) {
            BITMAPFILEHEADER& bfh = bfh_.wrapped();
            VEDERE_LOG_MESSAGE_DEBUG("..." << amount << " = bfh_.read(reader)");
            count += amount;

            VEDERE_LOG_MESSAGE_DEBUG("bih_.read(reader)...");
            if ((amount = bih_.read(reader))) {
                BITMAPINFOHEADER& bih = bih_.wrapped();
                VEDERE_LOG_MESSAGE_DEBUG("..." << amount << " = bih_.read(reader)");
                count += amount;

                switch(bih.biCompression) {
                case BI_RGB:
                    VEDERE_LOG_MESSAGE_DEBUG("bih.biCompression = BI_RGB (" << bih.biCompression << ")");
                    return read_rgb(bfh, bih, count, reader);
                    break;
                case BI_RLE8:
                case BI_RLE4:
                case BI_BITFIELDS:
                case BI_JPEG:
                case BI_PNG:
                default:
                    VEDERE_LOG_MESSAGE_ERROR("unsupported bih.biCompression = " << bih.biCompression << "");
                    return false;
                }
            }
        }
        return false;
    }
    virtual bool read_rgb
    (BITMAPFILEHEADER& bfh, BITMAPINFOHEADER& bih,
     size_t& count, byte_reader& reader) {
        size_t amount = 0;

        if (24 > (bih.biBitCount)) {
            if (256 < (rgb_quads_ = (1 << bih.biBitCount))) {
                VEDERE_LOG_MESSAGE_ERROR("256 < (rgb_quads_ = " << rgb_quads_ << ")");
                return false;
            } else {
                VEDERE_LOG_MESSAGE_ERROR("rgb_quads_ = " << rgb_quads_ << "");
            }
        }
        if (0 < (rgb_quads_)) {
            VEDERE_LOG_MESSAGE_DEBUG("rgb_.read(reader, rgb_quads_ = " << rgb_quads_ << ")...");
            if (rgb_quads_ == (amount = rgb_.read(reader, rgb_quads_))) {
                VEDERE_LOG_MESSAGE_DEBUG("..." << rgb_quads_ << " == (" << amount << " = rgb_.read(reader, rgb_quads_ = " << rgb_quads_ << "))");
                if ((rgb_quad_ = rgb_.elements())) {
                    if (256 > (rgb_quads_)) {
                        col_mask_ = (255 >> (8 - bih.biBitCount));
                        VEDERE_LOG_MESSAGE_DEBUG("on_bmp_row_ = &Derives::on_nbit_bmp_row");
                        VEDERE_LOG_MESSAGE_DEBUG("on_bmp_col_ = &Derives::on_nbit_palette_bmp_col");
                        on_bmp_row_ = &Derives::on_nbit_bmp_row;
                        on_bmp_col_ = &Derives::on_nbit_palette_bmp_col;
                    } else {
                        if (256 == (rgb_quads_)) {
                            VEDERE_LOG_MESSAGE_DEBUG("on_bmp_col_ = &Derives::on_8bit_palette_bmp_col");
                            on_bmp_col_ = &Derives::on_8bit_palette_bmp_col;
                        } else {
                            VEDERE_LOG_MESSAGE_ERROR("unexpected rgb_quads_ = " << rgb_quads_ << "");
                            return false;
                        }
                    }
                }
            } else {
                VEDERE_LOG_MESSAGE_DEBUG("..." << rgb_quads_ << " != (" << amount << " = rgb_.read(reader, rgb_quads_ = " << rgb_quads_ << "))");
                return false;
            }
        } else {
            if ((1 == bih.biPlanes)) {
                if ((24 == bih.biBitCount)) {
                    VEDERE_LOG_MESSAGE_DEBUG("on_bmp_col_ = &Derives::on_24bit_bmp_col");
                    on_bmp_col_ = &Derives::on_24bit_bmp_col;
                } else {
                    if ((32 == bih.biBitCount)) {
                        VEDERE_LOG_MESSAGE_DEBUG("on_bmp_col_ = &Derives::on_32bit_bmp_col");
                        on_bmp_col_ = &Derives::on_32bit_bmp_col;
                    } else {
                        VEDERE_LOG_MESSAGE_ERROR("unsupported bih.biBitCount = " << bih.biBitCount << "");
                        return false;
                    }
                }
            } else {
                VEDERE_LOG_MESSAGE_ERROR("unsupported bih.biPlanes = " << bih.biPlanes << "");
                return false;
            }
        }

        if (count != (bfh.bfOffBits)) {
            VEDERE_LOG_MESSAGE_ERROR("((count = " << count << ") != (bfh.bfOffBits = " << bfh.bfOffBits << "))");
            return false;
        }

        col_bytes_ = (bih.biBitCount+7)/8;
        VEDERE_LOG_MESSAGE_DEBUG("col_bytes_ = " << col_bytes_);

        row_bytes_ = ((bih.biBitCount*bih.biWidth)+7)/8;
        row_bytes_ += (row_padded_ = ((4-(row_bytes_ & 3)) & 3));
        VEDERE_LOG_MESSAGE_DEBUG("row_bytes_ = " << row_bytes_);

        if (row_bytes_ == (amount = row_.set_length(row_bytes_))) {
            if ((row_byte_ = (row_.elements()))) {
                if ((this->on_begin_bmp_image
                     (bih.biBitCount, bih.biWidth,
                      bih.biHeight, bih.biPlanes))) {
                    bool success = true;
                    TSIZE bytes = 0;
                    TSIZE plane = 0;
                    TSIZE row = 0;

                    for (row = 0, plane = 0, bytes = bih.biSizeImage;
                         bytes >= row_bytes_; bytes -= row_bytes_) {

                        if (row_bytes_ == (amount = reader.read(row_byte_, row_bytes_))) {

                            if ((this->on_begin_bmp_row
                                 (*row_byte_, row_bytes_, row, plane,
                                  bih.biBitCount, bih.biWidth, bih.biHeight, bih.biPlanes))) {

                                if ((this->on_bmp_row
                                     (*row_byte_, row_bytes_, row, plane,
                                      bih.biBitCount, bih.biWidth, bih.biHeight, bih.biPlanes))) {

                                    if ((this->on_end_bmp_row
                                         (*row_byte_, row_bytes_, row, plane,
                                          bih.biBitCount, bih.biWidth, bih.biHeight, bih.biPlanes))) {

                                        count += amount;

                                        if ((bih.biHeight) < (++row)) {
                                            row = 0;
                                            ++plane;
                                        }
                                        continue;
                                    }
                                }
                            }
                        } else {
                            VEDERE_LOG_MESSAGE_ERROR(row_bytes_ << " != (" << amount << " = reader.read(row_byte_, " << row_bytes_ << "))");
                        }
                        return false;
                    }

                    if (!(this->on_end_bmp_image
                         (bih.biBitCount, bih.biWidth,
                          bih.biHeight, bih.biPlanes))) {
                        success = false;
                    }
                    return success;
                }
            } else {
                VEDERE_LOG_MESSAGE_ERROR("0 = (row_.elements())");
                return false;
            }
        } else {
            VEDERE_LOG_MESSAGE_ERROR(row_bytes_ << " != (" << amount << " = row_.set_length(" << row_bytes_ << "))");
            return false;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_bmp_col
    (BYTE& col_byte, TSIZE col_bytes,
     TSIZE col, TSIZE row, TSIZE plane,
     TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        bool success = true;
        if ((on_bmp_col_)) {
            success = (this->*on_bmp_col_)
            (col_byte, col_bytes, col, row,
             plane, bits, cols, rows, planes);
        }
        return success;
    }
    virtual bool on_24bit_bmp_col
    (BYTE& col_byte, TSIZE col_bytes,
     TSIZE col, TSIZE row, TSIZE plane,
     TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        //VEDERE_LOG_MESSAGE_DEBUG("(" << (&col_byte)[0] << ", "  << (&col_byte)[1] << ", "  << (&col_byte)[2] << ")");
        rgb_t pixel((&col_byte)[0], (&col_byte)[1], (&col_byte)[2]);
        bool success = this->on_bmp_pixel
        (pixel, col_byte, col_bytes, col,
         row, plane, bits, cols, rows, planes);
        return success;
    }
    virtual bool on_32bit_bmp_col
    (BYTE& col_byte, TSIZE col_bytes,
     TSIZE col, TSIZE row, TSIZE plane,
     TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        rgb_quad_t pixel((&col_byte)[0], (&col_byte)[1], (&col_byte)[2], (&col_byte)[3]);
        bool success = this->on_bmp_pixel
        (pixel, col_byte, col_bytes, col,
         row, plane, bits, cols, rows, planes);
        return success;
    }
    virtual bool on_8bit_palette_bmp_col
    (BYTE& col_byte, TSIZE col_bytes,
     TSIZE col, TSIZE row, TSIZE plane,
     TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        bool success = true;
        return success;
    }
    virtual bool on_nbit_palette_bmp_col
    (BYTE& col_byte, TSIZE col_bytes,
     TSIZE col, TSIZE row, TSIZE plane,
     TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        bool success = true;
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_bmp_row
    (BYTE& row_byte, TSIZE row_bytes, TSIZE row, TSIZE plane,
     TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        bool success = true;
        if ((on_bmp_row_)) {
            success = (this->*on_bmp_row_)
            (row_byte, row_bytes, row, plane, bits, cols, rows, planes);
        } else {
            BYTE* col_byte;
            TSIZE col;

            for (col_byte = &row_byte, col = 0;
                 col < cols; ++col, col_byte += col_bytes_) {

                if ((on_bmp_col
                     (*col_byte, col_bytes_, col,
                      row, plane, bits, cols, rows, planes))) {
                    continue;
                }
                success = false;
                break;
            }
        }
        return success;
    }
    virtual bool on_nbit_bmp_row
    (BYTE& row_byte, TSIZE row_bytes, TSIZE row, TSIZE plane,
     TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        bool success = true;
        BYTE* col_byte;
        BYTE col_shift;
        TSIZE col;

        for (col_byte = &row_byte,
             col = 0; col < cols; ++col_byte) {

            for (col_shift = 0; col_shift < 8;
                 col_shift += (BYTE)(bits), ++col) {

                col_shift_ = (8 - col_shift - (BYTE)(bits));

                if ((on_bmp_col
                     (*col_byte, col_bytes_, col,
                      row, plane, bits, cols, rows, planes))) {
                    continue;
                }
                return false;
            }
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual reader_events* forward_bmp_reader_events(reader_events* to) {
        bmp_reader_events_forward_to_ = to;
        return bmp_reader_events_forward_to_;
    }
    virtual reader_events* bmp_reader_events_forward_to() const {
        return bmp_reader_events_forward_to_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    reader_events* bmp_reader_events_forward_to_;
    on_bmp_row_t on_bmp_row_;
    on_bmp_col_t on_bmp_col_;

    bfh_t bfh_;
    bih_t bih_;

    rgb_quad_array rgb_;
    RGBQUAD* rgb_quad_;
    TSIZE rgb_quads_;

    byte_array row_;
    BYTE* row_byte_;
    TSIZE row_bytes_;
    TSIZE row_padded_;

    TSIZE col_bytes_;
    BYTE col_shift_;
    BYTE col_mask_;
};
typedef readert<> reader;

} // namespace implement 
} // namespace bmp 
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_BMP_IMPLEMENT_READER_HPP 
