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
///   File: main.hpp
///
/// Author: $author$
///   Date: 5/29/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_QT_APPLICATION_MAIN_HPP
#define _VEDERE_GUI_QT_APPLICATION_MAIN_HPP

#include "vedere/gui/qt/main.hpp"
#include "vedere/gui/qt/gui.hpp"
#include "lamna/gui/qt/application/main.hpp"

namespace vedere {
namespace gui {
namespace qt {
namespace application {

typedef lamna::gui::qt::main_implements main_implements;
typedef lamna::gui::qt::main main;
/*typedef qt::main_implements main_implements;
typedef qt::main main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main: virtual public main_implements, public main_extends {
public:
    typedef main_implements Implements;
    typedef main_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main() {
    }
    virtual ~main() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int exec
    (QApplication& qApplication, int argc, char_t** argv, char_t** env) {
        int err = 0;
        VEDERE_LOG_MESSAGE_DEBUG("qApplication.exec()...");
        if ((err = qApplication.exec())) {
            VEDERE_LOG_ERROR("failed err = " << err << " on qApplication.exec()...");
        }
        return err;
    }
    virtual int before_exec
    (QApplication& qApplication, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_exec
    (QApplication& qApplication, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int event_loop(int argc, char_t** argv, char_t** env) {
        int err = 0;
        QApplication qApplication(argc, argv);

        VEDERE_LOG_MESSAGE_DEBUG("before_exec()...");
        if (!(err = before_exec(qApplication, argc, argv, env))) {
            int err2 = 0;

            VEDERE_LOG_MESSAGE_DEBUG("exec()...");
            if ((err = exec(qApplication, argc, argv, env))) {
                VEDERE_LOG_ERROR("failed " << err << " on exec()");
            }

            VEDERE_LOG_MESSAGE_DEBUG("after_exec()...");
            if ((err2 = after_exec(qApplication, argc, argv, env))) {
                VEDERE_LOG_ERROR("failed " << err2 << " on after_exec()");
                if (!err) err = err2;
            }
        } else {
            VEDERE_LOG_ERROR("failed " << err << " on before_exec()");
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};*/

} // namespace application 
} // namespace qt 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_QT_APPLICATION_MAIN_HPP 
