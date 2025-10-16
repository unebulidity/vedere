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
///   Date: 7/18/2016
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_LIBPGM_IMAGE_READER_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_LIBPGM_IMAGE_READER_HPP

#include "vedere/graphic/image/format/raw/libpgm/reader.hpp"
#include "lamna/graphic/image/format/raw/gamma/libraw/curve.hpp"
#include "vedere/graphic/image/to_bytes_reader.hpp"
#include "vedere/graphic/image/reader.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace raw {
namespace libpgm {

typedef image::reader image_reader_implement;
typedef libpgm::reader_events reader_implement;
///////////////////////////////////////////////////////////////////////
///  Class: image_reader_implements
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

    typedef lamna::graphic::image::format::raw::gamma::libraw::curve curve_t;
    typedef lamna::graphic::image::format::raw::bayer::rgb::pattern pattern_t;
    typedef lamna::graphic::image::format::raw::bayer::rgb::pattern_which_t pattern_which_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    image_readert() : reader_(this) {
    }
    virtual ~image_readert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_raw_libpgm_read_image
    (size_t cols, size_t rows, max_t max,
     gray_t** image, const pattern_t& pattern) {
        bool success = false;
        size_t col_size = (max > 255)?(2):(1);
        size_t image_width = cols/(2*col_size), image_height = rows/(2);
        size_t image_planes = 1, values_per_pixel = 3, bits_per_value = 8;
        pixel_value_interpretation_t pixel_value_interpretation = pixel_value_interpretation_rgb;

        if ((success = this->on_begin_image
             (image_width, image_height, image_planes,
              values_per_pixel, bits_per_value, pixel_value_interpretation))) {

            success = this->on_raw_libpgm_read_image_rows
            (rows, cols, col_size, image, pattern,
             image_width, image_height, image_planes,
             values_per_pixel, bits_per_value, pixel_value_interpretation);

            if (!(this->on_end_image
                (image_width, image_height, image_planes,
                 values_per_pixel, bits_per_value, pixel_value_interpretation))) {
                success = false;
            }
        }
        return success;
    }
    virtual bool on_raw_libpgm_read_image_rows
    (size_t height, size_t width, size_t col_size,
     gray_t** image, const pattern_t& pattern,
     size_t image_width, size_t image_height, size_t image_planes,
     size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = false;

        if ((width) && (height) && (image)) {
            size_t red = 0, green = 0, blue = 0, maximum = 255;
            rgba::pixel_t pixel(red, green, blue, maximum, maximum);
            size_t sample_maximum = (1 << (col_size*8)) - 1, sample_diff = sample_maximum;
            size_t sample_min = sample_maximum, sample_max = 0;
            size_t white = 4095, black = 128;
            gray_t* map[4] = {0, 0, 0, 0};
            double gamm[2] = {0.52, 4.5};
            gray_t* samples[2] = {0, 0};
            size_t row = 0, col = 0, byte = 0;

            curve_.generate(gamm[0], gamm[1], white);

            for (int pass = 0; pass < 2; ++pass) {
                if (pass) {
                    if (!(sample_diff = (sample_max - sample_min))) {
                        sample_diff = sample_maximum;
                    }
                }
                for (samples[0] = image[row = 0], samples[1] = image[row+1];
                     row < image_height;
                     samples[0] = image[(++row)*2], samples[1] = image[row*2+1]) {

                    for (col = 0; col < image_width; ++col) {
                        map[0] = samples[0]+(col*col_size*2); map[1] = map[0]+1;
                        map[2] = samples[1]+(col*col_size*2); map[3] = map[2]+1;

                        red = map[pattern[0]][0];
                        green = map[pattern[1]][0];
                        blue = map[pattern[2]][0];

                        for (byte = 1; byte < col_size; ++byte) {
                            red = (red << 8) | (map[pattern[0]][byte]);
                            green = (green << 8) | (map[pattern[1]][byte]);
                            blue = (blue << 8) | (map[pattern[2]][byte]);
                        }

                        red -= black;
                        green -= black;
                        blue -= black;

                        red = curve_[red];
                        green = curve_[green];
                        blue = curve_[blue];

                        if ((pass)) {
                            red = ((red - sample_min) * maximum) / (sample_diff);
                            green = ((green - sample_min) * maximum) / (sample_diff);
                            blue = ((blue - sample_min) * maximum) / (sample_diff);

                            pixel(red, green, blue);

                            if (!(success = this->on_image_pixel
                                (pixel, 0, 0,
                                 col, row, 0, image_width, image_height,
                                 image_planes, values_per_pixel, bits_per_value,
                                 pixel_value_interpretation))) {
                                break;
                            }
                        } else {
                            if ((sample_min > red)) sample_min = red;
                            if ((sample_max < red)) sample_max = red;

                            if ((sample_min > green)) sample_min = green;
                            if ((sample_max < green)) sample_max = green;

                            if ((sample_min > blue)) sample_min = blue;
                            if ((sample_max < blue)) sample_max = blue;
                        }
                    }
                }
            }
        }
        return success;
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
protected:
    reader reader_;
    curve_t curve_;
};
typedef image_readert<> image_reader;

typedef to_bgra_bytes_readert
<image_reader_implements, image_reader> to_bgra_image_reader;

} // namespace libpgm
} // namespace raw 
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_LIBPGM_IMAGE_READER_HPP 
