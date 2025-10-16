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
///   Date: 5/29/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_APPLICATION_MAIN_HPP
#define _VEDERE_GUI_GTK_APPLICATION_MAIN_HPP

#include "lamna/gui/gtk/application/main.hpp"
/*#include "vedere/gui/gtk/main.hpp"

#define VEDERE_GUI_GTK_APPLICATION_FLAGS G_APPLICATION_FLAGS_NONE
#define VEDERE_GUI_GTK_APPLICATION_ID "vedere.gui.gtk.application"*/

namespace vedere {
namespace gui {
namespace gtk {
namespace application {

typedef lamna::gui::gtk::application::main_implements main_implements;
typedef lamna::gui::gtk::application::main main;

/*typedef gtk::main_implements main_implements;
typedef gtk::main main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main: virtual public main_implements, public main_extends {
public:
    typedef main_implements Implements;
    typedef main_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main()
    : application_id_(VEDERE_GUI_GTK_APPLICATION_ID),
      application_flags_(VEDERE_GUI_GTK_APPLICATION_FLAGS),
      application_(0) {
    }
    virtual ~main() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int gui_main(int argc, char_t** argv, char_t** env) {
        int err = 0;
        int application_argc = 0;
        char** application_argv = 0;
        const gchar* application_id = application_id_.chars();
        GApplicationFlags application_flags =  application_flags_;

        VEDERE_LOG_MESSAGE_DEBUG("gtk_application_new()...");
        if ((application_ = gtk_application_new(application_id, application_flags))) {
            if ((accept_signal_activate())) {
                VEDERE_LOG_MESSAGE_DEBUG("gtk_application_run()...");
                if ((err = g_application_run
                     (G_APPLICATION(application_), application_argc, application_argv))) {
                    VEDERE_LOG_ERROR("failed " << err << " on g_application_run()");
                } else {
                    VEDERE_LOG_MESSAGE_DEBUG("...gtk_application_run()");
                }
            } else {
                VEDERE_LOG_ERROR("failed on accept_signal_activate()");
            }
            VEDERE_LOG_MESSAGE_DEBUG("g_object_unref()...");
            g_object_unref(application_);
            VEDERE_LOG_MESSAGE_DEBUG("...g_object_unref()");
            application_ = 0;
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool accept_signal_activate() {
        const char* signal_name = "activate";
        GtkApplication* detached = 0;
        if ((detached = this->application_)) {
            if ((g_signal_connect
                 (detached, signal_name,
                  G_CALLBACK(signal_activate_callback), ((gpointer)this)))) {
                return true;
            } else {
                VEDERE_LOG_ERROR("failed on g_signal_connect(..., \"" << signal_name << "\")");
            }
        }
        return false;
    }
    virtual void on_signal_activate(GtkApplication* application) {
        VEDERE_LOG_MESSAGE_DEBUG("on_signal_activate()in...");
        VEDERE_LOG_MESSAGE_DEBUG("on_signal_activate()...out");
    }
    static void signal_activate_callback(GtkApplication* application, gpointer data) {
        VEDERE_LOG_MESSAGE_DEBUG("activate_callback()in...");
        if ((application) && (data)) {
            main* this_main = 0;
            if ((this_main = ((main*)data)) && (application == (this_main->application_))) {
                this_main->on_signal_activate(application);
            }
        }
        VEDERE_LOG_MESSAGE_DEBUG("activate_callback()...out");
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    string_t application_id_;
    GApplicationFlags application_flags_;
    GtkApplication* application_;
};*/

} // namespace application 
} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_APPLICATION_MAIN_HPP 
