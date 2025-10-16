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
///   File: main.hpp
///
/// Author: $author$
///   Date: 7/18/2016
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_QT_MAIN_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_QT_MAIN_HPP

#include "vedere/graphic/image/format/viewer/qt/main_window.hpp"
#include "vedere/gui/qt/application/window_main.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace viewer {
namespace qt {

typedef vedere::gui::qt::application::window_main_implements main_implements;
typedef viewer::maint
<main_implements, vedere::gui::qt::application::window_main> main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main: virtual public main_implements, public main_extends {
public:
    typedef main_implements Implements;
    typedef main_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main(): main_window_(0), use_opengl_(false) {
    }
    virtual ~main() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual QMainWindow* create_main_window
    (QApplication& qApplication, int argc, char_t** argv, char_t** env) {
        if ((main_window_ = new main_window(this))) {
            main_window_->set_use_opengl(use_opengl());
            main_window_->resize(main_window_width_, main_window_height_);
            if ((main_window_->init
                 (image_width_, image_height_, image_depth_, image_file_.has_chars(),
                  image_format_, raw_image_format_, image_transform_))) {
                return main_window_;
            } else {
                VEDERE_LOG_ERROR("failed on main_window_->init()");
                delete main_window_;
                main_window_ = 0;
            }
        }
        return 0;
    }
    virtual bool destroy_main_window
    (QMainWindow* qMainWindow, QApplication& qApplication,
     int argc, char_t** argv, char_t** env) {
        if ((qMainWindow) && (qMainWindow == ((QMainWindow*)main_window_))) {
            bool success = false;
            if (!(success = main_window_->finish())) {
                VEDERE_LOG_ERROR("failed on main_window_->finish()");
            }
            delete main_window_;
            main_window_ = 0;
            return success;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void* set_image
    (byte_t* bytes, size_t size, size_t width, size_t height) {
        if ((main_window_)) {
            return main_window_->set_image(bytes, size, width, height);
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_use_opengl(bool to) {
        use_opengl_ = to;
        return use_opengl_;
    }
    virtual bool use_opengl() const {
        return use_opengl_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    main_window* main_window_;
    bool use_opengl_;
};

} // namespace qt
} // namespace viewer 
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_QT_MAIN_HPP 
