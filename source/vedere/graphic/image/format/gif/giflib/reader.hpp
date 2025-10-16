///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2020 $organization$
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
///   Date: 12/7/2020
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_GIF_GIFLIB_READER_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_GIF_GIFLIB_READER_HPP

#include "vedere/graphic/image/format/gif/giflib/reader_events.hpp"
#include "vedere/graphic/image/format/gif/giflib/file.hpp"
#include "vedere/io/logger.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace gif {
namespace giflib {

typedef ::xos::base::arrayt<GifPixelType> pixel_buffer_t;

typedef reader_events readert_implements;
typedef base readert_extends;
///////////////////////////////////////////////////////////////////////
///  Class: readert
///////////////////////////////////////////////////////////////////////
template <class TImplements = readert_implements, class TExtends = readert_extends>
class _EXPORT_CLASS readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef readert Derives;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    readert(reader_events* gif_reader_events_forward_to = 0)
    : gif_reader_events_forward_to_(gif_reader_events_forward_to) {
    }
    virtual ~readert() {
    }
private:
    readert(const readert &copy) {
    }
public:

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool read(const string filename) {
        const char* chars = 0;
        size_t length = 0;
        if ((chars = filename.has_chars(length))) {
            if ((this->read(chars))) {
                return true;
            }
        }
        return false;
    }
    virtual bool read(const char* filename) {
        if ((filename) && (filename[0])) {
            GifFileType* detached = 0;
            giflib::file file;

            VEDERE_LOG_MESSAGE_DEBUG("file.open_attached(\"" << filename << "\")...");
            if ((detached = file.open_attached(filename))) {
                bool success = false;

                VEDERE_LOG_MESSAGE_DEBUG("..." << pointer_to_string(detached) << " = file.open_attached(\"" << filename << "\")");
                success = this->on_gif_open(detached);

                VEDERE_LOG_MESSAGE_DEBUG("file.close_attached(" << pointer_to_string(detached) << ")...");
                if (!(file.close_attached(detached))) {
                    VEDERE_LOG_MESSAGE_ERROR("...failed on file.close_attached(" << pointer_to_string(detached) << ")");
                    success = false;
                } else {
                    VEDERE_LOG_MESSAGE_DEBUG("...file.close_attached(" << pointer_to_string(detached) << ")");
                }
                return success;
            } else {
                VEDERE_LOG_MESSAGE_ERROR("...failed on file.open_attached(\"" << filename << "\")");
            }
        }
        return false;
    }
    virtual bool read(xos::io::read::file& file) {
        FILE* file_attached = 0;
        if ((file_attached = file.attached_to())) {
            if ((this->read(file_attached))) {
                return true;
            }
        }
        return false;
    }
    virtual bool read(FILE* file) {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_gif_open(GifFileType* fileType) {
        bool success = true;
        GifRecordType type = UNDEFINED_RECORD_TYPE;
        giflib::file file(fileType);
        
        do {
            if ((UNDEFINED_RECORD_TYPE != (type = file.GetRecordType())) && (TERMINATE_RECORD_TYPE != type)) {
                success = on_gif_record_type(type, file);
            }
        } while ((UNDEFINED_RECORD_TYPE != type) && (TERMINATE_RECORD_TYPE != type));
        return success;
    }
    virtual bool on_gif_record_type(GifRecordType type, giflib::file& file) {
        bool success = true;
        switch (type) {
        case SCREEN_DESC_RECORD_TYPE:
            success = on_gif_SCREEN_DESC_RECORD_TYPE_record_type(type, file);
            break;           
        case IMAGE_DESC_RECORD_TYPE:
            success = on_gif_IMAGE_DESC_RECORD_TYPE_record_type(type, file);
            break;           
        case EXTENSION_RECORD_TYPE:
            success = on_gif_EXTENSION_RECORD_TYPE_record_type(type, file);
            break;           
        case TERMINATE_RECORD_TYPE:
            success = on_gif_TERMINATE_RECORD_TYPE_record_type(type, file);
            break;
        case UNDEFINED_RECORD_TYPE:
        default:
            success = on_gif_UNDEFINED_RECORD_TYPE_record_type(type, file);
            break;
        }
        return success;
    }
    virtual bool on_gif_SCREEN_DESC_RECORD_TYPE_record_type(GifRecordType type, giflib::file& file) {
        bool success = true;
        VEDERE_LOG_MESSAGE_DEBUG("on_gif_SCREEN_DESC_RECORD_TYPE_record_type(GifRecordType type = " << type << ")...");
        VEDERE_LOG_MESSAGE_DEBUG("...on_gif_SCREEN_DESC_RECORD_TYPE_record_type(GifRecordType type = " << type << ")");
        return success;
    }
    virtual bool on_gif_IMAGE_DESC_RECORD_TYPE_record_type(GifRecordType type, giflib::file& file) {
        bool success = true;
        GifImageDesc* image = 0;

        VEDERE_LOG_MESSAGE_DEBUG("on_gif_MAGE_DESC_RECORD_TYPE_record_type(GifRecordType type = " << type << ")...");
        if ((image = file.GetImageDesc())) {
            GifWord interlaceType = image->Interlace, width = image->Width, height = image->Height, 
                    colors = file.ColorResolution(), backgroundPixel = file.BackGroundColor();
            ColorMapObject* colorMap = 0;
            
            if (!(colorMap = image->ColorMap)) {
                colorMap = file.ColorMap();
            }
            VEDERE_LOG_MESSAGE_DEBUG("this->on_gif_image(height = " << height << ", width = " << width << ", colors = " << colors << ", interlaceType = " << interlaceType << ", backgroundPixel = " << backgroundPixel << ", colorMap = " << pointer_to_string(colorMap) << ")...");
            success = this->on_gif_image(height, width, colors, interlaceType, backgroundPixel, colorMap, file);
            VEDERE_LOG_MESSAGE_DEBUG("...this->on_gif_image(height = " << height << ", width = " << width << ", colors = " << colors << ", interlaceType = " << interlaceType << ", backgroundPixel = " << backgroundPixel << ", colorMap = " << pointer_to_string(colorMap) << ")");
        }
        VEDERE_LOG_MESSAGE_DEBUG("...on_gif_MAGE_DESC_RECORD_TYPE_record_type(GifRecordType type = " << type << ")");
        return success;
    }
    virtual bool on_gif_EXTENSION_RECORD_TYPE_record_type(GifRecordType type, giflib::file& file) {
        bool success = true;
        GifByteType* extBlock = 0;
        int extCode = 0;

        VEDERE_LOG_MESSAGE_DEBUG("on_gif_EXTENSION__RECORD_TYPE_record_type(GifRecordType type = " << type << ")...");
        if ((extBlock = file.GetExtension(extCode))) {
            do {
                extBlock = file.GetExtensionNext();
            } while (extBlock);
        }
        VEDERE_LOG_MESSAGE_DEBUG("...on_gif_EXTENSION__RECORD_TYPE_record_type(GifRecordType type = " << type << ")");
        return success;
    }
    virtual bool on_gif_TERMINATE_RECORD_TYPE_record_type(GifRecordType type, giflib::file& file) {
        bool success = true;
        VEDERE_LOG_MESSAGE_DEBUG("on_gif_TERMINATE_RECORD_TYPE_record_type(GifRecordType type = " << type << ")...");
        VEDERE_LOG_MESSAGE_DEBUG("...on_gif_TERMINATE_RECORD_TYPE_record_type(GifRecordType type = " << type << ")");
        return success;
    }
    virtual bool on_gif_UNDEFINED_RECORD_TYPE_record_type(GifRecordType type, giflib::file& file) {
        bool success = true;
        VEDERE_LOG_MESSAGE_DEBUG("on_gif_UNDEFINED_RECORD_TYPE_record_type(GifRecordType type = " << type << ")...");
        VEDERE_LOG_MESSAGE_DEBUG("...on_gif_UNDEFINED_RECORD_TYPE_record_type(GifRecordType type = " << type << ")");
        return success;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_gif_image
    (size_t height, size_t width, size_t colors, 
     GifWord interlaceType, GifPixelType backgroundPixel, ColorMapObject* colorMap, giflib::file& file) {
        bool success = true;
        GifPixelType* pixels = 0;
        size_t pixelsLength = 0;
        pixel_buffer_t& pixelBuffer = this->pixel_buffer_;

        VEDERE_LOG_MESSAGE_DEBUG("this->on_begin_gif_image(height = " << height << ", width = " << width << ", colors = " << colors << ", interlaceType, backgroundPixel, colorMap)...");
        if ((success = this->on_begin_gif_image(height, width, colors, interlaceType, backgroundPixel, colorMap, file))) {

            VEDERE_LOG_MESSAGE_DEBUG("...this->on_begin_gif_image(height = " << height << ", width = " << width << ", colors = " << colors << ", interlaceType, backgroundPixel, colorMap)");
            if (width <= (pixelsLength = pixelBuffer.set_length(width))) {

                VEDERE_LOG_MESSAGE_DEBUG("..." << width << " <= (" << pixelsLength << " = pixelBuffer.set_length(" << width << ")");
                if ((pixels = pixelBuffer.elements())) {
                    ssize_t count = 0;

                    VEDERE_LOG_MESSAGE_DEBUG("this->on_begin_gif_image(height = " << height << ", width = " << width << ", colors = " << colors << ", interlaceType, backgroundPixel, colorMap)...");
                    for (size_t line = 0; line < height; line++) {
                        
                        VEDERE_LOG_MESSAGE_DEBUG("file.GetLine(pixels = " << pointer_to_string(pixels) << ", " << width << ")...");
                        if (width != (count = file.GetLine(pixels, width))) {

                            VEDERE_LOG_MESSAGE_ERROR("...failed " << width << " != (" << count << " = file.GetLine(pixels = " << pointer_to_string(pixels) << ", " << width << "))");
                            return false;
                        } else {
                            VEDERE_LOG_MESSAGE_DEBUG("...this->on_gif_line(pixels = " << pointer_to_string(pixels) << ", pixelsLength = " << pixelsLength << ", line = " << line << ", height, width, colors, interlaceType, backgroundPixel, colorMap)");
                            success = this->on_gif_line(pixels, pixelsLength, line, height, width, colors, interlaceType, backgroundPixel, colorMap);
                        }
                    }
                    if ((success != this->on_end_gif_image(height, width, colors, interlaceType, backgroundPixel, colorMap, file))) {

                        VEDERE_LOG_MESSAGE_DEBUG("...this->on_begin_gif_image(height = " << height << ", width = " << width << ", colors = " << colors << ", interlaceType, backgroundPixel, colorMap))");
                    }
                }
            }
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_gif_line
    (GifPixelType* pixels, size_t pixelsLength, size_t pixelsLine,
     size_t height, size_t width, size_t colors, GifWord interlaceType,  GifPixelType backgroundPixel, 
     ColorMapObject* colorMap) {
        bool success = true;

        VEDERE_LOG_MESSAGE_DEBUG("...this->on_begin_gif_line(pixels = " << pointer_to_string(pixels) << ", pixelsLength = " << pixelsLength << ", line = " << pixelsLine << ", height, width, colors, interlaceType, backgroundPixel, colorMap)");
        if ((success = this->on_begin_gif_line(pixels, pixelsLength, pixelsLine, height, width, colors, interlaceType, backgroundPixel, colorMap))) {

            for (size_t pixelColumn = 0; pixelColumn < pixelsLength; pixelColumn++) {
                GifPixelType& pixel = pixels[pixelColumn];

                VEDERE_LOG_MESSAGE_TRACE("this->on_gif_column(pixel, pixelColumn = " << pixelColumn << ", pixelsLine = " << pixelsLine << ", height, width, colors, interlaceType, backgroundPixel, colorMap)...");
                if (!(success = this->on_gif_column(pixel, pixelColumn, pixelsLine, height, width, colors, interlaceType, backgroundPixel, colorMap))) {
                    VEDERE_LOG_MESSAGE_ERROR("...failed on this->on_gif_column(pixel, pixelColumn = " << pixelColumn << ", pixelsLine = " << pixelsLine << ", height, width, colors, interlaceType, backgroundPixel, colorMap)");
                    break;
                } else {
                    VEDERE_LOG_MESSAGE_TRACE("...this->on_gif_column(pixel, pixelColumn = " << pixelColumn << ", pixelsLine = " << pixelsLine << ", height, width, colors, interlaceType, backgroundPixel, colorMap)");
                }
            }
            VEDERE_LOG_MESSAGE_DEBUG("...this->on_end_gif_line(pixels = " << pointer_to_string(pixels) << ", pixelsLength = " << pixelsLength << ", line = " << pixelsLine << ", height, width, colors, interlaceType, backgroundPixel, colorMap)");
            if ((success = this->on_end_gif_line(pixels, pixelsLength, pixelsLine, height, width, colors, interlaceType, backgroundPixel, colorMap))) {
            }
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_gif_column
    (GifPixelType& pixel, size_t pixelColumn, size_t pixelLine, size_t height, size_t width, 
     size_t colors, GifWord interlaceType, GifPixelType backgroundPixel, ColorMapObject* colorMap) {
        bool success = true;

        if ((colorMap)) {
            GifColorType* mapColors = 0;
            GifWord colorCount = 0;
            
            if ((mapColors = colorMap->Colors) && (pixel < (colorCount = colorMap->ColorCount))) {
                GifColorType color = mapColors[pixel];

                VEDERE_LOG_MESSAGE_TRACE("this->on_gif_pixel_color(color, pixel, pixelColumn = " << pixelColumn << ", pixelLine = " << pixelLine << ", height, width, colors, interlaceType, backgroundPixel, colorMap)...");
                if (!(success = this->on_gif_pixel_color
                      (color, pixel, pixelColumn, pixelLine, height, width, 
                       colors, interlaceType, backgroundPixel, colorMap))) {
                    VEDERE_LOG_MESSAGE_ERROR("...failed on this->on_gif_pixel_color(color, pixel, pixelColumn = " << pixelColumn << ", pixelLine = " << pixelLine << ", height, width, colors, interlaceType, backgroundPixel, colorMap)");
                } else {
                    VEDERE_LOG_MESSAGE_TRACE("...this->on_gif_pixel_color(color, pixel, pixelColumn = " << pixelColumn << ", pixelLine = " << pixelLine << ", height, width, colors, interlaceType, backgroundPixel, colorMap)");
                }
            }
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual reader_events* forward_gif_reader_events(reader_events* to) {
        gif_reader_events_forward_to_ = to;
        return gif_reader_events_forward_to_;
    }
    virtual reader_events* gif_reader_events_forward_to() const {
        return gif_reader_events_forward_to_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    reader_events* gif_reader_events_forward_to_;
    pixel_buffer_t pixel_buffer_;
}; /// class _EXPORT_CLASS readert
typedef readert<> reader;

} /// namespace giflib
} /// namespace gif
} /// namespace format
} /// namespace image
} /// namespace graphic
} /// namespace vedere

#endif /// _VEDERE_GRAPHIC_IMAGE_FORMAT_GIF_GIFLIB_READER_HPP
