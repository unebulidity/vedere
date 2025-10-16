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
///   File: main_window.hpp
///
/// Author: $author$
///   Date: 7/17/2016, 1/5/2021
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_QT_MAIN_WINDOW_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_QT_MAIN_WINDOW_HPP

#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_USE_OPENGL)
#include "vedere/graphic/image/format/viewer/qt/opengl/window.hpp"
#else /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_USE_OPENGL)
#endif // defined(VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_USE_OPENGL)

#include "vedere/graphic/image/format/viewer/qt/window.hpp"
#include "vedere/graphic/image/format/viewer/main_window.hpp"
#include "vedere/gui/qt/application/main_window.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace viewer {
namespace qt {

typedef viewer::main_windowt
<vedere::gui::qt::application::main_window> main_window_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main_window
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main_window: public main_window_extends {
public:
    typedef main_window_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main_window
    (image_loader* _image_loader = 0)
    : Extends(_image_loader), main_widget_(0) 
#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_USE_OPENGL)
    , gl_main_widget_(0)
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_USE_OPENGL)
    {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init
    (size_t image_width, size_t image_height, size_t image_depth,
     const char_t* image_file, viewer::image_format_t image_format,
     viewer::raw_image_format_t raw_image_format,
     viewer::image_transform_t image_transform) {
#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_USE_OPENGL)
        if ((this->use_opengl())) {
            if ((gl_main_widget_ = new opengl::main_widget(this))) {
                if ((gl_main_widget_->init(image_transform))) {
                    this->setCentralWidget(gl_main_widget_);
                    load_image
                    (image_width, image_height, image_depth,
                     image_file, image_format, raw_image_format);
                    return true;
                }
                delete gl_main_widget_;
                gl_main_widget_ = 0;
                return false;
            }
        } else {
        }
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_USE_OPENGL)
        if (((!main_widget_)) && (main_widget_ = new main_widget(this))) {
            if ((main_widget_->init(image_transform))) {
                this->setCentralWidget(main_widget_);
                load_image
                (image_width, image_height, image_depth,
                 image_file, image_format, raw_image_format);
                return true;
            }
            delete main_widget_;
            main_widget_ = 0;
            return false;
        }
        return false;
    }
    virtual bool finish() {
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::load_image;
    virtual void* load_image
    (byte_reader& reader, size_t size, size_t width, size_t height) {
        if ((main_widget_)) {
            return main_widget_->load_image(reader, size, width, height);
        } else {
#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_USE_OPENGL)
                if ((gl_main_widget_)) {
                    return gl_main_widget_->load_image(reader, size, width, height);
                } else {
                }
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_USE_OPENGL)
        }
        return 0;
    }
    virtual void* set_image
    (byte_t* bytes, size_t size, size_t width, size_t height) {
        if ((main_widget_)) {
            return main_widget_->set_image(bytes, size, width, height);
        } else {
#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_USE_OPENGL)
                if ((gl_main_widget_)) {
                    return gl_main_widget_->set_image(bytes, size, width, height);
                } else {
                }
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_USE_OPENGL)
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    main_widget* main_widget_;
#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_USE_OPENGL)
    opengl::main_widget* gl_main_widget_;
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_USE_OPENGL)
};

} // namespace qt
} // namespace viewer 
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_QT_MAIN_WINDOW_HPP 
