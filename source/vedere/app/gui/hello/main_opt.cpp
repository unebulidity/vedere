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
///   File: main_opt.cpp
///
/// Author: $author$
///   Date: 10/24/2015
///////////////////////////////////////////////////////////////////////
#if !defined(_VEDERE_APP_GUI_HELLO_MAIN_HPP)
#include "vedere/app/gui/hello/main_opt.hpp"

namespace vedere {
namespace app {
namespace gui {
namespace hello {

typedef main_implements main_implements;
typedef main main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main: virtual public main_implements, public main_extends {
public:
    typedef main_implements Implements;
    typedef main_extends Extends;
#endif // !defined(_VEDERE_APP_GUI_HELLO_MAIN_HPP)

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_image_format_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        set_image_format(optarg);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_image_transform_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        set_image_transform(optarg);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_image_width_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        set_image_width(optarg);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_image_height_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        set_image_height(optarg);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_image_depth_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        set_image_depth(optarg);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        switch(optval) {
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_OPTVAL_C:
            err = on_image_format_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_OPTVAL_C:
            err = on_image_transform_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_WIDTH_OPTVAL_C:
            err = on_image_width_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_HEIGHT_OPTVAL_C:
            err = on_image_height_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_DEPTH_OPTVAL_C:
            err = on_image_depth_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        default:
            err = Extends::on_option
            (optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* option_usage
    (const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_OPTVAL_C:
            optarg = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_OPTARG;
            chars = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_OPTUSE;
            break;
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_OPTVAL_C:
            optarg = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_OPTARG;
            chars = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_OPTUSE;
            break;
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_WIDTH_OPTVAL_C:
            optarg = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_WIDTH_OPTARG;
            chars = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_WIDTH_OPTUSE;
            break;
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_HEIGHT_OPTVAL_C:
            optarg = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_HEIGHT_OPTARG;
            chars = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_HEIGHT_OPTUSE;
            break;
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_DEPTH_OPTVAL_C:
            optarg = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_DEPTH_OPTARG;
            chars = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_DEPTH_OPTUSE;
            break;
        default:
            chars = Extends::option_usage(optarg, longopt);
        }
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* options(const struct option*& longopts) {
        int err = 0;
        static const char_t* chars = VEDERE_APP_GUI_HELLO_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            VEDERE_APP_GUI_HELLO_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_argument
    (const char_t* arg, int argind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((arg) && (arg[0]) && (!argind)) {
            set_image_file(arg);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* arguments(const char_t**& argv) {
        static const char_t* _args = VEDERE_APP_GUI_HELLO_MAIN_ARGS;
        static const char_t* _argv[] = {
            VEDERE_APP_GUI_HELLO_MAIN_ARGV
            0};
        argv = _argv;
        return _args;
    }
#if !defined(_VEDERE_APP_GUI_HELLO_MAIN_HPP)
};

} // namespace hello
} // namespace gui 
} // namespace app 
} // namespace vedere 
#endif // !defined(_VEDERE_APP_GUI_HELLO_MAIN_HPP)
