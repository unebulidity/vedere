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
///   File: renderer.hpp
///
/// Author: $author$
///   Date: 1/5/2021
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_QT_OPENGL_RENDERER_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_QT_OPENGL_RENDERER_HPP

#include "vedere/graphic/image/format/viewer/qt/opengl/image_renderer.hpp"
#include "vedere/graphic/image/format/viewer/renderer.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace viewer {
namespace qt {
namespace opengl {

typedef implement renderer_implements;
typedef viewer::renderert
<image_renderer::image_format_t,
 image_renderer::image_format_none, image_renderer> renderer_extends;
///////////////////////////////////////////////////////////////////////
///  Class: renderer
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS renderer: virtual public renderer_implements, public renderer_extends {
public:
    typedef renderer_implements Implements;
    typedef renderer_extends Extends;
    typedef renderer Derives;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
private:
    renderer(const renderer &copy) {
    }
public:
    renderer() {
    }
    virtual ~renderer() {
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool initialize() {
        return image_renderer_.initialize();
    }
    virtual bool resize(size_t width, size_t height) {
        return image_renderer_.resize(width, height);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init(QGLWidget* widget) {
        return image_renderer_.init(widget);
    }
    virtual bool finish() {
        return image_renderer_.finish();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual image_renderer_t* image_renderer(const image_format_t& image_format) const {
        if (!(image_format != image_renderer_.image_format())) {
            return ((image_renderer_t*)&image_renderer_);
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    image_renderer_t image_renderer_;
}; /// class _EXPORT_CLASS renderer

} /// namespace opengl
} /// namespace qt
} /// namespace viewer
} /// namespace format
} /// namespace image
} /// namespace graphic
} /// namespace vedere

#endif /// _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_QT_OPENGL_RENDERER_HPP
