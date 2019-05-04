//
//  PHXResponder.mm
//  CocoaPhoenix-macOS
//
//  Created by Bodie Solomon on 5/3/19.
//

#import "CocoaPhoenix.hpp"

@implementation PHXResponder {
    __weak UIView* _view;
    PHXInput* _input;
}

+ (PHXResponder* _Nullable) makeWithView:(UIView* _Nonnull)view
                               withInput:(PHXInput* _Nonnull)input {
    PHXResponder* tmp = [[PHXResponder alloc] init];
    tmp->_view  = view;
    tmp->_input = input;
    
    return tmp;
}

- (BOOL)userInteractionEnabled  { return YES; }
- (BOOL)canBecomeFirstResponder { return YES; }
//- (BOOL)becomeFirstResponder    {
//    BOOL ok = [super becomeFirstResponder];
//    return ok;
//}

//- (BOOL)resignFirstResponder    { return [super resignFirstResponder]; }

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [touches anyObject];
    
    // Get the specific point that was touched.
    CGPoint pt = [touch locationInView:self->_view];
    _input->set_intent(pt.x, pt.y, YES);
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [touches anyObject];
    
    // Get the specific point that was touched.
    CGPoint pt = [touch locationInView:self->_view];
    _input->set_intent(pt.x, pt.y, NO);
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [touches anyObject];
    
    // Get the specific point that was touched.
    CGPoint pt = [touch locationInView:self->_view];
    _input->move_intent(pt.x, pt.y);
}

@end
