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
#ifndef _VEDERE_GUI_POINT_HPP
#define _VEDERE_GUI_POINT_HPP

#include "vedere/base/base.hpp"

namespace vedere {
namespace gui {

typedef implement pointt_implements;
typedef extend pointt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: pointt
///////////////////////////////////////////////////////////////////////
template <typename TNumber = int, class TImplements = pointt_implements, class TExtends = pointt_extends>
class _EXPORT_CLASS pointt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef pointt Derives;
    
    TNumber x, y;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    pointt(const pointt &copy): x(copy.x), y(copy.y) {
    }
    pointt(const TNumber& nx, const TNumber& ny): x(nx), y(ny) {
    }
    pointt(): x(0), y(0) {
    }
    virtual ~pointt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS pointt
typedef pointt<> point;

} /// namespace gui
} /// namespace vedere

#endif /// _VEDERE_GUI_POINT_HPP
