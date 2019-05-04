//
//  CocoaPhoenix.hpp
//  CocoaPhoenix
//
//  Created by Bodie Solomon on 3/6/19.
//
// TODO: Refactor docs
// High-level overview
//
// PHXViewController owns the UI-facing components and the Phoenix object.
// The Phoenix object owns all internal Phoenix components and provides
// C++ interfaces, which are wrapped in Objective-C++ event handlers for use by
// the UI components.
//
// PHXViewController -viewDidLoad obtains a factory using its class method
// getPhoenixFactory.  This method should be overridden by a user who wants to
// supply their own Game class or other classes, by returning the user's
// implementation of the PhoenixFactory protocol.
//
// Optionally, they may extend PHXDefaultFactory to implement only some of its
// methods, all of which are called from PHXViewController -viewDidLoad.

// Detailed overview
//
// Graphics/MetalGfx is the C++ interface to Phoenix, which is owned and
// controlled by Phoenix.
//
// PHXMetalRenderer is the Objective-C++ interface to Metal, which controls the
// Metal API internally.  It is manipulated only by Phoenix, through the
// MetalGfx interface.
//
// In order to provide a MTKViewDelegate and NSResponder so UI events can be
// handled, two Objective-C++ interfaces to Phoenix need to be provided, which
// interface directly with Phoenix, not its owned objects.
//
// This is the job of the CocoaPhoenix framework.  CocoaPhoenix provides three
// interfaces, for both Objective-C++ and Swift:
//
// PHXViewController implements NSViewController/UIViewController depending on
// platform.  It pauses any work the render thread depends on and draws the view
// as necessary.
//
// PHXResponder implements NSResponder/UIResponder depending on platform.  UI
// events are passed to the Input handle of Phoenix by calling its internal
// methods, which parse UI events into input events passed to Phoenix.
//
// PHXViewDelegate implements MTKViewDelegate by calling the appropriate methods
// on an internal reference to the Phoenix object.

#ifndef CocoaPhoenix_hpp
#define CocoaPhoenix_hpp

// PHXApplePrelude.hpp contains the necessary Apple framework @imports and
// definitions to use the CocoaPhoenix UI components.
#import "PHXApplePrelude.hpp"

// PHXCocoaClassNames contains forward declarations of CocoaPhoenix names.
#import "PHXCocoaClassNames.hpp"

//// PHXCoreIncludes.hpp includes the core C++ Phoenix classes.
//#import "PHXCoreIncludes.hpp"

// PHXCppWrappers.hpp defines the pure-C++ wrappers for native Objective-C++
// interfaces which allow them to be used in the core Phoenix engine.
#import "PHXCppWrappers.hpp"

// PHXCoreIncludes.hpp includes the core C++ Phoenix classes.
#import "PHXCoreIncludes.hpp"

// PHXCocoaTemplates defines names for instantiated Phoenix templates using
// CocoaPhoenix interfaces and protocols.  This reduces the need for
// CocoaPhoenix classes to use C++ template features.
#import "PHXCocoaTemplates.hpp"

// PHXCocoaClassDefs defines the real interfaces and protocols implemented by
// CocoaPhoenix.
#import "PHXCocoaClassDefs.hpp"

#endif /* CocoaPhoenix_hpp */
