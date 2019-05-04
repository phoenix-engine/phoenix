//
//  PHXResponder.mm
//  CocoaPhoenix-macOS
//
//  Created by Bodie Solomon on 5/3/19.
//

#import "CocoaPhoenix.hpp"

@implementation PHXResponder {
    __weak NSView* _view;
    PHXInput* _input;
}

+ (PHXResponder* _Nullable) makeWithView:(NSView* _Nonnull)view
                               withInput:(PHXInput* _Nonnull)input {
    PHXResponder* tmp = [[PHXResponder alloc] init];
    tmp->_view  = view;
    tmp->_input = input;
    
    return tmp;
}

- (BOOL)acceptsMouseMovedEvents { return YES; }
- (BOOL)acceptsFirstResponder   { return YES; }
- (BOOL)acceptsKeyDownEvents    { return YES; }

- (void)keyDown:(NSEvent *)evt {
    auto kc = [evt.charactersIgnoringModifiers lowercaseString];
    if([kc isEqualToString:@"q"] || evt.keyCode == 53) {
        _input->quit_command();
    }
}

- (void)mouseDown:(NSEvent *)evt {
    auto pt = [_view convertPoint:evt.locationInWindow fromView:nil];
    _input->set_intent(pt.x, pt.y, YES);
}

- (void)mouseUp:(NSEvent *)evt {
    auto pt = [_view convertPoint:evt.locationInWindow fromView:nil];
    _input->set_intent(pt.x, pt.y, NO);
}

- (void)mouseMoved:(NSEvent *)evt {
    auto pt = [_view convertPoint:evt.locationInWindow fromView:nil];
    _input->move_intent(pt.x, pt.y);
}

- (void)mouseDragged:(NSEvent *)evt {
    auto pt = [_view convertPoint:evt.locationInWindow fromView:nil];
    _input->move_intent(pt.x, pt.y);
}

@end
