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
#ifndef VEDERE_GRAPHIC_IMAGE_TO_BYTES_FILTER_HPP
#define VEDERE_GRAPHIC_IMAGE_TO_BYTES_FILTER_HPP

#include "vedere/base/base.hpp"

namespace vedere {
namespace graphic {
namespace image {

///////////////////////////////////////////////////////////////////////
/// class to_bytes_filter
///////////////////////////////////////////////////////////////////////
class EXPORT_CLASS to_bytes_filter: virtual public implement {
public:
    typedef implement Implements;
    typedef to_bytes_filter Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void on_bgra_image_pixel_byte(byte_t* byte) {
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static Derives* get_the_instance() {
        Derives* the_instance = Derives::the_instance();
        return the_instance;
    }
protected:
    static Derives*& the_instance() {
        static Derives* the_instance = 0;
        return the_instance;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
}; /// class to_bytes_filter

///////////////////////////////////////////////////////////////////////
/// class to_bytes_filter_extend
///////////////////////////////////////////////////////////////////////
class EXPORT_CLASS to_bytes_filter_extend: virtual public to_bytes_filter, public extend {
public:
    typedef to_bytes_filter Implements;
    typedef extend Extends;
    typedef to_bytes_filter_extend Derives;

    ///////////////////////////////////////////////////////////////////////
    /// constructor / destructor
    ///////////////////////////////////////////////////////////////////////
    to_bytes_filter_extend(): the_old_instance_(0) {
        to_bytes_filter*& the_instance = Implements::the_instance();
        the_old_instance_ = the_instance;
        the_instance = this;
    }
    virtual ~to_bytes_filter_extend() {
        to_bytes_filter*& the_instance = Implements::the_instance();
        if ((this == the_instance)) {
            the_instance = the_old_instance_;
            the_old_instance_ = 0;
        }
    }
private:
    to_bytes_filter_extend(const to_bytes_filter_extend& copy): the_old_instance_(0) {
    }
public:

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    to_bytes_filter* the_old_instance_;
}; /// class to_bytes_filter_extend

} /// namespace image 
} /// namespace graphic 
} /// namespace vedere 

#endif /// ndef VEDERE_GRAPHIC_IMAGE_TO_BYTES_FILTER_HPP 
