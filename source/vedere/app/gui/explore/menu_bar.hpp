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
///   File: menu_bar.hpp
///
/// Author: $author$
///   Date: 8/26/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_EXPLORE_MENU_BAR_HPP
#define _VEDERE_APP_GUI_EXPLORE_MENU_BAR_HPP

#include "vedere/gui/menu.hpp"

namespace vedere {
namespace gui {
namespace app {
namespace explore {

enum {
    menu_bar_item_id_file = 100,

    menu_bar_item_id_file_new,
    menu_bar_item_id_file_open,
    menu_bar_item_id_file_close,
    menu_bar_item_id_file_save,
    menu_bar_item_id_file_save_as,
    menu_bar_item_id_file_receint,
    menu_bar_item_id_file_exit,

    next_menu_bar_item_id_file,
    first_menu_bar_item_id_file = (menu_bar_item_id_file + 1),
    last_menu_bar_item_id_file = (next_menu_bar_item_id_file - 1),
    count_menu_bar_item_id_file = (last_menu_bar_item_id_file - first_menu_bar_item_id_file + 1)
};

enum {
    menu_bar_item_id_edit = 200,

    menu_bar_item_id_edit_undo,
    menu_bar_item_id_edit_cut,
    menu_bar_item_id_edit_copy,
    menu_bar_item_id_edit_paste,

    next_menu_bar_item_id_edit,
    first_menu_bar_item_id_edit = (menu_bar_item_id_edit + 1),
    last_menu_bar_item_id_edit = (next_menu_bar_item_id_edit - 1),
    count_menu_bar_item_id_edit = (last_menu_bar_item_id_edit - first_menu_bar_item_id_edit + 1)
};

enum {
    menu_bar_item_id_view = 300,

    menu_bar_item_id_view_sidebar,
    menu_bar_item_id_view_toolbar,
    menu_bar_item_id_view_statusbar,
    menu_bar_item_id_view_split,
    menu_bar_item_id_view_large_icons,
    menu_bar_item_id_view_small_icons,
    menu_bar_item_id_view_list,
    menu_bar_item_id_view_details,

    menu_bar_item_id_view_arrange,
    menu_bar_item_id_view_arrange_folders_first,
    menu_bar_item_id_view_arrange_name,
    menu_bar_item_id_view_arrange_date,
    menu_bar_item_id_view_arrange_auto,

    next_menu_bar_item_id_view,
    first_menu_bar_item_id_view = (menu_bar_item_id_view + 1),
    last_menu_bar_item_id_view = (next_menu_bar_item_id_view - 1),
    count_menu_bar_item_id_view = (last_menu_bar_item_id_view - first_menu_bar_item_id_view + 1)
};

enum {
    menu_bar_item_id_help = 400,

    menu_bar_item_id_help_about,

    next_menu_bar_item_id_help,
    first_menu_bar_item_id_help = (menu_bar_item_id_help + 1),
    last_menu_bar_item_id_help = (next_menu_bar_item_id_help - 1),
    count_menu_bar_item_id_help = (last_menu_bar_item_id_help - first_menu_bar_item_id_help + 1)
};

const menu_element_t menu_bar_element[] = {
    {menu_element_type_menubar, 0, 0},
        {menu_element_type_menu, menu_bar_item_id_file, "File"},
            {menu_element_type_item, menu_bar_item_id_file_new, "New"},
            {menu_element_type_item, menu_bar_item_id_file_open, "Open..."},
            {menu_element_type_item, menu_bar_item_id_file_close, "Close"},
            {menu_element_type_separator},
            {menu_element_type_item, menu_bar_item_id_file_save, "Save"},
            {menu_element_type_item, menu_bar_item_id_file_save_as, "Save As..."},
            {menu_element_type_separator},
            {menu_element_type_item, menu_bar_item_id_file_receint, "Receint"},
            {menu_element_type_separator},
            {menu_element_type_item, menu_bar_item_id_file_exit, "Exit"},
            {menu_element_type_none},
        {menu_element_type_menu, menu_bar_item_id_edit, "Edit"},
            {menu_element_type_item, menu_bar_item_id_edit_undo, "Undo"},
            {menu_element_type_separator},
            {menu_element_type_item, menu_bar_item_id_edit_cut, "Cut"},
            {menu_element_type_item, menu_bar_item_id_edit_copy, "Copy"},
            {menu_element_type_item, menu_bar_item_id_edit_paste, "Pase"},
            {menu_element_type_none},
        {menu_element_type_menu, menu_bar_item_id_view, "View"},
            {menu_element_type_item, menu_bar_item_id_view_sidebar, "Sidebar", menu_element_style_item_checked},
            {menu_element_type_item, menu_bar_item_id_view_toolbar, "Toolbar", menu_element_style_item_checked},
            {menu_element_type_item, menu_bar_item_id_view_statusbar, "Status Bar", menu_element_style_item_checked},
            {menu_element_type_item, menu_bar_item_id_view_split, "Split", menu_element_style_item_checked},
            {menu_element_type_separator},
            {menu_element_type_item, menu_bar_item_id_view_large_icons, "Large Icons", menu_element_style_item_radio},
            {menu_element_type_item, menu_bar_item_id_view_small_icons, "Small Icons", menu_element_style_item_radio},
            {menu_element_type_item, menu_bar_item_id_view_list, "List", menu_element_style_item_radio},
            {menu_element_type_item, menu_bar_item_id_view_details, "Details", menu_element_style_item_radio},
            {menu_element_type_separator},
            {menu_element_type_menu, menu_bar_item_id_view_arrange, "Arrange"},
                {menu_element_type_item, menu_bar_item_id_view_arrange_folders_first, "Folders First", menu_element_style_item_checked},
                {menu_element_type_separator},
                {menu_element_type_item, menu_bar_item_id_view_arrange_name, "By Name", menu_element_style_item_radio},
                {menu_element_type_item, menu_bar_item_id_view_arrange_date, "By Date", menu_element_style_item_radio},
                {menu_element_type_item, menu_bar_item_id_view_arrange_auto, "Auto Arrange", menu_element_style_item_radio},
                {menu_element_type_none},
            {menu_element_type_none},
        {menu_element_type_menu, menu_bar_item_id_help, "Help"},
            {menu_element_type_item, menu_bar_item_id_help_about, "About"},
            {menu_element_type_none},
        {menu_element_type_none},
    {menu_element_type_none},
};

} // namespace explore
} // namespace app 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_EXPLORE_MENU_BAR_HPP 
