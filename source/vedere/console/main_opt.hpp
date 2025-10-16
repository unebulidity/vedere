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
///   File: main_opt.hpp
///
/// Author: $author$
///   Date: 5/27/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_CONSOLE_MAIN_OPT_HPP
#define _VEDERE_CONSOLE_MAIN_OPT_HPP

#include "vedere/base/base.hpp"
#include "lamna/console/main.hpp"
#include "lamna/console/main_opt.hpp"

#define VEDERE_MAIN_LOGGING_OPTVAL_C LAMNA_MAIN_LOGGING_OPTVAL_C
#define VEDERE_MAIN_LOGGING_OPTARG LAMNA_MAIN_LOGGING_OPTARG
#define VEDERE_MAIN_LOGGING_OPTUSE LAMNA_MAIN_LOGGING_OPTUSE

#define VEDERE_MAIN_HELP_OPTVAL_C LAMNA_MAIN_HELP_OPTVAL_C
#define VEDERE_MAIN_HELP_OPTARG LAMNA_MAIN_HELP_OPTARG
#define VEDERE_MAIN_HELP_OPTUSE LAMNA_MAIN_HELP_OPTUSE

#define VEDERE_MAIN_OPTIONS_CHARS LAMNA_MAIN_OPTIONS_CHARS
#define VEDERE_MAIN_OPTIONS_OPTIONS LAMNA_MAIN_OPTIONS_OPTIONS

enum {
    VEDERE_MAIN_OPT_ARGUMENT_NONE     = LAMNA_MAIN_OPT_ARGUMENT_NONE,
    VEDERE_MAIN_OPT_ARGUMENT_REQUIRED = LAMNA_MAIN_OPT_ARGUMENT_REQUIRED,
    VEDERE_MAIN_OPT_ARGUMENT_OPTIONAL = LAMNA_MAIN_OPT_ARGUMENT_OPTIONAL
};

namespace vedere {
namespace console {

typedef int main_opt_argument_t;
enum {
    MAIN_OPT_ARGUMENT_NONE     = lamna::console::MAIN_OPT_ARGUMENT_NONE,
    MAIN_OPT_ARGUMENT_REQUIRED = lamna::console::MAIN_OPT_ARGUMENT_REQUIRED,
    MAIN_OPT_ARGUMENT_OPTIONAL = lamna::console::MAIN_OPT_ARGUMENT_OPTIONAL
};

} // namespace console

namespace app {
namespace console {

typedef vedere::console::main_opt_argument_t main_opt_argument_t;
enum {
    MAIN_OPT_ARGUMENT_NONE     = vedere::console::MAIN_OPT_ARGUMENT_NONE,
    MAIN_OPT_ARGUMENT_REQUIRED = vedere::console::MAIN_OPT_ARGUMENT_REQUIRED,
    MAIN_OPT_ARGUMENT_OPTIONAL = vedere::console::MAIN_OPT_ARGUMENT_OPTIONAL
};

} // namespace console
} // namespace app

namespace app {
namespace gui {

typedef vedere::console::main_opt_argument_t main_opt_argument_t;
enum {
    MAIN_OPT_ARGUMENT_NONE     = vedere::console::MAIN_OPT_ARGUMENT_NONE,
    MAIN_OPT_ARGUMENT_REQUIRED = vedere::console::MAIN_OPT_ARGUMENT_REQUIRED,
    MAIN_OPT_ARGUMENT_OPTIONAL = vedere::console::MAIN_OPT_ARGUMENT_OPTIONAL
};

} // namespace gui
} // namespace app
} // namespace vedere

#endif // _VEDERE_CONSOLE_MAIN_OPT_HPP 
