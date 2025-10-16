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
///   Date: 11/16/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_JPEG_LIBJPEG_READER_EVENTS_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_JPEG_LIBJPEG_READER_EVENTS_HPP

#include "vedere/graphic/image/format/jpeg/libjpeg/jpeg.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace jpeg {
namespace libjpeg {

typedef implement_base reader_events_implements;
///////////////////////////////////////////////////////////////////////
///  Class: reader_eventst
///////////////////////////////////////////////////////////////////////
template <class TImplements = reader_events_implements>
class _EXPORT_CLASS reader_eventst: virtual public reader_events_implements {
public:
    typedef reader_events_implements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_jpeg_image
    (JDIMENSION output_height, JDIMENSION output_width,
     JDIMENSION output_components, JDIMENSION out_color_components,
     JDIMENSION actual_number_of_colors, J_COLOR_SPACE out_color_space,
     JSAMPARRAY colormap) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = jpeg_reader_events_forward_to())) {
            success = events->on_jpeg_image
            (output_height, output_width, output_components,
             out_color_components, actual_number_of_colors,
             out_color_space, colormap);
        }
        return success;
    }
    virtual bool on_begin_jpeg_image
    (JDIMENSION output_height, JDIMENSION output_width,
     JDIMENSION output_components, JDIMENSION out_color_components,
     JDIMENSION actual_number_of_colors, J_COLOR_SPACE out_color_space,
     JSAMPARRAY colormap) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = jpeg_reader_events_forward_to())) {
            success = events->on_begin_jpeg_image
            (output_height, output_width, output_components,
             out_color_components, actual_number_of_colors,
             out_color_space, colormap);
        }
        return success;
    }
    virtual bool on_end_jpeg_image
    (JDIMENSION output_height, JDIMENSION output_width,
     JDIMENSION output_components, JDIMENSION out_color_components,
     JDIMENSION actual_number_of_colors, J_COLOR_SPACE out_color_space,
     JSAMPARRAY colormap) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = jpeg_reader_events_forward_to())) {
            success = events->on_end_jpeg_image
            (output_height, output_width, output_components,
             out_color_components, actual_number_of_colors,
             out_color_space, colormap);
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_jpeg_sample_row
    (JSAMPROW samples, size_t samples_size, size_t samples_row,
     JDIMENSION output_height, JDIMENSION output_width,
     JDIMENSION output_components, JDIMENSION out_color_components,
     JDIMENSION actual_number_of_colors, J_COLOR_SPACE out_color_space,
     JSAMPARRAY colormap) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = jpeg_reader_events_forward_to())) {
            success = events->on_jpeg_sample_row
            (samples, samples_size, samples_row,
             output_height, output_width, output_components,
             out_color_components, actual_number_of_colors,
             out_color_space, colormap);
        }
        return success;
    }
    virtual bool on_begin_jpeg_sample_row
    (JSAMPROW samples, size_t samples_size, size_t samples_row,
     JDIMENSION output_height, JDIMENSION output_width,
     JDIMENSION output_components, JDIMENSION out_color_components,
     JDIMENSION actual_number_of_colors, J_COLOR_SPACE out_color_space,
     JSAMPARRAY colormap) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = jpeg_reader_events_forward_to())) {
            success = events->on_begin_jpeg_sample_row
            (samples, samples_size, samples_row,
             output_height, output_width, output_components,
             out_color_components, actual_number_of_colors,
             out_color_space, colormap);
        }
        return success;
    }
    virtual bool on_end_jpeg_sample_row
    (JSAMPROW samples, size_t samples_size, size_t samples_row,
     JDIMENSION output_height, JDIMENSION output_width,
     JDIMENSION output_components, JDIMENSION out_color_components,
     JDIMENSION actual_number_of_colors, J_COLOR_SPACE out_color_space,
     JSAMPARRAY colormap) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = jpeg_reader_events_forward_to())) {
            success = events->on_end_jpeg_sample_row
            (samples, samples_size, samples_row,
             output_height, output_width, output_components,
             out_color_components, actual_number_of_colors,
             out_color_space, colormap);
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_jpeg_sample_col
    (JSAMPROW samples, size_t samples_size,
     size_t samples_row, size_t samples_col,
     JDIMENSION output_height, JDIMENSION output_width,
     JDIMENSION output_components, JDIMENSION out_color_components,
     JDIMENSION actual_number_of_colors, J_COLOR_SPACE out_color_space,
     JSAMPARRAY colormap) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = jpeg_reader_events_forward_to())) {
            success = events->on_jpeg_sample_col
            (samples, samples_size, samples_row, samples_col,
             output_height, output_width, output_components,
             out_color_components, actual_number_of_colors,
             out_color_space, colormap);
        }
        return success;
    }
    virtual bool on_begin_jpeg_sample_col
    (JSAMPROW samples, size_t samples_size,
     size_t samples_row, size_t samples_col,
     JDIMENSION output_height, JDIMENSION output_width,
     JDIMENSION output_components, JDIMENSION out_color_components,
     JDIMENSION actual_number_of_colors, J_COLOR_SPACE out_color_space,
     JSAMPARRAY colormap) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = jpeg_reader_events_forward_to())) {
            success = events->on_begin_jpeg_sample_col
            (samples, samples_size, samples_row, samples_col,
             output_height, output_width, output_components,
             out_color_components, actual_number_of_colors,
             out_color_space, colormap);
        }
        return success;
    }
    virtual bool on_end_jpeg_sample_col
    (JSAMPROW samples, size_t samples_size,
     size_t samples_row, size_t samples_col,
     JDIMENSION output_height, JDIMENSION output_width,
     JDIMENSION output_components, JDIMENSION out_color_components,
     JDIMENSION actual_number_of_colors, J_COLOR_SPACE out_color_space,
     JSAMPARRAY colormap) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = jpeg_reader_events_forward_to())) {
            success = events->on_end_jpeg_sample_col
            (samples, samples_size, samples_row, samples_col,
             output_height, output_width, output_components,
             out_color_components, actual_number_of_colors,
             out_color_space, colormap);
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual reader_eventst* forward_jpeg_reader_events(reader_eventst* to) {
        return 0;
    }
    virtual reader_eventst* jpeg_reader_events_forward_to() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef reader_eventst<> reader_events;

} // namespace libjpeg 
} // namespace jpeg 
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_JPEG_LIBJPEG_READER_EVENTS_HPP 
