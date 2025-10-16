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
///   Date: 8/23/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_SCROLLED_TREEVIEW_HPP
#define _VEDERE_GUI_GTK_SCROLLED_TREEVIEW_HPP

#include "vedere/gui/gtk/treeview.hpp"
#include "vedere/gui/gtk/scrolled/window.hpp"

namespace vedere {
namespace gui {
namespace gtk {
namespace scrolled {

typedef gtk::treeview_implements treeview_implements;
typedef gtk::treeview treeview_extends;
///////////////////////////////////////////////////////////////////////
///  Class: treeviewt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = treeview_implements, class TExtends = treeview_extends>

class _EXPORT_CLASS treeviewt: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    using Extends::create_attached;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    treeviewt() {
    }
    virtual ~treeviewt() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual widget_attached_t create_attached() {
        if ((this->destroyed())) {
            widget_attached_t scrolled_detached = 0;
            if ((scrolled_detached = scrolled_.create_attached())) {
                widget_attached_t detached = 0;
                if ((detached = this->create_detached())) {
                    this->attach(detached);
                    gtk_container_add(GTK_CONTAINER(scrolled_detached), detached);
                    return detached;
                }
                scrolled_.destroy();
            }
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool container_add_to(widget_attached_t container) {
        if ((container)) {
            widget_attached_t detached = 0;
            if ((detached = scrolled_.attached_to())) {
                gtk_container_add(GTK_CONTAINER(container), detached);
                return true;
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    scrolled::window scrolled_;
};
typedef treeviewt<> treeview;

} // namespace scrolled 
} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_SCROLLED_TREEVIEW_HPP 
