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
///   File: error.hpp
///
/// Author: $author$
///   Date: 11/16/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_JPEG_LIBJPEG_ERROR_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_JPEG_LIBJPEG_ERROR_HPP

#include "vedere/graphic/image/format/jpeg/libjpeg/jpeg.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace jpeg {
namespace libjpeg {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum error_which_t {
    error_none,
    error_failed,

    next_error,
    first_error = error_none,
    last_error = next_error - 1,
    errors = last_error - first_error + 1
};

typedef implement_base error_implements;
typedef base error_extends;
///////////////////////////////////////////////////////////////////////
///  Class: errort
///////////////////////////////////////////////////////////////////////
template
<class TImplements = error_implements, class TExtends = error_extends>
class _EXPORT_CLASS errort: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    errort(error_which_t which = error_none): which_(which) {
    }
    errort(const errort& copy): which_(copy.which_) {
    }
    virtual ~errort() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual error_which_t which() const {
        return which_;
    }
    virtual operator error_which_t() const {
        return which_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    error_which_t which_;
};
typedef errort<> error;

} // namespace libjpeg
} // namespace jpeg 
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_JPEG_LIBJPEG_ERROR_HPP 
