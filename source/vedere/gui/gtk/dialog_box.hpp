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
///   File: dialog_box.hpp
///
/// Author: $author$
///   Date: 8/29/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_DIALOG_BOX_HPP
#define _VEDERE_GUI_GTK_DIALOG_BOX_HPP

#include "vedere/gui/gtk/scrolled/window.hpp"
#include "vedere/gui/gtk/text_view.hpp"
#include "vedere/gui/gtk/progress_bar.hpp"
#include "vedere/gui/gtk/entry.hpp"
#include "vedere/gui/gtk/label.hpp"
#include "vedere/gui/gtk/frame.hpp"
#include "vedere/gui/gtk/box.hpp"
#include "vedere/gui/gtk/grid.hpp"
#include "vedere/gui/dialog.hpp"

#define VEDERE_GUI_GTK_DIALOG_MIN_EDIT_WIDTH 250

namespace vedere {
namespace gui {
namespace gtk {

typedef vertical::box_implements dialog_box_implements;
typedef dialogt
<dialog_box_implements,
 vertical::box, widget_attached_t> dialog_box_extends;
///////////////////////////////////////////////////////////////////////
///  Class: dialog_box
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS dialog_box
: virtual public dialog_box_implements, public dialog_box_extends {
public:
    typedef dialog_box_implements Implements;
    typedef dialog_box_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    dialog_box
    (widget_attached_t detached = 0, bool is_created = false)
    : Extends(detached, is_created),
      min_edit_width_(VEDERE_GUI_GTK_DIALOG_MIN_EDIT_WIDTH) {
    }
    virtual ~dialog_box() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual rows_attached_t create_rows_detached
    (dialog_items_t& items, attached_t detached) const {
        gtk::vertical::box box(detached);
        if ((detached)) {
            GtkWidget* frame_detached = 0;
            gtk::frame frame;
            if ((frame_detached = frame.create_attached())) {
                GtkWidget* grid_detached = 0;
                gtk::grid grid;
                if ((grid_detached = grid.create_attached())) {
                    grid.set_halign(GTK_ALIGN_CENTER);
                    frame.container_add(grid_detached);
                    box.pack_start(frame_detached);
                    return grid_detached;
                }
            }
        }
        return 0;
    }
    virtual row_attached_t create_row_detached
    (dialog_items_t& items, int& rownum,
     rows_attached_t rows, attached_t detached) const {
        return rows;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t create_text_col_detached
    (dialog_items_t& items, int& rownum, int& colnum,
     row_attached_t row, rows_attached_t rows,
     attached_t detached, const dialog_element_t*& element) const {
        gtk::grid grid(rows);
        if ((element)) {
            const dialog_element_t& e = *element;
            GtkWidget* label_detached = 0;
            gtk::label label;
            if ((label_detached = label.create_attached(e.label))) {
                dialog_item_t item(e.id, label_detached);
                GtkJustification justify = GTK_JUSTIFY_RIGHT;
                gfloat xalign = 1.0, yalign = 0.5;
                label.set_justify(justify);
                label.set_alignment(xalign, yalign);
                grid.attach(label_detached, colnum, rownum, 1,1);
                items.push_back(item);
                return label_detached;
            }
        }
        return 0;
    }
    virtual attached_t create_edit_col_detached
    (dialog_items_t& items, int& rownum, int& colnum,
     row_attached_t row, rows_attached_t rows,
     attached_t detached, const dialog_element_t*& element) const {
        gtk::grid grid(rows);
        if ((element)) {
            const dialog_element_t& e = *element;
            gint rowspan = (dialog_element_style_span_size & e.style)?(e.size.height):(1),
                 colspan = (dialog_element_style_span_size & e.style)?(e.size.width):(1);
            GtkWidget* entry_detached = 0;
            if (dialog_element_edit_style_multiline & (e.style)) {
                GtkWidget* frame_detached = 0;
                gtk::frame frame;
                if ((frame_detached = frame.create_attached())) {
                    GtkWidget* scrolled_detached = 0;
                    gtk::scrolled::window scrolled;
                    if ((scrolled_detached = scrolled.create_attached())) {
                        gtk::text_view text_view;
                        if ((entry_detached = text_view.create_attached())) {
                            dialog_item_t item(e.id, entry_detached);
                            items.push_back(item);
                            scrolled.container_add(entry_detached);
                            entry_detached = scrolled_detached;
                        }
                        frame.container_add(scrolled_detached);
                        entry_detached = frame_detached;
                    }
                }
            } else {
                gtk::entry entry;
                if ((entry_detached = entry.create_attached())) {
                    dialog_item_t item(e.id, entry_detached);
                    if (dialog_element_edit_style_readonly & (e.style)) {
                        entry.set_editable(FALSE);
                    }
                    if (dialog_element_edit_style_invisible & (e.style)) {
                        entry.set_visibility(FALSE);
                    }
                    items.push_back(item);
                 }
            }
            if ((entry_detached)) {
                gtk::widget entry(entry_detached);
                entry.set_size_request(min_edit_width(), 0);
                grid.attach(entry_detached, colnum, rownum, colspan, rowspan);
                return entry_detached;
            }
        }
        return 0;
    }
    virtual attached_t create_progress_col_detached
    (dialog_items_t& items, int& rownum, int& colnum,
     row_attached_t row, rows_attached_t rows,
     attached_t detached, const dialog_element_t*& element) const {
        gtk::grid grid(rows);
        if ((element)) {
            const dialog_element_t& e = *element;
            gint rowspan = (dialog_element_style_span_size & e.style)?(e.size.height):(1),
                 colspan = (dialog_element_style_span_size & e.style)?(e.size.width):(1);
            GtkWidget* progress_bar_detached = 0;
            gtk::progress_bar progress_bar;
            if ((progress_bar_detached = progress_bar.create_attached())) {
                dialog_item_t item(e.id, progress_bar_detached);
                grid.attach(progress_bar_detached, colnum, rownum, colspan, rowspan);
                items.push_back(item);
                return progress_bar_detached;
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual gint min_edit_width() const {
        return min_edit_width_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    gint min_edit_width_;
};

} // namespace gtk 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_DIALOG_BOX_HPP 
