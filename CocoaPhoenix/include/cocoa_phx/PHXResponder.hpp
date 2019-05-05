//
//  PHXResponder.hpp
//  CocoaPhoenix
//
// PHXResponder implements platform-specific Responders for handling UI input
// events such as touches, clicks, etc. and passes sanitized / translated events
// to the Phoenix Input object.
//
// These events should be considered as happening in a separate thread of
// execution from the main game logic, and are passed through a SPSC queue
// internally.  Phoenix games may obtain these events from the 
//
//  Created by Bodie Solomon on 3/6/19.
//

#ifndef PHXResponder_hpp
#define PHXResponder_hpp

/// PHXResponder proxies user-interaction UI events such as touches, clicks,
/// etc. through the Input interface to Phoenix.
@interface PHXResponder : PlatformResponder

// TODO: General-purpose type for inheritance....
/// To use a custom Input configuration, makeWithView must be overridden, since
/// PHXInput is a typedef for an instantiation of Phoenix input::Input<Consumer>
/// parameterized by input::Simple.
+ (PHXResponder* _Nullable) makeWithView:(PlatformView* _Nonnull)view
                               withInput:(PHXInput* _Nonnull)input;

@end

#endif /* PHXResponder_hpp */
