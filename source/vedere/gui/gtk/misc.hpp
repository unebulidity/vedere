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
///   File: misc.hpp
///
/// Author: $author$
///   Date: 8/29/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_MISC_HPP
#define _VEDERE_GUI_GTK_MISC_HPP

#include "vedere/gui/gtk/widget.hpp"

namespace vedere {
namespace gui {
namespace gtk {

typedef widget_implements misc_implements;
typedef widget misc_extends;
///////////////////////////////////////////////////////////////////////
///  Class: misct
///////////////////////////////////////////////////////////////////////
template
<class TImplements = misc_implements, class TExtends = misc_extends>

class _EXPORT_CLASS misct: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    misct
    (widget_attached_t detached = 0, bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~misct() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_alignment(gfloat xalign, gfloat yalign) {
        widget_attached_t detached = 0;
        if ((detached = this->attached_to())) {
            gtk_misc_set_alignment(GTK_MISC(detached), xalign, yalign);
            return true;
        }
        return false;
    }
    virtual bool get_alignment(gfloat& xalign, gfloat& yalign) const {
        widget_attached_t detached = 0;
        if ((detached = this->attached_to())) {
            gtk_misc_get_alignment(GTK_MISC(detached), &xalign, &yalign);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef misct<> misc;

} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_MISC_HPP 
