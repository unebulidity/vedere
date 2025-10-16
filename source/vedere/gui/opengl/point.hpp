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
///   File: point.hpp
///
/// Author: $author$
///   Date: 1/4/2021
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_OPENGL_POINT_HPP
#define _VEDERE_GUI_OPENGL_POINT_HPP

#include "vedere/gui/opengl/gl.hpp"
#include "vedere/gui/point.hpp"

namespace vedere {
namespace gui {
namespace opengl {

typedef gui::pointt<float> point_extends;
typedef point_extends::Implements point_implements;
///////////////////////////////////////////////////////////////////////
///  Class: point
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS point: virtual public point_implements, public point_extends {
public:
    typedef point_implements Implements;
    typedef point_extends Extends;
    typedef point Derives;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    point(const point &copy): Extends(copy) {
    }
    point(const float& x, const float& y): Extends(x,y) {
    }
    point(const int& x, const int& y): Extends(x,y) {
    }
    point(const unsigned& x, const unsigned& y): Extends(x,y) {
    }
    point() {
    }
    virtual ~point() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS point

} /// namespace opengl
} /// namespace gui
} /// namespace vedere

#endif /// _VEDERE_GUI_OPENGL_POINT_HPP
