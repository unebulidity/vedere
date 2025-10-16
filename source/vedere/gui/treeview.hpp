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
///   File: treeview.hpp
///
/// Author: $author$
///   Date: 6/28/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_TREEVIEW_HPP
#define _VEDERE_GUI_TREEVIEW_HPP

#include "vedere/io/logger.hpp"

namespace vedere {
namespace gui {

enum treeview_element_type_t {
    treeview_element_type_none,
    treeview_element_type_treeview,
    treeview_element_type_header,
    treeview_element_type_store,
    treeview_element_type_column,
};
enum treeview_element_style_t {
    treeview_element_style_none,
    treeview_element_style_string,
    treeview_element_style_double,
    treeview_element_style_integer,
    treeview_element_style_boolean,
    treeview_element_style_void,
};
typedef int treeview_element_id_t;
typedef const char* treeview_element_label_t;
struct treeview_element_t {
    treeview_element_type_t type;
    treeview_element_style_t style;
    treeview_element_label_t label;
    treeview_element_id_t id;
};

typedef const treeview_element_t* treeview_elements_attached_t;
typedef xos::base::creatort<implement_base> treeview_elements_creator;
typedef xos::base::attachert<treeview_elements_attached_t, int, 0, treeview_elements_creator> treeview_elements_attacher;
typedef xos::base::attachedt<treeview_elements_attached_t, int, 0, treeview_elements_attacher, base> treeview_elements_attached;
typedef xos::base::createdt<treeview_elements_attached_t, int, 0, treeview_elements_attacher, treeview_elements_attached> treeview_elements_created;
typedef treeview_elements_attacher treeview_elements_implements;
typedef treeview_elements_created treeview_elements_extends;
///////////////////////////////////////////////////////////////////////
///  Class: treeview_elementst
///////////////////////////////////////////////////////////////////////
template
<class TImplements = treeview_elements_implements, class TExtends = treeview_elements_extends>
class _EXPORT_CLASS treeview_elementst: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    treeview_elementst
    (const treeview_element_t* detached = 0, bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~treeview_elementst() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef treeview_elementst<> treeview_elements_t;

///////////////////////////////////////////////////////////////////////
///  Class: treeviewt
///////////////////////////////////////////////////////////////////////
template
<class TImplements, class TExtends,
 class TTreeViewAttached,
 typename TTreeViewUnattached = int,
 TTreeViewUnattached VTreeViewUnattached = 0>

class _EXPORT_CLASS treeviewt
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TTreeViewAttached treeview_attached_t;
    typedef TTreeViewUnattached treeview_unattached_t;
    enum { treeview_unattached = VTreeViewUnattached };

    using Extends::create_attached;
    using Extends::create_detached;
    using Extends::destroy_detached;
    using Extends::detach;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    treeviewt
    (treeview_attached_t detached = VTreeViewUnattached,
     bool is_created = false) {
    }
    virtual ~treeviewt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual treeview_attached_t create_attached
    (const treeview_elements_t& elements) {
        treeview_attached_t detached = create_attached(elements.attached_to());
        return detached;
    }
    virtual treeview_attached_t create_attached
    (const treeview_element_t* element) {
        treeview_attached_t detached = ((treeview_attached_t)treeview_unattached);
        if ((element)) {
            for (const treeview_element_t* e = element; e->type; ++e) {
                treeview_element_type_t t = e->type;
                switch (t) {
                case treeview_element_type_treeview: {
                    if ((detached = this->create_attached())) {
                        if ((detached == (create_detached(detached, ++e)))) {
                            break;
                        }
                        this->detach();
                        this->destroy_detached(detached);
                        detached = ((treeview_attached_t)treeview_unattached);
                    }
                    break; }
                default: {
                    return 0; }
                }
            }
        }
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual treeview_attached_t create_detached
    (const treeview_elements_t& elements) const {
        treeview_attached_t detached = create_detached(elements.attached_to());
        return detached;
    }
    virtual treeview_attached_t create_detached
    (const treeview_element_t* element) const {
        treeview_attached_t detached = ((treeview_attached_t)treeview_unattached);
        if ((element)) {
            for (const treeview_element_t* e = element; e->type; ++e) {
                treeview_element_type_t t = e->type;
                switch (t) {
                case treeview_element_type_treeview: {
                    if ((detached = this->create_detached())) {
                        if ((detached == (create_detached(detached, ++e)))) {
                            break;
                        }
                        this->destroy_detached(detached);
                        detached = ((treeview_attached_t)treeview_unattached);
                    }
                    break; }
                default: {
                    return 0; }
                }
            }
        }
        return detached;
    }
    virtual treeview_attached_t create_detached
    (treeview_attached_t detached, const treeview_element_t*& element) const {
        detached = ((treeview_attached_t)treeview_unattached);
        return detached;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace gui
} // namespace vedere 

#endif // _VEDERE_GUI_TREEVIEW_HPP 
