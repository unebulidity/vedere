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
///   File: window.hpp
///
/// Author: $author$
///   Date: 11/4/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_HELLO_WINDOW_HPP
#define _VEDERE_APP_GUI_HELLO_WINDOW_HPP

#include "vedere/app/gui/hello/window_extend.hpp"
#include "vedere/io/logger.hpp"
#include "vedere/base/base.hpp"

namespace vedere {
namespace app {
namespace gui {
namespace hello {

///////////////////////////////////////////////////////////////////////
///  Class: windowt
///////////////////////////////////////////////////////////////////////
template <class TExtends>

class _EXPORT_CLASS windowt: public TExtends {
public:
    typedef TExtends Extends;

    typedef typename Extends::message_type_t message_type_t;
    typedef typename Extends::message_data_t message_data_t;
    typedef typename Extends::message_t message_t;
    typedef xos::mt::queuet<message_t> message_queue_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    windowt() {
    }
    virtual ~windowt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool post_message(message_type_t type, message_data_t data) {
        message_t message(type, data);
        VEDERE_LOG_MESSAGE_DEBUG("post_message(message_type_t type = " << type << ",...)...");
        message_queue_.enqueue(message);
        VEDERE_LOG_MESSAGE_DEBUG("...post_message(message_type_t type = " << type << ",...)");
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    message_queue_t message_queue_;
};

} // namespace hello 
} // namespace gui 
} // namespace app 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_HELLO_WINDOW_HPP 
