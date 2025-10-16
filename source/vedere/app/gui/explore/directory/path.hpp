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
///   File: path.hpp
///
/// Author: $author$
///   Date: 6/29/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_EXPLORE_DIRECTORY_PATH_HPP
#define _VEDERE_APP_GUI_EXPLORE_DIRECTORY_PATH_HPP

#include "vedere/app/gui/explore/directory/entry.hpp"
#include "vedere/base/base.hpp"

#define VEDERE_APP_GUI_EXPLORE_DIRECTORY_PATH_SCHEME_SEPARATOR_CHARS "://"

namespace vedere {
namespace gui {
namespace app {
namespace explore {
namespace directory {

typedef xos::base::openert<entry_implements> path_implements;
///////////////////////////////////////////////////////////////////////
///  Class: patht
///////////////////////////////////////////////////////////////////////
template
<typename TChar = char,  typename TEnd = TChar, TEnd VEnd = 0,
 class TString = xos::base::stringt<TChar, TEnd, VEnd>,
 class TEntry = entryt<TChar, TEnd, VEnd>,
 class TImplements = path_implements>

class _EXPORT_CLASS patht: virtual public TImplements {
public:
    typedef TImplements Implements;

    typedef TEntry entry_t;
    typedef TString string_t;
    typedef TChar char_t;
    typedef TEnd end_t;
    enum { end = VEnd };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual patht* open(patht& root, const entry_t& parent) {
        return 0;
    }
    virtual bool open(const char_t* name) {
        return false;
    }
    virtual bool reopen() {
        return false;
    }
    virtual bool close() {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual entry_t* get_first_entry() {
        return 0;
    }
    virtual entry_t* get_next_entry() {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual patht* get(const char* scheme) const {
        return 0;
    }
    virtual patht* get_root() const {
        return 0;
    }
    virtual const char* name() const {
        return "";
    }
    virtual const char* scheme() const {
        return "";
    }
    virtual const char* scheme_separator() const {
        return VEDERE_APP_GUI_EXPLORE_DIRECTORY_PATH_SCHEME_SEPARATOR_CHARS;
    }
    virtual const char* separator() const {
        return "";
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static patht* get_default(const char* scheme) {
        patht* the_path = the_default();
        if ((the_path)) {
            return the_path->get(scheme);
        }
        return the_path;
    }
    static patht* get_default() {
        patht* the_path = the_default();
        return the_path;
    }
protected:
    static patht*& the_default() {
        static patht* the_path = 0;
        return the_path;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef patht<> path;

} // namespace directory
} // namespace explore 
} // namespace app 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_EXPLORE_DIRECTORY_PATH_HPP 
