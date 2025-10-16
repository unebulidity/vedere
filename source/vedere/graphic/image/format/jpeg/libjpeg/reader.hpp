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
///   Date: 11/16/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_JPEG_LIBJPEG_READER_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_JPEG_LIBJPEG_READER_HPP

#include "vedere/graphic/image/format/jpeg/libjpeg/reader_events.hpp"
#include "vedere/graphic/image/format/jpeg/libjpeg/decompress.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace jpeg {
namespace libjpeg {

typedef reader_events reader_implements;
typedef base reader_extends;
///////////////////////////////////////////////////////////////////////
///  Class: readert
///////////////////////////////////////////////////////////////////////
template
<class TImplements = reader_implements, class TExtends = reader_extends>

class _EXPORT_CLASS readert
: virtual public reader_implements, public reader_extends {
public:
    typedef reader_implements Implements;
    typedef reader_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    readert
    (reader_events* jpeg_reader_events_forward_to = 0)
    : jpeg_reader_events_forward_to_(jpeg_reader_events_forward_to) {
    }
    virtual ~readert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool read(const char* filename) {
        xos::io::read::file file;
        if ((file.open(filename))) {
            bool success = read(file.attached_to());
            file.close();
            return success;
        }
        return false;
    }
    virtual bool read(FILE* file) {
        if ((file)) {
            if ((jpeg_.create())) {
                bool success = false;

                if ((jpeg_.start_read(file, TRUE))) {
                    JDIMENSION output_width = jpeg_.output_width(),
                               output_height = jpeg_.output_height(),
                               output_components = jpeg_.output_components(),
                               out_color_components = jpeg_.out_color_components(),
                               actual_number_of_colors = jpeg_.actual_number_of_colors();
                    J_COLOR_SPACE out_color_space = jpeg_.out_color_space();
                    JSAMPARRAY colormap = jpeg_.colormap();
                    size_t samples_size = (output_width*output_components*sizeof(JSAMPLE));

                    if ((on_begin_jpeg_image
                         (output_height, output_width, output_components,
                          out_color_components, actual_number_of_colors,
                          out_color_space, colormap))) {
                        size_t samples_row = 0;
                        JSAMPARRAY samples = 0;

                        success = true;
                        for (samples_row = 0; samples_row < output_height ; ++samples_row) {
                            if ((samples = jpeg_.read_sample_rows())) {
                                if ((on_jpeg_sample_row
                                     (samples[0], samples_size, samples_row,
                                      output_height, output_width, output_components,
                                      out_color_components, actual_number_of_colors,
                                      out_color_space, colormap))) {
                                    continue;
                                }
                                success = false;
                                break;
                            }
                        }
                        if (!(on_end_jpeg_image
                             (output_height, output_width, output_components,
                              out_color_components, actual_number_of_colors,
                              out_color_space, colormap))) {
                            success = false;
                        }
                    }
                    jpeg_.finish_read(file);
                }
                jpeg_.destroy();
                return success;
            }
        }
        return false;
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

        if ((on_begin_jpeg_sample_row
             (samples, samples_size, samples_row,
              output_height, output_width, output_components,
              out_color_components, actual_number_of_colors,
              out_color_space, colormap))) {
            size_t sample_size = (output_components * sizeof(JSAMPLE)),
                   samples_col = 0;
            JSAMPROW sample = 0;

            for (sample = samples, samples_col = 0;
                 samples_col < output_width; ++samples_col, sample += sample_size) {
                if (!(on_jpeg_sample_col
                     (sample, sample_size, samples_row, samples_col,
                      output_height, output_width, output_components,
                      out_color_components, actual_number_of_colors,
                      out_color_space, colormap))) {
                    success = false;
                    break;
                }
            }
            if ((on_end_jpeg_sample_row
                 (samples, samples_size, samples_row,
                  output_height, output_width, output_components,
                  out_color_components, actual_number_of_colors,
                  out_color_space, colormap))) {
            } else {
                success = false;
            }
        } else {
            success = false;
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual reader_events* forward_jpeg_reader_events(reader_events* to) {
        jpeg_reader_events_forward_to_ = to;
        return jpeg_reader_events_forward_to_;
    }
    virtual reader_events* jpeg_reader_events_forward_to() const {
        return jpeg_reader_events_forward_to_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    reader_events* jpeg_reader_events_forward_to_;
    decompress jpeg_;
};
typedef readert<> reader;

} // namespace libjpeg 
} // namespace jpeg 
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_JPEG_LIBJPEG_READER_HPP 
