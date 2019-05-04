//
//  PHXDefaultFactory.mm
//  CocoaPhoenix
//
//  Created by Bodie Solomon on 5/3/19.
//

#import "CocoaPhoenix.hpp"

@implementation PHXDefaultFactory

+ (PHXViewDelegate* _Nullable) configurePhoenix:(MetalPhoenix&)p
                                       withView:(MTKView* _Nonnull)view
                                 withFullscreen:(BOOL)fullscreen {
    auto x = view.bounds.size.width, y = view.bounds.size.height;
    
    {
        id<PHXRenderer> renderer = [[self class] makeRendererWithView:view
                                                       withFullscreen:fullscreen];
        
        auto g = MetalGfx(mtlp::MetalRenderer(renderer), x, y);
        auto inp = input::Input(&input::simple);
        
        p = phx::Phoenix(std::move(g), std::move(inp));
    }
    
    return [PHXViewDelegate makeWithPhoenix:&p];
}

+ (id<PHXRenderer>) makeRendererWithView:(MTKView*)view
                          withFullscreen:(BOOL)fullscreen {
    return [PHXMetalRenderer makeWithView:view withFullscreen:fullscreen];
}

+ (PHXResponder* _Nullable) makeResponderWithView:(MTKView* _Nonnull)view
                                        withInput:(PHXInput* _Nonnull)inp {
    return [PHXResponder makeWithView:view withInput:inp];
}

@end
