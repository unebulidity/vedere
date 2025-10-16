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
///   File: window.hpp
///
/// Author: $author$
///   Date: 7/17/2016
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_WINDOW_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_WINDOW_HPP

#include "vedere/io/logger.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace viewer {

typedef implement_base window_extends;
///////////////////////////////////////////////////////////////////////
///  Class: windowt
///////////////////////////////////////////////////////////////////////
template <class TExtends = window_extends>
class _EXPORT_CLASS windowt: public TExtends {
public:
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    enum message_type_t {
        message_type_none,
        message_type_switch_render
    };
    typedef void* message_data_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS message_t {
    public:
        message_t(message_type_t type, message_data_t data): type_(type), data_(data) {}
        message_t(const message_t& copy): type_(copy.type_), data_(copy.data_) {}
        message_t(): type_(message_type_none), data_(0) {}
        virtual ~message_t() {}
    public:
        message_type_t type_;
        message_data_t data_;
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    windowt() {
    }
    virtual ~windowt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void switch_render() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool post_message(message_type_t type, message_data_t data) {
        VEDERE_LOG_MESSAGE_DEBUG("post_message(message_type_t type = " << type << ",...)...");
        return false;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void on_message(message_type_t type, message_data_t data) {
        switch (type) {
        case message_type_switch_render:
            VEDERE_LOG_MESSAGE_DEBUG("...on_message(message_type_t type = message_type_switch_render,...)");
            switch_render();
            break;
        default:
            VEDERE_LOG_MESSAGE_DEBUG("...on_message(message_type_t type = " << type << ",...)");
            break;
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef windowt<> window;

} // namespace viewer
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_WINDOW_HPP 
