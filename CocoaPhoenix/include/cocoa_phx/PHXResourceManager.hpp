//
//  PHXResourceManager.hpp
//  CocoaPhoenix
//
// PHXResourceManager manages the lifetimes and memory of PHXRenderer resources.
//
//  Created by Bodie Solomon on 2/8/19.
//

#ifndef PHX_ResourceManager_hpp
#define PHX_ResourceManager_hpp

@interface PHXResourceManager : NSObject

+ (nullable instancetype) makeWithDevice:(id<MTLDevice> _Nonnull)device;

- (NSURL* _Nonnull)findShaderLibraryWithName:(NSString* _Nonnull)name;

- (void) loadShadersWithFormat:(MTLPixelFormat)fmt
                     withError:(NSError* _Nullable)err
                       withURL:(NSURL* _Nonnull)url;

- (void) prepareTexturesWithCGSize:(CGSize)size;
- (void) prepareTexturesWithSize:(MTLSize)size;

- (void) createCommandQueue;

- (void) updateToCGSize:(CGSize)size;
- (void) updateToSize:(MTLSize)size;

- (void) drawInView:(nonnull MTKView *)view;

@end

#endif /* PHX_ResourceManager_hpp */
