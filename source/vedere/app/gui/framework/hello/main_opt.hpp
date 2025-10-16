///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2020 $organization$
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
///   File: main_opt.hpp
///
/// Author: $author$
///   Date: 12/1/2020
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_FRAMEWORK_HELLO_MAIN_OPT_HPP
#define _VEDERE_APP_GUI_FRAMEWORK_HELLO_MAIN_OPT_HPP

#include "vedere/app/gui/hello/main.hpp"
#include "vedere/gui/framework/main.hpp"

namespace vedere {
namespace app {
namespace gui {
namespace framework {
namespace hello {

typedef gui::hello::main::Implements main_optt_implements;
typedef gui::hello::main main_optt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main_optt
///////////////////////////////////////////////////////////////////////
template <class TImplements = main_optt_implements, class TExtends = main_optt_extends>
class _EXPORT_CLASS main_optt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef main_optt Derives;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
private:
    main_optt(const main_optt &copy) {
    }
public:
    main_optt() {
    }
    virtual ~main_optt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS main_optt
typedef main_optt<> main_opt;

} /// namespace hello
} /// namespace framework
} /// namespace gui
} /// namespace app
} /// namespace vedere

#endif /// _VEDERE_APP_GUI_FRAMEWORK_HELLO_MAIN_OPT_HPP 
