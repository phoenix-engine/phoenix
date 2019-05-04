//
//  PHXViewController.hpp
//  CocoaPhoenix
//
// PHXViewController defines a platform-dependent ViewController which contains
// the actual Phoenix object and responds to UI events.
//
//  Created by Bodie Solomon on 3/6/19.
//

#ifndef PHXViewController_hpp
#define PHXViewController_hpp

/// PhoenixFactory is a helper for configuring a Phoenix object with all of its
/// dependencies initialized.
///
/// See class method documentation for more details.
@protocol PhoenixFactory<NSObject>

/// +configurePhoenix:withView:withFullscreen is called during viewDidLoad in
/// PHXViewController.  It internally calls the other class methods in the
/// proper order to configure the dependencies of the Phoenix object, assigns
/// the newly created Phoenix object to the given MetalPhoenix, and returns a
/// handle to a new PHXViewDelegate to assign as the MTKView's delegate.
+ (PHXViewDelegate* _Nullable) configurePhoenix:(MetalPhoenix&)phx
                                       withView:(MTKView* _Nonnull)view
                                 withFullscreen:(BOOL)fullscreen;

/// +makePhoenixRendererWithView:withFullscreen prepares a PHXRenderer
/// implementation suitable for use by the Phoenix object.  This may be
/// implemented using various rendering backends.  For more details, see the
/// documentation of PHXRenderer in phoenix-apple-components.
+ (id<PHXRenderer> _Nullable) makeRendererWithView:(MTKView* _Nonnull)view
                                    withFullscreen:(BOOL)fullscreen;

/// +makeResponderWithView:withInput prepares a PHXResponder to respond to UI
/// events such as clicks and touches through the Input handle of the Phoenix
/// object.  The factory method passes a handle to the Phoenix Input object.
/// Please see the documentation of PHXResponder for more details.
+ (PHXResponder* _Nullable) makeResponderWithView:(MTKView* _Nonnull)view
                                        withInput:(PHXInput* _Nonnull)inp;

@end

@interface PHXDefaultFactory : NSObject<PhoenixFactory>

@end

/// PHXViewController is a view controller which configures and maintains the
/// lifetimes of a Phoenix object and its depedencies.  To add your own
/// Phoenix configuration, subclass it, returning your own implementation of
/// PhoenixFactory from getPhoenixFactory.
@interface PHXViewController : PlatformViewController

/// getPhoenixFactory returns a configuration helper for the internal Phoenix
/// engine object.  It is used in viewDidLoad to prepare the Phoenix renderer,
/// etc.  The returned object should be a _class_ reference, e.g.,
/// { return [SomePHXFactory class]; } since the factory methods are _class
/// methods_.
+ (id<PhoenixFactory> _Nullable) getPhoenixFactory;

@end

#endif /* PHXViewController_hpp */
