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
///   Date: 6/28/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_GTK_EXPLORE_APPLICATION_MAIN_HPP
#define _VEDERE_APP_GUI_GTK_EXPLORE_APPLICATION_MAIN_HPP

#include "vedere/app/gui/gtk/explore/application/window.hpp"
#include "vedere/gui/gtk/application/window_main.hpp"
#include "vedere/gui/gtk/application/window.hpp"
#include "vedere/gui/gtk/application/main.hpp"
#include "vedere/gui/gtk/main_window.hpp"
#include "vedere/gui/gtk/main.hpp"

namespace vedere {
namespace gui {
namespace gtk {
namespace app {
namespace explore {
namespace application {

typedef gtk::application::window_main_implements main_implements;
typedef gtk::application::window_main main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main
: virtual public main_implements, public main_extends {
public:
    typedef main_implements Implements;
    typedef main_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main() {
    }
    virtual ~main() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual GtkWidget* create_main_window(GtkApplication *application) {
        if ((application)) {
            GtkWidget* window = 0;
            if ((window = window_.create_attached(application))) {
                if ((window_.init(argv_.length(), argv_.elements()))) {
                    return window;
                }
                window_.destroy();
            }
        }
        return 0;
    }
    virtual bool destroy_main_window
    (GtkWidget* main_window, GtkApplication *application) {
        if ((application) && (main_window)
            && (main_window == (window_.attached_to()))) {
            if ((window_.detach())) {
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int after_create_application
    (GtkApplication* application,
     const gchar* application_id, GApplicationFlags application_flags,
     int argc, char_t** argv, char_t** env) {
        if ((argc > optind)) {
            xos::base::string arg;
            const char_t* arga;
            for (int a = optind; a < argc; ++a) {
                if ((argv) && (argv[a]) && (argv[a][0])) {
                    arg.assign(argv[a]);
                    arg_.append(&arg, 1);
                    arga = arg_[arg_.length()-1].chars();
                    argv_.append(&arga, 1);
                }
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    window window_;
    xos::base::arrayt<xos::base::string> arg_;
    xos::base::arrayt<const char*> argv_;
};

} // namespace application
} // namespace explore
} // namespace app
} // namespace gtk
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_GTK_EXPLORE_APPLICATION_MAIN_HPP


