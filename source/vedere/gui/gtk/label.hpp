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
///   File: label.hpp
///
/// Author: $author$
///   Date: 8/29/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_LABEL_HPP
#define _VEDERE_GUI_GTK_LABEL_HPP

#include "vedere/gui/gtk/misc.hpp"

namespace vedere {
namespace gui {
namespace gtk {

typedef misc_implements label_implements;
typedef misc label_extends;
///////////////////////////////////////////////////////////////////////
///  Class: labelt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = label_implements, class TExtends = label_extends>

class _EXPORT_CLASS labelt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    labelt
    (widget_attached_t detached = 0, bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~labelt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_justify(GtkJustification justify) {
        widget_attached_t detached = 0;
        if ((detached = this->attached_to())) {
            gtk_label_set_justify(GTK_LABEL(detached), justify);
            return true;
        }
        return false;
    }
    virtual bool get_justify(GtkJustification& justify) const {
        widget_attached_t detached = 0;
        if ((detached = this->attached_to())) {
            justify = gtk_label_get_justify(GTK_LABEL(detached));
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::create_attached;
    virtual widget_attached_t create_attached(const char* str) {
        widget_attached_t detached = 0;
        if ((detached = create_detached(str))) {
            this->attach(detached);
        }
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual widget_attached_t create_detached() const {
        widget_attached_t detached = 0;
        detached = create_detached(NULL);
        return detached;
    }
    virtual widget_attached_t create_detached(const char* str) const {
        widget_attached_t detached = 0;
        if (!(detached = gtk_label_new(str))) {
            VEDERE_LOG_ERROR("failed 0 == gtk_label_new(\"" << ((str)?(str):("")) << "\")");
        }
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef labelt<> label;

} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_LABEL_HPP 
