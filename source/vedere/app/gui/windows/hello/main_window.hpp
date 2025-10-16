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
///   File: main_window.hpp
///
/// Author: $author$
///   Date: 6/18/2016
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_WINDOWS_HELLO_MAIN_WINDOW_HPP
#define _VEDERE_APP_GUI_WINDOWS_HELLO_MAIN_WINDOW_HPP

#include "vedere/graphic/image/format/png/libpng/image_reader.hpp"
#include "vedere/graphic/image/format/jpeg/libjpeg/image_reader.hpp"
#include "vedere/graphic/image/format/tiff/libtiff/image_reader.hpp"
#include "vedere/graphic/image/format/raw/libraw/image_reader.hpp"
#include "vedere/graphic/image/format/bmp/implement/image_reader.hpp"
#include "vedere/app/gui/windows/hello/renderer.hpp"
#include "vedere/app/gui/windows/hello/image_renderer.hpp"
#include "vedere/app/gui/hello/main_window_extend.hpp"
#include "vedere/app/gui/hello/window_extend.hpp"
#include "vedere/gui/windows/main_window.hpp"

namespace vedere {
namespace app {
namespace gui {
namespace windows {
namespace hello {

typedef vedere::gui::windows::main_window_implements main_window_implements;
typedef vedere::app::gui::hello::main_window_extendt
<vedere::app::gui::hello::window_extendt
 <vedere::gui::windows::main_window> > main_window_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main_windowt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = main_window_implements, class TExtends = main_window_extends>
class _EXPORT_CLASS main_windowt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main_windowt() {
    }
    virtual ~main_windowt() {
        renderer_.free_image();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool load_bmp_image(const char_t* image_file) {
        if ((image_file)) {
            graphic::image::format::bmp::implement::to_bgra_image_reader reader;
            if ((reader.read(image_file))) {
                if ((this->load_image(reader))) {
                    return true;
                }
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool load_jpeg_image(const char_t* image_file) {
        if ((image_file)) {
            graphic::image::format::jpeg::libjpeg::to_bgra_image_reader reader;
            if ((reader.read(image_file))) {
                if ((this->load_image(reader))) {
                    return true;
                }
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool load_tiff_image(const char_t* image_file) {
        if ((image_file)) {
            graphic::image::format::tiff::libtiff::to_bgra_image_reader reader;
            if ((reader.read(image_file))) {
                if ((this->load_image(reader))) {
                    return true;
                }
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool load_png_image(const char_t* image_file) {
        if ((image_file)) {
            graphic::image::format::png::libpng::to_bgra_image_reader reader;
            if ((reader.read(image_file))) {
                if ((this->load_image(reader))) {
                    return true;
                }
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool load_raw_image(const char_t* image_file) {
        if ((image_file)) {
            graphic::image::format::raw::libraw::to_bgra_image_reader reader;
            if ((reader.read(image_file))) {
                if ((load_image(reader))) {
                    return true;
                }
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init
    (size_t image_width, size_t image_height, size_t image_depth,
     const char_t* image_file, gui::hello::image_format_t image_format,
     gui::hello::image_transform_t image_transform) {
        load_image
        (image_width, image_height,
         image_depth, image_file, image_format);
        return true;
    }
    virtual bool finish() {
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::load_image;
    virtual void* load_image
    (byte_reader& reader, size_t size, size_t width, size_t height) {
        void* image = 0;
        if ((image = renderer_.load_image(reader, size, width, height))) {
        }
        return image;
    }
    virtual void* set_image
    (byte_t* bytes, size_t size, size_t width, size_t height) {
        void* image = 0;
        if ((image = renderer_.set_image(bytes, size, width, height))) {
        }
        return image;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void switch_render() {
        renderer_.switch_render();
        this->invalidate();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    enum { MESSAGE = WM_USER};
    virtual bool post_message
    (typename Extends::message_type_t type, typename Extends::message_data_t data) {
        HWND hWnd = 0;
        if ((hWnd = this->attached_to())) {
            typename Extends::message_t *msg = 0;
            if ((msg = new typename Extends::message_t(type, data))) {
                if ((PostMessage(hWnd, MESSAGE, ((WPARAM)0), ((LPARAM)msg)))) {
                    return true;
                }
                delete msg;
            }
        }
        return false;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual LRESULT on_WM_PAINT_message
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        LRESULT lResult = 0;
        HDC hDC = 0;
        PAINTSTRUCT ps;
        if ((hDC = BeginPaint(hWnd, &ps))) {
            RECT rect;
            if ((GetClientRect(hWnd, &rect))) {
                if ((renderer_.init
                    (hDC, rect.right - rect.left + 1, 
                     rect.bottom - rect.top + 1))) {
                    renderer_.render();
                    renderer_.finish();
                }
            }
            EndPaint(hWnd, &ps);
        } else {
            lResult = this->on_message_default(hWnd,msg,wParam,lParam);
        }
        return lResult;
    }
    virtual LRESULT on_WM_SIZE_message
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        LRESULT lResult = 0;
        lResult = this->on_message_default(hWnd,msg,wParam,lParam);
        InvalidateRect(hWnd, NULL, TRUE);
        return lResult;
    }
    virtual LRESULT on_WM_LBUTTONUP_message
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        LRESULT lResult = 0;
        lResult = on_message_default(hWnd,msg,wParam,lParam);
        this->post_message(typename Extends::message_type_switch_render, 0);
        return lResult;
    }
    virtual LRESULT on_WM_USER_message
    (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        LRESULT lResult = 0;
        switch (msg) {
        case MESSAGE: {
            typename Extends::message_t *msg = 0;
            if ((msg = ((typename Extends::message_t*)lParam))) {
                this->on_message(msg->type_, msg->data_);
                delete msg;
            }
            break; }
        default:
            lResult = on_message_default(hWnd,msg,wParam,lParam);
            break;
        }
        return lResult;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    renderer renderer_;
};
typedef main_windowt<> main_window;

} // namespace hello 
} // namespace windows 
} // namespace gui 
} // namespace app 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_WINDOWS_HELLO_MAIN_WINDOW_HPP 
