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
///   File: window.hpp
///
/// Author: $author$
///   Date: 5/30/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_APPLICATION_WINDOW_HPP
#define _VEDERE_GUI_GTK_APPLICATION_WINDOW_HPP

#include "lamna/gui/gtk/application/window.hpp"
/*#include "vedere/gui/gtk/widget.hpp"*/

namespace vedere {
namespace gui {
namespace gtk {
namespace application {

typedef lamna::gui::gtk::application::window_implements window_implements;
typedef lamna::gui::gtk::application::window window;

/*typedef vedere::gui::gtk::widget_implements window_implements;
typedef vedere::gui::gtk::widget window_extends;
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
    window
    (GtkWidget* detached = 0, bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~window() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create(GtkApplication* application) {
        if ((application)) {
            if ((this->destroyed())) {
                GtkWidget* detached = 0;
                if ((detached = gtk_application_window_new(application))) {
                    this->attach(detached);
                    return true;
                } else {
                    VEDERE_LOG_ERROR("failed on gtk_application_window_new()");
                }
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};*/

} // namespace application 
} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_APPLICATION_WINDOW_HPP 
