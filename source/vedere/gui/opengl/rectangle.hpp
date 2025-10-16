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
///   File: rectangle.hpp
///
/// Author: $author$
///   Date: 1/4/2021
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_OPENGL_RECTANGLE_HPP
#define _VEDERE_GUI_OPENGL_RECTANGLE_HPP

#include "vedere/gui/opengl/gl.hpp"
#include "vedere/gui/opengl/point.hpp"
#include "vedere/gui/opengl/size.hpp"
#include "vedere/gui/rectangle.hpp"

namespace vedere {
namespace gui {
namespace opengl {

typedef gui::rectanglet<float, point, size> rectangle_extends;
typedef rectangle_extends::Implements rectangle_implements;
///////////////////////////////////////////////////////////////////////
///  Class: rectangle
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS rectangle: virtual public rectangle_implements, public rectangle_extends {
public:
    typedef rectangle_implements Implements;
    typedef rectangle_extends Extends;
    typedef rectangle Derives;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    rectangle(const opengl::size& fromSize, const opengl::size& toSize): Extends(fromSize, toSize) {
        normalize(toSize);
    }
    rectangle(const rectangle &copy): Extends(copy) {
    }
    rectangle() {
    }
    virtual ~rectangle() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS rectangle

} /// namespace opengl
} /// namespace gui
} /// namespace vedere

#endif /// _VEDERE_GUI_OPENGL_RECTANGLE_HPP
