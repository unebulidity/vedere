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
///   File: main.hpp
///
/// Author: $author$
///   Date: 10/2/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_FL_HELLO_MAIN_HPP
#define _VEDERE_APP_GUI_FL_HELLO_MAIN_HPP

#include "vedere/gui/fl/main.hpp"
#include "vedere/gui/fl/double_window.hpp"

namespace vedere {
namespace app {
namespace gui {
namespace fl {
namespace hello {

typedef vedere::gui::fl::double_window_implements window_implements;
typedef vedere::gui::fl::double_window window_extends;
///////////////////////////////////////////////////////////////////////
///  Class: window
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS window
: virtual public window_implements, public window_extends {
public:
    typedef window_implements Implements;
    typedef window_extends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    window(int width, int height): Extends(width, height) {
    }
    virtual ~window() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init() {
        bool success = true;
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
};

typedef vedere::gui::fl::main_implements main_implements;
typedef vedere::gui::fl::main main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main: virtual public main_implements, public main_extends {
public:
    typedef main_implements Implements;
    typedef main_extends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main() {
    }
    virtual ~main() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Fl_Window* create_window(int argc, char_t** argv, char_t** env) {
        if ((window_ = new window(this->width(), this->height()))) {
            if (!(window_->init())) {
                destroy_window(window_, argc, argv, env);
            }
        }
        return window_;
    }
    virtual int destroy_window
    (Fl_Window* window, int argc, char_t** argv, char_t** env) {
        int err = 1;
        if ((window) && (window_ == window)) {
            delete window_;
            window_ = 0;
            err = 0;
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    window* window_;
};

} // namespace hello 
} // namespace fl 
} // namespace gui 
} // namespace app 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_FL_HELLO_MAIN_HPP 
