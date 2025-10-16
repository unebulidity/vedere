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
///   Date: 5/30/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_APPLICATION_WINDOW_MAIN_HPP
#define _VEDERE_GUI_GTK_APPLICATION_WINDOW_MAIN_HPP

#include "lamna/gui/gtk/application/window_main.hpp"
/*#include "vedere/gui/gtk/application/main.hpp"
#include "vedere/gui/gtk/application/window.hpp"*/

namespace vedere {
namespace gui {
namespace gtk {
namespace application {

typedef lamna::gui::gtk::application::window_main_implements window_main_implements;
typedef lamna::gui::gtk::application::window_main window_main;

/*typedef application::main_implements window_main_implements;
typedef application::main window_main_extends;
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
    window_main(): main_window_(0) {
    }
    virtual ~window_main() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual GtkWidget* create_main_window(GtkApplication *application) {
        return 0;
    }
    virtual bool before_create_main_window(GtkApplication *application) {
        return true;
    }
    virtual bool after_create_main_window
    (GtkWidget* main_window, GtkApplication *application) {
        return true;
    }
    virtual bool destroy_main_window
    (GtkWidget* main_window, GtkApplication *application) {
        return false;
    }
    virtual bool show_main_window
    (GtkWidget* main_window, GtkApplication *application) {
        if ((main_window) && (application)) {
            gtk_widget_show_all(main_window);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void on_signal_activate(GtkApplication* application) {

        VEDERE_LOG_MESSAGE_DEBUG("on_signal_activate()in...");
        if ((application)) {
            if ((this->before_create_main_window(application))) {
                GtkWidget* main_window = 0;

                if ((main_window = this->create_main_window(application))) {
                    if ((this->after_create_main_window(main_window, application))) {
                        if ((this->show_main_window(main_window, application))) {
                            main_window_ = main_window;
                            main_window = 0;
                        } else {
                            VEDERE_LOG_ERROR("failed on show_main_window()");
                        }
                    } else {
                        VEDERE_LOG_ERROR("failed on after_create_main_window()");
                    }
                    if ((main_window)) {
                        if (!(this->destroy_main_window(main_window, application))) {
                            VEDERE_LOG_ERROR("failed on destroy_main_window()");
                        }
                    }
                } else {
                    VEDERE_LOG_ERROR("failed on create_main_window()");
                }
            } else {
                VEDERE_LOG_ERROR("failed on before_create_main_window()");
            }
        } else {
            VEDERE_LOG_ERROR("unexpected GtkApplication* application = 0");
        }
        VEDERE_LOG_MESSAGE_DEBUG("on_signal_activate()...out");
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    GtkWidget* main_window_;
};*/

} // namespace application 
} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_APPLICATION_WINDOW_MAIN_HPP 
