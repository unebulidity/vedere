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
///   Date: 10/27/2015, 11/28/2020
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_HELLO_MAIN_HPP
#define _VEDERE_APP_GUI_HELLO_MAIN_HPP

#include "vedere/app/gui/hello/main_opt.hpp"
#include "vedere/gui/main.hpp"
#include "vedere/base/base.hpp"

#define VEDERE_APP_GUI_HELLO_MAIN_WINDOW_WIDTH 500
#define VEDERE_APP_GUI_HELLO_MAIN_WINDOW_HEIGHT 250

namespace vedere {
namespace app {
namespace gui {
namespace hello {

enum image_format_t {
    image_format_raw,
    image_format_png,
    image_format_jpeg,
    image_format_tiff,
    image_format_gif,
    image_format_bmp,

    next_image_format,
    first_image_format = image_format_raw,
    last_image_format = (next_image_format - 1),
    image_formats = (last_image_format - first_image_format + 1)
};

enum image_transform_t {
    image_transform_fast,
    image_transform_smooth,

    next_image_transform,
    first_image_transform = image_transform_fast,
    last_image_transform = (next_image_transform - 1),
    image_transforms = (last_image_transform - first_image_transform + 1)
};

typedef vedere::gui::main_implements main_implements;
typedef vedere::gui::main main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: maint
///////////////////////////////////////////////////////////////////////
template
<class TImplements = main_implements, class TExtends = main_extends>

class _EXPORT_CLASS maint: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    maint()
    : main_window_width_(VEDERE_APP_GUI_HELLO_MAIN_WINDOW_WIDTH),
      main_window_height_(VEDERE_APP_GUI_HELLO_MAIN_WINDOW_HEIGHT),
      image_width_(0), image_height_(0), image_depth_(0),
      image_format_(first_image_format),
      image_transform_(first_image_transform) {
    }
    virtual ~maint() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_image_format(const char_t* to) {
        if ((to) && (to[0])) {
            VEDERE_LOG_MESSAGE_DEBUG("set image_format = \"" << to << "\"...");
            if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_RAW_OPTARG_C))
                || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_RAW_OPTARG_S))) {
                VEDERE_LOG_MESSAGE_DEBUG("image_format = image_format_raw");
                image_format_ = image_format_raw;
            } else {
                if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_JPEG_OPTARG_C))
                    || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_JPEG_OPTARG_S))) {
                    VEDERE_LOG_MESSAGE_DEBUG("image_format = image_format_jpeg");
                    image_format_ = image_format_jpeg;
                } else {
                    if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_TIFF_OPTARG_C))
                        || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_TIFF_OPTARG_S))) {
                        VEDERE_LOG_MESSAGE_DEBUG("image_format = image_format_tiff");
                        image_format_ = image_format_tiff;
                    } else {
                        if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_PNG_OPTARG_C))
                            || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_PNG_OPTARG_S))) {
                            VEDERE_LOG_MESSAGE_DEBUG("image_format = image_format_pmg");
                            image_format_ = image_format_png;
                        } else {
                            if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_GIF_OPTARG_C))
                                || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_GIF_OPTARG_S))) {
                                VEDERE_LOG_MESSAGE_DEBUG("image_format = image_format_gif");
                                image_format_ = image_format_gif;
                            } else {
                                if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_BMP_OPTARG_C))
                                    || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_BMP_OPTARG_S))) {
                                    VEDERE_LOG_MESSAGE_DEBUG("image_format = image_format_bmp");
                                    image_format_ = image_format_bmp;
                                } else {
                                }
                            }
                        }
                    }
                }
            }
        }
        return to;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_image_transform(const char_t* to) {
        if ((to) && (to[0])) {
            VEDERE_LOG_MESSAGE_DEBUG("set image_transform = \"" << to << "\"...");
            if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_FAST_OPTARG_C))
                || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_FAST_OPTARG_S))) {
                VEDERE_LOG_MESSAGE_DEBUG("image_transform = image_transform_fast");
                image_transform_ = image_transform_fast;
            } else {
                if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_SMOOTH_OPTARG_C))
                    || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_SMOOTH_OPTARG_S))) {
                    VEDERE_LOG_MESSAGE_DEBUG("image_transform = image_transform_smooth");
                    image_transform_ = image_transform_smooth;
                } else {
                }
            }
        }
        return to;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_image_width(const char_t* to) {
        if ((to) && (to[0])) {
            VEDERE_LOG_MESSAGE_DEBUG("set image_width = \"" << to << "\"...");
            image_width_ = chars_t::to_unsigned(to);
        }
        return to;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_image_height(const char_t* to) {
        if ((to) && (to[0])) {
            VEDERE_LOG_MESSAGE_DEBUG("set image_height = \"" << to << "\"...");
            image_height_ = chars_t::to_unsigned(to);
        }
        return to;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_image_depth(const char_t* to) {
        if ((to) && (to[0])) {
            VEDERE_LOG_MESSAGE_DEBUG("set image_depth = \"" << to << "\"...");
            image_depth_ = chars_t::to_unsigned(to);
        }
        return to;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_image_file(const char_t* to) {
        if ((to) && (to[0])) {
            VEDERE_LOG_MESSAGE_DEBUG("set image_file = \"" << to << "\"...");
            image_file_.assign(to);
        }
        return to;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
#include "vedere/app/gui/hello/main_opt.cpp"

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    size_t main_window_width_, main_window_height_,
           image_width_, image_height_, image_depth_;
    image_format_t image_format_;
    image_transform_t image_transform_;
    string image_file_;
};

typedef maint<> main;

} // namespace hello 
} // namespace gui 
} // namespace app 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_HELLO_MAIN_HPP 
