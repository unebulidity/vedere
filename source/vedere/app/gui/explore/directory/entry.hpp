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
///   File: entry.hpp
///
/// Author: $author$
///   Date: 6/29/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_EXPLORE_DIRECTORY_ENTRY_HPP
#define _VEDERE_APP_GUI_EXPLORE_DIRECTORY_ENTRY_HPP

#include "vedere/app/gui/explore/entry.hpp"

namespace vedere {
namespace gui {
namespace app {
namespace explore {
namespace directory {

typedef explore::entry_implements entry_implements;
///////////////////////////////////////////////////////////////////////
///  Class: entryt
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char, typename TEnd = TChar, TEnd VEnd = 0,
 class TString = xos::base::stringt<TChar, TEnd, VEnd>,
 class TExtends = explore::entryt<TChar, TEnd, VEnd>,
 class TImplements = entry_implements>

class _EXPORT_CLASS entryt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef TString string_t;
    typedef TChar char_t;
    typedef TEnd end_t;
    enum { end = VEnd };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    entryt() {
    }
    virtual ~entryt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* set_path(const char* to, size_t length) {
        path_.clear();
        path_.append(to, length);
        return path_.chars();
    }
    virtual const char* set_path(const char* to) {
        path_.clear();
        path_.append(to);
        return path_.chars();
    }
    virtual const char* path(size_t& length) const {
        return path_.chars(length);
    }
    virtual const char* path() const {
        return path_.chars();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    xos::base::string path_;
};
typedef entryt<> entry;

} // namespace directory
} // namespace explore 
} // namespace app 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_EXPLORE_DIRECTORY_ENTRY_HPP 
