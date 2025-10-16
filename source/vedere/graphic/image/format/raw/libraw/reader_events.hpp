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
///   File: reader_events.hpp
///
/// Author: $author$
///   Date: 2/24/2016
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_LIBRAW_READER_EVENTS_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_LIBRAW_READER_EVENTS_HPP

#include "vedere/graphic/image/format/raw/libraw/filter.hpp"
#include "lamna/graphic/image/format/raw/libraw/reader_events.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace raw {
namespace libraw {

typedef lamna::graphic::image::format::raw::libraw::rgb::reader_events reader_events_implements;
///////////////////////////////////////////////////////////////////////
///  Class: reader_eventst
///////////////////////////////////////////////////////////////////////
template <class TImplements = reader_events_implements>
class _EXPORT_CLASS reader_eventst: virtual public TImplements {
public:
    typedef TImplements Implements;
};
typedef reader_eventst<> reader_events;

} // namespace libraw 
} // namespace raw 
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_LIBRAW_READER_EVENTS_HPP 
