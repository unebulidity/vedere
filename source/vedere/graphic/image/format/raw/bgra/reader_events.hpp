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
///   File: reader_events.hpp
///
/// Author: $author$
///   Date: 1/10/2021
///////////////////////////////////////////////////////////////////////
#ifndef VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_BGRA_READER_EVENTS_HPP
#define VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_BGRA_READER_EVENTS_HPP

#include "vedere/graphic/image/format/raw/bgra/file.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace raw {
namespace bgra {

///////////////////////////////////////////////////////////////////////
/// class reader_events
///////////////////////////////////////////////////////////////////////
class EXPORT_CLASS reader_events: virtual public implement {
public:
    typedef implement Implements;
    typedef reader_events Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_bgra_file_open
    (bgra::file& file, size_t image_height, size_t image_width, 
     size_t values_per_pixel, size_t bits_per_pixel_value,
     bgra::pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = bgra_reader_events_begin_success();
        reader_events* forward_to = this->bgra_reader_events_forward_to();
        if ((forward_to)) {
            success = forward_to->on_bgra_file_open
            (file, image_height, image_width, 
             values_per_pixel, bits_per_pixel_value, pixel_value_interpretation);
        } else {
        }
        return success;
    }
    virtual bool on_bgra_file_close
    (bgra::file& file, size_t image_height, size_t image_width, 
     size_t values_per_pixel, size_t bits_per_pixel_value,
     bgra::pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = bgra_reader_events_end_success();
        reader_events* forward_to = this->bgra_reader_events_forward_to();
        if ((forward_to)) {
            success = forward_to->on_bgra_file_close
            (file, image_height, image_width, 
             values_per_pixel, bits_per_pixel_value, pixel_value_interpretation);
        } else {
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_bgra_image
    (bgra::file& file, size_t image_height, size_t image_width, 
     size_t values_per_pixel, size_t bits_per_pixel_value,
     bgra::pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = bgra_reader_events_success();
        reader_events* forward_to = this->bgra_reader_events_forward_to();
        if ((forward_to)) {
            success = forward_to->on_bgra_image
            (file, image_height, image_width, 
             values_per_pixel, bits_per_pixel_value, pixel_value_interpretation);
        } else {
        }
        return success;
    }
    virtual bool on_begin_bgra_image
    (bgra::file& file, size_t image_height, size_t image_width, 
     size_t values_per_pixel, size_t bits_per_pixel_value,
     bgra::pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = bgra_reader_events_begin_success();
        reader_events* forward_to = this->bgra_reader_events_forward_to();
        if ((forward_to)) {
            success = forward_to->on_begin_bgra_image
            (file, image_height, image_width, 
             values_per_pixel, bits_per_pixel_value, pixel_value_interpretation);
        } else {
        }
        return success;
    }
    virtual bool on_end_bgra_image
    (bgra::file& file, size_t image_height, size_t image_width, 
     size_t values_per_pixel, size_t bits_per_pixel_value,
     bgra::pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = bgra_reader_events_end_success();
        reader_events* forward_to = this->bgra_reader_events_forward_to();
        if ((forward_to)) {
            success = forward_to->on_end_bgra_image
            (file, image_height, image_width, 
             values_per_pixel, bits_per_pixel_value, pixel_value_interpretation);
        } else {
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_bgra_line
    (byte_t* pixels, size_t pixels_length, size_t pixels_line, size_t image_height, size_t image_width, 
     size_t values_per_pixel, size_t bits_per_pixel_value,
     bgra::pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = bgra_reader_events_success();
        reader_events* forward_to = this->bgra_reader_events_forward_to();
        if ((forward_to)) {
            success = forward_to->on_bgra_line
            (pixels, pixels_length, pixels_line, image_height, image_width, 
             values_per_pixel, bits_per_pixel_value, pixel_value_interpretation);
        } else {
        }
        return success;
    }
    virtual bool on_begin_bgra_line
    (byte_t* pixels, size_t pixels_length, size_t pixels_line, size_t image_height, size_t image_width, 
     size_t values_per_pixel, size_t bits_per_pixel_value,
     bgra::pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = bgra_reader_events_begin_success();
        reader_events* forward_to = this->bgra_reader_events_forward_to();
        if ((forward_to)) {
            success = forward_to->on_begin_bgra_line
            (pixels, pixels_length, pixels_line, image_height, image_width, 
             values_per_pixel, bits_per_pixel_value, pixel_value_interpretation);
        } else {
        }
        return success;
    }
    virtual bool on_end_bgra_line
    (byte_t* pixels, size_t pixels_length, size_t pixels_line, size_t image_height, size_t image_width, 
     size_t values_per_pixel, size_t bits_per_pixel_value,
     bgra::pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = bgra_reader_events_end_success();
        reader_events* forward_to = this->bgra_reader_events_forward_to();
        if ((forward_to)) {
            success = forward_to->on_end_bgra_line
            (pixels, pixels_length, pixels_line, image_height, image_width, 
             values_per_pixel, bits_per_pixel_value, pixel_value_interpretation);
        } else {
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_bgra_col
    (byte_t* pixels, size_t pixels_length, size_t pixels_col, size_t pixels_line, 
     size_t image_height, size_t image_width, 
     size_t values_per_pixel, size_t bits_per_pixel_value,
     bgra::pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = bgra_reader_events_success();
        reader_events* forward_to = this->bgra_reader_events_forward_to();
        if ((forward_to)) {
            success = forward_to->on_bgra_col
            (pixels, pixels_length, pixels_col, pixels_line, image_height, image_width, 
             values_per_pixel, bits_per_pixel_value, pixel_value_interpretation);
        } else {
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual reader_events* forward_bgra_reader_events(reader_events* to) {
        return 0;
    }
    virtual reader_events* bgra_reader_events_forward_to() const {
        return 0;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool bgra_reader_events_success() const {
        return bgra_reader_events_all_success();
    }
    virtual bool bgra_reader_events_begin_success() const {
        return bgra_reader_events_all_success();
    }
    virtual bool bgra_reader_events_end_success() const {
        return bgra_reader_events_all_success();
    }
    virtual bool bgra_reader_events_all_success() const {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class reader_events

} /// namespace bgra
} /// namespace raw
} /// namespace format
} /// namespace image
} /// namespace graphic
} /// namespace vedere

#endif /// ndef VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_BGRA_READER_EVENTS_HPP 
