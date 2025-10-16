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
///   File: text_view.hpp
///
/// Author: $author$
///   Date: 8/30/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_TEXT_VIEW_HPP
#define _VEDERE_GUI_GTK_TEXT_VIEW_HPP

#include "vedere/gui/gtk/container.hpp"

namespace vedere {
namespace gui {
namespace gtk {

typedef container_implements text_view_implements;
typedef container text_view_extends;
///////////////////////////////////////////////////////////////////////
///  Class: text_viewt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = text_view_implements, class TExtends = text_view_extends>

class _EXPORT_CLASS text_viewt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    text_viewt
    (widget_attached_t detached = 0, bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~text_viewt() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual widget_attached_t create_detached() const {
        widget_attached_t detached = 0;
        if (!(detached = gtk_text_view_new())) {
            VEDERE_LOG_ERROR("failed 0 == gtk_text_view_new()");
        }
        return detached;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef text_viewt<> text_view;

} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_TEXT_VIEW_HPP 
