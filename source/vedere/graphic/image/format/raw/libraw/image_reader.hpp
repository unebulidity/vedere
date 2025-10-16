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
///   Date: 2/24/2016
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_LIBRAW_IMAGE_READER_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_LIBRAW_IMAGE_READER_HPP

#include "vedere/graphic/image/format/raw/libraw/reader.hpp"
#include "lamna/graphic/image/format/raw/gamma/libraw/curve.hpp"
#include "vedere/graphic/image/to_bytes_reader.hpp"
#include "vedere/graphic/image/reader.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace raw {
namespace libraw {

typedef image::reader image_reader_implement;
typedef reader_events reader_implement;
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
    typedef filter filter_t;
    typedef filter::pattern_t pattern_t;
    typedef lamna::graphic::image::format::raw::gamma::libraw::curve curve_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    image_readert() : reader_(this) {
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
    virtual bool on_libraw_unpack_image
    (size_t height, size_t width, size_t stride,
     ushort* image, pattern_t& pattern, imgdata_t& imgdata) {
        bool success = false;
        size_t image_width = width/2, image_height = height/2;
        size_t image_planes = 1, values_per_pixel = 3, bits_per_value = 8;
        pixel_value_interpretation_t pixel_value_interpretation = pixel_value_interpretation_rgb;

        if ((success = this->on_begin_image
             (image_width, image_height, image_planes,
              values_per_pixel, bits_per_value, pixel_value_interpretation))) {

            success = this->on_libraw_unpack_image_rows
            (height, width, stride, image, pattern, imgdata,
             image_planes, values_per_pixel, bits_per_value, pixel_value_interpretation);

            if (!(this->on_end_image
                (image_width, image_height, image_planes,
                 values_per_pixel, bits_per_value, pixel_value_interpretation))) {
                success = false;
            }
        }
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_libraw_unpack_image_rows
    (size_t height, size_t width, size_t stride,
     ushort* image, pattern_t& pattern, imgdata_t& imgdata,
     size_t image_planes, size_t values_per_pixel, size_t bits_per_value,
     pixel_value_interpretation_t pixel_value_interpretation) {
        bool success = false;

        if ((width) && (height) && (stride) && (image)) {
            colordata_t& color = imgdata.color;
            output_params_t& params = imgdata.params;
            size_t image_width = width/2, image_height = height/2;
            byte_t* sample = ((byte_t*)image);
            size_t sample_size = sizeof(ushort);
            size_t sample_maximum = color.maximum, sample_diff = sample_maximum;
            size_t sample_min = sample_maximum, sample_max = 0;
            size_t red = 0, green = 0, blue = 0, maximum = 255;
            rgba::pixel_t pixel(red, green, blue, maximum, maximum);
            size_t map[4];

            success = true;

            size_t black = color.black;

            //color_cmatrix_t& color_cmatrix = color.cmatrix;
            color_cmatrix_t color_cmatrix = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

            to_rgb_row_t to_rgb;
            to_rgb_matrix_t to_rgb_matrix;
            to_rgb_vector_t raw_vector, rgb_vector, to_rgb_vector[3];

            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    to_rgb[col] = color_cmatrix[row][col];
                }
                to_rgb_vector[row].assign(to_rgb, 3);
            }
            to_rgb_matrix.assign(to_rgb_vector, 3);

            //raw::libraw::curve_t& curve = color.curve;
            curve_t& curve = curve_;
            gamm_t& gamm = params.gamm;
            curve.generate(gamm[0], gamm[1], 0x2000);
            //curve.generate(gamm[0], gamm[1], sample_maximum);

            for (unsigned pass = 0; pass < 2; ++pass) {

                if (pass) {
                    if (!(sample_diff = (sample_max - sample_min))) {
                        sample_diff = sample_maximum;
                    }
                }
                for (size_t row = 0; row < image_height; ++row) {

                    for (size_t col = 0; col < image_width; ++col) {

                        map[0] = col*2; map[1] = map[0]+1;
                        map[2] = map[0]+width; map[3] = map[2]+1;

                        red = image[row*width*2+map[pattern[0]]];
                        green = image[row*width*2+map[pattern[1]]];
                        blue = image[row*width*2+map[pattern[2]]];

                        red -= black; green -= black; blue -= black;

                        red = curve[red]; green = curve[green]; blue = curve[blue];

                        if (pass) {
                            red = ((red - sample_min) * maximum) / (sample_diff);
                            green = ((green - sample_min) * maximum) / (sample_diff);
                            blue = ((blue - sample_min) * maximum) / (sample_diff);

                            to_rgb[0] = red; to_rgb[1] = green; to_rgb[2] = blue;
                            raw_vector.assign(to_rgb, 3);
                            to_rgb_matrix.mul(rgb_vector, raw_vector);
                            red = rgb_vector[0]; green = rgb_vector[1]; blue = rgb_vector[2];

                            pixel(red, green, blue);

                            if (!(success = this->on_image_pixel
                                (pixel, (byte_t*)sample, sample_size,
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
protected:
    reader reader_;
    curve_t curve_;
};
typedef image_readert<> image_reader;

typedef to_bgra_bytes_readert
<image_reader_implements, image_reader> to_bgra_image_reader;

typedef to_rgba_bytes_readert
<image_reader_implements, image_reader> to_rgba_image_reader;

} // namespace libraw 
} // namespace raw 
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_LIBRAW_IMAGE_READER_HPP 
