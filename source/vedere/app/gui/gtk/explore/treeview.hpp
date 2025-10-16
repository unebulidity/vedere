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
///   File: treeview.hpp
///
/// Author: $author$
///   Date: 6/29/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_GTK_EXPLORE_TREEVIEW_HPP
#define _VEDERE_APP_GUI_GTK_EXPLORE_TREEVIEW_HPP

#include "vedere/app/gui/explore/directory/path.hpp"
#include "vedere/app/gui/explore/directory/entry.hpp"
#include "vedere/app/gui/explore/entry.hpp"
#include "vedere/app/gui/explore/time.hpp"
#include "vedere/app/gui/explore/treeview.hpp"
#include "vedere/gui/gtk/scrolled/treeview.hpp"
#include "vedere/gui/gtk/gtk.hpp"

#define VEDERE_APP_GUI_GTK_EXPLORE_ICON_ID_PREFIX "gvexplore-icon-"
#define VEDERE_APP_GUI_GTK_EXPLORE_ICON_FILENAME_EXTENSION ".png"

///////////////////////////////////////////////////////////////////////
#define VEDERE_APP_GUI_GTK_EXPLORE_DEFAULT_ICON_ID_FILE \
    GTK_STOCK_FILE

#define VEDERE_APP_GUI_GTK_EXPLORE_ICON_ID_FILE \
    VEDERE_APP_GUI_GTK_EXPLORE_ICON_ID_PREFIX "file"

#define VEDERE_APP_GUI_GTK_EXPLORE_ICON_FILENAME_FILE \
    VEDERE_APP_GUI_GTK_EXPLORE_ICON_ID_FILE \
    VEDERE_APP_GUI_GTK_EXPLORE_ICON_FILENAME_EXTENSION

///////////////////////////////////////////////////////////////////////
#define VEDERE_APP_GUI_GTK_EXPLORE_DEFAULT_ICON_ID_DIRECTORY \
    GTK_STOCK_DIRECTORY

#define VEDERE_APP_GUI_GTK_EXPLORE_ICON_ID_DIRECTORY \
    VEDERE_APP_GUI_GTK_EXPLORE_ICON_ID_PREFIX "directory"

#define VEDERE_APP_GUI_GTK_EXPLORE_ICON_FILENAME_DIRECTORY \
    VEDERE_APP_GUI_GTK_EXPLORE_ICON_ID_DIRECTORY \
    VEDERE_APP_GUI_GTK_EXPLORE_ICON_FILENAME_EXTENSION

namespace vedere {
namespace gui {
namespace gtk {
namespace app {
namespace explore {

typedef gtk::scrolled::treeview_implements treeview_implements;
typedef gtk::scrolled::treeview treeview_extends;
///////////////////////////////////////////////////////////////////////
///  Class: treeview
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS treeview
: virtual public treeview_implements, public treeview_extends {
public:
    typedef treeview_implements Implements;
    typedef treeview_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    treeview()
    : icon_id_file_(VEDERE_APP_GUI_GTK_EXPLORE_DEFAULT_ICON_ID_FILE),
      icon_id_directory_(VEDERE_APP_GUI_GTK_EXPLORE_DEFAULT_ICON_ID_DIRECTORY) {
    }
    virtual ~treeview() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual widget_attached_t create_attached_to() {
        widget_attached_t detached = create_attached
        (gui::app::explore::treeview_element);
        if ((detached)) {
            connect_signal_button_events();
        }
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool open(const char* name) {
        bool success = false;
        gui::app::explore::directory::path* path = 0;
        if ((path = gui::app::explore::directory::path::get_default())) {
            if ((path->open(name))) {
                success = on_path(*path);
                path->close();
            }
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool on_path
    (gui::app::explore::directory::path& p) {
        bool success = true;
        const gchar* icon = icon_id_directory_.chars();
        gui::app::explore::directory::entry* e = 0;
        GtkTreeIter parent;

        VEDERE_LOG_MESSAGE_DEBUG("on_path \"" << p.name() << "\"");
        if ((success = this->append
             (parent, row_column(gui::app::explore::treeview_column_name),
              p.name(), 0, icon))) {
            GtkTreeIter child;
            if ((e = p.get_first_entry())) {
                do {
                    success = on_entry(child, parent, p, *e);
                } while ((e = p.get_next_entry()));
            }
        }
        return success;
    }
    virtual bool on_path
    (GtkTreeIter& parent, gui::app::explore::directory::path& p) {
        bool success = true;
        gui::app::explore::directory::entry* e = 0;
        GtkTreeIter child;

        VEDERE_LOG_MESSAGE_DEBUG("on_path \"" << p.name() << "\"");
        if ((e = p.get_first_entry())) {
            do {
                success = on_entry(child, parent, p, *e);
            } while ((e = p.get_next_entry()));
        }
        return success;
    }
    virtual bool on_entry
    (GtkTreeIter& child, GtkTreeIter& parent,
     gui::app::explore::directory::path& p,
     const gui::app::explore::directory::entry& e) {
        bool success = true;
        gui::app::explore::entry_type_which t = e.type();
        const gchar* icon_chars = icon_id_file_.chars();
        const gchar* tooltip_chars = 0;
        gpointer data = 0;
        gstring tooltip;

        tooltip.appendl(p.name(), p.separator(), e.name(), NULL);
        tooltip_chars = tooltip.chars();
        VEDERE_LOG_MESSAGE_DEBUG("on_entry \"" << tooltip_chars << "\"");

        switch (t & (gui::app::explore::entry_type_directory)) {
        case gui::app::explore::entry_type_directory:
            icon_chars = icon_id_directory_.chars();
            break;
        }
        if ((success = this->append
             (child, parent, row_column(gui::app::explore::treeview_column_name), e.name(),
              data, icon_chars, tooltip_chars))) {
            on_append_entry(child, parent, p, e);
            switch (t & (gui::app::explore::entry_type_directory)) {
            case gui::app::explore::entry_type_directory: {
                gui::app::explore::directory::path* path = 0;
                if ((path = p.open(p, e))) {
                    success = on_path(child, *path);
                    path->close();
                }
                break; }
            }
        }
        return success;
    }
    virtual bool on_append_entry
    (GtkTreeIter& child, GtkTreeIter& parent,
     gui::app::explore::directory::path& p,
     const gui::app::explore::directory::entry& e) {
        bool success = true;
        gstring column;
        column.assign().append_uint64(e.size());
        this->set(child, row_column
        (gui::app::explore::treeview_column_size), column.chars());
        for (gui::app::explore::time_when_which t = gui::app::explore::first_time_when;
             t < gui::app::explore::next_time_when; t <<= 1) {
            if ((t & e.times())) {
                gint column_index = -1;
                gui::app::explore::time time;
                switch(t) {
                case gui::app::explore::time_when_modified: {
                    column_index = gui::app::explore::treeview_column_modified;
                    time = e.time_modified();
                    break; }
                case gui::app::explore::time_when_accessed: {
                    column_index = gui::app::explore::treeview_column_accessed;
                    time = e.time_accessed();
                    break; }
                case gui::app::explore::time_when_changed: {
                    column_index = gui::app::explore::treeview_column_changed;
                    time = e.time_changed();
                    break; }
                case gui::app::explore::time_when_created: {
                    column_index = gui::app::explore::treeview_column_created;
                    time = e.time_created();
                    break; }
                }
                if (0 < (column_index)) {
                    uint month = time.month(), day = time.day(), year = time.year();
                    column.assign().append_uint(month);
                    column.append("/");
                    column.append_uint(day);
                    column.append("/");
                    column.append_uint(year);
                    this->set(child, row_column(column_index), column.chars());
                }
            }
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual gstring& set_icon_id_file(const gchar* to) {
        icon_id_file_ = to;
        return icon_id_file_;
    }
    virtual gstring& set_icon_id_directory(const gchar* to) {
        icon_id_directory_ = to;
        return icon_id_directory_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    gstring icon_id_file_, icon_id_directory_;
};

} // namespace explore 
} // namespace app 
} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_GTK_EXPLORE_TREEVIEW_HPP 
