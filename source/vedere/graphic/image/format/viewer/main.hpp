///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   File: main.hpp
///
/// Author: $author$
///   Date: 7/17/2016, 1/15/2021, 3/13/2024
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_MAIN_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_MAIN_HPP

#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_JPEG_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_LIB_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)
#include "vedere/graphic/image/format/jpeg/libjpeg/image_reader.hpp"
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_JPEG_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_LIB_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)

#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_PNG_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_LIB_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)
#include "vedere/graphic/image/format/png/libpng/image_reader.hpp"
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_PNG_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_LIB_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)

#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_GIF_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_LIB_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)
#include "vedere/graphic/image/format/gif/giflib/image_reader.hpp"
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_GIF_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_LIB_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)

#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_TIFF_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_LIB_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)
#include "vedere/graphic/image/format/tiff/libtiff/image_reader.hpp"
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_TIFF_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_LIB_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)

#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_PGM_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)
#include "vedere/graphic/image/format/raw/libpgm/image_reader.hpp"
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_PGM_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)

#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_DNG_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)
#include "vedere/graphic/image/format/raw/libraw/image_reader.hpp"
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_DNG_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)

#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_BGRA_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)
#include "vedere/graphic/image/format/raw/bgra/image_reader.hpp"
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_BGRA_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)

#include "vedere/graphic/image/format/viewer/main_opt.hpp"
#include "vedere/graphic/image/format/viewer/image_loader.hpp"
#include "vedere/graphic/image/format/viewer/image_reader.hpp"
#include "vedere/gui/main.hpp"
#include "vedere/base/base.hpp"

#define VEDERE_APP_GUI_HELLO_MAIN_WINDOW_WIDTH 500
#define VEDERE_APP_GUI_HELLO_MAIN_WINDOW_HEIGHT 250

#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_PNG_VIEWER)
#else /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_PNG_VIEWER)
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_PNG_VIEWER)

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace viewer {

enum image_transform_t {
    image_transform_fast,
    image_transform_smooth,

    next_image_transform,
    first_image_transform = image_transform_fast,
    last_image_transform = (next_image_transform - 1),
    image_transforms = (last_image_transform - first_image_transform + 1)
};

typedef vedere::gui::main_implements main_implements;
typedef vedere::gui::main main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: maint
///////////////////////////////////////////////////////////////////////
template
<class TImplements = main_implements, class TExtends = main_extends>

class _EXPORT_CLASS maint
: virtual public image_loader,
  virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef maint Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    maint(): 
#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)
      load_image_(0),
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)
      main_window_width_(VEDERE_APP_GUI_HELLO_MAIN_WINDOW_WIDTH),
      main_window_height_(VEDERE_APP_GUI_HELLO_MAIN_WINDOW_HEIGHT),
      image_width_(0), image_height_(0), image_depth_(0),
      image_format_(first_image_format),
      raw_image_format_(first_raw_image_format),
      image_transform_(first_image_transform) {
    }
    virtual ~maint() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using image_loader::load_image;
    virtual bool load_raw_image
    (size_t image_width, size_t image_height,size_t image_depth, 
     const char_t* image_file, raw_image_format_t raw_image_format) {
#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_BGRA_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)
            graphic::image::format::raw::bgra::to_bgra_image_reader reader;
            VEDERE_LOG_MESSAGE_DEBUG("reader.init(image_height = " << image_height << ", image_width = " << image_width << ", image_depth = " << image_depth << ")...");
            if (!(reader.init(image_height_, image_width_, image_depth_))) {
                VEDERE_LOG_MESSAGE_ERROR("...failed on reader.init(image_height = " << image_height << ", image_width = " << image_width << ", image_depth = " << image_depth << ")");
                return false;
            } else {
                VEDERE_LOG_MESSAGE_DEBUG("reader.read(\"" << image_file << "\")...");
                if ((reader.read(image_file))) {
                    VEDERE_LOG_MESSAGE_DEBUG("load_image(reader)...");
                    if ((load_image(reader))) {
                        VEDERE_LOG_MESSAGE_DEBUG("...load_image(reader)");
                        return true;
                    } else {
                        VEDERE_LOG_MESSAGE_ERROR("...failed on load_image(reader)");
                    }
                } else {
                    VEDERE_LOG_MESSAGE_ERROR("...failed on reader.read(\"" << image_file << "\")");
                }
            }
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_BGRA_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)
        return false;
    }
    virtual bool load_image(const char_t* image_file, image_format_t image_format) {
#if !defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER) && !defined(VEDERE_GRAPHIC_IMAGE_FORMAT_LIB_VIEWER)
#if !defined(VEDERE_GRAPHIC_IMAGE_FORMAT_NONE_VIEWER)
        VEDERE_LOG_MESSAGE_DEBUG("load_image(" <<  chars_to_string(image_file) << ", " << image_format << ")...");
        if ((image_file) && (image_file[0])) {
#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_JPEG_VIEWER)
            graphic::image::format::jpeg::libjpeg::to_bgra_image_reader reader;
#elif defined(VEDERE_GRAPHIC_IMAGE_FORMAT_PNG_VIEWER)
            graphic::image::format::png::libpng::to_bgra_image_reader reader;
#elif defined(VEDERE_GRAPHIC_IMAGE_FORMAT_GIF_VIEWER)
            graphic::image::format::gif::giflib::to_bgra_image_reader reader;
#elif defined(VEDERE_GRAPHIC_IMAGE_FORMAT_TIFF_VIEWER)
            graphic::image::format::tiff::libtiff::to_bgra_image_reader reader;
#elif defined(VEDERE_GRAPHIC_IMAGE_FORMAT_DNG_VIEWER)
            graphic::image::format::raw::libraw::to_bgra_image_reader reader;
#elif defined(VEDERE_GRAPHIC_IMAGE_FORMAT_PGM_VIEWER)
            graphic::image::format::raw::libpgm::to_bgra_image_reader reader;
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_JPEG_VIEWER)
#if !defined(VEDERE_GRAPHIC_IMAGE_FORMAT_BGRA_VIEWER)
            if ((reader.read(image_file))) {
                if ((load_image(reader))) {
                    return true;
                }
            } else {
            }
#endif /// !defined(VEDERE_GRAPHIC_IMAGE_FORMAT_BGRA_VIEWER)
        } else {
        }
        VEDERE_LOG_MESSAGE_DEBUG("...load_image(" <<  chars_to_string(image_file) << ", " << image_format << ")");
#endif /// !defined(VEDERE_GRAPHIC_IMAGE_FORMAT_NONE_VIEWER)
#else /// !defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER) && !defined(VEDERE_GRAPHIC_IMAGE_FORMAT_LIB_VIEWER)
        if ((default_load_image(image_file, image_format))) {
            return true;
        }
#endif /// !defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER) && !defined(VEDERE_GRAPHIC_IMAGE_FORMAT_LIB_VIEWER)
        return false;
    }
#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_LIB_VIEWER)
    bool (Derives::*load_image_)(const char_t* image_file, image_format_t image_format);
    virtual bool default_load_image(const char_t* image_file, image_format_t image_format) {
        if ((this->load_image_)) {
            if (((this->*load_image_)(image_file, image_format))) {
                return true;
            }
        } else {
            if ((jpeg_load_image(image_file, image_format))) {
                return true;
            }
        }
        return false;
    }
    virtual bool png_load_image(const char_t* image_file, image_format_t image_format) {
        image_readert<graphic::image::format::png::libpng::to_bgra_image_reader> image_reader;
        if ((load_image(image_reader, image_file, image_format))) {
            return true;
        }
        return false;
    }
    virtual bool jpeg_load_image(const char_t* image_file, image_format_t image_format) {
        image_readert<graphic::image::format::jpeg::libjpeg::to_bgra_image_reader> image_reader;
        if ((load_image(image_reader, image_file, image_format))) {
            return true;
        }
        return false;
    }
    virtual bool tiff_load_image(const char_t* image_file, image_format_t image_format) {
        image_readert<graphic::image::format::tiff::libtiff::to_bgra_image_reader> image_reader;
        if ((load_image(image_reader, image_file, image_format))) {
            return true;
        }
        return false;
    }
    virtual bool gif_load_image(const char_t* image_file, image_format_t image_format) {
        image_readert<graphic::image::format::gif::giflib::to_bgra_image_reader> image_reader;
        if ((load_image(image_reader, image_file, image_format))) {
            return true;
        }
        return false;
    }
    virtual bool bmp_load_image(const char_t* image_file, image_format_t image_format) {
        /*image_readert<graphic::image::format::bmp::implemented::to_bgra_image_reader> image_reader;
        if ((load_image(image_reader, image_file, image_format))) {
            return true;
        }*/
        return false;
    }
    virtual bool pgm_load_image(const char_t* image_file, image_format_t image_format) {
#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)
        image_readert<graphic::image::format::raw::libpgm::to_bgra_image_reader> image_reader;
        if ((load_image(image_reader, image_file, image_format))) {
            return true;
        }
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)
        return false;
    }
    virtual bool dng_load_image(const char_t* image_file, image_format_t image_format) {
#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)
        image_readert<graphic::image::format::raw::libraw::to_bgra_image_reader> image_reader;
        if ((load_image(image_reader, image_file, image_format))) {
            return true;
        }
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER)
        return false;
    }
    virtual bool load_image(graphic::image::format::viewer::image_reader& reader, const char_t* image_file, image_format_t image_format) {
        VEDERE_LOG_MESSAGE_DEBUG("load_image(..., " <<  chars_to_string(image_file) << ", " << image_format << ")...");
        if ((image_file) && (image_file[0])) {
            if ((reader.read_image(image_file))) {
                if ((load_image(reader))) {
                    return true;
                }
            }
        }
        VEDERE_LOG_MESSAGE_DEBUG("...load_image(..., " <<  chars_to_string(image_file) << ", " << image_format << ")");
        return false;
    }
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_LIB_VIEWER)

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_image_format(const char_t* to) {
#if defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_LIB_VIEWER)
        if ((to) && (to[0])) {
            VEDERE_LOG_MESSAGE_DEBUG("set image_format = \"" << to << "\"...");
            if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_PNG_OPTARG_C))
                || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_PNG_OPTARG_S))) {
                VEDERE_LOG_MESSAGE_DEBUG("image_format = image_format_png");
                image_format_ = image_format_png;
                load_image_ = &Derives::png_load_image;
            } else {
                if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_JPEG_OPTARG_C))
                    || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_JPEG_OPTARG_S))) {
                    VEDERE_LOG_MESSAGE_DEBUG("image_format = image_format_jpeg");
                    image_format_ = image_format_jpeg;
                    load_image_ = &Derives::jpeg_load_image;
                } else {
                    if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_TIFF_OPTARG_C))
                        || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_TIFF_OPTARG_S))) {
                        VEDERE_LOG_MESSAGE_DEBUG("image_format = image_format_tiff");
                        image_format_ = image_format_tiff;
                        load_image_ = &Derives::tiff_load_image;
                    } else {
                        if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_GIF_OPTARG_C))
                            || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_GIF_OPTARG_S))) {
                            VEDERE_LOG_MESSAGE_DEBUG("image_format = image_format_gif");
                            image_format_ = image_format_gif;
                            load_image_ = &Derives::gif_load_image;
                        } else {
                            if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_BMP_OPTARG_C))
                                || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_BMP_OPTARG_S))) {
                                VEDERE_LOG_MESSAGE_DEBUG("image_format = image_format_bmp");
                                image_format_ = image_format_bmp;
                                load_image_ = &Derives::bmp_load_image;
                            } else {
                                if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_PGM_OPTARG_C))
                                    || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_PGM_OPTARG_S))) {
                                    VEDERE_LOG_MESSAGE_DEBUG("image_format = image_format_pgm");
                                    image_format_ = image_format_pgm;
                                    load_image_ = &Derives::pgm_load_image;
                                } else {
                                    if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_DNG_OPTARG_C))
                                        || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_DNG_OPTARG_S))) {
                                        VEDERE_LOG_MESSAGE_DEBUG("image_format = image_format_dng");
                                        image_format_ = image_format_dng;
                                        load_image_ = &Derives::dng_load_image;
                                    } else {
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
#endif /// defined(VEDERE_GRAPHIC_IMAGE_FORMAT_ALL_VIEWER) || defined(VEDERE_GRAPHIC_IMAGE_FORMAT_LIB_VIEWER)
        return to;
    }
    virtual const char_t* set_image_transform(const char_t* to) {
        if ((to) && (to[0])) {
            VEDERE_LOG_MESSAGE_DEBUG("set image_transform = \"" << to << "\"...");
            if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_FAST_OPTARG_C))
                || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_FAST_OPTARG_S))) {
                VEDERE_LOG_MESSAGE_DEBUG("image_transform = image_transform_fast");
                image_transform_ = image_transform_fast;
            } else {
                if ((!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_SMOOTH_OPTARG_C))
                    || (!chars_t::compare(to, VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_SMOOTH_OPTARG_S))) {
                    VEDERE_LOG_MESSAGE_DEBUG("image_transform = image_transform_smooth");
                    image_transform_ = image_transform_smooth;
                } else {
                }
            }
        }
        return to;
    }
    virtual const char_t* set_use_opengl(const char_t* to) {
        bool on = true;
        set_use_opengl(on);
        return to;
    }
    virtual bool set_use_opengl(bool to) {
        return to;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_image_width(const char_t* to) {
        if ((to) && (to[0])) {
            VEDERE_LOG_MESSAGE_DEBUG("set image_width = \"" << to << "\"...");
            image_width_ = chars_t::to_unsigned(to);
        }
        return to;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_image_height(const char_t* to) {
        if ((to) && (to[0])) {
            VEDERE_LOG_MESSAGE_DEBUG("set image_height = \"" << to << "\"...");
            image_height_ = chars_t::to_unsigned(to);
        }
        return to;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_image_depth(const char_t* to) {
        if ((to) && (to[0])) {
            VEDERE_LOG_MESSAGE_DEBUG("set image_depth = \"" << to << "\"...");
            image_depth_ = chars_t::to_unsigned(to);
        }
        return to;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_image_file(const char_t* to) {
        if ((to) && (to[0])) {
            VEDERE_LOG_MESSAGE_DEBUG("set image_file = \"" << to << "\"...");
            image_file_.assign(to);
        }
        return to;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
#include "vedere/graphic/image/format/viewer/main_opt.cpp"

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    size_t main_window_width_, main_window_height_,
           image_width_, image_height_, image_depth_;
    image_format_t image_format_;
    raw_image_format_t raw_image_format_;
    image_transform_t image_transform_;
    string image_file_;
};

} // namespace viewer
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_VIEWER_MAIN_HPP 
