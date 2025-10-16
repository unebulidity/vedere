///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2021 $organization$
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
///   File: context.hpp
///
/// Author: $author$
///   Date: 1/4/2021
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_OPENGL_CONTEXT_HPP
#define _VEDERE_GUI_OPENGL_CONTEXT_HPP

#include "vedere/gui/opengl/gl.hpp"

namespace vedere {
namespace gui {
namespace opengl {

class _EXPORT_CLASS context_implemented;

typedef implement context_implements;
typedef extend context_extends;
///////////////////////////////////////////////////////////////////////
///  Class: context
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS context: virtual public context_implements, public context_extends {
public:
    typedef context_implements Implements;
    typedef context_extends Extends;
    typedef context Derives;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
private:
    context(const context &copy) {
    }
public:
    context() {
    }
    virtual ~context() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool initialize(context_implemented& implement) {
        return true;
    }
    virtual bool finalize(context_implemented& implement) {
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS context

} /// namespace opengl
} /// namespace gui
} /// namespace vedere

#endif /// _VEDERE_GUI_OPENGL_CONTEXT_HPP
