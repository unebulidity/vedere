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
///   File: pixel.hpp
///
/// Author: $author$
///   Date: 11/17/2015, 1/14/2021
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_PIXEL_HPP
#define _VEDERE_GRAPHIC_IMAGE_PIXEL_HPP

#include "vedere/graphic/image/color.hpp"

namespace vedere {
namespace graphic {
namespace image {

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef int pixel_value_interpretation_t;
enum {
    pixel_value_interpretation_none,
    pixel_value_interpretation_palette,
    pixel_value_interpretation_greyscale,
    pixel_value_interpretation_rgb,
    pixel_value_interpretation_bgr,
    pixel_value_interpretation_rgba,
    pixel_value_interpretation_bgra,
    pixel_value_interpretation_argb,
    pixel_value_interpretation_abgr,

    next_pixel_value_interpretation,
    first_pixel_value_interpretation = (pixel_value_interpretation_none),
    last_pixel_value_interpretation  = (next_pixel_value_interpretation - 1),
    pixel_value_interpretations      = (last_pixel_value_interpretation - first_pixel_value_interpretation + 1)
};

typedef implement_base pixel_implements;
///////////////////////////////////////////////////////////////////////
///  Class: pixelt
///////////////////////////////////////////////////////////////////////
template <class TImplements = pixel_implements>
class _EXPORT_CLASS pixelt: virtual public TImplements {
public:
    typedef TImplements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual color::space::axis_t color_axis(color::space::axes_t which) const {
        return 0;
    }
    virtual color::space::axis_t color_axis_min() const {
        return 0;
    }
    virtual color::space::axis_t color_axis_max() const {
        return 0;
    }
    virtual color::space::axes_t first_color_axis() const {
        return 0;
    }
    virtual color::space::axes_t last_color_axis() const {
        return 0;
    }
    virtual color::space::axes_t color_axes() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef pixelt<> pixel_t;

namespace rgba {

typedef image::pixel_t pixel_implements;
typedef base pixel_extends;
///////////////////////////////////////////////////////////////////////
///  Class: pixelt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = pixel_implements, class TExtends = pixel_extends>
class _EXPORT_CLASS pixelt: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    pixelt
    (color::space::axis_t red, color::space::axis_t green, color::space::axis_t blue,
     color::space::axis_t alpha = 255, color::space::axis_t max = 255)
    : red_(red), green_(green), blue_(blue),
      alpha_(alpha), max_(max) {
    }
    pixelt(const pixelt& copy)
    : red_(copy.red_), green_(copy.green_), blue_(copy.blue_),
      alpha_(copy.alpha_), max_(copy.max_) {
    }
    virtual ~pixelt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual color::space::axis_t color_axis(color::space::axes_t which) const {
        switch (which) {
        case color::space::rgba::axis_red:
            return red_;
        case color::space::rgba::axis_green:
            return green_;
        case color::space::rgba::axis_blue:
            return blue_;
        case color::space::rgba::axis_alpha:
            return alpha_;
        }
        return 0;
    }
    virtual color::space::axis_t color_axis_min() const {
        return 0;
    }
    virtual color::space::axis_t color_axis_max() const {
        return max_;
    }
    virtual color::space::axes_t first_color_axis() const {
        return color::space::rgba::axis_red;
    }
    virtual color::space::axes_t last_color_axis() const {
        return  color::space::rgba::axis_alpha;
    }
    virtual color::space::axes_t color_axes() const {
        return color::space::axes_rgba;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual pixelt& operator()
    (color::space::axis_t red, color::space::axis_t green, color::space::axis_t blue,
     color::space::axis_t alpha = 255, color::space::axis_t max = 255) {
        red_ = red; green_ = green; blue_ = blue; alpha_ = alpha; max_ = max;
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    color::space::axis_t red_, green_, blue_, alpha_, max_;
};
typedef pixelt<> pixel_t;

} // namespace rgba

} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_PIXEL_HPP 
