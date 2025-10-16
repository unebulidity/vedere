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
#ifndef _VEDERE_APP_GUI_GTK_HELLO_MAIN_HPP
#define _VEDERE_APP_GUI_GTK_HELLO_MAIN_HPP

#include "vedere/app/gui/gtk/hello/renderer.hpp"
#include "vedere/app/gui/gtk/hello/image_renderer.hpp"
#include "vedere/app/gui/hello/main_window.hpp"
#include "vedere/app/gui/hello/main.hpp"
#include "vedere/app/gui/hello/renderer.hpp"
#include "vedere/app/gui/hello/window.hpp"
#include "vedere/gui/gtk/application/window_main.hpp"
#include "vedere/gui/gtk/application/window.hpp"
#include "vedere/gui/gtk/application/main.hpp"
#include "vedere/gui/gtk/main_window.hpp"
#include "vedere/gui/gtk/main.hpp"
#include "vedere/gui/gtk/drawing_area.hpp"
#include "xos/mt/queue.hpp"

namespace vedere {
namespace app {
namespace gui {
namespace gtk {
namespace hello {

typedef gui::hello::windowt
<gui::hello::window_extendt
 <vedere::gui::gtk::drawing_area> > drawing_area_extends;
///////////////////////////////////////////////////////////////////////
///  Class: drawing_area
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS drawing_area: public drawing_area_extends {
public:
    typedef drawing_area_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    drawing_area() {
    }
    virtual ~drawing_area() {
        the_signal_idle_id() = 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void* load_image
    (byte_reader& reader, size_t size, size_t width, size_t height) {
        return renderer_.load_image(reader, size, width, height);
    }
    virtual void* set_image
    (byte_t* bytes, size_t size, size_t width, size_t height) {
        return renderer_.set_image(bytes, size, width, height);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void switch_render() {
        renderer_.switch_render();
        queue_draw();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool connect_signal_idle() {
        guint& the_id = the_signal_idle_id();
        if (!(the_id)) {
            guint id = 0;
            if ((id = g_idle_add(signal_idle_callback, ((gpointer*)this)))) {
                the_id = id;
                return true;
            } else {
                VEDERE_LOG_MESSAGE_ERROR("failed on g_idle_add()");
            }
        }
        return false;
    }
    virtual bool disconnect_signal_idle() {
        guint& the_id = the_signal_idle_id();
        if ((the_id)) {
            the_id = 0;
            if ((g_idle_remove_by_data(((gpointer*)this)))) {
                return true;
            } else {
                VEDERE_LOG_MESSAGE_ERROR("failed on g_idle_remove_by_data()");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool post_message(message_type_t type, message_data_t data) {
        message_t message(type, data);
        if ((message_queue_.enqueue(message))) {
            return true;
        }
        return false;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool got_message(message_type_t& type, message_data_t& data) {
        message_t message;
        if ((message_queue_.try_dequeue(message))) {
            type = message.type_;
            data = message.data_;
            return true;
        }
        return false;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void on_signal_draw(GtkWidget* widget, cairo_t* cr) {
        gint width = 0, height = 0, x = 0, y = 0;
        if ((get_size(width, height))) {
            if ((renderer_.init(cr, width,height))) {
                renderer_.render();
                renderer_.finish();
            }
        }
    }
    virtual void on_signal_button_release_event(GtkWidget* widget, GdkEvent* event) {
        VEDERE_LOG_MESSAGE_DEBUG("on_signal_button_release_event()...");
        VEDERE_LOG_MESSAGE_DEBUG("post_message(message_type_switch_render, 0)...");
        post_message(message_type_switch_render, 0);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual gboolean on_signal_idle() {
        message_type_t type = message_type_none;
        message_data_t data = 0;
        if ((got_message(type, data))) {
            on_message(type, data);
        }
        return TRUE;
    }
    static gboolean signal_idle_callback(gpointer data) {
        guint& the_id = the_signal_idle_id();
        if ((the_id)) {
            drawing_area* the_drawing_area = ((drawing_area*)data);
            if ((the_drawing_area)) {
                return the_drawing_area->on_signal_idle();
            }
        }
        return FALSE;
    }
    static guint& the_signal_idle_id() {
        static guint the_id = 0;
        return the_id;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    renderer renderer_;
    message_queue_t message_queue_;
};

typedef app::gui::hello::main_windowt
<gui::hello::main_window_extendt
 <vedere::gui::gtk::application::window> > window_extends;
///////////////////////////////////////////////////////////////////////
///  Class: window
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS window: public window_extends {
public:
    typedef window_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    window() {
    }
    virtual ~window() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init
    (size_t image_width, size_t image_height,
     size_t image_depth, const char_t* image_file,
     gui::hello::image_format_t image_format = gui::hello::image_format_raw) {
        GtkWidget* parent = this->attached_to();
        if ((parent)) {
            GtkWidget* child = 0;
            if ((child = d_.create_attached())) {
                d_.connect_signal_idle();
                d_.connect_signal_draw();
                d_.connect_signal_button_events();
                gtk_container_add(GTK_CONTAINER(parent), child);
                load_image
                (image_width, image_height, image_depth,
                 image_file, image_format);
            }
        }
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::load_image;
    virtual void* load_image
    (byte_reader& reader, size_t size, size_t width, size_t height) {
        return d_.load_image(reader, size, width, height);
    }
    virtual void* set_image
    (byte_t* bytes, size_t size, size_t width, size_t height) {
        return d_.set_image(bytes, size, width, height);
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void on_signal_configure
    (GtkWidget* widget, GdkWindow *window, gint x,gint y,
     gint width,gint height, gboolean sent_explicitly) {
        VEDERE_LOG_MESSAGE_DEBUG("on_signal_configure(..., x=" << x << ",y=" << y << ", width=" << width << ",height=" << height << ")...");
    }
    virtual void on_signal_destroy(GtkWidget* widget) {
        VEDERE_LOG_MESSAGE_DEBUG("on_signal_destroy()...");
        d_.disconnect_signal_idle();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    drawing_area d_;
};

typedef vedere::gui::gtk::application::window_main_implements main_implements;
typedef vedere::app::gui::hello::maint
<main_implements, vedere::gui::gtk::application::window_main> main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main
: virtual public lamna::gui::gtk::widget_signals,
  virtual public main_implements, public main_extends {
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
    virtual GtkWidget* create_main_window(GtkApplication *application) {
        if ((application)) {
            GtkWidget* main_window = 0;
            if ((main_window = main_window_.create_attached(application))) {
                main_window_.set_default_size(main_window_width_, main_window_height_);
                main_window_.connect_signal_configure_event();
                main_window_.connect_signal_destroy();
                main_window_.init
                (image_width_, image_height_,
                 image_depth_, image_file_.has_chars(),
                 image_format_);
                return main_window;
            }
        }
        return 0;
    }
    virtual bool destroy_main_window
    (GtkWidget* main_window, GtkApplication *application) {
        if ((application) && (main_window)
            && (main_window == (main_window_.attached_to()))) {
            if ((main_window_.destroyed())) {
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    hello::window main_window_;
};

} // namespace hello 
} // namespace gtk 
} // namespace gui 
} // namespace app 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_GTK_HELLO_MAIN_HPP 
