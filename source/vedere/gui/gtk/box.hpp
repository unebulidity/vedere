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
///   File: box.hpp
///
/// Author: $author$
///   Date: 8/24/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_BOX_HPP
#define _VEDERE_GUI_GTK_BOX_HPP

#include "vedere/gui/gtk/container.hpp"

#define VEDERE_GUI_GTK_BOX_DEFAULT_SPACING 0

namespace vedere {
namespace gui {
namespace gtk {

typedef container_implements box_implements;
typedef container box_extends;
///////////////////////////////////////////////////////////////////////
///  Class: boxt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = box_implements, class TExtends = box_extends>

class _EXPORT_CLASS boxt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    boxt
    (GtkOrientation orientation,
     widget_attached_t detached = 0, bool is_created = false)
    : Extends(detached, is_created),
      default_orientation_(orientation),
      default_spacing_(VEDERE_GUI_GTK_BOX_DEFAULT_SPACING) {
    }
    virtual ~boxt() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool pack_start
    (GtkWidget *child, gboolean expand = TRUE,
     gboolean fill = FALSE, guint padding = 0) {
        widget_attached_t detached = 0;
        if ((detached = this->attached_to())) {
            if ((child)) {
                gtk_box_pack_start
                (GTK_BOX(detached), child, expand, fill, padding);
                return true;
            }
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::create_attached;
    virtual widget_attached_t create_attached
    (GtkOrientation orientation, gint spacing) {
        widget_attached_t detached = 0;
        if ((detached = create_detached(orientation, spacing))) {
            this->attach(detached);
        }
        return detached;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual widget_attached_t create_detached() const {
        GtkOrientation orientation = default_orientation_;
        gint spacing = default_spacing_;
        return create_detached(orientation, spacing);
    }
    virtual widget_attached_t create_detached
    (GtkOrientation orientation, gint spacing) const {
        widget_attached_t detached = 0;
        if (!(detached = gtk_box_new(orientation, spacing))) {
            VEDERE_LOG_ERROR("failed 0 == gtk_box_new(orientation = " << orientation << ", spacing = " << spacing << ")");
        }
        return detached;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    GtkOrientation default_orientation_;
    gint default_spacing_;
};
typedef boxt<> box;

namespace horizontal {
typedef gtk::box_implements box_implements;
typedef gtk::box box_extends;
///////////////////////////////////////////////////////////////////////
///  Class: boxt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = box_implements, class TExtends = box_extends>

class _EXPORT_CLASS boxt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    boxt
    (widget_attached_t detached = 0, bool is_created = false)
    : Extends(GTK_ORIENTATION_HORIZONTAL, detached, is_created) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef boxt<> box;
} // namespace horizontal

namespace vertical {
typedef gtk::box_implements box_implements;
typedef gtk::box box_extends;
///////////////////////////////////////////////////////////////////////
///  Class: boxt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = box_implements, class TExtends = box_extends>

class _EXPORT_CLASS boxt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    boxt
    (widget_attached_t detached = 0, bool is_created = false)
    : Extends(GTK_ORIENTATION_VERTICAL, detached, is_created) {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef boxt<> box;
} // namespace vertical

} // namespace gtk
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_BOX_HPP 
