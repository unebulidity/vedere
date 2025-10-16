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
///   File: bmp.hpp
///
/// Author: $author$
///   Date: 11/24/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GRAPHIC_IMAGE_FORMAT_BMP_IMPLEMENT_BMP_HPP
#define _VEDERE_GRAPHIC_IMAGE_FORMAT_BMP_IMPLEMENT_BMP_HPP

#include "vedere/base/base.hpp"

#if !defined(WINDOWS)
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef struct tagRGBQUAD {
  BYTE rgbBlue;
  BYTE rgbGreen;
  BYTE rgbRed;
  BYTE rgbReserved;
} RGBQUAD;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef struct tagRGBTRIPLE {
  BYTE rgbtBlue;
  BYTE rgbtGreen;
  BYTE rgbtRed;
} RGBTRIPLE;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    BF_BM = 0x424D
};

// All of the integer values are stored in little-endian format
// (i.e. least-significant byte first)
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef struct tagBITMAPFILEHEADER {
  WORD  bfType;
  DWORD bfSize;
  WORD  bfReserved1;
  WORD  bfReserved2;
  DWORD bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
enum {
    BI_RGB = 0x0000,
    BI_RLE8 = 0x0001,
    BI_RLE4 = 0x0002,
    BI_BITFIELDS = 0x0003,
    BI_JPEG = 0x0004,
    BI_PNG = 0x0005,
    BI_CMYK = 0x000B,
    BI_CMYKRLE8 = 0x000C,
    BI_CMYKRLE4 = 0x000D
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;
  LONG  biWidth;
  LONG  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;
#else // !defined(WINDOWS)
#endif // !defined(WINDOWS)

namespace vedere {
namespace graphic {
namespace image {
namespace format {
namespace bmp {
namespace implement {

typedef xos::base::arrayt<BYTE> byte_array;

typedef xos::base::arrayt<RGBQUAD> rgb_quad_array_extends;
///////////////////////////////////////////////////////////////////////
///  Class: rgb_quad_array
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS rgb_quad_array: public rgb_quad_array_extends {
public:
    typedef rgb_quad_array_extends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read(byte_reader& reader, size_t length) {
        ssize_t count = 0;

        if (length == (this->set_length(length))) {
            RGBQUAD* quads = 0;

            if ((quads = this->elements())) {
                BYTE byte = 0;

                for (size_t i = 0; i < length; ++i, ++quads, ++count) {
                    RGBQUAD& quad = *quads;

                    if (1 == (reader.read(&byte, 1))) {
                        quad.rgbBlue = byte;
                        if (1 == (reader.read(&byte, 1))) {
                            quad.rgbGreen = byte;
                            if (1 == (reader.read(&byte, 1))) {
                                quad.rgbRed = byte;
                                if (1 == (reader.read(&byte, 1))) {
                                    quad.rgbReserved = byte;
                                    continue;
                                }
                            }
                        }
                    }
                    return 0;
                }
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef xos::base::wrappedt<RGBQUAD> rgb_quad_extends_t;
///////////////////////////////////////////////////////////////////////
///  Class: rgb_quad_t
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS rgb_quad_t: public rgb_quad_extends_t {
public:
    typedef rgb_quad_extends_t Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    rgb_quad_t(BYTE blue, BYTE green, BYTE red, BYTE reserved) {
        RGBQUAD& rgb = this->wrapped();
        rgb.rgbBlue = blue;
        rgb.rgbGreen = green;
        rgb.rgbRed = red;
        rgb.rgbReserved = reserved;
    }
    virtual ~rgb_quad_t() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef xos::base::wrappedt<RGBTRIPLE> rgb_extends_t;
///////////////////////////////////////////////////////////////////////
///  Class: rgb_t
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS rgb_t: public rgb_extends_t {
public:
    typedef rgb_extends_t Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    rgb_t(BYTE blue, BYTE green, BYTE red) {
        RGBTRIPLE& rgb = this->wrapped();
        rgb.rgbtBlue = blue;
        rgb.rgbtGreen = green;
        rgb.rgbtRed = red;
    }
    virtual ~rgb_t() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef xos::base::wrappedt<BITMAPFILEHEADER> bfh_extends_t;
///////////////////////////////////////////////////////////////////////
///  Class: bfh_t
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS bfh_t: public bfh_extends_t {
public:
    typedef bfh_extends_t Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    bfh_t() {
    }
    virtual ~bfh_t() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read(byte_reader& reader) {
        BITMAPFILEHEADER& bfh = this->wrapped();
        ssize_t count = 0, amount = 0;
        DWORD dword = 0;
        WORD word = 0;

        if (sizeof(WORD) == (amount = reader.WORD_read_lsb(word))) {
            bfh.bfType = word;
            count += amount;

            if (sizeof(DWORD) == (amount = reader.DWORD_read_lsb(dword))) {
                bfh.bfSize = dword;
                count += amount;

                if (sizeof(WORD) == (amount = reader.WORD_read_lsb(word))) {
                    bfh.bfReserved1 = word;
                    count += amount;

                    if (sizeof(WORD) == (amount = reader.WORD_read_lsb(word))) {
                        bfh.bfReserved2 = word;
                        count += amount;

                        if (sizeof(DWORD) == (amount = reader.DWORD_read_lsb(dword))) {
                            bfh.bfOffBits = dword;
                            count += amount;
                            return count;
                        }
                    }
                }
            }
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef xos::base::wrappedt<BITMAPINFOHEADER> bih_extends_t;
///////////////////////////////////////////////////////////////////////
///  Class: bih_t
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS bih_t: public bih_extends_t {
public:
    typedef bih_extends_t Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    bih_t() {
    }
    virtual ~bih_t() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read(byte_reader& reader) {
        BITMAPINFOHEADER& bih = this->wrapped();
        ssize_t count = 0, amount = 0;
        DWORD dword = 0;
        WORD word = 0;
        LONG llong = 0;

        if (sizeof(DWORD) == (amount = reader.DWORD_read_lsb(dword))) {
            bih.biSize= dword;
            count += amount;

            if (sizeof(LONG) == (amount = reader.LONG_read_lsb(llong))) {
                bih.biWidth = llong;
                count += amount;

                if (sizeof(LONG) == (amount = reader.LONG_read_lsb(llong))) {
                    bih.biHeight = llong;
                    count += amount;

                    if (sizeof(WORD) == (amount = reader.WORD_read_lsb(word))) {
                        bih.biPlanes = word;
                        count += amount;

                        if (sizeof(WORD) == (amount = reader.WORD_read_lsb(word))) {
                            bih.biBitCount = word;
                            count += amount;

                            if (sizeof(DWORD) == (amount = reader.DWORD_read_lsb(dword))) {
                                bih.biCompression = dword;
                                count += amount;

                                if (sizeof(DWORD) == (amount = reader.DWORD_read_lsb(dword))) {
                                    bih.biSizeImage = dword;
                                    count += amount;

                                    if (sizeof(LONG) == (amount = reader.LONG_read_lsb(llong))) {
                                        bih.biXPelsPerMeter = llong;
                                        count += amount;

                                        if (sizeof(LONG) == (amount = reader.LONG_read_lsb(llong))) {
                                            bih.biYPelsPerMeter = llong;
                                            count += amount;

                                            if (sizeof(DWORD) == (amount = reader.DWORD_read_lsb(dword))) {
                                                bih.biClrUsed = dword;
                                                count += amount;

                                                if (sizeof(DWORD) == (amount = reader.DWORD_read_lsb(dword))) {
                                                    bih.biClrImportant = dword;
                                                    count += amount;
                                                    return count;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace implement
} // namespace bmp
} // namespace format 
} // namespace image 
} // namespace graphic 
} // namespace vedere 

#endif // _VEDERE_GRAPHIC_IMAGE_FORMAT_BMP_IMPLEMENT_BMP_HPP
