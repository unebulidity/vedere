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
///   File: icon_set.hpp
///
/// Author: $author$
///   Date: 10/8/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_ICON_SET_HPP
#define _VEDERE_GUI_GTK_ICON_SET_HPP

#include "vedere/gui/gtk/gtk.hpp"
#include "lamna/gui/glib/boxed.hpp"
#include "vedere/io/logger.hpp"

namespace vedere {
namespace gui {
namespace gtk {

typedef GtkIconSet* icon_set_attached_t;
typedef xos::base::creatort<lamna::gui::glib::boxed_implements> icon_set_creator;
typedef xos::base::attachert<icon_set_attached_t, int, 0, icon_set_creator> icon_set_attacher;
typedef xos::base::attachedt<icon_set_attached_t, int, 0, icon_set_attacher, lamna::gui::glib::boxed> icon_set_attached;
typedef xos::base::createdt<icon_set_attached_t, int, 0, icon_set_attacher, icon_set_attached> icon_set_created;
typedef icon_set_attacher icon_set_implements;
typedef icon_set_created icon_set_extends;
///////////////////////////////////////////////////////////////////////
///  Class: icon_sett
///////////////////////////////////////////////////////////////////////
template
<class TImplements = icon_set_implements, class TExtends = icon_set_extends>

class _EXPORT_CLASS icon_sett: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef typename Extends::attached_t attached_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    icon_sett(attached_t detached = 0, bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~icon_sett() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create(GdkPixbuf* pixbuf) {
        attached_t detached = 0;
        if ((detached = create_attached(pixbuf))) {
            this->set_is_created();
            return true;
        }
        return false;
    }
    virtual bool destroy() {
        attached_t detached = 0;
        if ((detached = this->detach())) {
            if ((destroy_detached(detached))) {
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t create_attached(GdkPixbuf* pixbuf) {
        attached_t detached = 0;
        if ((this->destroyed())) {
            if ((detached = create_detached(pixbuf))) {
                this->attach(detached);
            }
        }
        return detached;
    }
    virtual attached_t create_detached(GdkPixbuf* pixbuf) const {
        attached_t detached = 0;
        if ((pixbuf)) {
            if (!(detached = gtk_icon_set_new_from_pixbuf(pixbuf))) {
                VEDERE_LOG_ERROR("fained 0 == gtk_icon_set_new_from_pixbuf()");
            }
        }
        return detached;
    }
    virtual bool destroy_detached(attached_t detached) const {
        if ((detached)) {
            gtk_icon_set_unref(detached);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual operator attached_t () const {
        return this->attached_to();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef icon_sett<> icon_set;

} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_ICON_SET_HPP 
