///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   File: filter.hpp
///
/// Author: $author$
///   Date: 2/25/2016
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_LIBRAW_FILTER_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_LIBRAW_FILTER_HPP

#include "vedere/graphic/image/format/raw/libraw/libraw.hpp"
#include "lamna/graphic/image/format/raw/libraw/filter.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace raw {
namespace libraw {

typedef lamna::graphic::image::format::raw::libraw::rgb::filter_implements filter_implements;
typedef lamna::graphic::image::format::raw::libraw::rgb::filter filter_extends;
///////////////////////////////////////////////////////////////////////
///  Class: filtert
///////////////////////////////////////////////////////////////////////
template
<class TImplements = filter_implements, class TExtends = filter_extends>

class _EXPORT_CLASS filtert: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    filtert() {
    }
    virtual ~filtert() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef filtert<> filter;

} // namespace libraw 
} // namespace raw 
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_LIBRAW_FILTER_HPP
