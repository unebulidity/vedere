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
///   File: menu_shell.hpp
///
/// Author: $author$
///   Date: 8/24/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_MENU_SHELL_HPP
#define _VEDERE_GUI_GTK_MENU_SHELL_HPP

#include "vedere/gui/gtk/container.hpp"

namespace vedere {
namespace gui {
namespace gtk {

typedef container_implements menu_shell_implements;
typedef container menu_shell_extends;
///////////////////////////////////////////////////////////////////////
///  Class: menu_shellt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = menu_shell_implements, class TExtends = menu_shell_extends>

class _EXPORT_CLASS menu_shellt: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    menu_shellt
    (widget_attached_t detached = 0, bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~menu_shellt() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef menu_shellt<> menu_shell;

} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_MENU_SHELL_HPP 
