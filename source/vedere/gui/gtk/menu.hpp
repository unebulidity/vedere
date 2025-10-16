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
///   File: menu.hpp
///
/// Author: $author$
///   Date: 8/24/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_MENU_HPP
#define _VEDERE_GUI_GTK_MENU_HPP

#include "vedere/gui/gtk/menu_shell.hpp"
#include <list>

namespace vedere {
namespace gui {
namespace gtk {

typedef implement_base menu_item_activate_id_implements;
typedef base menu_item_activate_id_extends;
///////////////////////////////////////////////////////////////////////
///  Class: menu_item_activate_idt
///////////////////////////////////////////////////////////////////////
template
<typename TMenuItem = GtkMenuItem,
 typename TMenuActivateId = gint,
 class TImplements = menu_item_activate_id_implements,
 class TExtends = menu_item_activate_id_extends>
class _EXPORT_CLASS menu_item_activate_idt
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TMenuItem menu_item_t;
    typedef TMenuActivateId menu_activate_id_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    menu_item_activate_idt
    (menu_activate_id_t activate_id, menu_item_t* item)
    : activate_id_(activate_id), item_(item) {
    }
    menu_item_activate_idt(const menu_item_activate_idt& copy)
    : activate_id_(copy.activate_id_), item_(copy.item_) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual menu_activate_id_t activate_id() const {
        return activate_id_;
    }
    virtual menu_item_t* item() const {
        return (menu_item_t*)item_;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    menu_activate_id_t activate_id_;
    menu_item_t* item_;
};
typedef menu_item_activate_idt<> menu_item_activate_id;
typedef std::list<menu_item_activate_id> menu_item_activate_id_list;

typedef menu_shell_implements menu_implements;
typedef menu_shell menu_extends;
///////////////////////////////////////////////////////////////////////
///  Class: menut
///////////////////////////////////////////////////////////////////////
template
<class TImplements = menu_implements, class TExtends = menu_extends>

class _EXPORT_CLASS menut: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    menut() {
    }
    virtual ~menut() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_MENU_HPP 
