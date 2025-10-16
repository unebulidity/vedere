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
///   File: widget.hpp
///
/// Author: $author$
///   Date: 5/28/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_WIDGET_HPP
#define _VEDERE_GUI_GTK_WIDGET_HPP

#include "lamna/gui/gtk/widget.hpp"
#include "vedere/io/logger.hpp"
/*#include "xos/base/created.hpp"
#include "xos/base/creator.hpp"
#include "xos/base/attached.hpp"
#include "xos/base/attacher.hpp"
#include <gtk/gtk.h>*/

namespace vedere {
namespace gui {
namespace gtk {

typedef lamna::gui::gtk::widget_attached_t widget_attached_t;
typedef lamna::gui::gtk::widget_signals widget_signals;
typedef lamna::gui::gtk::widget_attacher widget_attacher;
typedef lamna::gui::gtk::widget_implements widget_implements;
typedef lamna::gui::gtk::widget widget;

/*typedef GtkWidget* widget_attached_t;
typedef xos::base::creatort<implement_base> widget_creator;
typedef xos::base::attachert<widget_attached_t, int, 0, widget_creator> widget_attacher;
typedef xos::base::attachedt<widget_attached_t, int, 0, widget_attacher, base> widget_attached;
typedef xos::base::createdt<widget_attached_t, int, 0, widget_attacher, widget_attached> widget_created;
typedef widget_attacher widget_implements;
typedef widget_created widget_extends;
///////////////////////////////////////////////////////////////////////
///  Class: widget
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS widget
: virtual public widget_implements, public widget_extends {
public:
    typedef widget_implements Implements;
    typedef widget_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    widget
    (widget_attached_t detached = 0, bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~widget() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool destroy() {
        widget_attached_t detached = 0;
        if ((detached = this->detach())) {
            gtk_widget_destroy(detached);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool accept_signal_destroy() {
        const char* signal_name = "destroy";
        widget_attached_t detached = 0;
        if ((detached = this->attached_to())) {
            if ((g_signal_connect
                 (detached, signal_name,
                  G_CALLBACK(signal_destroy_callback), ((gpointer)this)))) {
                return true;
            } else {
                VEDERE_LOG_ERROR("failed on g_signal_connect(..., \"" << signal_name << "\")");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool show_all() {
        widget_attached_t detached = 0;
        if ((detached = this->attached_to())) {
            gtk_widget_show_all(detached);
            return true;
        }
        return false;
    }
    virtual bool show() {
        widget_attached_t detached = 0;
        if ((detached = this->attached_to())) {
            gtk_widget_show(detached);
            return true;
        }
        return false;
    }
    virtual bool hide() {
        widget_attached_t detached = 0;
        if ((detached = this->attached_to())) {
            gtk_widget_hide(detached);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_sensitive(bool to = true) {
        widget_attached_t detached = 0;
        if ((detached = this->attached_to())) {
            gtk_widget_set_sensitive(detached, (to)?(TRUE):(FALSE));
            return true;
        }
        return false;
    }
    virtual bool get_sensitive() const {
        widget_attached_t detached = 0;
        if ((detached = this->attached_to())) {
            if (FALSE != (gtk_widget_get_sensitive(detached)))
                return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool queue_draw() {
        widget_attached_t detached = 0;
        if ((detached = this->attached_to())) {
            gtk_widget_queue_draw(detached);
            return true;
        }
        return false;
    }
    virtual bool queue_draw_area(gint x,gint y, gint width,gint height) {
        widget_attached_t detached = 0;
        if ((detached = this->attached_to())) {
            gtk_widget_queue_draw_area(detached, x,y, width,height);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual operator widget_attached_t() const {
        return this->attached_to();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    virtual void on_signal_destroy() {
    }
    static void signal_destroy_callback(gpointer instance, gpointer data) {
        widget* w = 0;
        if ((w = ((widget*)data))) {
            widget_attached_t detached = 0;
            if ((detached = ((widget_attached_t)instance)) && (detached = (w->attached_to()))) {
                w->on_signal_destroy();
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};*/

} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_WIDGET_HPP 
