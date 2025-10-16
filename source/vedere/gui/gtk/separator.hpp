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
///   File: separator.hpp
///
/// Author: $author$
///   Date: 8/24/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_SEPARATOR_HPP
#define _VEDERE_GUI_GTK_SEPARATOR_HPP

#include "vedere/gui/gtk/widget.hpp"

namespace vedere {
namespace gui {
namespace gtk {

typedef widget_implements separator_implements;
typedef widget separator_extends;
///////////////////////////////////////////////////////////////////////
///  Class: separatort
///////////////////////////////////////////////////////////////////////
template
<class TImplements = separator_implements, class TExtends = separator_extends>

class _EXPORT_CLASS separatort: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    separatort
    (GtkOrientation default_orientation,
     widget_attached_t detached = 0, bool is_created = false)
    : Extends(detached, is_created),
      default_orientation_(default_orientation) {
    }
    virtual ~separatort() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual widget_attached_t create_detached() const {
        GtkOrientation orientation = default_orientation_;
        widget_attached_t detached = create_detached(orientation);
        return detached;
    }
    virtual widget_attached_t create_detached(GtkOrientation orientation) const {
        widget_attached_t detached = 0;
        if (!(detached = gtk_separator_new(orientation))) {
            VEDERE_LOG_ERROR("failed 0 == gtk_separator_new(orientation = " << orientation << ")");
        }
        return detached;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    GtkOrientation default_orientation_;
};
typedef separatort<> separator;

namespace horizontal {
typedef gtk::separator_implements separator_implements;
typedef gtk::separator separator_extends;
///////////////////////////////////////////////////////////////////////
///  Class: separatort
///////////////////////////////////////////////////////////////////////
template
<class TImplements = separator_implements, class TExtends = separator_extends>

class _EXPORT_CLASS separatort: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    separatort
    (widget_attached_t detached = 0, bool is_created = false)
    : Extends(GTK_ORIENTATION_HORIZONTAL, detached, is_created) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef separatort<> separator;
} // namespace horizontal

namespace vertical {
typedef gtk::separator_implements separator_implements;
typedef gtk::separator separator_extends;
///////////////////////////////////////////////////////////////////////
///  Class: separatort
///////////////////////////////////////////////////////////////////////
template
<class TImplements = separator_implements, class TExtends = separator_extends>

class _EXPORT_CLASS separatort: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    separatort
    (widget_attached_t detached = 0, bool is_created = false)
    : Extends(GTK_ORIENTATION_VERTICAL, detached, is_created) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef separatort<> separator;
} // namespace vertical

} // namespace gtk
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_SEPARATOR_HPP 
