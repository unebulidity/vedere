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
///   File: reader_events.hpp
///
/// Author: $author$
///   Date: 12/7/2020
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_GIF_GIFLIB_READER_EVENTS_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_GIF_GIFLIB_READER_EVENTS_HPP

#include "vedere/graphic/image/format/gif/giflib/file.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace gif {
namespace giflib {

class _EXPORT_CLASS reader_pixel;

typedef implement_base reader_eventst_implements;
///////////////////////////////////////////////////////////////////////
///  Class: reader_eventst
///////////////////////////////////////////////////////////////////////
template <class TImplements = reader_eventst_implements>
class _EXPORT_CLASS reader_eventst: virtual public TImplements {
public:
    typedef TImplements Implements;
    typedef reader_eventst Derives;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_gif_open(GifFileType* fileType) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = gif_reader_events_forward_to())) {
            success = events->on_gif_open(fileType);
        }
        return success;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_gif_image
    (size_t height, size_t width, size_t colors, 
     GifWord interlaceType, GifPixelType backgroundPixel, ColorMapObject* colorMap, giflib::file& file) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = gif_reader_events_forward_to())) {
            success = events->on_gif_image
            (height, width, colors, interlaceType, backgroundPixel, colorMap, file);
        }
        return success;
    }
    virtual bool on_begin_gif_image
    (size_t height, size_t width, size_t colors, 
     GifWord interlaceType, GifPixelType backgroundPixel, ColorMapObject* colorMap, giflib::file& file) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = gif_reader_events_forward_to())) {
            success = events->on_begin_gif_image
            (height, width, colors, interlaceType, backgroundPixel, colorMap, file);
        }
        return success;
    }
    virtual bool on_end_gif_image
    (size_t height, size_t width, size_t colors, 
     GifWord interlaceType, GifPixelType backgroundPixel, ColorMapObject* colorMap, giflib::file& file) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = gif_reader_events_forward_to())) {
            success = events->on_end_gif_image
            (height, width, colors, interlaceType, backgroundPixel, colorMap, file);
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
        reader_eventst* events = 0;
        if ((events = gif_reader_events_forward_to())) {
            success = events->on_gif_line
            (pixels, pixelsLength, pixelsLine, height, width, colors, interlaceType, backgroundPixel, colorMap);
        }
        return success;
    }
    virtual bool on_begin_gif_line
    (GifPixelType* pixels, size_t pixelsLength, size_t pixelsLine,
     size_t height, size_t width, size_t colors, GifWord interlaceType,  GifPixelType backgroundPixel, 
     ColorMapObject* colorMap) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = gif_reader_events_forward_to())) {
            success = events->on_begin_gif_line
            (pixels, pixelsLength, pixelsLine, height, width, colors, interlaceType, backgroundPixel, colorMap);
        }
        return success;
    }
    virtual bool on_end_gif_line
    (GifPixelType* pixels, size_t pixelsLength, size_t pixelsLine,
     size_t height, size_t width, size_t colors, GifWord interlaceType,  GifPixelType backgroundPixel, 
     ColorMapObject* colorMap) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = gif_reader_events_forward_to())) {
            success = events->on_end_gif_line
            (pixels, pixelsLength, pixelsLine, height, width, colors, interlaceType, backgroundPixel, colorMap);
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_gif_column
    (GifPixelType& pixel, size_t pixelColumn, size_t pixelLine, size_t height, size_t width, 
     size_t colors, GifWord interlaceType, GifPixelType backgroundPixel, ColorMapObject* colorMap) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = gif_reader_events_forward_to())) {
            success = events->on_gif_column
            (pixel, pixelColumn, pixelLine, height, width, colors, interlaceType, backgroundPixel, colorMap);
        }
        return success;
    }
    virtual bool on_begin_gif_column
    (GifPixelType& pixel, size_t pixelColumn, size_t pixelLine, size_t height, size_t width, 
     size_t colors, GifWord interlaceType, GifPixelType backgroundPixel, ColorMapObject* colorMap) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = gif_reader_events_forward_to())) {
            success = events->on_begin_gif_column
            (pixel, pixelColumn, pixelLine, height, width, colors, interlaceType, backgroundPixel, colorMap);
        }
        return success;
    }
    virtual bool on_end_gif_column
    (GifPixelType& pixel, size_t pixelColumn, size_t pixelLine, size_t height, size_t width, 
     size_t colors, GifWord interlaceType, GifPixelType backgroundPixel, ColorMapObject* colorMap) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = gif_reader_events_forward_to())) {
            success = events->on_end_gif_column
            (pixel, pixelColumn, pixelLine, height, width, colors, interlaceType, backgroundPixel, colorMap);
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_gif_pixel_color
    (GifColorType& color, GifPixelType& pixel, size_t pixelColumn, size_t pixelLine,
     size_t height, size_t width, size_t colors, GifWord interlaceType, GifPixelType backgroundPixel, ColorMapObject* colorMap) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = gif_reader_events_forward_to())) {
            success = events->on_gif_pixel_color
            (color, pixel, pixelColumn, pixelLine, height, width, colors, interlaceType, backgroundPixel, colorMap);
        }
        return success;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_gif_pixel
    (reader_pixel& pixel,
     GifColorType& color, GifPixelType& columnPixel, size_t pixelColumn, size_t pixelLine,
     size_t height, size_t width, size_t colors, GifWord interlaceType, GifPixelType backgroundPixel, ColorMapObject* colorMap) {
        bool success = true;
        reader_eventst* events = 0;
        if ((events = gif_reader_events_forward_to())) {
            success = events->on_gif_pixel
            (pixel, color, columnPixel, pixelColumn, pixelLine, 
             height, width, colors, interlaceType, backgroundPixel, colorMap);
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual reader_eventst* forward_gif_reader_events(reader_eventst* to) {
        return 0;
    }
    virtual reader_eventst* gif_reader_events_forward_to() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class exported reader_eventst
typedef reader_eventst<> reader_events;

} /// namespace giflib
} /// namespace gif
} /// namespace format
} /// namespace image
} /// namespace graphic
} /// namespace vedere

#endif /// _VEDERE_GRAPHIC_IMAGE_FORMAT_GIF_GIFLIB_READER_EVENTS_HPP
