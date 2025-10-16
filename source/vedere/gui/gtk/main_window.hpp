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
///   File: main_window.hpp
///
/// Author: $author$
///   Date: 5/28/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_MAIN_WINDOW_HPP
#define _VEDERE_GUI_GTK_MAIN_WINDOW_HPP

#include "lamna/gui/gtk/application/window.hpp"
/*#include "vedere/gui/gtk/widget.hpp"
#include "vedere/io/logger.hpp"*/

namespace vedere {
namespace gui {
namespace gtk {

typedef lamna::gui::gtk::application::window_implements main_window_implements;
typedef lamna::gui::gtk::application::window main_window;

/*typedef widget_implements main_window_implements;
typedef widget main_window_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main_window
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main_window
: virtual public main_window_implements, public main_window_extends {
public:
    typedef main_window_implements Implements;
    typedef main_window_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main_window
    (widget_attached_t detached = 0, bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~main_window() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create() {
        if ((this->destroyed())) {
            widget_attached_t detached = 0;
            if ((detached = gtk_window_new(GTK_WINDOW_TOPLEVEL))) {
                this->attach(detached);
                this->accept_signal_destroy();
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void on_signal_destroy() {
        VEDERE_LOG_MESSAGE_DEBUG("gtk_main_quit()...");
        gtk_main_quit();
        VEDERE_LOG_MESSAGE_DEBUG("...gtk_main_quit()");
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};*/

} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_MAIN_WINDOW_HPP 
