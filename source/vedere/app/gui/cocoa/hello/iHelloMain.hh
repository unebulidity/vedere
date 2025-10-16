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
///   File: iHelloMain.hh
///
/// Author: $author$
///   Date: 11/7/2015
///////////////////////////////////////////////////////////////////////
#ifndef _VEDERE_APP_GUI_COCOA_HELLO_IHELLOMAIN_HH
#define _VEDERE_APP_GUI_COCOA_HELLO_IHELLOMAIN_HH

#include "lamna/gui/cocoa/iWindowMain.hh"
#include "vedere/app/gui/cocoa/hello/renderer.hh"
#include "vedere/app/gui/cocoa/hello/image_renderer.hh"
#include "vedere/app/gui/hello/main.hpp"

#define VEDERE_APP_GUI_COCOA_HELLO_WINDOW_TITLE "ivhello"

namespace vedere {
namespace app {
namespace gui {
namespace cocoa {
namespace hello {

} // namespace hello
} // namespace cocoa
} // namespace gui
} // namespace app 
} // namespace vedere 

///////////////////////////////////////////////////////////////////////
/// Interface: iHelloMainView
///////////////////////////////////////////////////////////////////////
@interface iHelloMainView: iMainView {
    vedere::app::gui::cocoa::hello::renderer* renderer_;
    }
    - (id)init:(vedere::app::gui::cocoa::hello::renderer*)renderer;
    - (void)drawRect:(iRect)rect;
    - (void)boundsDidResize:(NSNotification*)notification;
    - (void)mouseUp:(iEvent*)theEvent;
    - (void)switchRender;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iHelloMainWindow
///////////////////////////////////////////////////////////////////////
@interface iHelloMainWindow: iMainWindow {
    vedere::app::gui::cocoa::hello::renderer* renderer_;
    }
    - (iMainWindow*)initWithRect:(iRect)contentRect
                    argc:(int)argc argv:(char**)argv env:(char**)env
                    renderer:(vedere::app::gui::cocoa::hello::renderer*)renderer;
    - (iView*)createMainView:(int)argc argv:(char**)argv env:(char**)env;
    - (void)windowDidResize:(NSNotification*)notification;
    - (void)invalidate;
@end

///////////////////////////////////////////////////////////////////////
/// Interface: iHelloMain
///////////////////////////////////////////////////////////////////////
@interface iHelloMain: iWindowMain {
    vedere::app::gui::cocoa::hello::renderer* renderer_;
    }
    - (id)init:(lamna::gui::main*)main;
    - (iMainWindow*)createMainWindow:(iRect)contentRect
                    argc:(int)argc argv:(char**)argv env:(char**)env;
    - (iRect)contentRect:(int)argc argv:(char**)argv env:(char**)env;
    - (int)beforeRunApplication:(iApplication*)app argc:(int)argc argv:(char**)argv env:(char**)env;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    - (int)onOption:(int)optval optarg:(const char*)optarg optname:(const char*)optname optind:(int)optind argc:(int)argc argv:(char**)argv env:(char**)env;
    - (int)onArgument:(const char*)arg argind:(int)argind argc:(int)argc argv:(char**)argv env:(char**)env;
    - (const char*)optionUsage:(const char*&)optarg longopt:(const struct option*)longopt;
    - (const char*)options:(const struct option*&)longopts;
    - (const char*)arguments:(const char**&)args;
@end

#endif // _VEDERE_APP_GUI_COCOA_HELLO_IHELLOMAIN_HH
