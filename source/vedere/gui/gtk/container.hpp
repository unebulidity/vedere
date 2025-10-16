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
///   File: container.hpp
///
/// Author: $author$
///   Date: 6/28/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_CONTAINER_HPP
#define _VEDERE_GUI_GTK_CONTAINER_HPP

#include "vedere/gui/gtk/widget.hpp"

namespace vedere {
namespace gui {
namespace gtk {

typedef widget_implements container_implements;
typedef widget container_extends;
///////////////////////////////////////////////////////////////////////
///  Class: containert
///////////////////////////////////////////////////////////////////////
template
<class TImplements = container_implements, class TExtends = container_extends>

class _EXPORT_CLASS containert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    containert
    (widget_attached_t detached = 0, bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~containert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool container_add(gtk::widget& widget) {
        widget_attached_t detached = widget.attached_to();
        if ((detached)) {
            return container_add(detached);
        }
        return false;
    }
    virtual bool container_add(widget_attached_t widget) {
        if ((widget)) {
            widget_attached_t detached = 0;
            if ((detached = this->attached_to())) {
                gtk_container_add(GTK_CONTAINER(detached), widget);
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef containert<> container;

} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_CONTAINER_HPP 
