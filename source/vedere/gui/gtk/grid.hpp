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
///   File: grid.hpp
///
/// Author: $author$
///   Date: 8/28/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_GRID_HPP
#define _VEDERE_GUI_GTK_GRID_HPP

#include "vedere/gui/gtk/container.hpp"

namespace vedere {
namespace gui {
namespace gtk {

typedef container_implements grid_implements;
typedef container grid_extends;
///////////////////////////////////////////////////////////////////////
///  Class: gridt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = grid_implements, class TExtends = grid_extends>

class _EXPORT_CLASS gridt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    gridt
    (widget_attached_t detached = 0, bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~gridt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::attach;
    virtual bool attach
    (GtkWidget* child, gint left, gint top, gint width, gint height) {
        widget_attached_t detached = 0;
        if ((detached = this->attached_to())) {
            gtk_grid_attach
            (GTK_GRID(detached), child, left,top, width,height);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual widget_attached_t create_detached() const {
        widget_attached_t detached = 0;
        if (!(detached = gtk_grid_new())) {
            VEDERE_LOG_ERROR("failed 0 == gtk_grid_new()");
        }
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef gridt<> grid;

} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_GRID_HPP 
