//
//  PHXRenderer_iOS.mm
//  CocoaPhoenix
//
//  Created by Bodie Solomon on 5/3/19.
//

#import "CocoaPhoenix.hpp"

// TODO: Reduce redundancy by refactoring into "fullscreener" + whatever else
@implementation PHXMetalRenderer {
    PHXResourceManager* _manager;
}

+ (void)enterFullscreenForView:(MTKView* _Nonnull)view {
    [view enterFullScreenMode:[NSScreen mainScreen]
                  withOptions:@{NSFullScreenModeAllScreens: @YES}];
}

+ (instancetype _Nullable)makeWithView:(MTKView* _Nonnull)view
                        withFullscreen:(BOOL)fullscreen {
    PHXMetalRenderer* tmp = [[super alloc] init];
    
    if (!tmp) {
        NSLog(@"Failed to allocate PHXMetalRenderer");
        return nil;
    }
    
    auto manager = [PHXResourceManager makeWithDevice:view.device];
    if (!manager) {
        NSLog(@"Failed to create resource manager for PHXMetalRenderer");
        return nil;
    }
    
    // If iOS, ignore "fullscreen" since apps are always fullscreen.
    // TODO: Implement this using two classes?
    if (fullscreen) {
        [self enterFullscreenForView:view];
    }
    
    tmp->_manager = manager;
    
    // Was MTLPixelFormatRGBA8Unorm, but no!
    // https://developer.apple.com/documentation/quartzcore/cametallayer/1478155-pixelformat
    // The pixel format for a Metal layer must be
    //   - MTLPixelFormatBGRA8Unorm
    //   - MTLPixelFormatBGRA8Unorm_sRGB
    //   - MTLPixelFormatRGBA16Float
    //   - MTLPixelFormatBGRA10_XR
    //   - or MTLPixelFormatBGRA10_XR_sRGB.
    // The default value is MTLPixelFormatBGRA8Unorm.
    
    auto fmt = MTLPixelFormatBGRA8Unorm;
    NSError* err = NULL;
    
    // TODO: Support the use of externally-defined shaders, located by NSBundle.
    auto url = [manager findShaderLibraryWithName:@"PHXMetal-macOS"];
    [manager loadShadersWithFormat:fmt withError:err withURL:url];
    if (err) {
        NSLog(@"Failed to load shaders: %@", err);
        return nil;
    }
    
    // Set the view's color format to be the same as the target.
    [view setColorPixelFormat:fmt];
    
    [manager prepareTexturesWithCGSize:view.drawableSize];
    
    [manager createCommandQueue];
    
    return tmp;
}

- (void)drawInMTKView:(MTKView* _Nonnull)view {
    [_manager drawInView:view];
}

- (void)mtkView:(MTKView* _Nonnull)view drawableSizeWillChange:(CGSize)size {
    [_manager updateToCGSize:size];
}

// TODO
- (void)update { }
- (void)clear  { }

- (void)draw:(MTKView* _Nonnull)view {
    [self drawInMTKView:view];
}

- (void)drawPointAt:(simd_int2)point withColor:(MTLClearColor)color {
    // TODO
}

@end
