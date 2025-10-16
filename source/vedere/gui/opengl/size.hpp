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
///   File: size.hpp
///
/// Author: $author$
///   Date: 1/4/2021
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_OPENGL_SIZE_HPP
#define _VEDERE_GUI_OPENGL_SIZE_HPP

#include "vedere/gui/opengl/gl.hpp"
#include "vedere/gui/size.hpp"

namespace vedere {
namespace gui {
namespace opengl {

typedef gui::sizet<float> size_extends;
typedef size_extends::Implements size_implements;
///////////////////////////////////////////////////////////////////////
///  Class: size
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS size: virtual public size_implements, public size_extends {
public:
    typedef size_implements Implements;
    typedef size_extends Extends;
    typedef size Derives;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    size(const size &copy, const size &to): Extends(copy) {
        normalize(to);
    }
    size(const size &copy): Extends(copy) {
    }
    size(const float& width, const float& height): Extends(width, height) {
    }
    size(const int& width, const int& height): Extends(width, height) {
    }
    size(const unsigned& width, const unsigned& height): Extends(width, height) {
    }
    virtual ~size() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS size

} /// namespace opengl
} /// namespace gui
} /// namespace vedere

#endif /// _VEDERE_GUI_OPENGL_SIZE_HPP
