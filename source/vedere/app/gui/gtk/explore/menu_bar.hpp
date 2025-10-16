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
///   Date: 8/26/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_GTK_EXPLORE_MENU_BAR_HPP
#define _VEDERE_APP_GUI_GTK_EXPLORE_MENU_BAR_HPP

#include "vedere/app/gui/explore/menu_bar.hpp"
#include "vedere/gui/gtk/menu_bar.hpp"
#include "vedere/gui/menu.hpp"

namespace vedere {
namespace gui {
namespace gtk {
namespace app {
namespace explore {

typedef gtk::menu_bar_implements menu_bar_implements;
typedef gtk::menu_bar menu_bar_extends;
///////////////////////////////////////////////////////////////////////
///  Class: menu_bar
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS menu_bar
: virtual public menu_bar_implements, public menu_bar_extends {
public:
    typedef menu_bar_implements Implements;
    typedef menu_bar_extends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    menu_bar() {
    }
    virtual ~menu_bar() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual widget_attached_t create_attached_to() {
        widget_attached_t detached = 0;
        menu_item_activate_id_list list;
        if ((detached = create_attached
            (list, gui::app::explore::menu_bar_element))) {
        }
        return detached;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace explore 
} // namespace app 
} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_GTK_EXPLORE_MENU_BAR_HPP 
