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
///   File: double_window.hpp
///
/// Author: $author$
///   Date: 10/3/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_FL_DOUBLE_WINDOW_HPP
#define _VEDERE_GUI_FL_DOUBLE_WINDOW_HPP

#include "vedere/gui/fl/fl.hpp"

namespace vedere {
namespace gui {
namespace fl {

typedef lamna::gui::fl::widget_implements double_window_implements;
typedef lamna::gui::fl::widgett
<Fl_Window, double_window_implements> double_window_extends;
///////////////////////////////////////////////////////////////////////
///  Class: double_windowt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = double_window_implements, class TExtends = double_window_extends>

class _EXPORT_CLASS double_windowt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    double_windowt(int width, int height): Extends(width, height) {
    }
    virtual ~double_windowt() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef double_windowt<> double_window;

} // namespace fl 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_FL_DOUBLE_WINDOW_HPP 
