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
///   File: dialog.hpp
///
/// Author: $author$
///   Date: 8/29/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_CRYPTO_HASH_DIALOG_HPP
#define _VEDERE_APP_GUI_CRYPTO_HASH_DIALOG_HPP

#include "vedere/gui/dialog.hpp"

#define VEDERE_APP_GUI_CRYPTO_HASH_DIALOG_TEXT_ID 2000
#define VEDERE_APP_GUI_CRYPTO_HASH_DIALOG_EDIT_ID 1000

namespace vedere {
namespace gui {
namespace app {
namespace crypto {
namespace hash {

typedef int dialog_text_id_t;
enum {
    dialog_text_id = VEDERE_APP_GUI_CRYPTO_HASH_DIALOG_TEXT_ID,
    dialog_text_id_hash,
    dialog_text_id_file,
    dialog_text_id_text,
    dialog_text_id_progress,
};

typedef int dialog_edit_id_t;
enum {
    dialog_edit_id = VEDERE_APP_GUI_CRYPTO_HASH_DIALOG_EDIT_ID,
    dialog_edit_id_hash,
    dialog_edit_id_file,
    dialog_edit_id_text,
    dialog_edit_id_progress,
};

const dialog_element_t dialog_entry[] = {
{dialog_element_type_dialog, 0, "Hash"},
    //
    // Hash
    //
    {dialog_element_type_row, 0,0, dialog_element_style_none},
        {dialog_element_type_text, dialog_text_id_hash,
         "Hash", dialog_element_style_none},
        {dialog_element_type_edit, dialog_edit_id_hash,
         "", dialog_element_edit_style_readonly},
        {dialog_element_type_none},
    //
    // File
    //
    {dialog_element_type_row, 0,0, dialog_element_style_none},
        {dialog_element_type_text, dialog_text_id_file,
         "File", dialog_element_style_none},
        {dialog_element_type_edit, dialog_edit_id_file,
         "", dialog_element_style_none},
        {dialog_element_type_none},
    //
    // Text
    //
    {dialog_element_type_row, 0,0, dialog_element_style_none},
        {dialog_element_type_text, dialog_text_id_text,
         "Text", dialog_element_style_none},
        {dialog_element_type_edit, dialog_edit_id_text,
         "", (dialog_element_edit_style_multiline
              | dialog_element_style_span_size), {1, 2}},
        {dialog_element_type_none},
    //
    // progress
    //
    {dialog_element_type_row, 0,0, dialog_element_style_none},
        {dialog_element_type_progress, dialog_text_id_progress,
         "", dialog_element_style_span_size, {2, 1}},
        {dialog_element_type_none},
    {dialog_element_type_none},
{dialog_element_type_none}
};

} // namespace hash
} // namespace crypto 
} // namespace app 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_CRYPTO_HASH_DIALOG_HPP 
