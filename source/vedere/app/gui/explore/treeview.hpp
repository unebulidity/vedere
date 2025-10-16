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
///   Date: 8/24/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_EXPLORE_TREEVIEW_HPP
#define _VEDERE_APP_GUI_EXPLORE_TREEVIEW_HPP

#include "vedere/gui/treeview.hpp"

namespace vedere {
namespace gui {
namespace app {
namespace explore {

enum {
    treeview_column_name,
    treeview_column_size,
    treeview_column_type,
    treeview_column_modified,
    treeview_column_accessed,
    treeview_column_changed,
    treeview_column_created,
};

static const treeview_element_t treeview_element[] = {
    {treeview_element_type_treeview},
        {treeview_element_type_header},
            {treeview_element_type_column, treeview_element_style_string, "Name", treeview_column_name},
            {treeview_element_type_column, treeview_element_style_string, "Size", treeview_column_size},
            {treeview_element_type_column, treeview_element_style_string, "Type", treeview_column_type},
            {treeview_element_type_column, treeview_element_style_string, "Modified", treeview_column_modified},
            {treeview_element_type_column, treeview_element_style_string, "Accessed", treeview_column_accessed},
            {treeview_element_type_column, treeview_element_style_string, "Changed", treeview_column_changed},
            {treeview_element_type_column, treeview_element_style_string, "Created", treeview_column_created},
            {treeview_element_type_none},
        {treeview_element_type_store},
            {treeview_element_type_column, treeview_element_style_string, 0, treeview_column_name},
            {treeview_element_type_column, treeview_element_style_string, 0, treeview_column_size},
            {treeview_element_type_column, treeview_element_style_string, 0, treeview_column_type},
            {treeview_element_type_column, treeview_element_style_string, 0, treeview_column_modified},
            {treeview_element_type_column, treeview_element_style_string, 0, treeview_column_accessed},
            {treeview_element_type_column, treeview_element_style_string, 0, treeview_column_changed},
            {treeview_element_type_column, treeview_element_style_string, 0, treeview_column_created},
            {treeview_element_type_none},
        {treeview_element_type_none},
    {treeview_element_type_none},
};

} // namespace explore
} // namespace app 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_EXPLORE_TREEVIEW_HPP 
