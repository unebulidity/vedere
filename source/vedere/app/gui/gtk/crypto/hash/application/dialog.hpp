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
///   File: dialog.hpp
///
/// Author: $author$
///   Date: 8/29/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_GTK_CRYPTO_HASH_APPLICATION_DIALOG_HPP
#define _VEDERE_APP_GUI_GTK_CRYPTO_HASH_APPLICATION_DIALOG_HPP

#include "vedere/app/gui/crypto/hash/dialog.hpp"
#include "vedere/gui/gtk/dialog_box.hpp"

namespace vedere {
namespace gui {
namespace gtk {
namespace app {
namespace crypto {
namespace hash {
namespace application {

typedef dialog_box_implements dialog_implements;
typedef dialog_box dialog_extends;
///////////////////////////////////////////////////////////////////////
///  Class: dialog
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS dialog
: virtual public dialog_implements,public dialog_extends {
public:
    typedef dialog_implements Implements;
    typedef dialog_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    dialog
    (widget_attached_t detached = 0, bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~dialog() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::create_attached;
    virtual widget_attached_t create_attached_to() {
        widget_attached_t detached = 0;
        detached = this->create_attached
        (items_, gui::app::crypto::hash::dialog_entry);
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    dialog_items_t items_;
};

} // namespace application 
} // namespace hash 
} // namespace crypto 
} // namespace app 
} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_GTK_CRYPTO_HASH_APPLICATION_DIALOG_HPP 
