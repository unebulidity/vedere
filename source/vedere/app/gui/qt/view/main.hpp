///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   Date: 3/27/2016
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_QT_VIEW_MAIN_HPP
#define _VEDERE_APP_GUI_QT_VIEW_MAIN_HPP

#include "vedere/app/gui/view/main.hpp"
#include "vedere/gui/qt/application/window_main.hpp"
#include "vedere/graphic/image/format/png/libpng/image_reader.hpp"
#include "lamna/graphic/image/format/png/libpng/reader.hpp"

namespace vedere {
namespace app {
namespace gui {
namespace qt {
namespace view {

typedef vedere::gui::qt::application::window_main_implements main_implements;
typedef vedere::app::gui::view::maint
<main_implements, vedere::gui::qt::application::window_main> main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main: virtual public main_implements, public main_extends {
public:
    typedef main_implements Implements;
    typedef main_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main() {
    }
    virtual ~main() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int run(int argc, char** argv, char** env) {
        int err = 0;
        const char* chars = 0;
        if ((chars = this->image_file_.has_chars())) {
            vedere::graphic::image::format::png::libpng::image_reader r;
            r.read(chars);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace view 
} // namespace qt 
} // namespace gui 
} // namespace app 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_QT_VIEW_MAIN_HPP 
