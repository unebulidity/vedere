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
///   File: file.hpp
///
/// Author: $author$
///   Date: 12/9/2020
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_GIF_GIFLIB_FILE_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_GIF_GIFLIB_FILE_HPP

#include "vedere/graphic/image/format/gif/giflib/giflib.hpp"
#include "vedere/io/logger.hpp"
#include "xos/base/opened.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace gif {
namespace giflib {

typedef ::xos::base::openedt<GifFileType*> filet_extends;
typedef filet_extends::Implements filet_implements;
///////////////////////////////////////////////////////////////////////
///  Class: filet
///////////////////////////////////////////////////////////////////////
template <class TImplements = filet_implements, class TExtends = filet_extends>
class _EXPORT_CLASS filet: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef filet Derives;
    
    typedef typename Extends::attached_t attached_t;
    typedef typename Extends::unattached_t unattached_t;
    enum { unattached = Extends::unattached };
    typedef ::xos::base::open_exception open_exception;
    enum {close_failed = ::xos::base::close_failed };
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    filet(attached_t attached): Extends(attached) {
    }
    filet(const filet &copy): Extends(copy) {
    }
    filet() {
    }
    virtual ~filet() {
        if (!(this->closed())) {
            VEDERE_LOG_MESSAGE_ERROR("...failed on this->closed() throw open_exception(close_failed)...");
            throw open_exception(close_failed);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool open(const char* filename) {
        if ((this->open_attached(filename))) {
            return true;
        }
        return false;
    }
    virtual GifFileType* open_attached(const char* filename) {
        GifFileType* detached = 0;
        
        if ((detached = this->open_detached(filename))) {
            this->attach(detached);
            this->set_is_open();
        }
        return detached;
    }
    virtual bool close_attached(GifFileType* detached) {
        if ((detached) && (detached == (this->attached_to()))) {
            bool success = false;
            
            this->set_is_open(false);
            this->detach();
            success = this->close_detached(detached);
            return success;
        }
        return false;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual GifImageDesc* GetImageDesc() {
        GifFileType* detached = 0;

        if ((detached = this->attached_to())) {
            GifImageDesc* desc = 0;

            VEDERE_LOG_MESSAGE_DEBUG("::DGifGetImageDesc(detached = " << pointer_to_string(detached) << ")...");
            if (GIF_OK != (::DGifGetImageDesc(detached))) {
                VEDERE_LOG_MESSAGE_ERROR("...failed on ::DGifGetImageDesc(detached = " << pointer_to_string(detached) << ")");
                desc = 0;
            } else {
                VEDERE_LOG_MESSAGE_DEBUG("...::DGifGetImageDesc(detached = " << pointer_to_string(detached) << ")");
                desc = &detached->Image;
            }
            return desc;
        }
        return 0;
    }
    virtual TLENGTH GetLine(GifPixelType* line, int lineSize) {
        if ((line) && (0 <= lineSize)) {
            GifFileType* detached = 0;
    
            if ((detached = this->attached_to())) {
                TLENGTH count = 0;
    
                VEDERE_LOG_MESSAGE_DEBUG("::DGifGetLine(detached = " << pointer_to_string(detached) << ", line, lineSize)...");
                if (GIF_OK != (::DGifGetLine(detached, line, lineSize))) {
                    VEDERE_LOG_MESSAGE_ERROR("...failed on ::DGifGetLine(detached = " << pointer_to_string(detached) << ", line, lineSize)");
                    count = 0;
                } else {
                    VEDERE_LOG_MESSAGE_DEBUG("...::DGifGetLine(detached = " << pointer_to_string(detached) << ", line = " ", lineSize = " ")");
                    count = (TLENGTH)lineSize;
                }
                return count;
            }
        }
        return 0;
    }
    virtual GifByteType* GetExtension(int& extCode) {
        GifFileType* detached = 0;

        if ((detached = this->attached_to())) {
            GifByteType* extBytes = 0;

            VEDERE_LOG_MESSAGE_DEBUG("::DGifGetExtension(detached = " << pointer_to_string(detached) << ", &extCode, &extBytes)...");
            if (GIF_OK != (::DGifGetExtension(detached, &extCode, &extBytes))) {
                VEDERE_LOG_MESSAGE_ERROR("...failed on ::DGifGetExtension(detached = " << pointer_to_string(detached) << ", &extCode, &extBytes)");
                extBytes = 0;
            } else {
                VEDERE_LOG_MESSAGE_DEBUG("...::DGifGetExtension(detached = " << pointer_to_string(detached) << ", &extCode = " ", &extBytes = " << pointer_to_string(extBytes) << ")");
            }
            return extBytes;
        }
        return 0;
    }
    virtual GifByteType* GetExtensionNext() {
        GifFileType* detached = 0;

        if ((detached = this->attached_to())) {
            GifByteType* extBytes = 0;

            VEDERE_LOG_MESSAGE_DEBUG("::DGifGetExtensionNext(detached = " << pointer_to_string(detached) << ", &extBytes)...");
            if (GIF_OK != (::DGifGetExtensionNext(detached, &extBytes))) {
                VEDERE_LOG_MESSAGE_ERROR("...failed on ::DGifGetExtensionNext(detached = " << pointer_to_string(detached) << ", &extBytes)");
                extBytes = 0;
            } else {
                VEDERE_LOG_MESSAGE_DEBUG("...::DGifGetExtensionNext(detached = " << pointer_to_string(detached) << ", extBytes = " << pointer_to_string(extBytes) << ")");
            }
            return extBytes;
        }
        return 0;
    }
    virtual GifRecordType GetRecordType() {
        GifFileType* detached = 0;

        if ((detached = this->attached_to())) {
            GifRecordType type = UNDEFINED_RECORD_TYPE;

            VEDERE_LOG_MESSAGE_DEBUG("::DGifGetRecordType(detached = " << pointer_to_string(detached) << ", &type)...");
            if (GIF_OK != (::DGifGetRecordType(detached, &type))) {
                VEDERE_LOG_MESSAGE_ERROR("...failed on ::DGifGetRecordType(detached = " << pointer_to_string(detached) << ", &type)");
                type = UNDEFINED_RECORD_TYPE;
            } else {
                VEDERE_LOG_MESSAGE_DEBUG("...::DGifGetRecordType(detached = " << pointer_to_string(detached) << ", type = " << type << ")");
            }
            return type;
        }
        return UNDEFINED_RECORD_TYPE;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual GifWord ColorResolution() const {
        GifFileType* detached = 0;

        if ((detached = this->attached_to())) {
            return detached->SColorResolution;
        }
        return 0;
    }
    virtual GifWord BackGroundColor() const {
        GifFileType* detached = 0;

        if ((detached = this->attached_to())) {
            return detached->SBackGroundColor;
        }
        return 0;
    }
    virtual ColorMapObject* ColorMap() const {
        GifFileType* detached = 0;

        if ((detached = this->attached_to())) {
            return detached->SColorMap;
        }
        return 0;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual GifFileType* open_detached(const char* filename) const {
        if ((filename) && (filename[0])) {
           GifFileType* detached = 0;

           VEDERE_LOG_MESSAGE_DEBUG("::DGifOpenFileName(\"" << filename << "\")...");
           if ((detached = ::DGifOpenFileName(filename))) {
               VEDERE_LOG_MESSAGE_DEBUG("...::DGifOpenFileName(\"" << filename << "\")");
           } else {
               VEDERE_LOG_MESSAGE_ERROR("...failed on ::DGifOpenFileName(\"" << filename << "\")");
           }
           return detached;
        }
        return 0;
    }
    virtual bool close_detached(GifFileType* detached) const {
        if ((detached)) {
            bool success = false;
            
            VEDERE_LOG_MESSAGE_DEBUG("::DGifCloseFile(" << pointer_to_string(detached) << ")...");
            if (GIF_OK != (::DGifCloseFile(detached))) {
                VEDERE_LOG_MESSAGE_ERROR("...failed on ::DGifCloseFile(" << pointer_to_string(detached) << ")");
            } else {
                VEDERE_LOG_MESSAGE_DEBUG("...::DGifCloseFile(" << pointer_to_string(detached) << ")");
                success = true;
            }
            return success;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
}; /// class _EXPORT_CLASS filet
typedef filet<> file;

} /// namespace giflib
} /// namespace gif
} /// namespace format
} /// namespace image
} /// namespace graphic
} /// namespace vedere

#endif /// _VEDERE_GRAPHIC_IMAGE_FORMAT_GIF_GIFLIB_FILE_HPP
