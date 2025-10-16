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
#ifndef _VEDERE_GUI_MENU_HPP
#define _VEDERE_GUI_MENU_HPP

#include "vedere/io/logger.hpp"
#include <list>

namespace vedere {
namespace gui {

enum menu_element_type_t {
    menu_element_type_none,
    menu_element_type_menubar,
    menu_element_type_menu,
    menu_element_type_item,
    menu_element_type_separator
};
enum menu_element_style_t {
    menu_element_style_none,
    menu_element_style_item_checked,
    menu_element_style_item_radio,
};
typedef int menu_element_id_t;
typedef const char* menu_element_label_t;
struct menu_element_t {
    menu_element_type_t type;
    menu_element_id_t id;
    menu_element_label_t label;
    menu_element_style_t style;
};
typedef std::list<const menu_element_t*> menu_element_list_t;

typedef const menu_element_t* menu_elements_attached_t;
typedef xos::base::creatort<implement_base> menu_elements_creator;
typedef xos::base::attachert<menu_elements_attached_t, int, 0, menu_elements_creator> menu_elements_attacher;
typedef xos::base::attachedt<menu_elements_attached_t, int, 0, menu_elements_attacher, base> menu_elements_attached;
typedef xos::base::createdt<menu_elements_attached_t, int, 0, menu_elements_attacher, menu_elements_attached> menu_elements_created;
typedef menu_elements_attacher menu_elements_implements;
typedef menu_elements_created menu_elements_extends;
///////////////////////////////////////////////////////////////////////
///  Class: menu_elementst
///////////////////////////////////////////////////////////////////////
template
<class TImplements = menu_elements_implements, class TExtends = menu_elements_extends>
class _EXPORT_CLASS menu_elementst: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    menu_elementst
    (const menu_element_t* detached = 0, bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~menu_elementst() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef menu_elementst<> menu_elements_t;

///////////////////////////////////////////////////////////////////////
///  Class: menut
///////////////////////////////////////////////////////////////////////
template
<menu_element_type_t TopMenuElementType,
 class TImplements, class TExtends,
 typename TMenuItemActivateIdList, typename TMenuAttached,
 typename TMenuUnattached = int, TMenuUnattached VMenuUnattached = 0>

class _EXPORT_CLASS menut: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TMenuItemActivateIdList menu_item_activate_id_list_t;
    typedef TMenuAttached menu_attached_t;
    typedef TMenuUnattached menu_unattached_t;
    enum { menu_unattached = VMenuUnattached };

    using Extends::create_attached;
    using Extends::create_detached;
    using Extends::destroy_detached;
    using Extends::detach;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    menut
    (menu_attached_t detached = VMenuUnattached,
     bool is_created = false) {
    }
    virtual ~menut() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual menu_attached_t create_attached
    (menu_item_activate_id_list_t& list, const menu_elements_t& elements) {
        menu_attached_t detached = create_attached(list, elements.attached_to());
        return detached;
    }
    virtual menu_attached_t create_attached
    (menu_item_activate_id_list_t& list, const menu_element_t* element) {
        menu_attached_t detached = ((menu_attached_t)menu_unattached);
        if ((element)) {
            for (const menu_element_t* e = element; e->type; ++e) {
                menu_element_type_t t = e->type;
                VEDERE_LOG_MESSAGE_DEBUG("menu_element_type_t t = " << t);
                switch (t) {
                case TopMenuElementType: {
                    if ((detached = this->create_attached())) {
                        VEDERE_LOG_MESSAGE_DEBUG("create_menu_detached()...");
                        if ((detached == (create_menu_detached(detached, list, ++e)))) {
                            VEDERE_LOG_MESSAGE_DEBUG("...create_menu_detached()");
                            break;
                        }
                        this->detach();
                        this->destroy_detached(detached);
                        detached = ((menu_attached_t)menu_unattached);
                    }
                    break; }
                default: {
                    VEDERE_LOG_ERROR("invalid top menu_element_type_t = " << t);
                    return 0; }
                }
            }
        }
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual menu_attached_t create_detached
    (menu_item_activate_id_list_t& list, const menu_elements_t& elements) const {
        menu_attached_t detached = create_detached(list, elements.attached_to());
        return detached;
    }
    virtual menu_attached_t create_detached
    (menu_item_activate_id_list_t& list, const menu_element_t* element) const {
        menu_attached_t detached = ((menu_attached_t)menu_unattached);
        if ((element)) {
            for (const menu_element_t* e = element; e->type; ++e) {
                menu_element_type_t t = e->type;
                VEDERE_LOG_MESSAGE_DEBUG("menu_element_type_t t = " << t);
                switch (t) {
                case TopMenuElementType: {
                    if ((detached = this->create_detached())) {
                        VEDERE_LOG_MESSAGE_DEBUG("create_menu_detached()...");
                        if ((detached == (create_menu_detached(detached, list, ++e)))) {
                            VEDERE_LOG_MESSAGE_DEBUG("...create_menu_detached()");
                            break;
                        }
                        this->destroy_detached(detached);
                        detached = ((menu_attached_t)menu_unattached);
                    }
                    break; }
                default: {
                    VEDERE_LOG_ERROR("invalid top menu_element_type_t = " << t);
                    return 0; }
                }
            }
        }
        return detached;
    }
    virtual menu_attached_t create_menu_detached
    (menu_attached_t detached,
     menu_item_activate_id_list_t& list, const menu_element_t*& element) const {
        detached = ((menu_attached_t)menu_unattached);
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_MENU_HPP 
