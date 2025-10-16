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
///   File: renderer.hpp
///
/// Author: $author$
///   Date: 6/19/2016
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_WINDOWS_HELLO_RENDERER_HPP
#define _VEDERE_APP_GUI_WINDOWS_HELLO_RENDERER_HPP

#include "vedere/app/gui/windows/hello/image_renderer.hpp"
#include "vedere/app/gui/hello/renderer_extend.hpp"

namespace vedere {
namespace app {
namespace gui {
namespace windows {
namespace hello {

typedef implement_base renderer_implements;
typedef gui::hello::renderer_extendt
<image_renderer::image_format_t,
 image_renderer::image_format_none, image_renderer> renderer_extends;
///////////////////////////////////////////////////////////////////////
///  Class: renderert
///////////////////////////////////////////////////////////////////////
template
<class TImplements = renderer_implements, class TExtends = renderer_extends>
class _EXPORT_CLASS renderert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef typename Extends::image_format_t image_format_t;
    typedef typename Extends::image_renderer_t image_renderer_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    renderert(): image_renderer_(bmi_) {
        ZeroMemory(&bmi_, sizeof(bmi_));
    }
    virtual ~renderert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init(HDC hDC, size_t width, size_t height) {
        return image_renderer_.init(hDC, width,height);
    }
    virtual bool finish() {
        return image_renderer_.finish();
    }
    virtual bool resize(size_t width, size_t height) {
        return image_renderer_.resize(width, height);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::set_image;
    virtual void* set_image
    (byte_t* bytes, size_t size,
     size_t width, size_t height, const image_format_t& format) {
        void* image = 0;
        if ((image = Extends::set_image
             (bytes, size, width, height, format))) {
            bmi_.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi_.bmiHeader.biPlanes = 1;
            bmi_.bmiHeader.biBitCount = 32;
            bmi_.bmiHeader.biCompression = BI_RGB;
            bmi_.bmiHeader.biWidth = width;
            bmi_.bmiHeader.biHeight = -height;
            bmi_.bmiHeader.biSizeImage = width * height * 4;
            return image;
        }
        return 0;
    }
    virtual void free_image() {
        ZeroMemory(&bmi_, sizeof(bmi_));
        Extends::free_image();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual image_renderer_t* 
    image_renderer(const image_format_t& image_format) const {
        if (!(image_format != image_renderer_.image_format())) {
            return ((image_renderer_t*)&image_renderer_);
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    BITMAPINFO bmi_;
    image_renderer_t image_renderer_;
};
typedef renderert<> renderer;

} // namespace hello 
} // namespace windows 
} // namespace gui 
} // namespace app 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_WINDOWS_HELLO_RENDERER_HPP 
