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
///   File: os.hh
///
/// Author: $author$
///   Date: 11/6/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_GUI_COCOA_OS_OS_HH
#define _VEDERE_GUI_COCOA_OS_OS_HH

#include "lamna/gui/cocoa/os/os.hh"

namespace vedere {
namespace gui {
namespace cocoa {
namespace apple {
namespace ios { }
namespace osx { }
} // namespace apple
namespace os {

#if defined(APPLE_IOS)
namespace os = apple::ios;
#else // defined(APPLE_IOS)
namespace os = apple::osx;
#endif // defined(APPLE_IOS)

} // namespace os
} // namespace cocoa 
} // namespace gui 
} // namespace vedere 

#endif // _VEDERE_GUI_COCOA_OS_OS_HH 
        

