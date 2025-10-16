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
///   File: main_window.hpp
///
/// Author: $author$
///   Date: 5/29/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_QT_APPLICATION_MAIN_WINDOW_HPP
#define _VEDERE_GUI_QT_APPLICATION_MAIN_WINDOW_HPP

#include "vedere/gui/qt/gui.hpp"

namespace vedere {
namespace gui {
namespace qt {
namespace application {

typedef implement_base main_window_implements;
typedef QMainWindow main_window_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main_window
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main_window
: virtual public main_window_implements, public main_window_extends {
public:
    typedef main_window_implements Implements;
    typedef main_window_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main_window()
    : bg_color_
      (VEDERE_APP_GUI_QT_DEFAULT_BACKGROUND_RED,
       VEDERE_APP_GUI_QT_DEFAULT_BACKGROUND_GREEN,
       VEDERE_APP_GUI_QT_DEFAULT_BACKGROUND_BLUE) {
    }
    virtual ~main_window() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init() {
        return true;
    }
    virtual bool finish() {
        return true;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void resizeEvent(QResizeEvent *event) {
        Extends::resizeEvent(event);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    QColor bg_color_;
};

} // namespace application 
} // namespace qt 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_QT_APPLICATION_MAIN_WINDOW_HPP 
