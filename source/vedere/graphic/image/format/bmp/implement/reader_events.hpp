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
///   File: reader_events.hpp
///
/// Author: $author$
///   Date: 11/25/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_BMP_IMPLEMENT_READER_EVENTS_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_BMP_IMPLEMENT_READER_EVENTS_HPP

#include "vedere/graphic/image/format/bmp/implement/bmp.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace bmp {
namespace implement {

typedef implement_base reader_events_implements;
///////////////////////////////////////////////////////////////////////
///  Class: reader_eventst
///////////////////////////////////////////////////////////////////////
template <class TImplements = reader_events_implements>
class _EXPORT_CLASS reader_eventst: virtual public TImplements {
public:
    typedef TImplements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_bmp_pixel
    (RGBQUAD& rgb,
     BYTE& col_byte, TSIZE col_bytes,
     TSIZE col, TSIZE row, TSIZE plane,
     TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = this->bmp_reader_events_forward_to())) {
            success = to->on_bmp_pixel
            (rgb, col_byte, col_bytes, col, row, plane,
             bits, cols, rows, planes);
        }
        return success;
    }
    virtual bool on_bmp_pixel
    (RGBTRIPLE& rgb,
     BYTE& col_byte, TSIZE col_bytes,
     TSIZE col, TSIZE row, TSIZE plane,
     TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = this->bmp_reader_events_forward_to())) {
            success = to->on_bmp_pixel
            (rgb, col_byte, col_bytes, col, row, plane,
             bits, cols, rows, planes);
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_bmp_col
    (BYTE& col_byte, TSIZE col_bytes,
     TSIZE col, TSIZE row, TSIZE plane,
     TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = this->bmp_reader_events_forward_to())) {
            success = to->on_bmp_col
            (col_byte, col_bytes, col, row, plane,
             bits, cols, rows, planes);
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_bmp_row
    (BYTE& row_byte, TSIZE row_bytes, TSIZE row, TSIZE plane,
     TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = this->bmp_reader_events_forward_to())) {
            success = to->on_bmp_row
            (row_byte, row_bytes, row, plane,
             bits, cols, rows, planes);
        }
        return success;
    }
    virtual bool on_begin_bmp_row
    (BYTE& row_byte, TSIZE row_bytes, TSIZE row, TSIZE plane,
     TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = this->bmp_reader_events_forward_to())) {
            success = to->on_begin_bmp_row
            (row_byte, row_bytes, row, plane,
             bits, cols, rows, planes);
        }
        return success;
    }
    virtual bool on_end_bmp_row
    (BYTE& row_byte, TSIZE row_bytes, TSIZE row, TSIZE plane,
     TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = this->bmp_reader_events_forward_to())) {
            success = to->on_end_bmp_row
            (row_byte, row_bytes, row, plane,
             bits, cols, rows, planes);
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_begin_bmp_image
    (TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = this->bmp_reader_events_forward_to())) {
            success = to->on_begin_bmp_image
            (bits, cols, rows, planes);
        }
        return success;
    }
    virtual bool on_end_bmp_image
    (TSIZE bits, TSIZE cols, TSIZE rows, TSIZE planes) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = this->bmp_reader_events_forward_to())) {
            success = to->on_end_bmp_image
            (bits, cols, rows, planes);
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual reader_eventst* forward_bmp_reader_events(reader_eventst* to) {
        return 0;
    }
    virtual reader_eventst* bmp_reader_events_forward_to() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef reader_eventst<> reader_events;

} // namespace implement 
} // namespace bmp 
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_BMP_IMPLEMENT_READER_EVENTS_HPP 
