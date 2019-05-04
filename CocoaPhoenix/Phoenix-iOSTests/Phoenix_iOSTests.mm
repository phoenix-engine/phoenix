//
//  Phoenix_iOSTests.m
//  Phoenix-iOSTests
//
//  Created by Bodie Solomon on 3/1/19.
//

#import <XCTest/XCTest.h>

#include "CocoaPhoenix.hpp"

@interface FooRenderer : NSObject<PHXRenderer>

@end

@implementation FooRenderer

- (void)drawInMTKView:(nonnull MTKView *)view {}
- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size {}
- (void)clear {}
- (void)drawPointAt:(simd_int2)point withColor:(MTLClearColor)color {}
- (void)update {}

+ (instancetype _Nonnull)makeWithView:(MTKView* _Nonnull)view
                       withFullscreen:(BOOL)fullscreen {
    return [[super alloc] init];
}

- (void)draw:(MTKView * _Nonnull)inView {
    // Do something
}


@end

@interface FooPhoenixBuilder : NSObject<PhoenixFactory>

@end

@implementation FooPhoenixBuilder

+ (id<PHXRenderer>)configurePhoenix:(MetalPhoenix&)phx
                           withView:(UIView*)view
                     withFullscreen:(BOOL)fullscreen {
    id<PHXRenderer> renderer = [[FooRenderer alloc] init];
    return renderer;
}

+ (id<PHXRenderer> _Nullable)makeRendererWithView:(MTKView * _Nonnull)view withFullscreen:(BOOL)fullscreen {
    return [PHXDefaultFactory makeRendererWithView:view withFullscreen:fullscreen];
}


+ (PHXResponder * _Nullable)makeResponderWithView:(MTKView * _Nonnull)view withInput:(PHXInput * _Nonnull)inp {
    return [PHXDefaultFactory makeResponderWithView:view withInput:inp];
}


@end

@interface FooPhoenixView : PHXViewController

@end

@implementation FooPhoenixView

+ (id<PhoenixFactory>) getPhoenixFactory {
    return [FooPhoenixBuilder class];
}

@end

@interface Phoenix_iOSTests : XCTestCase

@end

@implementation Phoenix_iOSTests

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testExample {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
}

- (void)testActual {
    // This is just for syntax and typechecking.
    auto vc = [[PHXViewController alloc] init];
    [vc viewDidLoad];
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
