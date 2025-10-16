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
///   File: main.hpp
///
/// Author: $author$
///   Date: 6/16/2016
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_WINDOWS_HELLO_MAIN_HPP
#define _VEDERE_APP_GUI_WINDOWS_HELLO_MAIN_HPP

#include "vedere/app/gui/windows/hello/main_window.hpp"
#include "vedere/app/gui/hello/main.hpp"
#include "vedere/gui/windows/getopt/main.hpp"
#include "vedere/gui/windows/main_window.hpp"

namespace vedere {
namespace app {
namespace gui {
namespace windows {
namespace hello {

typedef vedere::gui::windows::getopt::main_implements main_implements;
typedef vedere::app::gui::hello::maint
<main_implements, vedere::gui::windows::getopt::main> main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: maint
///////////////////////////////////////////////////////////////////////
template
<class TImplements = main_implements, class TExtends = main_extends>
class _EXPORT_CLASS maint: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    maint() {
    }
    virtual ~maint() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual lamna::gui::windows::window* create_main_window
    (lamna::gui::windows::window_class& main_window_class, 
     HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
        LPCSTR windowClassName = 0;
        if ((windowClassName = main_window_class.GetWindowClassName())) {
            if ((main_window_.create(hInstance, windowClassName))) {
                if (!(main_window_.init
                     (this->image_width_, this->image_height_, this->image_depth_,
                      this->image_file_.has_chars(), this->image_format_, this->image_transform_))) {
                    VEDERE_LOG_ERROR("failed on main_window_.init()");
                }
                return &main_window_;
            }
        }
        return 0;
    }
    virtual bool destroy_main_window
    (lamna::gui::windows::window& main_window, 
     lamna::gui::windows::window_class& main_window_class, 
     HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {
         if (&main_window == (&main_window_)) {
             if (!(main_window_.finish())) {
                 VEDERE_LOG_ERROR("failed on main_window_.fini()");
             }
             if ((main_window_.destroy())) {
                 return true;
             }
         }
         return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    main_window main_window_;
};
typedef maint<> main;

} // namespace hello 
} // namespace windows 
} // namespace gui 
} // namespace app 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_WINDOWS_HELLO_MAIN_HPP 
