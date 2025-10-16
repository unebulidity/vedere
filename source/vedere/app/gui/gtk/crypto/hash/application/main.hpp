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
///   File: main.hpp
///
/// Author: $author$
///   Date: 8/28/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_GTK_CRYPTO_HASH_APPLICATION_MAIN_HPP
#define _VEDERE_APP_GUI_GTK_CRYPTO_HASH_APPLICATION_MAIN_HPP

#include "vedere/app/gui/gtk/crypto/hash/application/window.hpp"
#include "vedere/gui/gtk/application/window_main.hpp"
#include "vedere/gui/gtk/application/main.hpp"

namespace vedere {
namespace gui {
namespace gtk {
namespace app {
namespace crypto {
namespace hash {
namespace application {

typedef gtk::application::window_main_implements main_implements;
typedef gtk::application::window_main main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main: virtual public main_implements,public main_extends {
public:
    typedef main_implements Implements;
    typedef main_extends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main() {
    }
    virtual ~main() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual GtkWidget* create_main_window(GtkApplication *application) {
        GtkWidget* window_detached = 0;
        if ((window_detached = window_.create_attached(application))) {
            if ((window_.init())) {
            }
        }
        return window_detached;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    window window_;
};

} // namespace application
} // namespace hash
} // namespace crypto 
} // namespace app 
} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_GTK_CRYPTO_HASH_APPLICATION_MAIN_HPP
