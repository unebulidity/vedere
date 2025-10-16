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
///   File: rectangle.hpp
///
/// Author: $author$
///   Date: 10/25/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_RECTANGLE_HPP
#define _VEDERE_GRAPHIC_RECTANGLE_HPP

#include "vedere/base/base.hpp"

namespace vedere {
namespace graphic {

namespace surface {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template <typename TNumber>
struct pointt {
    TNumber x, y;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    pointt(TNumber _x, TNumber _y) : x(_x), y(_y) { }
    pointt() : x(0), y(0) { }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef pointt<int> point_t;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template <typename TNumber>
struct sizet {
    TNumber width, height;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    sizet(TNumber _width, TNumber _height) : width(_width), height(_height) { }
    sizet() : width(0), height(0) { }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef sizet<int> size_t;

} // namespace surface

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
template
<typename TNumber,
 typename TPoint = surface::pointt<TNumber>,
 typename TSize = surface::sizet<TNumber> >

struct rectanglet {
    TPoint origin;
    TSize size;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    rectanglet(const TSize& fromSize, const TSize& toSize): origin(0,0), size(0,0) {
        resize(fromSize, toSize);
    }
    rectanglet(int nx, int ny, int nw, int nh): origin(nx, ny), size(nw, nh) { }
    rectanglet(): origin(0,0), size(0,0) { }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    rectanglet& resize(const TSize& fromSize, const TSize& toSize) {
        return resize(*this, fromSize, toSize);
    }
    rectanglet& normalize(const TSize& fromSize, const TSize& toSize) {
        return normalize(*this, fromSize, toSize);
    }
    rectanglet& normalize(const TSize& toSize) {
        return normalize(*this, toSize);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static rectanglet& resize
    (rectanglet& rect, const TSize& fromSize, const TSize& toSize) {
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
    static rectanglet& normalize
    (rectanglet& rect, const TSize& fromSize, const TSize& toSize) {
        resize(rect, fromSize, toSize);
        normalize(rect, toSize);
        return rect;
    }
    static rectanglet& normalize
    (rectanglet& rect, const TSize& toSize) {
        rect.origin.x /= toSize.width; rect.origin.y /= toSize.height;
        rect.size.width /= toSize.width; rect.size.height /= toSize.height;
        return rect;
    }
};
typedef rectanglet<int, surface::point_t, surface::size_t> rectangle_t;

} // namespace graphic
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_RECTANGLE_HPP 
