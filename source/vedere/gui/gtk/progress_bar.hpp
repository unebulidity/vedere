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
///   File: progress_bar.hpp
///
/// Author: $author$
///   Date: 8/31/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_PROGRESS_BAR_HPP
#define _VEDERE_GUI_GTK_PROGRESS_BAR_HPP

#include "vedere/gui/gtk/widget.hpp"

namespace vedere {
namespace gui {
namespace gtk {

typedef widget_implements progress_bar_implements;
typedef widget progress_bar_extends;
///////////////////////////////////////////////////////////////////////
///  Class: progress_bart
///////////////////////////////////////////////////////////////////////
template
<class TImplements = progress_bar_implements,
 class TExtends = progress_bar_extends>

class _EXPORT_CLASS progress_bart
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    progress_bart
    (widget_attached_t detached = 0, bool is_created = false)
    : Extends(detached, is_created) {
    }
    virtual ~progress_bart() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual widget_attached_t create_detached() const {
        widget_attached_t detached = 0;
        if (!(detached = gtk_progress_bar_new())) {
            VEDERE_LOG_ERROR("failed 0 == gtk_progress_bar_new()");
        }
        return detached;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef progress_bart<> progress_bar;

} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_PROGRESS_BAR_HPP 
