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
///   File: image_renderer.hpp
///
/// Author: $author$
///   Date: 11/10/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_HPP
#define _VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_HPP

#include "vedere/gui/qt/gui.hpp"
#include "vedere/app/gui/hello/image_renderer.hpp"

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_IMAGE_FORMAT_ARGB32 QImage::Format_ARGB32

#define VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_ASPECT_RATIO_IGNORE Qt::IgnoreAspectRatio
#define VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_ASPECT_RATIO_KEEP Qt::KeepAspectRatio

#define VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_TRANSFORMATION_MODE_FAST Qt::FastTransformation
#define VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_TRANSFORMATION_MODE_SMOOTH Qt::SmoothTransformation

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_IMAGE_FORMAT \
    VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_IMAGE_FORMAT_ARGB32

#define VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_ASPECT_RATIO \
    VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_ASPECT_RATIO_IGNORE

#if defined(MACOSX)
#define VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_TRANSFORMATION_MODE \
    VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_TRANSFORMATION_MODE_FAST
#else // defined(MACOSX)
#define VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_TRANSFORMATION_MODE \
    VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_TRANSFORMATION_MODE_SMOOTH
#endif // defined(MACOSX)

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

namespace vedere {
namespace app {
namespace gui {
namespace qt {
namespace hello {

typedef QImage::Format image_format_t;
typedef Qt::AspectRatioMode aspect_ratio_mode_t;
typedef Qt::TransformationMode transformation_mode_t;

typedef gui::hello::image_renderert
<image_format_t, VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_IMAGE_FORMAT,
 aspect_ratio_mode_t, VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_ASPECT_RATIO,
 transformation_mode_t, VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_TRANSFORMATION_MODE>
image_renderer_implements;

typedef gui::hello::image_renderer_extendt
<image_renderer_implements> image_renderer_extends;
///////////////////////////////////////////////////////////////////////
///  Class: image_renderer
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS image_renderer
: virtual public image_renderer_implements, public image_renderer_extends {
public:
    typedef image_renderer_implements Implements;
    typedef image_renderer_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    image_renderer(QWidget* widget = 0)
    : widget_(widget),
      transformation_mode_
      (VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_TRANSFORMATION_MODE) {
    }
    virtual ~image_renderer() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init(QWidget* widget) {
        widget_ = widget;
        return true;
    }
    virtual bool finish() {
        widget_ = 0;
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::render;
    virtual bool render
    (const void* image, size_t image_width, size_t image_height,
     size_t width, size_t height, size_t x, size_t y, QImage::Format image_format,
     Qt::AspectRatioMode aspectRatioMode, Qt::TransformationMode transformationMode) {
        if ((widget_) && (image)) {
            QPainter qPainter(widget_);
            QImage qImage
            ((const unsigned char*)(image),
             image_width, image_height, image_format);
            qPainter.drawImage
            (x,y, qImage.scaled(width, height, aspectRatioMode, transformationMode));
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual aspect_ratio_mode_t aspect_ratio_mode() const {
        return VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_ASPECT_RATIO_KEEP;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool transform_smooth(bool on = true) {
        if ((on)) {
            transformation_mode_ = VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_TRANSFORMATION_MODE_SMOOTH;
        } else {
            transformation_mode_ = VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_TRANSFORMATION_MODE_FAST;
        }
        return on;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual Qt::TransformationMode transformation_mode() const {
        return transformation_mode_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    QWidget* widget_;
    Qt::TransformationMode transformation_mode_;
};

} // namespace hello
} // namespace qt 
} // namespace gui 
} // namespace app 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_QT_HELLO_IMAGE_RENDERER_HPP 
