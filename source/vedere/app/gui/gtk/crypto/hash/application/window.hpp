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
///   Date: 8/28/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_GTK_CRYPTO_HASH_APPLICATION_WINDOW_HPP
#define _VEDERE_APP_GUI_GTK_CRYPTO_HASH_APPLICATION_WINDOW_HPP

#include "vedere/gui/gtk/application/window.hpp"
#include "vedere/app/gui/gtk/crypto/hash/application/dialog.hpp"

namespace vedere {
namespace gui {
namespace gtk {
namespace app {
namespace crypto {
namespace hash {
namespace application {

typedef gtk::application::window_implements window_implements;
typedef gtk::application::window window_extends;
///////////////////////////////////////////////////////////////////////
///  Class: window
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS window
: virtual public window_implements, public window_extends {
public:
    typedef window_implements Implements;
    typedef window_extends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    window() {
    }
    virtual ~window() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init() {
        bool success = true;
        widget_attached_t dialog_detached = 0;
        if ((dialog_detached = dialog_.create_attached_to())) {
            this->container_add(dialog_detached);
        }
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    dialog dialog_;
};

} // namespace application 
} // namespace hash 
} // namespace crypto 
} // namespace app 
} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_GTK_CRYPTO_HASH_APPLICATION_WINDOW_HPP 
