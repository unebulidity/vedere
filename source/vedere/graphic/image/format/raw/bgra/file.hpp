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
///   File: file.hpp
///
/// Author: $author$
///   Date: 1/10/2021
///////////////////////////////////////////////////////////////////////
#ifndef VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_BGRA_FILE_HPP
#define VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_BGRA_FILE_HPP

#include "vedere/io/logger.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace raw {
namespace bgra {

///////////////////////////////////////////////////////////////////////
/// enum pixel_value_interpretation_t
///////////////////////////////////////////////////////////////////////
typedef int pixel_value_interpretation_t;
enum {
    pixel_value_interpretation_none = 0,

    pixel_value_interpretation_bgra, pixel_value_interpretation_rbga,

    pixel_value_interpretation_argb, pixel_value_interpretation_brga,

    pixel_value_interpretation_agrb, pixel_value_interpretation_grba,

    pixel_value_interpretation_gbra, pixel_value_interpretation_agbr,

    pixel_value_interpretation_bgr, pixel_value_interpretation_rgb,

    pixel_value_interpretation_gbr, pixel_value_interpretation_rbg,

    pixel_value_interpretation_brg, pixel_value_interpretation_grb,
    
    next_pixel_value_interpretation,
    first_pixel_value_interpretation = pixel_value_interpretation_none + 1,
    last_pixel_value_interpretation = next_pixel_value_interpretation + 1,
    pixel_value_interpretations = (last_pixel_value_interpretation - first_pixel_value_interpretation) + 1
}; /// enum typedef int pixel_value_interpretation_t

///////////////////////////////////////////////////////////////////////
/// class filet
///////////////////////////////////////////////////////////////////////
template <class TExtends = xos::io::read::byte_file, class TImplements = typename TExtends::Implements>
class EXPORT_CLASS filet: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef filet Derives;

    ///////////////////////////////////////////////////////////////////////
    /// constructor / destructor
    ///////////////////////////////////////////////////////////////////////
    filet() {
    }
    virtual ~filet() {
    }
private:
    filet(const filet& copy): Extends(copy) {
    }
public:

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class filet
typedef filet<> file;

} /// namespace bgra
} /// namespace raw
} /// namespace format
} /// namespace image
} /// namespace graphic
} /// namespace vedere

#endif /// ndef VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_BGRA_FILE_HPP 
