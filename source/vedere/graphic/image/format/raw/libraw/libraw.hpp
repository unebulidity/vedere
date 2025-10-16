///////////////////////////////////////////////////////////////////////
/// Copyright (C) 2008-2016 LibRaw LLC (http://www.libraw.org, info@libraw.org)
///
/// LibRaw is free software; you can redistribute it and/or modify
/// it under the terms of the one of three licenses as you choose:
///
/// 1. GNU LESSER GENERAL PUBLIC LICENSE version 2.1
///    (See file LICENSE.LGPL provided in LibRaw distribution archive for details).
///
/// 2. COMMON DEVELOPMENT AND DISTRIBUTION LICENSE (CDDL) Version 1.0
///    (See file LICENSE.CDDL provided in LibRaw distribution archive for details).
///
/// 3. LibRaw Software License 27032010
///    (See file LICENSE.LibRaw.pdf provided in LibRaw distribution archive for details).
///
///
/// LibRaw uses code from dcraw.c -- Dave Coffin's raw photo decoder,
/// dcraw.c is copyright 1997-2012 by Dave Coffin, dcoffin a cybercom o net.
///
/// LibRaw uses DCB demosaic and FBDD denoise licensed under BSD-like 3-clause license
/// DCB and FBDD are Copyright (C) 2010,  Jacek Gozdz (cuniek@kft.umcs.lublin.pl)
///
/// LibRaw uses X3F library to unpack Foveon Files, licensed BSD-style license
/// Copyright (c) 2010, Roland Karlsson (roland@proxel.se)
/// All rights reserved.
///
///   File: libraw.hpp
///
/// Author: $author$
///   Date: 2/24/2016
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_LIBRAW_LIBRAW_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_LIBRAW_LIBRAW_HPP

#include "lamna/graphic/image/format/raw/libraw/libraw.hpp"

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace raw {
namespace libraw {

typedef lamna::graphic::image::format::raw::libraw::imgdata_t imgdata_t;
typedef lamna::graphic::image::format::raw::libraw::colordata_t colordata_t;
typedef lamna::graphic::image::format::raw::libraw::output_params_t output_params_t;
typedef lamna::graphic::image::format::raw::libraw::color_cmatrix_t color_cmatrix_t;
typedef lamna::graphic::image::format::raw::libraw::curve_t curve_t;
typedef lamna::graphic::image::format::raw::libraw::gamm_t gamm_t;

typedef lamna::graphic::image::format::raw::libraw::to_rgb_row_t to_rgb_row_t;
typedef lamna::graphic::image::format::raw::libraw::to_rgb_vector_t to_rgb_vector_t;
typedef lamna::graphic::image::format::raw::libraw::to_rgb_matrix_t to_rgb_matrix_t;

inline void gamma_curve
(curve_t curve, gamm_t gamm, double pwr, double ts, int mode, int imax) {
    lamna::graphic::image::format::raw::libraw::gamma::curve(curve, gamm, pwr, ts, mode, imax);
}

} // namespace libraw
} // namespace raw 
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_RAW_LIBRAW_LIBRAW_HPP 
