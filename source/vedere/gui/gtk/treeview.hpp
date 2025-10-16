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
///   Date: 6/28/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_GTK_TREEVIEW_HPP
#define _VEDERE_GUI_GTK_TREEVIEW_HPP

#include "vedere/gui/gtk/container.hpp"
#include "vedere/gui/gtk/widget.hpp"
#include "vedere/gui/treeview.hpp"

#define VEDERE_GUI_GTK_TREEVIEW_LEVEL_INDENTATION 12

namespace vedere {
namespace gui {
namespace gtk {

typedef container_implements treeview_implements;
typedef gui::treeviewt
<treeview_implements, container, widget_attached_t> treeview_extends;
///////////////////////////////////////////////////////////////////////
///  Class: treeviewt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = treeview_implements, class TExtends = treeview_extends>

class _EXPORT_CLASS treeviewt
: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    treeviewt
    (widget_attached_t detached = 0, bool is_created = false)
    : Extends(detached, is_created),
      headers_visible_(TRUE),
      show_expanders_(TRUE),
      single_click_(TRUE),
      tree_lines_(FALSE),
      has_row_icons_(TRUE),
      has_row_data_(TRUE),
      has_row_tooltips_(TRUE),
      has_row_editable_(TRUE),
      level_indentation_(VEDERE_GUI_GTK_TREEVIEW_LEVEL_INDENTATION) {
    }
    virtual ~treeviewt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool append
    (GtkTreeIter& root, gint column, const gchar* chars,
     gpointer data = 0, const gchar* icon = 0, const gchar* tooltip = 0) {
        return append(root, root, column, chars, data, icon, tooltip);
    }
    virtual bool append
    (GtkTreeIter& child, GtkTreeIter &parent,
     gint column, const gchar* chars, gpointer data = 0,
     const gchar* icon = 0, const gchar* tooltip = 0) {
        GtkTreeModel* model = 0;
        GtkTreeStore* store = 0;
        if ((store = get_store(model))) {
            if ((&child != &parent)) {
                gtk_tree_store_append(store, &child, &parent);
            } else {
                gtk_tree_store_append(store, &child, 0);
            }
            if ((chars)) {
                gtk_tree_store_set(store, &child, column, chars, -1);
            }
            if ((data)) {
                gtk_tree_store_set
                (store, &child, data_row_column(), data, -1);
            }
            if ((icon)) {
                gtk_tree_store_set
                (store, &child, icon_row_column(), icon, -1);
            }
            if ((tooltip)) {
                gtk_tree_store_set
                (store, &child, tooltip_row_column(), tooltip, -1);
            }
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set
    (GtkTreeIter& child, gint column, const gchar* value) {
        GtkTreeModel* model = 0;
        GtkTreeStore* store = 0;
        if ((store = get_store(model))) {
            return set(*model, *store, child, column, value);
        }
        return false;
    }
    virtual bool set
    (GtkTreeModel& model, GtkTreeStore& store,
     GtkTreeIter& child, gint column, const gchar* value) {
        GType type = gtk_tree_model_get_column_type(&model, column);
        if (!(type != G_TYPE_STRING)) {
            gtk_tree_store_set(&store, &child, column, value, -1);
            return true;
        } else {
            VEDERE_LOG_ERROR("column " << column << " type != G_TYPE_STRING");
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool set
    (GtkTreeIter& child, gint column, const gpointer value) {
        GtkTreeModel* model = 0;
        GtkTreeStore* store = 0;
        if ((store = get_store(model))) {
            return set(*model, *store, child, column, value);
        }
        return false;
    }
    virtual bool set
    (GtkTreeModel& model, GtkTreeStore& store,
     GtkTreeIter& child, gint column, const gpointer value) {
        GType type = gtk_tree_model_get_column_type(&model, column);
        if (!(type != G_TYPE_POINTER)) {
            gtk_tree_store_set(&store, &child, column, value, -1);
            return true;
        } else {
            VEDERE_LOG_ERROR("column " << column << " type != G_TYPE_POINTER");
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool set
    (GtkTreeIter& child, gint column, const gboolean value) {
        GtkTreeModel* model = 0;
        GtkTreeStore* store = 0;
        if ((store = get_store(model))) {
            return set(*model, *store, child, column, value);
        }
        return false;
    }
    virtual bool set
    (GtkTreeModel& model, GtkTreeStore& store,
     GtkTreeIter& child, gint column, const gboolean value) {
        GType type = gtk_tree_model_get_column_type(&model, column);
        if (!(type != G_TYPE_BOOLEAN)) {
            gtk_tree_store_set(&store, &child, column, value, -1);
            return true;
        } else {
            VEDERE_LOG_ERROR("column " << column << " type != G_TYPE_BOOLEAN");
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual GtkTreeStore* get_store(GtkTreeModel*& model) const {
        if ((model = get_model())) {
            GtkTreeStore* store = GTK_TREE_STORE(model);
            return store;
        }
        return 0;
    }
    virtual GtkTreeModel* get_model() const {
        widget_attached_t detached = 0;
        if ((detached = this->attached_to())) {
            GtkTreeModel* model = 0;
            if ((model = gtk_tree_view_get_model(GTK_TREE_VIEW(detached)))) {
                return model;
            } else {
                VEDERE_LOG_ERROR("failed 0 == gtk_tree_view_get_model()");
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual widget_attached_t create_detached
    (widget_attached_t treeview, const treeview_element_t*& element) const {
        if ((treeview) && (element)) {
            gint columns = 0;
            GtkTreeStore* store = 0;
            for (const treeview_element_t*& e = element; (treeview) && (e->type); ++e) {
                treeview_element_type_t t = e->type;
                switch (t) {
                case treeview_element_type_header: {
                    if (!(columns)) {
                        if ((create_header_detached(columns, treeview, ++e))) {
                            break;
                        }
                    }
                    treeview = 0;
                    break; }
                case treeview_element_type_store: {
                    if (!(store)) {
                        if ((create_store_detached(store, treeview, ++e))) {
                            break;
                        }
                    }
                    treeview = 0;
                    break; }
                default: {
                    treeview = 0;
                    break; }
                }
            }
            return treeview;
        }
        return 0;
    }
    virtual widget_attached_t create_header_detached
    (gint& columns,
     widget_attached_t treeview, const treeview_element_t*& element) const {
        if ((treeview) && (element)) {
            for (const treeview_element_t*& e = element; (treeview) && (e->type); ++e) {
                treeview_element_type_t t = e->type;

                switch (t) {
                case treeview_element_type_column: {
                    const gchar* editable_attribute = "editable";
                    const gchar* column_attribute = "text";
                    GtkCellRenderer *column_renderer = gtk_cell_renderer_text_new();
                    gint column_index = e->id;
                    gint row_column_index = row_column(e->id);
                    GtkTreeViewColumn *column = 0;

                    if ((column_renderer)) {
                        if ((has_row_icons_) && (1 > (column_index))) {
                            const gchar* column_attribute0 = "stock-id";
                            GtkCellRenderer *column_renderer0 = gtk_cell_renderer_pixbuf_new();

                            if ((column = gtk_tree_view_column_new())) {
                                gtk_tree_view_column_set_title(column, e->label);
                                gtk_tree_view_column_pack_start(column, column_renderer0, FALSE);
                                gtk_tree_view_column_set_attributes
                                (column, column_renderer0, column_attribute0, icon_row_column(), NULL);
                                gtk_tree_view_column_pack_start(column, column_renderer, TRUE);
                                gtk_tree_view_column_set_attributes
                                (column, column_renderer,
                                 column_attribute, first_row_column(),
                                 (has_row_editable_)?(editable_attribute):(NULL),
                                 (has_row_editable_)?(editable_row_column()):(0), NULL);
                            }
                        } else {
                            column = gtk_tree_view_column_new_with_attributes
                            (e->label, column_renderer, column_attribute, row_column_index, NULL);
                        }

                        if ((column)) {
                            gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
                            columns += 1;
                            break;
                        } else {
                            g_object_unref(column_renderer);
                        }
                    }
                }
                default: {
                    treeview = 0;
                    break; }
                }
            }
            return treeview;
        }
        return 0;
    }
    virtual widget_attached_t create_store_detached
    (GtkTreeStore*& store,
     widget_attached_t treeview, const treeview_element_t*& element) const {
        if ((treeview) && (element)) {
            gint columns = 0;
            GType* types = 0;
            xos::base::arrayt<GType> types_array;

            if ((has_row_icons_)) {
                GType type = G_TYPE_STRING;
                types_array.append(&type, 1);
            }
            if ((has_row_tooltips_)) {
                GType type = G_TYPE_STRING;
                types_array.append(&type, 1);
            }
            if ((has_row_data_)) {
                GType type = G_TYPE_POINTER;
                types_array.append(&type, 1);
            }
            if ((has_row_editable_)) {
                GType type = G_TYPE_BOOLEAN;
                types_array.append(&type, 1);
            }
            for (const treeview_element_t*& e = element; (treeview) && (e->type); ++e) {
                treeview_element_type_t t = e->type;

                switch (t) {
                case treeview_element_type_column: {
                    GType type = G_TYPE_STRING;
                    switch(e->style) {
                    case treeview_element_style_double:
                        type = G_TYPE_DOUBLE;
                        break;
                    case treeview_element_style_integer:
                        type = G_TYPE_INT;
                        break;
                    case treeview_element_style_boolean:
                        type = G_TYPE_BOOLEAN;
                        break;
                    case treeview_element_style_void:
                        type = G_TYPE_POINTER;
                        break;
                    }
                    types_array.append(&type, 1);
                    break;
                }
                default: {
                    treeview = 0;
                    break; }
                }
            }
            if ((treeview)
                 && (0 < (columns = types_array.length()))
                 && (types = types_array.elements())) {
                if ((store = gtk_tree_store_newv(columns, types))) {
                    gtk_tree_view_set_model
                    (GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
                    g_object_unref(store);
                } else {
                    VEDERE_LOG_ERROR("failed on gtk_tree_store_newv(" << columns << ",...)");
                    treeview = 0;
                }
            }
            return treeview;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual widget_attached_t create_detached() const {
        widget_attached_t detached = 0;
        if ((detached = gtk_tree_view_new())) {
            gtk_tree_view_set_show_expanders(GTK_TREE_VIEW(detached), show_expanders_);
            gtk_tree_view_set_activate_on_single_click(GTK_TREE_VIEW(detached), single_click_);
            gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(detached), tree_lines_);
            gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(detached), headers_visible_);
            gtk_tree_view_set_level_indentation(GTK_TREE_VIEW(detached), level_indentation_);
            if ((has_row_tooltips_)) {
                gtk_tree_view_set_tooltip_column(GTK_TREE_VIEW(detached), tooltip_row_column());
            }
        } else {
            VEDERE_LOG_ERROR("failed on  gtk_tree_view_new()");
        }
        return detached;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void on_signal_row_double_clicked
    (GtkTreeView* instance, GtkTreeModel* model,
     GtkTreePath* path, GtkTreeIter* iter) {
        VEDERE_LOG_MESSAGE_DEBUG("on_signal_row_double_clicked()...");
        if (!(gtk_tree_view_row_expanded(instance, path))) {
            gtk_tree_view_expand_row(instance, path, FALSE);
        } else {
            gtk_tree_view_collapse_row(instance, path);
        }
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static void signal_2button_release_event_foreach
    (GtkTreeModel* model, GtkTreePath* path, GtkTreeIter* iter, gpointer data) {
        treeviewt* tv = ((treeviewt*)data);
        if ((tv)) {
            GtkWidget* detached = 0;
            if ((detached = tv->attached_to())) {
                tv->on_signal_row_double_clicked
                (GTK_TREE_VIEW(detached), model, path, iter);
            }
        }
    }
    virtual void on_signal_2button_release_event(GtkWidget* widget, GdkEvent* event) {
        widget_signals* to = 0;
        VEDERE_LOG_MESSAGE_DEBUG("on_signal_2button_release_event()...");
        if ((single_click_)) {
            GtkWidget* detached = 0;
            if ((detached = this->attached_to())) {
                GtkTreeSelection* sel = 0;
                if ((sel = gtk_tree_view_get_selection(GTK_TREE_VIEW(detached)))) {
                    if (1 == (gtk_tree_selection_count_selected_rows(sel))) {
                        gtk_tree_selection_selected_foreach
                        (sel, signal_2button_release_event_foreach, G_POINTER(this));
                    }
                }
            }
        }
        if ((to = this->widget_signals_forward_to())) {
            to->on_signal_2button_release_event(widget, event);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual gint row_column(gint column) const {
        return first_row_column() + column;
    }
    virtual gint icon_row_column() const {
        return 0;
    }
    virtual gint tooltip_row_column() const {
        return icon_row_column()+((has_row_icons_)?(1):(0));
    }
    virtual gint data_row_column() const {
        return tooltip_row_column()+((has_row_tooltips_)?(1):(0));
    }
    virtual gint editable_row_column() const {
        return data_row_column()+((has_row_data_)?(1):(0));
    }
    virtual gint first_row_column() const {
        return editable_row_column()+((has_row_editable_)?(1):(0));
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    gboolean headers_visible_, show_expanders_,
             single_click_, tree_lines_,
             has_row_icons_, has_row_data_,
             has_row_tooltips_, has_row_editable_;
    gint level_indentation_;
};
typedef treeviewt<> treeview;

} // namespace gtk
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_GTK_TREEVIEW_HPP 
