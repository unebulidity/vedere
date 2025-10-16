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
///   Date: 11/18/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_JPEG_LIBJPEG_IMAGE_READER_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_JPEG_LIBJPEG_IMAGE_READER_HPP

#include "vedere/graphic/image/format/jpeg/libjpeg/reader.hpp"
#include "vedere/graphic/image/to_bytes_reader.hpp"
#include "vedere/graphic/image/reader.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace jpeg {
namespace libjpeg {

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
    : on_jpeg_sample_col_(0),
      bits_per_pixel_value_(0),
      pixel_value_interpretation_(pixel_value_interpretation_none) {
    }
    virtual ~image_readert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Implements::Implements::read;
    virtual bool read(FILE* file) {
        if ((file)) {
            libjpeg::reader reader(this);
            if ((reader.read(file))) {
                return true;
            }
        }
        return false;
    }

protected:
    typedef bool (Derives::*on_jpeg_sample_col_t)
    (JSAMPROW samples, size_t samples_size,
     size_t samples_row, size_t samples_col,
     JDIMENSION output_height, JDIMENSION output_width,
     JDIMENSION output_components, JDIMENSION out_color_components,
     JDIMENSION actual_number_of_colors, J_COLOR_SPACE out_color_space,
     JSAMPARRAY colormap);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_begin_jpeg_image
    (JDIMENSION output_height, JDIMENSION output_width,
     JDIMENSION output_components, JDIMENSION out_color_components,
     JDIMENSION actual_number_of_colors, J_COLOR_SPACE out_color_space,
     JSAMPARRAY colormap) {
        bool success = true;
        VEDERE_LOG_MESSAGE_DEBUG
        ("on_begin_jpeg_image"
         "\n(output_height = " << output_height << ", output_width = " << output_width <<
         ",\n output_components = " << output_components <<
         ", out_color_components = " << out_color_components <<
         ",\n actual_number_of_colors = " << actual_number_of_colors <<
         ", out_color_space = " << out_color_space <<
         " \"" << color_space().name(out_color_space) << "\""
         ",...)...");
        switch(out_color_space) {
        case JCS_GRAYSCALE:
            if (1 != out_color_components) {
                VEDERE_LOG_ERROR("unexpected 1 != out_color_components");
                success = false;
            } else {
                if (1 != output_components) {
                    VEDERE_LOG_ERROR("unexpected 1 != output_components");
                    success = false;
                } else {
                    on_jpeg_sample_col_ = &Derives::on_greyscale_jpeg_sample_col;
                    pixel_value_interpretation_ = pixel_value_interpretation_greyscale;
                    bits_per_pixel_value_ = (sizeof(JSAMPLE) * 8);
                }
            }
            break;
        case JCS_RGB:
            if (3 != out_color_components) {
                VEDERE_LOG_ERROR("unexpected 3 != out_color_components");
                success = false;
            } else {
                if ((colormap)) {
                    if (1 != output_components) {
                        VEDERE_LOG_ERROR("unexpected 1 != output_components");
                        success = false;
                    } else {
                        on_jpeg_sample_col_ = &Derives::on_rgb_palette_jpeg_sample_col;
                        pixel_value_interpretation_ = pixel_value_interpretation_palette;
                        bits_per_pixel_value_ = (sizeof(JSAMPLE) * 8);
                    }
                } else {
                    if (3 != output_components) {
                        VEDERE_LOG_ERROR("unexpected 3 != output_components");
                        success = false;
                    } else {
                        on_jpeg_sample_col_ = &Derives::on_rgb_jpeg_sample_col;
                        pixel_value_interpretation_ = pixel_value_interpretation_rgb;
                        bits_per_pixel_value_ = (sizeof(JSAMPLE) * 8);
                    }
                }
            }
            break;
        default:
            VEDERE_LOG_ERROR("color space " << out_color_space << " \"" << color_space().name(out_color_space) << "\" not implemented");
            success = false;
            break;
        }
        if ((success)) {
            success = this->on_begin_image
            (output_width, output_height, 1, output_components,
             bits_per_pixel_value_, pixel_value_interpretation_);
        }
        return success;
    }
    virtual bool on_end_jpeg_image
    (JDIMENSION output_height, JDIMENSION output_width,
     JDIMENSION output_components, JDIMENSION out_color_components,
     JDIMENSION actual_number_of_colors, J_COLOR_SPACE out_color_space,
     JSAMPARRAY colormap) {
        bool success = true;
        VEDERE_LOG_MESSAGE_DEBUG("...on_end_jpeg_image()");
        success = this->on_end_image
        (output_width, output_height, 1, output_components,
         bits_per_pixel_value_, pixel_value_interpretation_);
        pixel_value_interpretation_ = pixel_value_interpretation_none;
        bits_per_pixel_value_ = 0;
        on_jpeg_sample_col_ = 0;
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
        bool success = false;
        if ((on_jpeg_sample_col_)) {
            success = (this->*on_jpeg_sample_col_)
            (samples, samples_size, samples_row, samples_col,
             output_height, output_width, output_components,
             out_color_components, actual_number_of_colors,
             out_color_space, colormap);
        }
        return success;
    }
    virtual bool on_greyscale_jpeg_sample_col
    (JSAMPROW samples, size_t samples_size,
     size_t samples_row, size_t samples_col,
     JDIMENSION output_height, JDIMENSION output_width,
     JDIMENSION output_components, JDIMENSION out_color_components,
     JDIMENSION actual_number_of_colors, J_COLOR_SPACE out_color_space,
     JSAMPARRAY colormap) {
        bool success = true;
        if (!(1 != samples_size)) {
            byte_t* byte = ((byte_t*)samples);
            rgba::pixel_t pixel(byte[0], byte[0], byte[0]);
            success = this->on_image_pixel
            (pixel, byte, samples_size, samples_col, samples_row, 0,
             output_width, output_height, 1, 1, 8, pixel_value_interpretation_);
        } else {
            success = false;
        }
        return success;
    }
    virtual bool on_rgb_jpeg_sample_col
    (JSAMPROW samples, size_t samples_size,
     size_t samples_row, size_t samples_col,
     JDIMENSION output_height, JDIMENSION output_width,
     JDIMENSION output_components, JDIMENSION out_color_components,
     JDIMENSION actual_number_of_colors, J_COLOR_SPACE out_color_space,
     JSAMPARRAY colormap) {
        bool success = true;
        if (!(3 != samples_size)) {
            byte_t* byte = ((byte_t*)samples);
            rgba::pixel_t pixel(byte[0], byte[1], byte[2]);
            success = this->on_image_pixel
            (pixel, byte, samples_size, samples_col, samples_row, 0,
             output_width, output_height, 1, 3, 8, pixel_value_interpretation_);
        } else {
            success = false;
        }
        return success;
    }
    virtual bool on_rgb_palette_jpeg_sample_col
    (JSAMPROW samples, size_t samples_size,
     size_t samples_row, size_t samples_col,
     JDIMENSION output_height, JDIMENSION output_width,
     JDIMENSION output_components, JDIMENSION out_color_components,
     JDIMENSION actual_number_of_colors, J_COLOR_SPACE out_color_space,
     JSAMPARRAY colormap) {
        bool success = true;
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    on_jpeg_sample_col_t on_jpeg_sample_col_;
    size_t bits_per_pixel_value_;
    pixel_value_interpretation_t pixel_value_interpretation_;
};
typedef image_readert<> image_reader;

typedef to_bgra_bytes_readert
<image_reader_implements, image_reader> to_bgra_image_reader;

typedef to_rgba_bytes_readert
<image_reader_implements, image_reader> to_rgba_image_reader;

} // namespace libjpeg
} // namespace jpeg 
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_JPEG_LIBJPEG_IMAGE_READER_HPP 
