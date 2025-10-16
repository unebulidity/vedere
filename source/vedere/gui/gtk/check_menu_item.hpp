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
///   File: check_menu_item.hpp
///
/// Author: $author$
///   Date: 10/7/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_CHECK_MENU_ITEM_HPP
#define _VEDERE_GUI_GTK_CHECK_MENU_ITEM_HPP

#include "vedere/gui/gtk/menu_item.hpp"

namespace vedere {
namespace gui {
namespace gtk {

typedef menu_item_implements check_menu_item_implements;
typedef menu_item check_menu_item_extends;
///////////////////////////////////////////////////////////////////////
///  Class: check_menu_itemt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = check_menu_item_implements,
 class TExtends = check_menu_item_extends>

class _EXPORT_CLASS check_menu_itemt
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    check_menu_itemt
    (widget_attached_t detached = 0, bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~check_menu_itemt() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual widget_attached_t create_detached() const {
        widget_attached_t detached = create_detached(NULL);
        return detached;
    }
    virtual widget_attached_t create_detached
    (const gchar* label, gboolean is_active = FALSE) const {
        widget_attached_t detached = 0;
        if ((label)) {
            if (!(detached = gtk_check_menu_item_new_with_label(label))) {
                VEDERE_LOG_ERROR("failed 0 == gtk_check_menu_item_new_with_lebel(\"" << label << "\")");
            }
        } else {
            if (!(detached = gtk_check_menu_item_new())) {
                VEDERE_LOG_ERROR("failed 0 == gtk_check_menu_item_new()");
            }
        }
        if ((detached)) {
            gtk_check_menu_item_set_active
            (GTK_CHECK_MENU_ITEM(detached), is_active);
        }
        return detached;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef check_menu_itemt<> check_menu_item;

} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_CHECK_MENU_ITEM_HPP
