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
///   File: color.hpp
///
/// Author: $author$
///   Date: 11/17/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_COLOR_HPP
#define _VEDERE_GRAPHIC_IMAGE_COLOR_HPP

#include "vedere/base/base.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace color {
namespace space {

typedef uint64_t axis_t;
typedef int axes_t;
enum {
    axes_unknown,
    axes_rgba,
    axes_bgra
};

namespace rgba {
typedef int axis_t;
enum {
    axis_red,
    axis_green,
    axis_blue,
    axis_alpha,

    next_axis,
    first_axis = axis_red,
    last_axis = next_axis - 1,
    axes = last_axis - first_axis + 1
}; // enum axis_t
} // namespace rgba

namespace bgra {
typedef int axis_t;
enum {
    axis_blue,
    axis_green,
    axis_red,
    axis_alpha,

    next_axis,
    first_axis = axis_red,
    last_axis = next_axis - 1,
    axes = last_axis - first_axis + 1
}; // enum axis_t
} // namespace bgra

} // namespace space

} // namespace color 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_COLOR_HPP 
