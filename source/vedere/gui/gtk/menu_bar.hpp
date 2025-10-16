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
///   File: menu_bar.hpp
///
/// Author: $author$
///   Date: 8/24/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_MENU_BAR_HPP
#define _VEDERE_GUI_GTK_MENU_BAR_HPP

#include "vedere/gui/gtk/radio_menu_item.hpp"
#include "vedere/gui/gtk/check_menu_item.hpp"
#include "vedere/gui/gtk/menu_item.hpp"
#include "vedere/gui/gtk/menu_signals.hpp"
#include "vedere/gui/gtk/menu_shell.hpp"
#include "vedere/gui/gtk/menu.hpp"
#include "vedere/gui/menu.hpp"

namespace vedere {
namespace gui {
namespace gtk {

class _EXPORT_CLASS menu_bar_signals;
typedef menu_signal_activate_tot
<menu_bar_signals, GtkMenuBar> menu_bar_signal_activate_to;
typedef std::list
<menu_bar_signal_activate_to> menu_bar_signal_activate_to_list;
typedef menu_signalst
<menu_bar_signal_activate_to, GtkMenuBar> menu_bar_signals_implement;
///////////////////////////////////////////////////////////////////////
///  Class: menu_bar_signals
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS menu_bar_signals: virtual public menu_bar_signals_implement {
public:
    typedef menu_bar_signals_implement Implements;
};
typedef GCallback menu_bar_signal_callback_t;
typedef menu_bar_signals* menubar_signal_data_t;
typedef gint menu_bar_signal_event_mask_t;

typedef menu_shell_implements menu_bar_implements;
typedef gui::menut
<menu_element_type_menubar, menu_bar_implements,
 menu_shell, menu_item_activate_id_list, widget_attached_t> menu_bar_extends;
///////////////////////////////////////////////////////////////////////
///  Class: menu_bart
///////////////////////////////////////////////////////////////////////
template
<class TImplements = menu_bar_implements, class TExtends = menu_bar_extends>

class _EXPORT_CLASS menu_bart
: virtual public menu_bar_signals,
  virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    menu_bart
    (widget_attached_t detached = 0, bool is_created = false)
    : Extends(detached, is_created),
      menu_bar_signals_forward_to_(0) {
    }
    virtual ~menu_bart() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    /*virtual widget_attached_t create_detached
    (menu_item_activate_id_list& list, const menu_element_t*& element) const {
        widget_attached_t detached = 0;
        for (const menu_element_t* e = element; e->type; ++e) {
            menu_element_type_t t = e->type;
            switch (t) {
            case menu_element_type_menubar: {
                if ((detached = this->create_detached())) {
                    if ((create_menu_detached(detached, list, ++e))) {
                        break;
                    }
                    this->destroy_detached(detached);
                }
                return 0;
                break; }
            default:
                VEDERE_LOG_ERROR("invalid menu_element_type_t t = " << e->type);
                return 0;
            }
        }
        return detached;
    }*/
    virtual widget_attached_t create_menu_detached
    (widget_attached_t menu,
     menu_item_activate_id_list& list, const menu_element_t*& element) const {
        for (const menu_element_t*& e = element; e->type; ++e) {
            menu_element_type_t t = e->type;
            VEDERE_LOG_MESSAGE_DEBUG("menu_element_type_t t = " << e->type);
            switch (t) {
            case menu_element_type_menu: {
                GtkWidget* new_menu = 0;
                GtkWidget* new_submenu = 0;
                if ((new_menu = gtk_menu_new())) {
                    if ((new_submenu = gtk_menu_item_new_with_label(e->label))) {
                        VEDERE_LOG_MESSAGE_DEBUG("create_submenu_detached()...");
                        if ((create_submenu_detached(new_menu, new_submenu, list, ++e))) {
                            VEDERE_LOG_MESSAGE_DEBUG("...create_submenu_detached()");
                            gtk_menu_item_set_submenu(GTK_MENU_ITEM(new_submenu), new_menu);
                            gtk_menu_shell_append(GTK_MENU_SHELL(menu), new_submenu);
                            break;
                        }
                        gtk_widget_destroy(new_submenu);
                    }
                    gtk_widget_destroy(new_menu);
                    return 0;
                }
                break; }
            default:
                VEDERE_LOG_ERROR("invalid menu_element_type_t t = " << t);
                return 0;
            }
        }
        return menu;
    }
    virtual widget_attached_t create_submenu_detached
    (widget_attached_t menu, widget_attached_t submenu,
     menu_item_activate_id_list& list, const menu_element_t*& element) const {
        widget_attached_t menu_item = 0;
        for (const menu_element_t*& e = element; e->type; ++e) {
            menu_element_type_t t = e->type;
            VEDERE_LOG_MESSAGE_DEBUG("menu_element_type_t t = " << t);
            switch (t) {
            case menu_element_type_menu: {
                GtkWidget* new_menu = 0;
                GtkWidget* new_submenu = 0;
                if ((new_menu = gtk_menu_new())) {
                    if ((new_submenu = gtk_menu_item_new_with_label(e->label))) {
                        VEDERE_LOG_MESSAGE_DEBUG("create_submenu_detached()...");
                        if ((create_submenu_detached(new_menu, new_submenu, list, ++e))) {
                            VEDERE_LOG_MESSAGE_DEBUG("...create_submenu_detached()");
                            gtk_menu_item_set_submenu(GTK_MENU_ITEM(new_submenu), new_menu);
                            gtk_menu_shell_append(GTK_MENU_SHELL(menu), new_submenu);
                            break;
                        }
                        gtk_widget_destroy(new_submenu);
                    }
                    gtk_widget_destroy(new_menu);
                }
                return 0;
                break; }
            case menu_element_type_item: {
                if ((menu_item = create_menu_item_detached(list, e))) {
                    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);
                    break;
                }
                return 0;
                break; }
            case menu_element_type_separator: {
                if ((menu_item = gtk_separator_menu_item_new())) {
                    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);
                    break;
                }
                return 0;
                break; }
            default:
                VEDERE_LOG_ERROR("invalid menu_element_type_t t = " << e->type);
                return 0;
            }
        }
        return submenu;
    }
    virtual widget_attached_t create_menu_item_detached
    (menu_item_activate_id_list& list, const menu_element_t*& element) const {
        widget_attached_t menu_item = 0;
        const menu_element_t* e = 0;
        if ((e = element)) {
            switch (e->style) {
            case menu_element_style_item_radio:
                menu_item = gtk::radio_menu_item().create_detached(0, e->label);
                break;
            case menu_element_style_item_checked:
                menu_item = gtk::check_menu_item().create_detached(e->label, TRUE);
                break;
            default:
                menu_item = gtk::menu_item().create_detached(e->label);
                break;
            }
            if ((menu_item)) {
                list.push_back
                (menu_item_activate_id(e->id, GTK_MENU_ITEM(menu_item)));
            }
        } else {
            VEDERE_LOG_ERROR("unexpected 0 == (e = element)");
        }
        return menu_item;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual widget_attached_t create_detached() const {
        widget_attached_t detached = 0;
        if (!(detached = gtk_menu_bar_new())) {
            VEDERE_LOG_ERROR("failed 0 == gtk_menu_bar_new()");
        }
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual menu_bar_signals*
    forward_menu_signals_to(menu_bar_signals* to) {
        menu_bar_signals_forward_to_ = to;
        return menu_bar_signals_forward_to_;
    }
    virtual menu_bar_signals*
    menu_signals_forward_to(menu_bar_signals* from) const {
        return menu_bar_signals_forward_to_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    menu_bar_signals* menu_bar_signals_forward_to_;
};
typedef menu_bart<> menu_bar;

} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_MENU_BAR_HPP 
