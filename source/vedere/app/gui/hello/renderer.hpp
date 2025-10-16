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
///   File: renderer.hpp
///
/// Author: $author$
///   Date: 10/22/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_HELLO_RENDERER_HPP
#define _VEDERE_APP_GUI_HELLO_RENDERER_HPP

#include "vedere/app/gui/hello/renderer_extend.hpp"

namespace vedere {
namespace app {
namespace gui {
namespace hello {

enum renderer_image_format_t {
    IMAGE_RENDERER_IMAGE_FORMAT_NONE
};
enum renderer_aspect_ratio_mode_t {
    IMAGE_RENDERER_ASPECT_RATIO_MODE_IGNORE,
    IMAGE_RENDERER_ASPECT_RATIO_MODE_KEEP
};
enum renderer_transformation_mode_t {
    IMAGE_RENDERER_TRANSFORMATION_MODE_NONE,
    IMAGE_RENDERER_TRANSFORMATION_MODE_FAST,
    IMAGE_RENDERER_TRANSFORMATION_MODE_SMOOTH
};

typedef gui::hello::image_renderert
<renderer_image_format_t, IMAGE_RENDERER_IMAGE_FORMAT_NONE,
 renderer_aspect_ratio_mode_t, IMAGE_RENDERER_ASPECT_RATIO_MODE_IGNORE,
 renderer_transformation_mode_t, IMAGE_RENDERER_TRANSFORMATION_MODE_NONE>
image_renderer_implements;

typedef gui::hello::image_renderer_extendt
<image_renderer_implements> image_renderer;

typedef implement_base renderer_implements;
typedef base renderer_extends;
typedef renderer_extendt
<renderer_image_format_t, IMAGE_RENDERER_IMAGE_FORMAT_NONE,
 image_renderer, renderer_implements, renderer_extends> renderer;

} // namespace hello 
} // namespace gui 
} // namespace app 
} // namespace vedere 

#endif // _VEDERE_APP_GUI_HELLO_RENDERER_HPP 
