///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2021 $organization$
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
///   Date: 1/4/2021
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_QT_OPENGL_IMAGE_RENDERER_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_QT_OPENGL_IMAGE_RENDERER_HPP

#include "vedere/graphic/image/format/viewer/opengl/image_renderer.hpp"
#include "vedere/gui/qt/opengl.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace viewer {
namespace qt {
namespace opengl {

typedef viewer::opengl::image_renderer image_renderer_extends;
typedef image_renderer_extends::Implements image_renderer_implements;
///////////////////////////////////////////////////////////////////////
///  Class: image_renderer
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS image_renderer: virtual public image_renderer_implements, public image_renderer_extends {
public:
    typedef image_renderer_implements Implements;
    typedef image_renderer_extends Extends;
    typedef image_renderer Derives;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    image_renderer(): widget_(0) {
    }
    virtual ~image_renderer() {
    }
private:
    image_renderer(const image_renderer &copy) {
    }
public:

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SwapBuffers() {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init(QGLWidget* widget) {
        if ((widget_ = widget))
            return true;
        return false;
    }
    virtual bool finish() {
        if ((widget_)) {
            widget_ = 0;
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    QGLWidget* widget_;
}; /// class _EXPORT_CLASS image_renderer

} /// namespace opengl
} /// namespace qt
} /// namespace viewer
} /// namespace format
} /// namespace image
} /// namespace graphic
} /// namespace vedere

#endif /// _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_QT_OPENGL_IMAGE_RENDERER_HPP
