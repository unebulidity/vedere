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
///   File: window.hpp
///
/// Author: $author$
///   Date: 6/28/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_GTK_EXPLORE_APPLICATION_WINDOW_HPP
#define _VEDERE_APP_GUI_GTK_EXPLORE_APPLICATION_WINDOW_HPP

#include "vedere/app/gui/gtk/explore/treeview.hpp"
#include "vedere/app/gui/gtk/explore/menu_bar.hpp"
#include "vedere/gui/gtk/application/window.hpp"
#include "vedere/gui/gtk/listview.hpp"
#include "vedere/gui/gtk/treeview.hpp"
#include "vedere/gui/treeview.hpp"
#include "vedere/gui/gtk/container.hpp"
#include "vedere/gui/gtk/frame.hpp"
#include "vedere/gui/gtk/box.hpp"
#include "vedere/gui/gtk/stock/icon.hpp"

#define VEDERE_APP_GUI_EXPLORE_APPLICATION_WINDOW_WIDTH 400
#define VEDERE_APP_GUI_EXPLORE_APPLICATION_WINDOW_HEIGHT 200

namespace vedere {
namespace gui {
namespace gtk {
namespace app {
namespace explore {
namespace application {

typedef gtk::application::window_implements window_implements;
typedef gtk::application::window window_extends;
///////////////////////////////////////////////////////////////////////
///  Class: window
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS window
: virtual public window_implements, public window_extends {
public:
    typedef window_implements Implements;
    typedef window_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    window()
    : width_(VEDERE_APP_GUI_EXPLORE_APPLICATION_WINDOW_WIDTH),
      height_(VEDERE_APP_GUI_EXPLORE_APPLICATION_WINDOW_HEIGHT) {
    }
    virtual ~window() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool init(int argc, const char_t** argv) {
        bool success = true;
        gtk::vertical::box box;
        GtkWidget* box_detached = 0;

        load_icons();

        if ((box_detached = box.create_attached())) {
            menu_bar& mb = menu_bar_;
            gtk::frame frame;
            GtkWidget* frame_detached = 0;
            GtkWidget* mb_detached = 0;

            if ((mb_detached = mb.create_attached_to())) {
                box.pack_start(mb_detached, FALSE, FALSE);
            }
            if ((frame_detached = frame.create_attached())) {
                treeview& tv = treeview_;
                GtkWidget* tv_detached = 0;

                if ((tv_detached = tv.create_attached_to())) {
                    tv.container_add_to(frame_detached);
                    if ((0 < (argc)) && (argv[0]) && (argv[0][0])) {
                        tv.open(argv[0]);
                    }
                }
                box.pack_start(frame_detached, TRUE, TRUE);
            }
            this->set_size_request(width_, height_);
            this->container_add(box_detached);
        }
        return success;
    }
    virtual bool fini() {
        bool success = true;
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool load_icons() {
        bool success = true;
        if ((icon_.create
             (icon_factory_, icon_set_, icon_pixbuf_,
              VEDERE_APP_GUI_GTK_EXPLORE_ICON_FILENAME_FILE,
              VEDERE_APP_GUI_GTK_EXPLORE_ICON_ID_FILE,
              VEDERE_APP_GUI_GTK_EXPLORE_DEFAULT_ICON_ID_FILE))) {
            treeview_.set_icon_id_file(icon_);
            icon_.destroy();
        }
        if ((icon_.create
             (icon_factory_, icon_set_, icon_pixbuf_,
              VEDERE_APP_GUI_GTK_EXPLORE_ICON_FILENAME_DIRECTORY,
              VEDERE_APP_GUI_GTK_EXPLORE_ICON_ID_DIRECTORY,
              VEDERE_APP_GUI_GTK_EXPLORE_DEFAULT_ICON_ID_DIRECTORY))) {
            treeview_.set_icon_id_directory(icon_);
            icon_.destroy();
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    guint width_, height_;
    menu_bar menu_bar_;
    treeview treeview_;
    stock::icon icon_;
    gdk::pixbuf icon_pixbuf_;
    icon_set icon_set_;
    icon_factory icon_factory_;
};

} // namespace application 
} // namespace explore 
} // namespace app
} // namespace gtk
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_GTK_EXPLORE_APPLICATION_WINDOW_HPP 
