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
///   File: icon_factory.hpp
///
/// Author: $author$
///   Date: 10/8/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_ICON_FACTORY_HPP
#define _VEDERE_GUI_GTK_ICON_FACTORY_HPP

#include "vedere/gui/gtk/icon_set.hpp"
#include "lamna/gui/glib/object.hpp"

namespace vedere {
namespace gui {
namespace gtk {

typedef GtkIconFactory* icon_factory_attached_t;
typedef xos::base::creatort<lamna::gui::glib::object_implements> icon_factory_creator;
typedef xos::base::attachert<icon_factory_attached_t, int, 0, icon_factory_creator> icon_factory_attacher;
typedef xos::base::attachedt<icon_factory_attached_t, int, 0, icon_factory_attacher, lamna::gui::glib::object> icon_factory_attached;
typedef xos::base::createdt<icon_factory_attached_t, int, 0, icon_factory_attacher, icon_factory_attached> icon_factory_created;
typedef icon_factory_attacher icon_factory_implements;
typedef icon_factory_created icon_factory_extends;
///////////////////////////////////////////////////////////////////////
///  Class: icon_factoryt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = icon_factory_implements, class TExtends = icon_factory_extends>

class _EXPORT_CLASS icon_factoryt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef typename Extends::attached_t attached_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    icon_factoryt(attached_t detached = 0, bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~icon_factoryt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create() {
        attached_t detached = 0;
        if ((detached = create_attached())) {
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
    virtual attached_t create_attached() {
        attached_t detached = 0;
        if ((this->destroyed())) {
            if ((detached = create_detached())) {
                this->attach(detached);
            }
        }
        return detached;
    }
    virtual attached_t create_detached() const {
        attached_t detached = 0;
        if (!(detached = gtk_icon_factory_new())) {
            VEDERE_LOG_ERROR("fained 0 == gtk_icon_factory_new()");
        }
        return detached;
    }
    virtual bool destroy_detached(attached_t detached) const {
        if ((detached)) {
            g_object_unref(detached);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool add(const gchar* stock_id, GtkIconSet* icon_set) {
        attached_t detached = 0;
        if ((detached = this->attached_to())) {
            if ((stock_id) && (icon_set)) {
                gtk_icon_factory_add
                (GTK_ICON_FACTORY(detached), stock_id, icon_set);
                return true;
            }
        }
        return false;
    }
    virtual bool add_default() {
        attached_t detached = 0;
        if ((detached = this->attached_to())) {
            gtk_icon_factory_add_default(GTK_ICON_FACTORY(detached));
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
typedef icon_factoryt<> icon_factory;

} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_ICON_FACTORY_HPP 
