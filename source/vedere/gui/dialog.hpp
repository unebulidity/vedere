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
///   File: dialog.hpp
///
/// Author: $author$
///   Date: 8/27/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_DIALOG_HPP
#define _VEDERE_GUI_DIALOG_HPP

#include "vedere/io/logger.hpp"
#include <list>

namespace vedere {
namespace gui {

enum dialog_element_type_t {
    dialog_element_type_none,
    dialog_element_type_dialog,
    dialog_element_type_row,
    dialog_element_type_text,
    dialog_element_type_edit,
    dialog_element_type_progress,
};
typedef int dialog_element_style_t;
enum {
    dialog_element_style_none = 0,
    dialog_element_style_span_size = (1 << 0),
    next_dialog_element_style,
    last_dialog_element_style = (next_dialog_element_style - 1),

    dialog_element_edit_style = (last_dialog_element_style << 1),
    dialog_element_edit_style_readonly  = (dialog_element_edit_style << 0),
    dialog_element_edit_style_invisible = (dialog_element_edit_style << 1),
    dialog_element_edit_style_multiline = (dialog_element_edit_style << 2),
    next_dialog_element_edit_style,
    last_dialog_element_edit_style = (next_dialog_element_edit_style - 1),
};
typedef int dialog_element_id_t;
typedef const char* dialog_element_label_t;
struct dialog_element_size_t {
    int width, height;
};
struct dialog_element_t {
    dialog_element_type_t type;
    dialog_element_id_t id;
    dialog_element_label_t label;
    dialog_element_style_t style;
    dialog_element_size_t size;
};

typedef const dialog_element_t* dialog_elements_attached_t;
typedef xos::base::creatort<implement_base> dialog_elements_creator;
typedef xos::base::attachert<dialog_elements_attached_t, int, 0, dialog_elements_creator> dialog_elements_attacher;
typedef xos::base::attachedt<dialog_elements_attached_t, int, 0, dialog_elements_attacher, base> dialog_elements_attached;
typedef xos::base::createdt<dialog_elements_attached_t, int, 0, dialog_elements_attacher, dialog_elements_attached> dialog_elements_created;
typedef dialog_elements_attacher dialog_elements_implements;
typedef dialog_elements_created dialog_elements_extends;
///////////////////////////////////////////////////////////////////////
///  Class: dialog_elementst
///////////////////////////////////////////////////////////////////////
template
<class TImplements = dialog_elements_implements, class TExtends = dialog_elements_extends>
class _EXPORT_CLASS dialog_elementst: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    dialog_elementst
    (const dialog_element_t* detached = 0, bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~dialog_elementst() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef dialog_elementst<> dialog_elements_t;

typedef implement_base dialog_item_implements;
typedef base dialog_item_extends;
///////////////////////////////////////////////////////////////////////
///  Class: dialog_itemt
///////////////////////////////////////////////////////////////////////
template
<typename TAttached,
 typename TUnattached = int, TUnattached VUnattached = 0,
 class TImplements = dialog_item_implements,
 class TExtends = dialog_item_extends>

class _EXPORT_CLASS dialog_itemt
: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TAttached attached_t;
    typedef TUnattached unattached_t;
    enum { unattached = VUnattached };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    dialog_itemt(dialog_element_id_t id, attached_t attached)
    : id_(id), attached_(attached) {
    }
    dialog_itemt(const dialog_itemt& copy)
    : id_(copy.id_), attached_(copy.attached_) {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual dialog_element_id_t id() const {
        return (dialog_element_id_t)id_;
    }
    virtual attached_t attached() const {
        return (attached_t)attached_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    dialog_element_id_t id_;
    attached_t attached_;
};

///////////////////////////////////////////////////////////////////////
///  Class: dialogt
///////////////////////////////////////////////////////////////////////
template
<class TImplements, class TExtends, typename TAttached,
 typename TRowsAttached = TAttached, typename TRowAttached = TAttached,
 typename TUnattached = int, TUnattached VUnattached = 0>

class _EXPORT_CLASS dialogt: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef dialog_itemt
    <TAttached, TUnattached, VUnattached> dialog_item_t;
    typedef std::list<dialog_item_t> dialog_items_t;

    typedef TAttached attached_t;
    typedef TRowsAttached rows_attached_t;
    typedef TRowAttached row_attached_t;
    typedef TUnattached unattached_t;
    enum { unattached = VUnattached };

    using Extends::create_attached;
    using Extends::create_detached;
    using Extends::destroy_detached;
    using Extends::detach;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    dialogt
    (TAttached detached = ((attached_t)unattached),
     bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~dialogt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t create_attached
    (dialog_items_t& items, const dialog_elements_t& elements) {
        attached_t detached = create_attached(items, elements.attached_to());
        return detached;
    }
    virtual attached_t create_attached
    (dialog_items_t& items, const dialog_element_t* element) {
        attached_t detached = ((attached_t)unattached);
        if ((element)) {
            for (const dialog_element_t* e = element; e->type; ++e) {
                dialog_element_type_t t = e->type;
                switch (t) {
                case dialog_element_type_dialog: {
                    if ((detached = this->create_attached())) {
                        if (((create_detached(items, detached, ++e)))) {
                            break;
                        }
                        this->detach();
                        this->destroy_detached(detached);
                        detached = ((attached_t)unattached);
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
    virtual attached_t create_detached
    (dialog_items_t& items, const dialog_elements_t& elements) const {
        attached_t detached = create_detached
        (items, elements.attached_to());
        return detached;
    }
    virtual attached_t create_detached
    (dialog_items_t& items, const dialog_element_t* element) const {
        attached_t detached = ((attached_t)unattached);
        if ((element)) {
            for (const dialog_element_t* e = element; e->type; ++e) {
                dialog_element_type_t t = e->type;
                switch (t) {
                case dialog_element_type_dialog: {
                    if ((detached = this->create_detached())) {
                        if (((create_detached(items, detached, ++e)))) {
                            break;
                        }
                        this->destroy_detached(detached);
                        detached = ((attached_t)unattached);
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
    virtual attached_t create_detached
    (dialog_items_t& items, attached_t detached, const dialog_element_t*& element) const {
        if ((detached)) {
            if ((element)) {
                rows_attached_t rows = ((rows_attached_t)unattached);
                if ((rows = create_rows_detached(items, detached))) {
                    int rownum = 0;
                    for (const dialog_element_t*& e = element; e->type; ++e) {
                        int rowspan = 1;
                        dialog_element_type_t t = e->type;
                        switch (t) {
                        case dialog_element_type_row: {
                            VEDERE_LOG_MESSAGE_DEBUG("dialog_element_type_row = " << t << "...");
                            if (!(create_row_detached(items, rowspan, rownum, rows, detached, ++e))) {
                                return 0;
                            }
                            VEDERE_LOG_MESSAGE_DEBUG("...dialog_element_type_row = " << t << "");
                            break; }
                        default: {
                            VEDERE_LOG_ERROR("invalid dialog_element_type_t t = " << t << "");
                            return 0; }
                        }
                        rownum += rowspan;
                    }
                }
            }
        }
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t create_row_detached
    (dialog_items_t& items, int& rowspan, int& rownum, rows_attached_t rows,
     attached_t detached, const dialog_element_t*& element) const {
        if ((detached)) {
            if ((element)) {
                row_attached_t row = ((row_attached_t)unattached);
                if ((row = create_row_detached(items, rownum, rows, detached))) {
                    int colnum = 0;
                    for (const dialog_element_t*& e = element; e->type; ++e) {
                        dialog_element_type_t t = e->type;
                        switch (t) {
                        case dialog_element_type_text: {
                            VEDERE_LOG_MESSAGE_DEBUG("dialog_element_type_text = " << t << "...");
                            if (!(create_text_col_detached
                                  (items, rownum, colnum, row, rows, detached, e))) {
                                return 0;
                            }
                            VEDERE_LOG_MESSAGE_DEBUG("...dialog_element_type_text = " << t << "");
                            break; }
                        case dialog_element_type_edit: {
                            VEDERE_LOG_MESSAGE_DEBUG("dialog_element_type_edit = " << t << "...");
                            if (!(create_edit_col_detached
                                  (items, rownum, colnum, row, rows, detached, e))) {
                                return 0;
                            }
                            VEDERE_LOG_MESSAGE_DEBUG("...dialog_element_type_edit = " << t << "");
                            break; }
                        case dialog_element_type_progress: {
                            VEDERE_LOG_MESSAGE_DEBUG("dialog_element_type_progress = " << t << "...");
                            if (!(create_progress_col_detached
                                  (items, rownum, colnum, row, rows, detached, e))) {
                                return 0;
                            }
                            VEDERE_LOG_MESSAGE_DEBUG("...dialog_element_type_progress = " << t << "");
                            break; }
                        default: {
                            VEDERE_LOG_ERROR("invalid dialog_element_type_t t = " << t << "");
                            return 0; }
                        }
                        if ((dialog_element_style_span_size & e->style)) {
                            colnum += (e->size.width);
                            if (rowspan < (e->size.height)) {
                                rowspan = (e->size.height);
                            }
                        } else {
                            ++colnum;
                        }
                    }
                }
            }
        }
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual rows_attached_t create_rows_detached
    (dialog_items_t& items, attached_t detached) const {
        VEDERE_LOG_ERROR("not implemented");
        return 0;
    }
    virtual row_attached_t create_row_detached
    (dialog_items_t& items, int& rownum,
     rows_attached_t rows, attached_t detached) const {
        VEDERE_LOG_ERROR("not implemented");
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t create_text_col_detached
    (dialog_items_t& items, int& rownum, int& colnum,
     row_attached_t row, rows_attached_t rows,
     attached_t detached, const dialog_element_t*& element) const {
        VEDERE_LOG_ERROR("not implemented");
        return 0;
    }
    virtual attached_t create_edit_col_detached
    (dialog_items_t& items, int& rownum, int& colnum,
     row_attached_t row, rows_attached_t rows,
     attached_t detached, const dialog_element_t*& element) const {
        VEDERE_LOG_ERROR("not implemented");
        return 0;
    }
    virtual attached_t create_progress_col_detached
    (dialog_items_t& items, int& rownum, int& colnum,
     row_attached_t row, rows_attached_t rows,
     attached_t detached, const dialog_element_t*& element) const {
        VEDERE_LOG_ERROR("not implemented");
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t get_item_attached
    (const dialog_items_t& items, dialog_element_id_t id) const {
        attached_t detached = 0;
        for (typename dialog_items_t::const_iterator i = items.begin(); i != items.end(); ++i) {
            const dialog_item_t& item = *i;
            if (!(item.id() != id)) {
                detached = item.attached();
                break;
            }
        }
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const dialog_element_t* get_element
    (dialog_element_id_t id, const dialog_element_t*& e) const {
        dialog_element_type_t t;
        for (; dialog_element_type_none != (t = e->type); ++e) {
            switch(t) {
            case dialog_element_type_dialog:
            case dialog_element_type_row: {
                const dialog_element_t* found;
                if ((found = get_element(id, ++e))) {
                    return found;
                }
                break; }
            default:
                if ((id == e->id)) {
                    return e;
                }
                break;
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace gui
} // namespace vedere 

#endif // _VEDERE_GUI_DIALOG_HPP 
