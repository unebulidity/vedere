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
///   File: menu_signals.hpp
///
/// Author: $author$
///   Date: 8/25/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_MENU_SIGNALS_HPP
#define _VEDERE_GUI_GTK_MENU_SIGNALS_HPP

#include "vedere/gui/gtk/widget.hpp"

namespace vedere {
namespace gui {
namespace gtk {

typedef implement_base menu_signal_activate_to_implements;
typedef base menu_signal_activate_to_extends;
///////////////////////////////////////////////////////////////////////
///  Class: menu_signal_activate_tot
///////////////////////////////////////////////////////////////////////
template
<class TMenuSignals,
 typename TMenu = GtkMenu,
 typename TMenuItem = GtkMenuItem,
 typename TMenuActivateId = gint,
 class TImplements = menu_signal_activate_to_implements,
 class TExtends = menu_signal_activate_to_extends>

class _EXPORT_CLASS menu_signal_activate_tot
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TMenuSignals menu_signals_t;
    typedef TMenu menu_t;
    typedef TMenuItem menu_item_t;
    typedef TMenuActivateId menu_activate_id_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    menu_signal_activate_tot
    (menu_activate_id_t activate_id, menu_signals_t* signals_to,
     menu_item_t* item_from, menu_t* menu_from)
    : activate_id_(activate_id), signals_to_(signals_to),
      item_from_(item_from), menu_from_(menu_from) {
    }
    menu_signal_activate_tot
    (const  menu_signal_activate_tot& copy)
    : activate_id_(copy.activate_id_), signals_to_(copy.signals_to_),
      item_from_(copy.item_from_), menu_from_(copy.menu_from_) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual menu_activate_id_t activate_id() const {
        return activate_id_;
    }
    virtual menu_signals_t* signals_to() const {
        return (menu_signals_t*)signals_to_;
    }
    virtual menu_item_t* item_from() const {
        return (menu_item_t*)item_from_;
    }
    virtual menu_t* menu_from() const {
        return (menu_t*)menu_from_;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    menu_activate_id_t activate_id_;
    menu_signals_t* signals_to_;
    menu_item_t* item_from_;
    menu_t* menu_from_;
};

typedef implement_base menu_signals_implements;
///////////////////////////////////////////////////////////////////////
///  Class: menu_signalst
///////////////////////////////////////////////////////////////////////
template
<class TMenuSignalsActivateTo,
 typename TMenu = GtkMenu,
 typename TMenuItem = GtkMenuItem,
 typename TMenuActivateId = gint,
 class TImplements = menu_signals_implements>

class _EXPORT_CLASS menu_signalst: virtual public TImplements {
public:
    typedef TImplements Implements;

    typedef TMenuSignalsActivateTo menu_signal_activate_to_t;
    typedef TMenu menu_t;
    typedef TMenuItem menu_item_t;
    typedef TMenuActivateId menu_activate_id_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void on_signal_activate
    (menu_t* menu, menu_item_t* menu_item, menu_activate_id_t activate_id) {
        menu_signalst* to = 0;
        VEDERE_LOG_MESSAGE_DEBUG("on_signal_activate(..., activate_id = " << activate_id << ")...");
        if ((to = menu_signals_forward_to(this))) {
            to->on_signal_activate(menu, menu_item, activate_id);
        }
        VEDERE_LOG_MESSAGE_DEBUG("...on_signal_activate(..., activate_id = " << activate_id << ")");
    }
    static void signal_activate_callback
    (menu_item_t* menu_item, menu_signal_activate_to_t* to) {
        VEDERE_LOG_MESSAGE_DEBUG("signal_activate_callback()...");
        if ((to)) {
            menu_signalst* signals_to = 0;
            if ((signals_to = to->signals_to())) {
                VEDERE_LOG_MESSAGE_DEBUG("signals_to->on_signal_activate(..., activate_id = " << to->activate_id() << ")...");
                signals_to->on_signal_activate(to->menu_from(), to->item_from(), to->activate_id());
                VEDERE_LOG_MESSAGE_DEBUG("...signals_to->on_signal_activate(..., activate_id = " << to->activate_id() << ")");
            } else {
                VEDERE_LOG_ERROR("unexpected 0 == to->signals_to()");
            }
        } else {
            VEDERE_LOG_ERROR("unexpected 0 == to");
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual menu_signalst* forward_menu_signals_to(menu_signalst* to) {
        return 0;
    }
    virtual menu_signalst* menu_signals_forward_to(menu_signalst* from) const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

class _EXPORT_CLASS menu_signals;
typedef menu_signal_activate_tot<menu_signals> menu_signal_activate_to;
typedef menu_signalst<menu_signal_activate_to> menu_signals_implement;
///////////////////////////////////////////////////////////////////////
///  Class: menu_signals
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS menu_signals: virtual public menu_signals_implement {
public:
    typedef menu_signals_implement Implements;
};

} // namespace gtk
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_MENU_SIGNALS_HPP 
