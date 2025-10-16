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
///   File: entry.hpp
///
/// Author: $author$
///   Date: 8/29/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_ENTRY_HPP
#define _VEDERE_GUI_GTK_ENTRY_HPP

#include "vedere/gui/gtk/editable.hpp"
#include "vedere/gui/gtk/widget.hpp"

namespace vedere {
namespace gui {
namespace gtk {

typedef editable entry_editable_implements;
typedef widget_implements entry_widget_implements;
///////////////////////////////////////////////////////////////////////
///  Class: entry_implements
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS entry_implements
: virtual public entry_editable_implements,
  virtual public entry_widget_implements {
public:
    typedef entry_editable_implements EditableImplements;
    typedef entry_widget_implements WidgetImplements;
};
typedef widget entry_extends;
///////////////////////////////////////////////////////////////////////
///  Class: entryt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = entry_implements, class TExtends = entry_extends>

class _EXPORT_CLASS entryt: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    entryt
    (widget_attached_t detached = 0, bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~entryt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_visibility(gboolean is_true = TRUE) {
        widget_attached_t detached = 0;
        if ((detached = this->attached_to())) {
            gtk_entry_set_visibility(GTK_ENTRY(detached), is_true);
            return true;
        }
        return false;
    }
    virtual bool get_visibility(gboolean& is_true) const {
        widget_attached_t detached = 0;
        if ((detached = this->attached_to())) {
            is_true = gtk_entry_get_visibility(GTK_ENTRY(detached));
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual widget_attached_t create_detached() const {
        widget_attached_t detached = 0;
        if (!(detached = gtk_entry_new())) {
            VEDERE_LOG_ERROR("failed 0 == gtk_entry_new()");
        }
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef entryt<> entry;

} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_ENTRY_HPP 
