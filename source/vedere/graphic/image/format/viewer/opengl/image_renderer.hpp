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
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_OPENGL_IMAGE_RENDERER_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_OPENGL_IMAGE_RENDERER_HPP

#include "vedere/graphic/image/format/viewer/image_renderer.hpp"
#include "vedere/gui/opengl/context.hpp"
#include "vedere/gui/opengl/rectangle.hpp"
#include "vedere/gui/opengl/size.hpp"
#include "vedere/gui/opengl/point.hpp"
#include "vedere/io/logger.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace viewer {
namespace opengl {

typedef viewer::image_renderert<> image_renderer_implements;
typedef viewer::image_renderer_extendt<image_renderer_implements> image_renderer_extends;
///////////////////////////////////////////////////////////////////////
///  Class: image_renderer
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS image_renderer: virtual public image_renderer_implements, public image_renderer_extends {
public:
    typedef image_renderer_implements Implements;
    typedef image_renderer_extends Extends;
    typedef image_renderer Derives;
    
    typedef gui::opengl::rectangle Rectangle;
    typedef gui::opengl::size Size;
    typedef gui::opengl::point Point;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    image_renderer(const image_renderer &copy) {
    }
    image_renderer()
    : m_textureMagFilter(GL_LINEAR), m_textureMinFilter(GL_LINEAR), m_texture(0) {
    }
    virtual ~image_renderer() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_initialize() {
        Prepare();
        return true;
    }
    virtual bool on_realize() {
        SwapBuffers();
        return true;
    }
    virtual bool on_resize(size_t width, size_t height) {
        Reshape(width, height);
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool render
    (const void* image, size_t image_width, size_t image_height,
     const void* in_image, size_t in_image_width, size_t in_image_height) {
        return RenderResizedImage
        (m_texture, image, image_width, image_height, in_image, in_image_width, in_image_height, 
         this->width(), this->height(), this->in_offset_x(), this->in_offset_y(), 
         this->in_min_width(), this->in_min_height(), this->in_ratio(), this->in_ratio_to());
    }
    virtual bool render
    (const void* image, size_t image_width, size_t image_height) {
        return RenderResizedImage
        (m_texture, image, image_width, image_height, this->width(), this->height());
    }
    virtual bool render_stretched
    (const void* image, size_t image_width, size_t image_height) {
        return RenderStretchedImage
        (m_texture, image, image_width, image_height, image_width, image_height);
    }
    virtual bool render_raw
    (const void* image, size_t image_width, size_t image_height) {
        return RenderStretchedImage
        (m_texture, image, image_width, image_height, this->width(), this->height());
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool RenderResizedImage
    (GLuint glTexture, 
     const void* image, unsigned width, unsigned height, 
     const void* inImage, unsigned inWidth, unsigned inHeight, 
     unsigned toWidth, unsigned toHeight, unsigned inX, unsigned inY, 
     unsigned minInWidth, unsigned minInHeight, unsigned inRatio, unsigned inRatioTo = 1,
     GLint textureMagFilter = GL_LINEAR, GLint textureMinFilter = GL_LINEAR) {
        BeginRenderImage();
        Image2DTexture(glTexture, image, width, height);
        Rectangle rect(Size(width, height), Size(toWidth, toHeight));
        RenderTexture(glTexture, rect.origin, rect.size);

        if ((toWidth >= minInWidth) && (toHeight >= minInHeight))
        {
            float oX = (float)(inX);
            float oY = (float)(inY);
            float r = (float)(inRatio);
            float rTo = (float)(inRatioTo);
            float x = rect.origin.x + rect.size.width - (oX / toWidth);
            float y = rect.origin.y + rect.size.height - (oY / toHeight);

            Image2DTexture(glTexture, inImage, inWidth, inHeight);

            Rectangle inRect(Size(inWidth, inHeight), Size(toWidth, toHeight));

            RenderTexture
            (glTexture, 
             Point(x - ((inRect.size.width * rTo) / r), y - ((inRect.size.height * rTo) / r)),
             Size(((inRect.size.width * rTo) / r), ((inRect.size.height * rTo) / r)));
        }
        EndRenderImage();
        return !(GL_NO_ERROR != glGetError()); 
    }
    virtual bool RenderResizedImage
    (GLuint glTexture, const void* image, 
     unsigned width, unsigned height, unsigned toWidth, unsigned toHeight,
     GLint textureMagFilter = GL_LINEAR, GLint textureMinFilter = GL_LINEAR) {
        BeginRenderImage();
        Image2DTexture(glTexture, image, width, height);
        Rectangle rect(Size(width, height), Size(toWidth, toHeight));
        RenderTexture(glTexture, rect.origin, rect.size);
        EndRenderImage();
        return !(GL_NO_ERROR != glGetError()); 
    }
    virtual bool RenderStretchedImage
    (GLuint glTexture, const void* image, 
     unsigned width, unsigned height, unsigned toWidth, unsigned toHeight,
     GLint textureMagFilter = GL_LINEAR, GLint textureMinFilter = GL_LINEAR) {
        BeginRenderImage();
        Image2DTexture(glTexture, image, width, height);
        Size from(width, height), to(toWidth, toHeight), size(from, to);
        RenderTexture(glTexture, Point(0, 0), size);
        EndRenderImage();
        return !(GL_NO_ERROR != glGetError()); 
    }
    virtual bool RenderTexture(GLuint glTexture, const Point& p, const Size& s) {
        glBindTexture(GL_TEXTURE_2D, glTexture);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(p.x, p.y);
        glTexCoord2f(1, 0); glVertex2f(p.x + s.width, p.y);
        glTexCoord2f(1, 1); glVertex2f(p.x + s.width, p.y + s.height);
        glTexCoord2f(0, 1); glVertex2f(p.x, p.y + s.height);
        glEnd();
        return !(GL_NO_ERROR != glGetError()); 
    }
    virtual bool Image2DTexture
    (GLuint glTexture, const void* image, unsigned width, unsigned height,
     GLint textureMagFilter = GL_LINEAR, GLint textureMinFilter = GL_LINEAR) {
        glBindTexture(GL_TEXTURE_2D, glTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureMagFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureMinFilter);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, image);
        return !(GL_NO_ERROR != glGetError()); 
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool BeginRenderImage() {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_TEXTURE_2D);
        
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, 1, 1, 0);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        return !(GL_NO_ERROR != glGetError()); 
    }
    virtual bool EndRenderImage() {
        glFlush();
        return !(GL_NO_ERROR != glGetError()); 
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool Prepare() {
        glGenTextures(1, &m_texture);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        return !(GL_NO_ERROR != glGetError()); 
    }
    virtual bool Reshape(int width, int height) {
        bool success = false;
        glViewport(0, 0, width, height);
        if (!(success = !(GL_NO_ERROR != glGetError()))) {
            VEDERE_LOG_MESSAGE_ERROR("...failed on glViewport(0, 0, width, height)");
        }
        return success; 
    }
    virtual bool SwapBuffers() {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    GLint m_textureMagFilter, m_textureMinFilter;
    GLuint m_texture;
}; /// class _EXPORT_CLASS image_renderer

} /// namespace opengl
} /// namespace viewer
} /// namespace format
} /// namespace image
} /// namespace graphic
} /// namespace vedere

#endif /// _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_OPENGL_IMAGE_RENDERER_HPP
