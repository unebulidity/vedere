%########################################################################
%# Copyright (c) 1988-2020 $organization$
%#
%# This software is provided by the author and contributors ``as is'' 
%# and any express or implied warranties, including, but not limited to, 
%# the implied warranties of merchantability and fitness for a particular 
%# purpose are disclaimed. In no event shall the author or contributors 
%# be liable for any direct, indirect, incidental, special, exemplary, 
%# or consequential damages (including, but not limited to, procurement 
%# of substitute goods or services; loss of use, data, or profits; or 
%# business interruption) however caused and on any theory of liability, 
%# whether in contract, strict liability, or tort (including negligence 
%# or otherwise) arising in any way out of the use of this software, 
%# even if advised of the possibility of such damage.
%#
%#   File: set_image_format-hpp.t
%#
%# Author: $author$
%#   Date: 12/25/2020
%########################################################################
%with(%
%is_application,%(%else-then(%is_application%,%(%is_Application%)%)%)%,%
%application,%(%else-then(%if-no(%is_application%,,%(%application%)%)%,%(%if-no(%is_application%,,%(Hello)%)%)%)%)%,%
%Application,%(%else-then(%if-no(%is_application%,,%(%Application%)%)%,%(%if-no(%is_application%,,%(%application%)%)%)%)%)%,%
%APPLICATION,%(%else-then(%APPLICATION%,%(%toupper(%Application%)%)%)%)%,%
%application,%(%else-then(%_application%,%(%tolower(%Application%)%)%)%)%,%
%is_format,%(%else-then(%is_format%,%(%is_Format%)%)%)%,%
%format,%(%else-then(%if-no(%is_format%,,%(%format%)%)%,%(%if-no(%is_format%,,%(Png)%)%)%)%)%,%
%Format,%(%else-then(%if-no(%is_format%,,%(%Format%)%)%,%(%if-no(%is_format%,,%(%format%)%)%)%)%)%,%
%FORMAT,%(%else-then(%FORMAT%,%(%toupper(%Format%)%)%)%)%,%
%format,%(%else-then(%_format%,%(%tolower(%Format%)%)%)%)%,%
%%(    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_image_format(const char_t* to) {
    #if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)
        if ((to) && (to[0])) {
            VEDERE_LOG_MESSAGE_DEBUG("set image_format = \"" << to << "\"...");
            if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_%FORMAT%_OPTARG_C))
                || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_%FORMAT%_OPTARG_S))) {
                VEDERE_LOG_MESSAGE_DEBUG("image_format = image_format_%format%");
                image_format_ = image_format_%format%;
                load_image_ = &Derives::%format%_load_image;
            } else {
            }
        }
    #endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)
        return to;
    }
)%)%