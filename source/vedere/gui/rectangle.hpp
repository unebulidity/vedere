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
#ifndef _VEDERE_GUI_RECTANGLE_HPP
#define _VEDERE_GUI_RECTANGLE_HPP

#include "vedere/gui/opengl/gl.hpp"
#include "vedere/gui/point.hpp"
#include "vedere/gui/size.hpp"

namespace vedere {
namespace gui {

typedef implement rectanglet_implements;
typedef extend rectanglet_extends;
///////////////////////////////////////////////////////////////////////
///  Class: rectanglet
///////////////////////////////////////////////////////////////////////
template 
<typename TNumber = int, typename TPoint = pointt<TNumber>, typename TSize = sizet<TNumber>,
 class TImplements = rectanglet_implements, class TExtends = rectanglet_extends>
class _EXPORT_CLASS rectanglet: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef rectanglet Derives;
    
    TPoint origin; TSize size;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    rectanglet(const TSize& fromSize, const TSize& toSize): origin(0,0), size(0,0) {
        resize(fromSize, toSize);
    }
    rectanglet(const rectanglet &copy): origin(copy.origin), size(copy.size) {
    }
    rectanglet(const TNumber& nx, const TNumber& ny, const TNumber& nw, const TNumber& nh): origin(nx, ny), size(nw, nh) {
    }
    rectanglet(): origin(0,0), size(0,0) {
    }
    virtual ~rectanglet() {
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Derives& resize(const TSize& fromSize, const TSize& toSize) {
        return resize(*this, fromSize, toSize);
    }
    Derives& normalize(const TSize& fromSize, const TSize& toSize) {
        return Normalize(*this, fromSize, toSize);
    }
    Derives& normalize(const TSize& toSize) {
        return normalize(*this, toSize);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static Derives& resize(Derives& rect, const TSize& fromSize, const TSize& toSize) {
        if (toSize.height < toSize.width) {
            if ((rect.size.width = (toSize.height * fromSize.width) / fromSize.height) > toSize.width) {
                rect.size.height = (toSize.width * fromSize.height) / fromSize.width;
                rect.size.width = toSize.width;
            } else {
                rect.size.height = toSize.height;
            }
        } else {
            if ((rect.size.height = (toSize.width * fromSize.height) / fromSize.width) > toSize.height) {
                rect.size.width = (toSize.height * fromSize.width) / fromSize.height;
                rect.size.height = toSize.height;
            } else {
                rect.size.width = toSize.width;
            }
        }
        rect.origin.x = (toSize.width - rect.size.width) / 2;
        rect.origin.y = (toSize.height - rect.size.height) / 2;
        return rect;
    }
    static Derives& normalize(Derives& rect, const TSize& fromSize, const TSize& toSize) {
        resize(rect, fromSize, toSize);
        normalize(rect, toSize);
        return rect;
    }
    static Derives& normalize(Derives& rect, const TSize& toSize) {
        rect.origin.x /= toSize.width; rect.origin.y /= toSize.height;
        rect.size.width /= toSize.width; rect.size.height /= toSize.height;
        return rect;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS rectanglet
typedef rectanglet<> rectangle;

} /// namespace gui
} /// namespace vedere

#endif /// _VEDERE_GUI_RECTANGLE_HPP
