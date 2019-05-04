//
//  PHXViewDelegate.mm
//  CocoaPhoenix
//
//  Created by Bodie Solomon on 5/3/19.
//

#import "CocoaPhoenix.hpp"

@implementation PHXViewDelegate {
    MetalPhoenix* _phx;
}

+ (instancetype _Nullable) makeWithPhoenix:(MetalPhoenix* _Nonnull)p {
    PHXViewDelegate* tmp = [[super alloc] init];
    tmp->_phx = p;
    
    return tmp;
}

- (void)drawInMTKView:(MTKView* _Nonnull)view {
    _phx->render(view);
}

- (void)mtkView:(MTKView *)view drawableSizeWillChange:(CGSize)size {
    // TODO: add resize to Phoenix draw render handle.
}

@end
