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
///   File: reader.hpp
///
/// Author: $author$
///   Date: 1/10/2021
///////////////////////////////////////////////////////////////////////
#ifndef VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_BGRA_READER_HPP
#define VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_BGRA_READER_HPP

#include "vedere/graphic/image/format/raw/bgra/reader_events.hpp"
#include "vedere/graphic/image/format/raw/bgra/file.hpp"
#include "vedere/io/logger.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace raw {
namespace bgra {

typedef ::xos::base::byte_array pixel_byte_array_t;

///////////////////////////////////////////////////////////////////////
/// class readert
///////////////////////////////////////////////////////////////////////
template <class TExtends = extend, class TImplements = reader_events>
class EXPORT_CLASS readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef readert Derives;

    ///////////////////////////////////////////////////////////////////////
    /// constructor / destructor
    ///////////////////////////////////////////////////////////////////////
    readert
    (size_t image_height, size_t image_width,size_t values_per_pixel, size_t bits_per_pixel_value,
     bgra::pixel_value_interpretation_t pixel_value_interpretation, reader_events* forward_to)
     : image_height_(image_height), image_width_(image_width),
       values_per_pixel_(values_per_pixel), bits_per_pixel_value_(bits_per_pixel_value),
       pixel_value_interpretation_(pixel_value_interpretation), bgra_reader_events_forward_to_(forward_to) {
    }
    virtual ~readert() {
    }
private:
    readert(const readert& copy): Extends(copy) {
    }
public:

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool read(const char* filename) {
        bgra::file file;

        VEDERE_LOG_MESSAGE_DEBUG("file.open(\"" << filename << "\")...");
        if ((file.open(filename))) {
            bool success = false;

            VEDERE_LOG_MESSAGE_DEBUG("on_bgra_file_open(...)...");
            if ((success = this->on_bgra_file_open
                 (file, image_height_, image_width_, 
                  values_per_pixel_, bits_per_pixel_value_, pixel_value_interpretation_))) {
            } else {
                VEDERE_LOG_MESSAGE_ERROR("...failed on on_bgra_file_open(...)...");
            }
            VEDERE_LOG_MESSAGE_DEBUG("file.close() (\"" << filename << "\")...");
            if (!(file.close())) {
                VEDERE_LOG_MESSAGE_ERROR("...failed on file.close() (\"" << filename << "\")");
                success = false;
            } else {
                VEDERE_LOG_MESSAGE_DEBUG("this->on_bgra_file_close(...)...");
                if (!(this->on_bgra_file_close
                    (file, image_height_, image_width_, 
                     values_per_pixel_, bits_per_pixel_value_, pixel_value_interpretation_))) {
                    VEDERE_LOG_MESSAGE_ERROR("...failed on this->on_bgra_file_file.close(...)");
                    success = false;
                } else {
                }
            }
            return success;
        } else {
            VEDERE_LOG_MESSAGE_ERROR("...failed on file.open(\"" << filename << "\")");
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_bgra_file_open
    (bgra::file& file, size_t image_height, size_t image_width, 
     size_t values_per_pixel, size_t bits_per_pixel_value,
     bgra::pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = false;

        if ((this->on_bgra_image
             (file, image_height, image_width, values_per_pixel, 
              bits_per_pixel_value, pixel_value_interpretation))) {
            success = true;
        } else {
            VEDERE_LOG_MESSAGE_ERROR("...failed on this->on_bgra_image(image_height = " << image_height << ", image_width = " << image_width << ", ...)");
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_bgra_image
    (bgra::file& file, size_t image_height, size_t image_width, 
     size_t values_per_pixel, size_t bits_per_pixel_value,
     bgra::pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = false;

        VEDERE_LOG_MESSAGE_DEBUG("this->on_begin_bgra_image(image_height = " << image_height << ", image_width = " << image_width << ", ...)...");
        if ((this->on_begin_bgra_image
             (file, image_height, image_width, values_per_pixel, 
              bits_per_pixel_value, pixel_value_interpretation))) {
            pixel_byte_array_t& pixel_byte_array = this->pixel_byte_array_;
            byte_t* pixels = 0; size_t pixels_length = 0;

            if ((pixels = pixel_byte_array.elements()) && (pixels_length = pixel_byte_array.length())) {
                ssize_t count = 0, amount = 0;

                for (size_t line = 0; line < image_height; line++) {

                    VEDERE_LOG_MESSAGE_DEBUG("file.read(pixels = " << pointer_to_string(pixels) << ", pixels_length = " << pixels_length << ") (line = " << line << ")...")
                    if (pixels_length <= (amount = file.read(pixels, pixels_length))) {
                        count += amount;
                        if ((this->on_bgra_line
                             (pixels, pixels_length, line, image_height, image_width, 
                              values_per_pixel, bits_per_pixel_value, pixel_value_interpretation))) {
                        } else {
                            VEDERE_LOG_MESSAGE_ERROR("...failed on this->on_bgra_line(..., line = " << line << ", image_height = " << image_height << ", image_width = " << image_width << ", ...)...");
                            break;
                        }
                    } else {
                        VEDERE_LOG_MESSAGE_ERROR("...failed on " << amount << " = file.read(pixels = " << pointer_to_string(pixels) << ", pixels_length = " << pixels_length << ") (line = " << line << ")")
                        break;
                    }
                }
            } else {
                VEDERE_LOG_ERROR("...unexpected");
            }
            VEDERE_LOG_MESSAGE_DEBUG("this->on_end_bgra_image(image_height = " << image_height << ", image_width = " << image_width << ", ...)...");
            if ((this->on_end_bgra_image
                 (file, image_height, image_width, values_per_pixel, 
                  bits_per_pixel_value, pixel_value_interpretation))) {
                success = true;
            } else {
                VEDERE_LOG_MESSAGE_ERROR("...failed on this->on_end_bgra_image(image_height = " << image_height << ", image_width = " << image_width << ", ...)");
            }
        } else {
            VEDERE_LOG_MESSAGE_ERROR("...failed on this->on_begin_bgra_image(image_height = " << image_height << ", image_width = " << image_width << ", ...)");
        }
        return success;
    }
    virtual bool on_begin_bgra_image
    (bgra::file& file, size_t image_height, size_t image_width, 
     size_t values_per_pixel, size_t bits_per_pixel_value,
     bgra::pixel_value_interpretation_t pixel_value_interpretation) {
        reader_events* forward_to = this->bgra_reader_events_forward_to();
        bool success = false;
        size_t pixels_size = 0, pixels_length = 0;
        pixel_byte_array_t& pixel_byte_array = this->pixel_byte_array_;

        pixels_size = image_width * values_per_pixel;
        VEDERE_LOG_MESSAGE_DEBUG("pixel_byte_array.set_length(pixels_size = " << pixels_size << ")...");
        if ((success = (pixels_size <= (pixels_length = pixel_byte_array.set_length(pixels_size))))) {
            VEDERE_LOG_MESSAGE_DEBUG("..." << pixels_length << " = pixel_byte_array.set_length(pixels_size = " << pixels_size << ")");

            if ((forward_to)) {
                if ((success = forward_to->on_begin_bgra_image
                    (file, image_height, image_width, 
                     values_per_pixel, bits_per_pixel_value, pixel_value_interpretation))) {
                } else {
                    VEDERE_LOG_MESSAGE_ERROR("...failed on forward_to->on_begin_bgra_image(..., image_height = " << image_height << ", image_width = " << image_width << ", ...)");
                    if (pixels_size < (pixels_length = pixel_byte_array.set_size(pixels_size = 0))) {
                    } else {
                        VEDERE_LOG_MESSAGE_ERROR("...failed on " << pixels_length << " = pixel_byte_array.set_size(pixels_size = " << pixels_size << ")");
                    }
                }
            } else {
            }
        } else {
            VEDERE_LOG_MESSAGE_ERROR("...failed on " << pixels_length << " = pixel_byte_array.set_length(pixels_size = " << pixels_size << ")");
        }
        return success;
    }
    virtual bool on_end_bgra_image
    (bgra::file& file, size_t image_height, size_t image_width, 
     size_t values_per_pixel, size_t bits_per_pixel_value,
     bgra::pixel_value_interpretation_t pixel_value_interpretation) {
        reader_events* forward_to = this->bgra_reader_events_forward_to();
        bool success = false;
        size_t pixels_size = 0, pixels_length = 0;
        pixel_byte_array_t& pixel_byte_array = this->pixel_byte_array_;

        VEDERE_LOG_MESSAGE_DEBUG("pixel_byte_array.set_size(pixels_size = " << pixels_size << ")...");
        if ((success = (pixels_size < (pixels_length = pixel_byte_array.set_size(pixels_size))))) {
            VEDERE_LOG_MESSAGE_DEBUG("..." << pixels_length << " on pixel_byte_array.set_size(pixels_size = " << pixels_size << ")");
        } else {
            VEDERE_LOG_MESSAGE_ERROR("...failed on " << pixels_length << " = pixel_byte_array.set_size(pixels_size = " << pixels_size << ")");
        }
        if ((forward_to)) {
            if ((forward_to->on_end_bgra_image
                (file, image_height, image_width, 
                 values_per_pixel, bits_per_pixel_value, pixel_value_interpretation))) {
            } else {
                VEDERE_LOG_MESSAGE_ERROR("...failed on forward_to->on_end_bgra_image(..., image_height = " << image_height << ", image_width = " << image_width << ", ...)");
                success = false;
            }
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
        bool success = false;

        if ((success = this->on_begin_bgra_line
             (pixels, pixels_length, pixels_line, image_height, image_width, 
              values_per_pixel, bits_per_pixel_value, pixel_value_interpretation))) {
            byte_t* col_pixels = pixels; 

            for (size_t col = 0; col < image_width; col++, col_pixels += values_per_pixel) {
                
                if ((this->on_bgra_col
                     (col_pixels, values_per_pixel, col, pixels_line, image_height, image_width, 
                      values_per_pixel, bits_per_pixel_value, pixel_value_interpretation))) {
                } else {
                    VEDERE_LOG_MESSAGE_ERROR("...failed on this->on_bgra_col(..., col = " << col << ", line = " << pixels_line << ", image_height = " << image_height << ", image_width = " << image_width << ", ...)...");
                    success = false;
                    break;
                }
            }
            if ((this->on_end_bgra_line
                 (pixels, pixels_length, pixels_line, image_height, image_width, 
                  values_per_pixel, bits_per_pixel_value, pixel_value_interpretation))) {
            } else {
                success = false;
            }
        } else {
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual reader_events* forward_bgra_reader_events(reader_events* to) {
        bgra_reader_events_forward_to_ = to;
        return bgra_reader_events_forward_to_;
    }
    virtual reader_events* bgra_reader_events_forward_to() const {
        return bgra_reader_events_forward_to_;
    }
    virtual bool bgra_reader_events_all_success() const {
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    reader_events* bgra_reader_events_forward_to_;
    size_t image_height_, image_width_, values_per_pixel_, bits_per_pixel_value_;
    bgra::pixel_value_interpretation_t pixel_value_interpretation_;
    pixel_byte_array_t pixel_byte_array_;
}; /// class readert
typedef readert<> reader;

} /// namespace bgra
} /// namespace raw
} /// namespace format
} /// namespace image
} /// namespace graphic
} /// namespace vedere

#endif /// ndef VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_BGRA_READER_HPP 
