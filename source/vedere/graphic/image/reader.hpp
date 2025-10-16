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
///   Date: 11/18/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_READER_HPP
#define _VEDERE_GRAPHIC_IMAGE_READER_HPP

#include "vedere/graphic/image/pixel.hpp"
#include "vedere/graphic/image/color.hpp"

namespace vedere {
namespace graphic {
namespace image {

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
    virtual bool on_image_pixel
    (pixel_t& pixel, byte_t* pixel_byte, size_t pixel_bytes,
     size_t image_col, size_t image_row, size_t image_plane,
     size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = reader_events_forward_to())) {
            success = to->on_image_pixel
            (pixel, pixel_byte, pixel_bytes,
             image_col, image_row, image_plane,
             image_width, image_height, image_planes,
             values_per_pixel, bits_per_value, pixel_value_interpretation);
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_image_col
    (byte_t* col_byte, size_t col_bytes,
     size_t image_col, size_t image_row, size_t image_plane,
     size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = reader_events_forward_to())) {
            success = to->on_image_col
            (col_byte, col_bytes,
             image_col, image_row, image_plane,
             image_width, image_height, image_planes,
             values_per_pixel, bits_per_value, pixel_value_interpretation);
        }
        return success;
    }
    virtual bool on_begin_image_col
    (byte_t* col_byte, size_t col_bytes,
     size_t image_col, size_t image_row, size_t image_plane,
     size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = reader_events_forward_to())) {
            success = to->on_begin_image_col
            (col_byte, col_bytes,
             image_col, image_row, image_plane,
             image_width, image_height, image_planes,
             values_per_pixel, bits_per_value, pixel_value_interpretation);
        }
        return success;
    }
    virtual bool on_end_image_col
    (byte_t* col_byte, size_t col_bytes,
     size_t image_col, size_t image_row, size_t image_plane,
     size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = reader_events_forward_to())) {
            success = to->on_end_image_col
            (col_byte, col_bytes,
             image_col, image_row, image_plane,
             image_width, image_height, image_planes,
             values_per_pixel, bits_per_value, pixel_value_interpretation);
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_image_row
    (byte_t* row_byte, size_t row_bytes,
     size_t image_row, size_t image_plane,
     size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = reader_events_forward_to())) {
            success = to->on_image_row
            (row_byte, row_bytes,
             image_row, image_plane,
             image_width, image_height, image_planes,
             values_per_pixel, bits_per_value, pixel_value_interpretation);
        }
        return success;
    }
    virtual bool on_begin_image_row
    (byte_t* row_byte, size_t row_bytes,
     size_t image_row, size_t image_plane,
     size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = reader_events_forward_to())) {
            success = to->on_begin_image_row
            (row_byte, row_bytes,
             image_row, image_plane,
             image_width, image_height, image_planes,
             values_per_pixel, bits_per_value, pixel_value_interpretation);
        }
        return success;
    }
    virtual bool on_end_image_row
    (byte_t* row_byte, size_t row_bytes,
     size_t image_row, size_t image_plane,
     size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = reader_events_forward_to())) {
            success = to->on_end_image_row
            (row_byte, row_bytes,
             image_row, image_plane,
             image_width, image_height, image_planes,
             values_per_pixel, bits_per_value, pixel_value_interpretation);
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_image_plane
    (size_t image_plane,
     size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = reader_events_forward_to())) {
            success = to->on_image_plane
            (image_plane,
             image_width, image_height, image_planes,
             values_per_pixel, bits_per_value, pixel_value_interpretation);
        }
        return success;
    }
    virtual bool on_begin_image_plane
    (size_t image_plane,
     size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = reader_events_forward_to())) {
            success = to->on_begin_image_plane
            (image_plane,
             image_width, image_height, image_planes,
             values_per_pixel, bits_per_value, pixel_value_interpretation);
        }
        return success;
    }
    virtual bool on_end_image_plane
    (size_t image_plane,
     size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = reader_events_forward_to())) {
            success = to->on_end_image_plane
            (image_plane,
             image_width, image_height, image_planes,
             values_per_pixel, bits_per_value, pixel_value_interpretation);
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_image
    (size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = reader_events_forward_to())) {
            success = to->on_image
            (image_width, image_height, image_planes,
             values_per_pixel, bits_per_value, pixel_value_interpretation);
        }
        return success;
    }
    virtual bool on_begin_image
    (size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = reader_events_forward_to())) {
            success = to->on_begin_image
            (image_width, image_height, image_planes,
             values_per_pixel, bits_per_value, pixel_value_interpretation);
        }
        return success;
    }
    virtual bool on_end_image
    (size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = true;
        reader_eventst* to = 0;
        if ((to = reader_events_forward_to())) {
            success = to->on_end_image
            (image_width, image_height, image_planes,
             values_per_pixel, bits_per_value, pixel_value_interpretation);
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual reader_eventst* forward_reader_events(reader_eventst* to) {
        return 0;
    }
    virtual reader_eventst* reader_events_forward_to() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef reader_eventst<> reader_events;

typedef reader_events reader_implements;
///////////////////////////////////////////////////////////////////////
///  Class: readert
///////////////////////////////////////////////////////////////////////
template <class TImplements = reader_implements>
class _EXPORT_CLASS readert: virtual public TImplements {
public:
    typedef TImplements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool read(const char* filename) {
        if ((filename)) {
            xos::io::read::file file;
            if ((file.open(filename))) {
                bool success = read(file.attached_to());
                file.close();
                return success;
            }
        }
        return false;
    }
    virtual bool read(FILE* file) {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef readert<> reader;

} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_READER_HPP 
