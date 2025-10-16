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
///   File: window.hpp
///
/// Author: $author$
///   Date: 8/23/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_SCROLLED_WINDOW_HPP
#define _VEDERE_GUI_GTK_SCROLLED_WINDOW_HPP

#include "vedere/gui/gtk/widget.hpp"

namespace vedere {
namespace gui {
namespace gtk {
namespace scrolled {

typedef widget_implements window_implements;
typedef widget window_extends;
///////////////////////////////////////////////////////////////////////
///  Class: windowt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = window_implements, class TExtends = window_extends>

class _EXPORT_CLASS windowt: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    windowt() {
    }
    virtual ~windowt() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual widget_attached_t create_detached() const {
        widget_attached_t detached = create_detached(NULL, NULL);
        return detached;
    }
    virtual widget_attached_t create_detached
    (GtkAdjustment* hadjustment, GtkAdjustment* vadjustment) const {
        widget_attached_t detached = 0;
        if (!(detached = gtk_scrolled_window_new(hadjustment, vadjustment))) {
            VEDERE_LOG_ERROR("failed on gtk_scrolled_window_new()");
        }
        return detached;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef windowt<> window;

} // namespace scrolled
} // namespace gtk
} // namespace gui
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_SCROLLED_WINDOW_HPP
