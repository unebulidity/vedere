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
///   File: window.hpp
///
/// Author: $author$
///   Date: 1/5/2021
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_QT_OPENGL_WINDOW_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_QT_OPENGL_WINDOW_HPP

#include "vedere/graphic/image/format/viewer/qt/opengl/renderer.hpp"
#include "vedere/graphic/image/format/viewer/window.hpp"
#include "vedere/graphic/image/format/viewer/main.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace viewer {
namespace qt {
namespace opengl {

typedef viewer::windowt<QGLWidget> main_widget_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main_widget
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main_widget: public main_widget_extends {
public:
    typedef main_widget_extends Extends;
    typedef main_widget Derives;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
private:
    main_widget(const main_widget &copy) {
    }
public:
    main_widget(QWidget* parent) {
        setParent(parent);
    }
    virtual ~main_widget() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init(viewer::image_transform_t image_transform) {
        renderer_.init(this);
        renderer_.transform_smooth(!(viewer::image_transform_smooth != image_transform));
        return true;
    }
    virtual bool finish() {
        renderer_.finish();
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void* load_image(byte_reader& reader, size_t size, size_t width, size_t height) {
        return renderer_.load_image(reader, size, width, height);
    }
    virtual void* set_image(byte_t* bytes, size_t size, size_t width, size_t height) {
        return renderer_.set_image(bytes, size, width, height);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void switch_render() {
        renderer_.switch_render();
        update(0,0, width(),height());
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool post_message(message_type_t type, message_data_t data) {
        VEDERE_LOG_MESSAGE_DEBUG("QApplication::postEvent(this, new MessageQEvent(message_type_t type = " << type << ",...))...");
        QApplication::postEvent(this, new MessageQEvent(type, data));
        return false;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void initializeGL() {
        VEDERE_LOG_MESSAGE_DEBUG("renderer_.initialize()");
        renderer_.initialize();
    }
    virtual void resizeGL(int width, int height) {
        VEDERE_LOG_MESSAGE_DEBUG("renderer_.resize(" << width << ", " << height << ")");
        renderer_.resize(width, height);
    }
    virtual void paintGL() {
        renderer_.render();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void mouseReleaseEvent(QMouseEvent *event) {
        Qt::MouseButton button = Qt::NoButton;
        Extends::mouseReleaseEvent(event);
        switch((button = event->button())) {
        case Qt::LeftButton:
            post_message(message_type_switch_render, 0);
            break;
        case Qt::RightButton:
            break;
        default:
            break;
        }
    }
    virtual void customEvent(QEvent* event) {
        QEvent::Type type = event->type();
        switch(type) {
        case MessageQEvent::Message: {
            MessageQEvent* message = ((MessageQEvent*)event);
            on_message(message->type(), message->data());
            break; }
        default:
            VEDERE_LOG_MESSAGE_DEBUG("...customEvent() type = " << type);
            break;
        }
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    class MessageQEvent: public QEvent {
    public:
        enum { Message = QEvent::User + 1};
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        MessageQEvent
        (message_type_t type, message_data_t data)
        : QEvent((Type)Message), message_(type, data) {}
        MessageQEvent
        (const MessageQEvent& copy)
        : QEvent((Type)Message), message_(copy.message_) {}
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual message_type_t type() const { return message_.type_; }
        virtual message_data_t data() const { return message_.data_; }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        message_t message_;
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    renderer renderer_;
}; /// class _EXPORT_CLASS main_widget

} /// namespace opengl
} /// namespace qt
} /// namespace viewer
} /// namespace format
} /// namespace image
} /// namespace graphic
} /// namespace vedere

#endif /// _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_QT_OPENGL_WINDOW_HPP
