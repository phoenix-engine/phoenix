//
//  GameViewController.m
//  CocoaPhoenixTestingApp macOS
//
//  Created by Bodie Solomon on 4/10/19.
//

#import "GameViewController.hpp"

@implementation TestAppPHXFactory

+ (PHXViewDelegate* _Nullable) configurePhoenix:(MetalPhoenix&)phx
                                       withView:(MTKView* _Nonnull)view
                                 withFullscreen:(BOOL)fullscreen {
    
    auto vd = [super configurePhoenix:phx
                             withView:view
                       withFullscreen:fullscreen];
    
    return vd;
}

@end

@implementation GameViewController

+ (id<PhoenixFactory> _Nullable) getPhoenixFactory {
    return [TestAppPHXFactory class];
}

- (void)viewWillAppear {
    [super viewWillAppear];
    // Get the window so the first-responder can be set to the Phoenix view
    // controller.
    [self.view.window makeFirstResponder:self];
//    [super becomeFirstResponder];
}

@end
