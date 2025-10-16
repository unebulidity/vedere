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
///   File: editable.hpp
///
/// Author: $author$
///   Date: 8/29/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_EDITABLE_HPP
#define _VEDERE_GUI_GTK_EDITABLE_HPP

#include "vedere/gui/gtk/widget.hpp"

namespace vedere {
namespace gui {
namespace gtk {

typedef widget_attacher editablet_implements;
///////////////////////////////////////////////////////////////////////
///  Class: editablet
///////////////////////////////////////////////////////////////////////
template <class TImplements = editablet_implements>

class _EXPORT_CLASS editablet: virtual public TImplements {
public:
    typedef TImplements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_editable(gboolean is_true = TRUE) {
        widget_attached_t detached = 0;
        if ((detached = this->attached_to())) {
            gtk_editable_set_editable(GTK_EDITABLE(detached), is_true);
            return true;
        }
        return false;
    }
    virtual bool get_editable(gboolean& is_true) const {
        widget_attached_t detached = 0;
        if ((detached = this->attached_to())) {
            is_true = gtk_editable_get_editable(GTK_EDITABLE(detached));
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef editablet<> editable;

} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_EDITABLE_HPP 
