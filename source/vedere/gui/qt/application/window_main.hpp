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
///   File: window_main.hpp
///
/// Author: $author$
///   Date: 5/29/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_QT_APPLICATION_WINDOW_MAIN_HPP
#define _VEDERE_GUI_QT_APPLICATION_WINDOW_MAIN_HPP

#include "vedere/gui/qt/application/main.hpp"
#include "lamna/gui/qt/application/window_main.hpp"

namespace vedere {
namespace gui {
namespace qt {
namespace application {

typedef lamna::gui::qt::application::window_main_implements window_main_implements;
typedef lamna::gui::qt::application::window_main window_main;
/*typedef vedere::gui::qt::application::main_implements window_main_implements;
typedef vedere::gui::qt::application::main window_main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: window_main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS window_main
: virtual public window_main_implements, public window_main_extends {
public:
    typedef window_main_implements Implements;
    typedef window_main_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    window_main(): qMainWindow_(0) {
    }
    virtual ~window_main() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual QMainWindow* create_main_window
    (QApplication& qApplication, int argc, char_t** argv, char_t** env) {
        return 0;
    }
    virtual bool destroy_main_window
    (QMainWindow* qMainWindow, QApplication& qApplication,
     int argc, char_t** argv, char_t** env) {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int before_exec
    (QApplication& qApplication, int argc, char_t** argv, char_t** env) {
        int err = 0;
        VEDERE_LOG_MESSAGE_DEBUG("create_main_window()...");
        if ((qMainWindow_ = create_main_window(qApplication, argc, argv, env))) {
            VEDERE_LOG_MESSAGE_DEBUG("qMainWindow_->show()...");
            qMainWindow_->show();
        } else {
            VEDERE_LOG_ERROR("failed on create_main_window()");
            err = 1;
        }
        return err;
    }
    virtual int after_exec
    (QApplication& qApplication, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if ((qMainWindow_)) {
            VEDERE_LOG_MESSAGE_DEBUG("destroy_main_window()...");
            if (!(destroy_main_window(qMainWindow_, qApplication, argc, argv, env))) {
                VEDERE_LOG_ERROR("failed on destroy_main_window()");
                err = 1;
            }
            qMainWindow_ = 0;
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    QMainWindow* qMainWindow_;
};*/

} // namespace application 
} // namespace qt 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_QT_APPLICATION_WINDOW_MAIN_HPP 
