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
///   File: iHelloMain.mm
///
/// Author: $author$
///   Date: 11/7/2015
///////////////////////////////////////////////////////////////////////
#include "vedere/app/gui/cocoa/hello/iHelloMain.hh"

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
/// Implentation: iHelloMainView
///////////////////////////////////////////////////////////////////////
@implementation iHelloMainView
    - (id)init:(vedere::app::gui::cocoa::hello::renderer*)renderer {
        [super init];
        renderer_ = renderer;
        return self;
    }
    - (void)drawRect:(iRect)rect {
        iRect bounds = [self bounds];
        iCGContextRef context = (iCGContextRef)[[iGraphicsContext currentContext] graphicsPort];
        size_t width = (bounds.size.width), height = (bounds.size.height);
        [super drawRect:rect];
        if ((renderer_)) {
            renderer_->init(context, width, height);
            renderer_->render();
            renderer_->finish();
        }
    }
    - (void)boundsDidResize:(NSNotification*)notification {
        iRect bounds = [self bounds];
        size_t width = (bounds.size.width), height = (bounds.size.height);
        VEDERE_LOG_MESSAGE_DEBUG("boundsDidResize width = " << width << " height = " << height << "...");
    }
    - (void)mouseUp:(iEvent*)theEvent {
        iPoint point = [theEvent locationInWindow];
        int x = point.x, y = point.y;
        VEDERE_LOG_MESSAGE_DEBUG("mouseUp x = " << x << " y = " << y << "...");
        [self performSelectorOnMainThread:@selector(switchRender) withObject:nil waitUntilDone:NO];
    }
    - (void)switchRender {
        VEDERE_LOG_MESSAGE_DEBUG("switchRender...");
        renderer_->switch_render();
        [self setNeedsDisplay:TRUE];
    }
@end

//////////////////////////////////////////////////////////////////////
/// Implentation: iHelloMainWindow
///////////////////////////////////////////////////////////////////////
@implementation iHelloMainWindow
    - (iHelloMainWindow*)initWithRect:(iRect)contentRect
                         argc:(int)argc argv:(char**)argv env:(char**)env
                         renderer:(vedere::app::gui::cocoa::hello::renderer*)renderer {
        [super initWithRect:contentRect argc:argc argv:argv env:env];
        renderer_ = renderer;
        return self;
    }
    - (iView*)createMainView:(int)argc argv:(char**)argv env:(char**)env {
        if ((mainView_ = [[iHelloMainView alloc] init:renderer_])) {
        }
        return mainView_;
    }
    - (const char*)mainTitleUTF8String:(int)argc argv:(char**)argv env:(char**)env {
        return VEDERE_APP_GUI_COCOA_HELLO_WINDOW_TITLE;
    }
    - (void)windowDidResize:(NSNotification*)notification {
        if ((mainView_)) {
            [mainView_ boundsDidResize:notification];
        }
    }
    - (void)invalidate {
        if ((mainView_)) {
            [mainView_ setNeedsDisplay:TRUE];
        }
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iHelloMain
///////////////////////////////////////////////////////////////////////
@implementation iHelloMain
    - (id)init:(lamna::gui::main*)main {
        [super init:main];
        renderer_ = new vedere::app::gui::cocoa::hello::renderer();
        return self;
    }
    - (iMainWindow*)createMainWindow:(iRect)contentRect
                    argc:(int)argc argv:(char**)argv env:(char**)env {
        iMainWindow* mainWindow = [[iHelloMainWindow alloc]
                                   initWithRect:contentRect
                                   argc:argc argv:argv env:env renderer:renderer_];
        return mainWindow;
    }
    - (iRect)contentRect:(int)argc argv:(char**)argv env:(char**)env {
        int x = LAMNA_GUI_COCOA_IWINDOWMAIN_WINDOW_X,
            y = LAMNA_GUI_COCOA_IWINDOWMAIN_WINDOW_Y,
            width = VEDERE_APP_GUI_HELLO_MAIN_WINDOW_WIDTH,
            height = VEDERE_APP_GUI_HELLO_MAIN_WINDOW_HEIGHT;
        iRect contentRect = iMakeRect(x,y, width, height);
        return contentRect;
    }
    - (int)beforeRunApplication:(iApplication*)app argc:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        if ((renderer_->load_image_file())) {
            [mainWindow_ invalidate];
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    - (int)onOption:(int)optval optarg:(const char*)optarg optname:(const char*)optname optind:(int)optind argc:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        switch(optval) {
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_OPTVAL_C:
            renderer_->set_image_format_option(optarg);
            break;
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_OPTVAL_C:
            renderer_->set_image_transform_option(optarg);
            break;
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_WIDTH_OPTVAL_C:
            renderer_->set_image_width_option(optarg);
            break;
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_HEIGHT_OPTVAL_C:
            renderer_->set_image_height_option(optarg);
            break;
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_DEPTH_OPTVAL_C:
            renderer_->set_image_depth_option(optarg);
            break;
        default:
            err = [super onOption:optval optarg:optarg optname:optname optind:optind argc:argc argv:argv env:env];
            break;
        }
        return err;
    }
    - (int)onArgument:(const char*)arg argind:(int)argind argc:(int)argc argv:(char**)argv env:(char**)env {
        int err = 0;
        switch(argind) {
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FILE_ARG:
            renderer_->set_image_file_option(arg);
            break;
        default:
            err = [super onArgument:arg argind:argind argc:argc argv:argv env:env];
            break;
        }
        return err;
    }
    - (const char*)optionUsage:(const char*&)optarg longopt:(const struct option*)longopt {
        const char* chars = "";
        switch(longopt->val) {
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_OPTVAL_C:
            optarg = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_OPTARG;
            chars = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_FORMAT_OPTUSE;
            break;
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_OPTVAL_C:
            optarg = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_OPTARG;
            chars = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_TRANSFORM_OPTUSE;
            break;
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_WIDTH_OPTVAL_C:
            optarg = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_WIDTH_OPTARG;
            chars = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_WIDTH_OPTUSE;
            break;
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_HEIGHT_OPTVAL_C:
            optarg = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_HEIGHT_OPTARG;
            chars = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_HEIGHT_OPTUSE;
            break;
        case VEDERE_APP_GUI_HELLO_MAIN_IMAGE_DEPTH_OPTVAL_C:
            optarg = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_DEPTH_OPTARG;
            chars = VEDERE_APP_GUI_HELLO_MAIN_IMAGE_DEPTH_OPTUSE;
            break;
        default:
            chars = [super optionUsage:optarg longopt:longopt];
            break;
        }
        return chars;
    }
    - (const char*)options:(const struct option*&)longopts {
        static const char* chars = VEDERE_APP_GUI_HELLO_MAIN_OPTIONS_CHARS;
        static struct option optstruct[] = {
            VEDERE_APP_GUI_HELLO_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }
    - (const char*)arguments:(const char**&)args {
        static const char* _args = VEDERE_APP_GUI_HELLO_MAIN_ARGS;
        static const char* _argv[] = {
            VEDERE_APP_GUI_HELLO_MAIN_ARGV
            0};
        args = _argv;
        return _args;
    }
@end

///////////////////////////////////////////////////////////////////////
/// Implentation: iMain
///////////////////////////////////////////////////////////////////////
@implementation iMain
    + (id<iOptMain>)create:(lamna::gui::main*)main {
        return [[iHelloMain alloc] init:main];
    }
@end
