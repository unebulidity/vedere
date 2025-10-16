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
#ifndef _VEDERE_GUI_SIZE_HPP
#define _VEDERE_GUI_SIZE_HPP

#include "vedere/base/base.hpp"

namespace vedere {
namespace gui {

typedef implement sizet_implements;
typedef extend sizet_extends;
///////////////////////////////////////////////////////////////////////
///  Class: sizet
///////////////////////////////////////////////////////////////////////
template <typename TNumber = int, class TImplements = sizet_implements, class TExtends = sizet_extends>
class _EXPORT_CLASS sizet: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef sizet Derives;
    
    TNumber width, height;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    sizet(const Derives &copy) : width(copy.width), height(copy.height) {
    }
    sizet(const TNumber& w, const TNumber& h): width(w), height(h) {
    }
    sizet(): width(0), height(0) {
    }
    virtual ~sizet() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    Derives& normalize(const Derives& to) {
        return normalize(*this, to);
    }
    static Derives& normalize(Derives& from, const Derives& to) {
        from.width /= to.width; from.height /= to.height;
        return from;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS sizet
typedef sizet<> size;

} /// namespace gui
} /// namespace vedere

#endif /// _VEDERE_GUI_SIZE_HPP
