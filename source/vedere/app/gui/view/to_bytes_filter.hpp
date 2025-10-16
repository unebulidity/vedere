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
///   File: to_bytes_filter.hpp
///
/// Author: $author$
///   Date: 1/19/2021
///////////////////////////////////////////////////////////////////////
#ifndef VEDERE_APP_GUI_VIEW_TO_BYTES_FILTER_HPP
#define VEDERE_APP_GUI_VIEW_TO_BYTES_FILTER_HPP

#include "vedere/graphic/image/to_bytes_filter.hpp"

namespace vedere {
namespace app {
namespace gui {
namespace view {

///////////////////////////////////////////////////////////////////////
/// class to_bytes_filter
///////////////////////////////////////////////////////////////////////
class EXPORT_CLASS to_bytes_filter: public graphic::image::to_bytes_filter_extend {
public:
    typedef graphic::image::to_bytes_filter_extend Extends;
    typedef to_bytes_filter Derives;

    ///////////////////////////////////////////////////////////////////////
    /// constructor / destructor
    ///////////////////////////////////////////////////////////////////////
    to_bytes_filter() {
    }
    virtual ~to_bytes_filter() {
    }
private:
    to_bytes_filter(const to_bytes_filter& copy) {
    }
public:

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void on_bgra_image_pixel_byte(byte_t* byte) {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
}; /// class to_bytes_filter

} /// namespace view 
} /// namespace gui 
} /// namespace app 
} /// namespace vedere 

#endif /// ndef VEDERE_APP_GUI_VIEW_TO_BYTES_FILTER_HPP 
