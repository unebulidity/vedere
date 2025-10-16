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
///   File: image_renderer.hpp
///
/// Author: $author$
///   Date: 6/19/2016
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_WINDOWS_HELLO_IMAGE_RENDERER_HPP
#define _VEDERE_APP_GUI_WINDOWS_HELLO_IMAGE_RENDERER_HPP

#include "vedere/app/gui/hello/image_renderer.hpp"

namespace vedere {
namespace app {
namespace gui {
namespace windows {
namespace hello {

enum image_format_t {
    IMAGE_FORMAT_ARGB32
};
enum aspect_ratio_mode_t {
    ASPECT_RATIO_MODE_IGNORE,
    ASPECT_RATIO_MODE_KEEP
};
enum transformation_mode_t {
    TRANSFORMATION_MODE_NONE,
    TRANSFORMATION_MODE_FAST,
    TRANSFORMATION_MODE_SMOOTH
};

typedef gui::hello::image_renderert
<image_format_t, IMAGE_FORMAT_ARGB32,
 aspect_ratio_mode_t, ASPECT_RATIO_MODE_IGNORE,
 transformation_mode_t, TRANSFORMATION_MODE_NONE> image_renderer_implements;

typedef gui::hello::image_renderer_extendt
<image_renderer_implements> image_renderer_extends;
///////////////////////////////////////////////////////////////////////
///  Class: image_renderert
///////////////////////////////////////////////////////////////////////
template
<class TImplements = image_renderer_implements, 
 class TExtends = image_renderer_extends>

class _EXPORT_CLASS image_renderert
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    image_renderert(BITMAPINFO& bmi, HDC hDC = 0): bmi_(bmi), hDC_(hDC) {
    }
    virtual ~image_renderert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init(HDC hDC, size_t width, size_t height) {
        hDC_ = hDC;
        this->width_ = width;
        this->height_ = height;
        return true;
    }
    virtual bool finish() {
        hDC_ = 0;
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::render;
    virtual bool render
    (const void* image, size_t image_width, size_t image_height,
     size_t width, size_t height, size_t x, size_t y, image_format_t image_format,
     aspect_ratio_mode_t aspect_ratio_mode, transformation_mode_t transformation_mode) {
         if ((hDC_)) {
             int stretchBltMode = 0;
             HBRUSH hBR = 0;
             if ((hBR = CreateSolidBrush(RGB(0, 0, 0)))) {
                 RECT r = {x,y, x + width,y + height};
                 FillRect(hDC_, &r, hBR);
                 DeleteObject(hBR);
             }
             if ((stretchBltMode = GetStretchBltMode(hDC_))) {
                 SetStretchBltMode(hDC_, HALFTONE);
                 StretchDIBits
                 (hDC_, x, y, width, height,
                  0, 0, image_width, image_height, 
                  image, &bmi_, DIB_RGB_COLORS, SRCCOPY);
                 SetStretchBltMode(hDC_, stretchBltMode);
             }
         }
         return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    BITMAPINFO& bmi_;
    HDC hDC_;
};
typedef image_renderert<> image_renderer;

} // namespace hello 
} // namespace windows 
} // namespace gui 
} // namespace app 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_WINDOWS_HELLO_IMAGE_RENDERER_HPP 
