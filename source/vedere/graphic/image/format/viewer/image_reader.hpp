///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2020 $organization$
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
///   File: image_reader.hpp
///
/// Author: $author$
///   Date: 12/25/2020
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_IMAGE_READER_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_IMAGE_READER_HPP

#include "vedere/graphic/image/to_bytes_reader.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace viewer {

typedef to_bytes_reader image_reader_implements;
///////////////////////////////////////////////////////////////////////
///  Class: image_reader
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS image_reader: virtual public image_reader_implements {
public:
    typedef image_reader_implements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual byte_t* detach_image
    (size_t& image_width, size_t& image_height,
     size_t& image_depth, size_t& image_size) {
        return 0;
    }
    virtual byte_t* alloc_image
    (size_t image_width, size_t image_height,
     size_t image_depth, size_t image_size) {
        return 0;
    }
    virtual void free_image() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool read_image(const char* filename) {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS image_reader

///////////////////////////////////////////////////////////////////////
///  Class: image_readert
///////////////////////////////////////////////////////////////////////
template 
<class TToBytesReader = to_bytes_reader,
 class TImplements = image_reader, class TExtends = base>
class _EXPORT_CLASS image_readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef image_readert Derives;
    
    typedef TToBytesReader to_bytes_reader_t;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    image_readert() {
    }
    virtual ~image_readert() {
    }
private:
    image_readert(const image_readert &copy) {
    }
public:

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual byte_t* detach_image
    (size_t& image_width, size_t& image_height,
     size_t& image_depth, size_t& image_size) {
        return to_bytes_reader_.detach_image(image_width, image_height, image_depth, image_size);
    }
    virtual byte_t* alloc_image
    (size_t image_width, size_t image_height,
     size_t image_depth, size_t image_size) {
        return to_bytes_reader_.alloc_image(image_width, image_height, image_depth, image_size);
    }
    virtual void free_image() {
        to_bytes_reader_.free_image();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool read_image(const char* filename) {
        return to_bytes_reader_.read(filename);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    to_bytes_reader_t to_bytes_reader_;
}; /// class _EXPORT_CLASS image_readert

} /// namespace viewer
} /// namespace format
} /// namespace image
} /// namespace graphic
} /// namespace vedere

#endif /// _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_IMAGE_READER_HPP
