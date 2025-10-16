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
///   File: base.hpp
///
/// Author: $author$
///   Date: 5/26/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_BASE_BASE_HPP
#define _VEDERE_BASE_BASE_HPP

#include "lamna/base/base.hpp"
#include "xos/mt/queue.hpp"
#include "xos/io/write/file.hpp"
#include "xos/io/read/file.hpp"
#include "xos/io/writer.hpp"
#include "xos/io/reader.hpp"

namespace vedere {

typedef lamna::implement_base implement_base;
typedef lamna::base extend_base;
typedef lamna::base base;

typedef implement_base implement;
typedef extend_base extend;

typedef xos::base::chars_t chars_t;
typedef xos::base::tchars_t tchars_t;
typedef xos::base::wchars_t wchars_t;

typedef xos::base::string string;
typedef xos::base::tstring tstring;
typedef xos::base::wstring wstring;

typedef xos::base::date_implements date_implements;
typedef xos::base::date date;

typedef xos::io::reader reader;
typedef xos::io::writer writer;

typedef xos::io::byte_reader byte_reader;
typedef xos::io::byte_writer byte_writer;

typedef lamna::chars_to_string chars_to_string;
typedef lamna::pointer_to_string pointer_to_string;

} // namespace vedere

#endif // _VEDERE_BASE_BASE_HPP 
