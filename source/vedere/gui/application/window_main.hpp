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
///   File: window_main.hpp
///
/// Author: $author$
///   Date: 3/27/2016
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_APPLICATION_WINDOW_MAIN_HPP
#define _VEDERE_GUI_APPLICATION_WINDOW_MAIN_HPP

#include "vedere/gui/application/main.hpp"

namespace vedere {
namespace gui {
namespace application {

typedef application::main_implements window_main_implements;
typedef application::main window_main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: window_maint
///////////////////////////////////////////////////////////////////////
template
<class TImplements = window_main_implements, class TExtends = window_main_extends>

class _EXPORT_CLASS window_maint: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    window_maint() {
    }
    virtual ~window_maint() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef window_maint<> window_main;

} // namespace application
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_APPLICATION_WINDOW_MAIN_HPP 
