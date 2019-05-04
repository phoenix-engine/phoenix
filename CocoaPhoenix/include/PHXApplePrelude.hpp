//
// PHXApplePrelude.hpp
// CocoaPhoenix
//
// PHXApplePrelude.hpp contains the necessary Apple framework @imports and
// definitions to use the CocoaPhoenix UI components.  It also contains any
// platform-dependent definitions and imports (such as between macOS and iOS.)
//
// It defines the following names for UIKit/AppKit respectively on iOS/macOS:
//  - PlatformViewController
//  - PlatformResponder
//  - PlatformView
//  - PlatformEvent
//
// Created by Bodie Solomon on 4/6/19.
//

#ifndef PHXApplePrelude_hpp
#define PHXApplePrelude_hpp

#import <Foundation/Foundation.h>

#include <simd/simd.h>

// Always import MetalKit for both.
@import MetalKit;

// If iOS, import UIKit and define UIKit typename macro constants.
#if TARGET_OS_IPHONE
@import UIKit;
#define PlatformViewController UIViewController
#define PlatformResponder UIResponder
#define PlatformView UIView

// If macOS, use AppKit and NS typename constants.
#else
@import AppKit;
#define PlatformViewController NSViewController
#define PlatformResponder NSResponder
#define PlatformView NSView

#endif // TARGET_OS_IPHONE

#endif // PHXApplePrelude_hpp
