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
///   Date: 5/27/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_MAIN_HPP
#define _VEDERE_GUI_MAIN_HPP

#include "vedere/console/main.hpp"
#include "lamna/gui/main.hpp"

namespace vedere {
namespace gui {

typedef lamna::gui::main_implements main_implements;
typedef lamna::gui::main main;
/*typedef console::main_implements main_implements;
typedef console::main main_extends;
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
    virtual int run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_gui_main(argc, argv, env))) {
            int err2 = 0;
            VEDERE_LOG_MESSAGE_DEBUG("gui_main()...");
            err = gui_main(argc, argv, env);
            VEDERE_LOG_MESSAGE_DEBUG("...gui_main()");
            if ((err2 = after_gui_main(argc, argv, env))) {
                if (!err) err = err2;
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int gui_main(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_event_loop(argc, argv, env))) {
            int err2 = 0;
            VEDERE_LOG_MESSAGE_DEBUG("event_loop()...");
            err = event_loop(argc, argv, env);
            VEDERE_LOG_MESSAGE_DEBUG("...event_loop()");
            if ((err2 = after_event_loop(argc, argv, env))) {
                if (!err) err = err2;
            }
        }
        return err;
    }
    virtual int before_gui_main(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_gui_main(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int event_loop(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int before_event_loop(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_event_loop(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};*/

} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_MAIN_HPP 
