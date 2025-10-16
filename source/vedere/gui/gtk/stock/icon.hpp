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
///   File: icon.hpp
///
/// Author: $author$
///   Date: 10/9/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_STOCK_ICON_HPP
#define _VEDERE_GUI_GTK_STOCK_ICON_HPP

#include "vedere/gui/gtk/icon_factory.hpp"
#include "vedere/gui/gtk/icon_set.hpp"
#include "vedere/gui/gdk/gdk.hpp"

namespace vedere {
namespace gui {
namespace gtk {
namespace stock {

enum icon_type {
    icon_type_none,
    icon_type_stock_id,
    icon_type_gdk_pixbuf
};

typedef icon_type icon_attached_t;
typedef xos::base::creatort<implement_base> icon_creator;
typedef xos::base::attachert<icon_attached_t, icon_type, icon_type_none, icon_creator> icon_attacher;
typedef xos::base::attachedt<icon_attached_t, icon_type, icon_type_none, icon_attacher, gstring> icon_attached;
typedef xos::base::createdt<icon_attached_t, icon_type, icon_type_none, icon_attacher, icon_attached> icon_created;
typedef icon_attacher icon_implements;
typedef icon_created icon_extends;
///////////////////////////////////////////////////////////////////////
///  Class: icont
///////////////////////////////////////////////////////////////////////
template
<class TImplements = icon_implements, class TExtends = icon_extends>

class _EXPORT_CLASS icont: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef typename Extends::attached_t attached_t;
    enum {unattached = Extends::unattached};

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    icont(attached_t detached = icon_type_none, bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~icont() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create
    (icon_factory& factory, icon_set& set,
     gdk::pixbuf& pixbuf, const char* filename,
     const gchar* stock_id, const gchar* default_stock_id = 0) {
        attached_t detached = ((attached_t)unattached);
        if ((detached = create_attached
             (factory, set, pixbuf, filename, stock_id, default_stock_id))) {
            this->set_is_created();
            return true;
        }
        return false;
    }
    virtual bool destroy() {
        attached_t detached = ((attached_t)unattached);
        if ((detached = this->detach())) {
            this->clear();
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t create_attached
    (icon_factory& factory, icon_set& set,
     gdk::pixbuf& pixbuf, const char* filename,
     const gchar* stock_id, const gchar* default_stock_id = 0) {
        if ((this->destroyed())) {
            attached_t detached = ((attached_t)unattached);
            if ((detached = create_detached
                 (factory, set, pixbuf, filename, stock_id, default_stock_id))) {
                switch(detached) {
                case icon_type_gdk_pixbuf:
                    this->assign(stock_id);
                    break;
                case icon_type_stock_id:
                default:
                    this->assign(default_stock_id);
                    break;
                }
                this->attach(detached);
                return detached;
            }
        }
        return ((attached_t)unattached);
    }
    virtual attached_t create_detached
    (icon_factory& factory, icon_set& set,
     gdk::pixbuf& pixbuf, const char* filename,
     const gchar* stock_id, const gchar* default_stock_id = 0) const {
        attached_t detached = ((attached_t)unattached);
        if ((filename) && (stock_id)) {
            if ((pixbuf.create(filename))) {
                if ((set.create(pixbuf))) {
                    if ((factory.create())) {
                        if ((factory.add(stock_id, set))) {
                            if ((factory.add_default())) {
                                detached = icon_type_gdk_pixbuf;
                            }
                        }
                        factory.destroy();
                    }
                    set.destroy();
                }
                pixbuf.destroy();
            }
        }
        if (!(detached)) {
            if ((default_stock_id) && (default_stock_id[0])) {
                detached = icon_type_stock_id;
            }
        }
        return detached;
    }
    virtual bool destroy_detached(attached_t detached) const {
        if ((detached)) {
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual operator const gchar* () const {
        return this->chars();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef icont<> icon;

} // namespace stock 
} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_STOCK_ICON_HPP 
