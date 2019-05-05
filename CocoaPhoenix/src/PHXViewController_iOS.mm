//
//  PHXViewController.mm
//  CocoaPhoenix
//
//  Created by Bodie Solomon on 5/3/19.
//

#import "CocoaPhoenix.hpp"

@implementation PHXViewController {
    PHXResponder* _input;
    PHXViewDelegate* _delegate;
    MTKView* _view;
    
    MetalPhoenix _phx;
}

+ (id<PhoenixFactory> _Nullable) getPhoenixFactory {
    return [PHXDefaultFactory class];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    _view = (MTKView *)self.view;
    
    _view.device = MTLCreateSystemDefaultDevice();
    
    if (!_view.device) {
        NSLog(@"Metal is not supported on this device");
        self.view = [[UIView alloc] initWithFrame:self.view.frame];
        return;
    }
    
    _delegate = [[[self class] getPhoenixFactory] configurePhoenix:_phx
                                                          withView:_view
                                                    withFullscreen:NO];
    
    _input = [PHXResponder makeWithView:_view withInput:&_phx.input_handle()];
    
    _view.delegate = _delegate;
}

- (BOOL)canBecomeFirstResponder { return YES; }
- (UIResponder*)nextResponder   { return _input; }

@end
