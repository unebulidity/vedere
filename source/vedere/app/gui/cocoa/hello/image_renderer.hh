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
///   File: image_renderer.hh
///
/// Author: $author$
///   Date: 11/7/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_COCOA_HELLO_IMAGE_RENDERER_HH
#define _VEDERE_APP_GUI_COCOA_HELLO_IMAGE_RENDERER_HH

#include "vedere/gui/cocoa/iCocoa.hh"
#include "vedere/app/gui/hello/image_renderer.hpp"
#include "vedere/io/logger.hpp"

namespace vedere {
namespace app {
namespace gui {
namespace cocoa {
namespace hello {

enum image_format_t {
    IMAGE_FORMAT_ABGR32
};
enum aspect_ratio_mode_t {
    ASPECT_RATIO_MODE_IGNORE,
    ASPECT_RATIO_MODE_KEEP
};
typedef CGInterpolationQuality transformation_mode_t;

typedef gui::hello::image_renderert
<image_format_t, IMAGE_FORMAT_ABGR32,
 aspect_ratio_mode_t, ASPECT_RATIO_MODE_IGNORE,
 transformation_mode_t, kCGInterpolationDefault> image_renderer_implements;

typedef gui::hello::image_renderer_extendt
<image_renderer_implements> image_renderer_extends;
///////////////////////////////////////////////////////////////////////
///  Class: image_renderer
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS image_renderer
: virtual public image_renderer_implements, public image_renderer_extends {
public:
    typedef image_renderer_implements Implements;
    typedef image_renderer_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    image_renderer(iCGContextRef context = NULL): context_(context) {
    }
    virtual ~image_renderer() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init(iCGContextRef context, size_t width, size_t height) {
        context_ = context;
        width_ = width;
        height_ = height;
        return true;
    }
    virtual bool finish() {
        context_ = NULL;
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::render;
    virtual bool render
    (const void* image, size_t image_width, size_t image_height,
     size_t width, size_t height, size_t x, size_t y, image_format_t image_format,
     aspect_ratio_mode_t aspect_ratio_mode, iCGInterpolationQuality interpolation_quality) {
        if ((context_) && (image)) {
            iCGImageRef cg_image = NULL;

            if ((cg_image = iCGImageCreateFromData
                 (image, image_width, image_height, image_format))) {
                iCGFloat x_scale = 1, y_scale = 1,
                         y_pos = (height <= height_)?(height_-y-height):(0);
                iRect rect = iMakeRect(x,y_pos, width,height);

                iCGContextSaveGState(context_);
                iCGContextSetShouldAntialias(context_, false);
                iCGContextSetInterpolationQuality(context_, interpolation_quality);
                iCGContextScaleCTM(context_, x_scale,y_scale);
                iCGContextDrawImage(context_, rect, cg_image);
                iCGContextRestoreGState(context_);
                iCGImageRelease(cg_image);
                return true;
            } else {
                VEDERE_LOG_MESSAGE_ERROR("...failed on CGImageCreateFromData()");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual iCGImageRef iCGImageCreateFromData
    (const void* image, size_t image_width, size_t image_height,
     image_format_t image_format) const {
        switch(image_format) {
        case IMAGE_FORMAT_ABGR32:
            return iCGImageCreateFromABGR32(image, image_width, image_height);
            break;
        }
        return NULL;
    }
    virtual iCGImageRef iCGImageCreateFromABGR32
    (const void* image, size_t image_width, size_t image_height) const {
        iCGImageRef cg_image = NULL;

        if ((image) && (image_width) && (image_height)) {
            iCGColorSpaceRef color_space = NULL;

            if ((color_space = iCGColorSpaceCreateDeviceRGB())) {
                iCGDataProviderRef data_provider = NULL;

                if ((data_provider = iCGDataProviderCreateWithData
                     (NULL, image, image_width * image_height * 4, NULL))) {

                    cg_image = iCGImageCreate
                    (image_width, image_height, 8,32, image_width*4,
                     color_space, kCGImageAlphaNoneSkipLast, data_provider,
                     NULL, false, kCGRenderingIntentDefault);

                    iCGDataProviderRelease(data_provider);
                }
                iCGColorSpaceRelease(color_space);
            }
        }
        return cg_image;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
 protected:
    iCGContextRef context_;
};

} // namespace hello 
} // namespace cocoa 
} // namespace gui 
} // namespace app 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_COCOA_HELLO_IMAGE_RENDERER_HH 
