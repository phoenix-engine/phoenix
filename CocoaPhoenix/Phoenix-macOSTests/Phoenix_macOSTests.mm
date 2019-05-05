//
//  Phoenix_macOSTests.m
//  Phoenix-macOSTests
//
//  Created by Bodie Solomon on 3/1/19.
//

#import <XCTest/XCTest.h>

#import "CocoaPhoenix.hpp"

@interface FooRenderer : NSObject<PHXRenderer>

@end

@implementation FooRenderer

+ (instancetype _Nullable)makeWithView:(MTKView* _Nonnull)view
                        withFullscreen:(BOOL)fullscreen {
    return [[super alloc] init];
}
+ (void)enterFullscreenForView:(MTKView* _Nonnull)view {}

- (void)drawInMTKView:(nonnull MTKView *)view {}
- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size {}
- (void)clear {}
- (void)draw:(MTKView * _Nonnull)inView {}
- (void)drawPointAt:(simd_int2)point withColor:(MTLClearColor)color {}
- (void)update {}

@end

@interface FooPhoenixBuilder : NSObject<PhoenixFactory>

@end

@implementation FooPhoenixBuilder

+ (id<PHXRenderer>)configurePhoenix:(MetalPhoenix&)phx
                           withView:(NSView* _Nonnull)view
                     withFullscreen:(BOOL)fullscreen {
    id<PHXRenderer> renderer = [[FooRenderer alloc] init];
    return renderer;
}

+ (id<PHXRenderer> _Nullable)makeRendererWithView:(MTKView* _Nonnull)view
                                   withFullscreen:(BOOL)fullscreen {
    return [FooRenderer makeWithView: view withFullscreen:fullscreen];
}


+ (PHXResponder* _Nullable)makeResponderWithView:(MTKView* _Nonnull)view
                                        withInput:(PHXInput* _Nonnull)inp {
    return [PHXResponder makeWithView:view withInput:inp];
}


@end

@interface FooPhoenixView : PHXViewController

@end

@implementation FooPhoenixView

+ (id<PhoenixFactory>) getPhoenixFactory {
    return [[FooPhoenixBuilder alloc] init];
}

@end

@interface Phoenix_macOSTests : XCTestCase

@end

@implementation Phoenix_macOSTests

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testActual {
    // This is just for syntax and typechecking.
//    auto vc = [[PHXViewController alloc] init];
//    auto g = phx::Phoenix();
//    [vc viewDidLoad withGame:&g];
}

// These are really just syntax / compilation tests.....
- (void)testCustomPHXViewSubclass {
    auto fpv = [[FooPhoenixView alloc] init];
    [fpv viewDidLoad];
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
