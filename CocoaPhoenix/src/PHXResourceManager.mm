//
//  PHXResourceManager.mm
//  CocoaPhoenix
//
//  Created by Bodie Solomon on 5/3/19.
//

#import "CocoaPhoenix.hpp"

@implementation PHXResourceManager {
    // Note that the device is owned by the creator of this resource, so it
    // doesn't need to manage its lifetime.
    __weak id<MTLDevice> _device;
    
    PHXDrawer* _drawer;
    
    // Texture-related handles and parameters.
    MTLPixelFormat _format;
    id<MTLTexture> _texture;
    
    MTLSize _viewportSize;
    
    id<MTLCommandQueue> _cmdQueue;
    id<MTLRenderPipelineState> _pipeline;
}

+ (instancetype _Nullable) makeWithDevice:(id<MTLDevice>)device {
    PHXResourceManager* tmp = [[super alloc] init];
    if (!tmp) {
        return tmp;
    }
    
    tmp->_device = device;
    
    return tmp;
}

- (NSURL* _Nonnull)findShaderLibraryWithName:(NSString*)name {
    auto mb = [NSBundle bundleForClass:[self class]];
    return [mb URLForResource:name withExtension:@"metallib"];
}

- (void) loadShadersWithFormat:(MTLPixelFormat)fmt
                     withError:(NSError*)err
                       withURL:(NSURL* _Nonnull)url {
    _format = fmt;
    
    // The PHXResourceManager should always look for its shader libraries
    // internally.  Since PHXResourceManager is statically linked, it is part of
    // the NSBundle which linked to it.
    
    auto metalLib = [_device newLibraryWithURL:url error:&err];
    if (err != nil) {
        NSLog(@"Failed to initialize default Metal library: %@", [err description]);
        return;
    }
    
    auto vertFn = [metalLib newFunctionWithName:@"vertexShader"];
    auto fragFn = [metalLib newFunctionWithName:@"fragmentShader"];
    
    // Set up a Metal pipeline descriptor.
    auto pipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineDescriptor.label = @"Default rendering pipeline";
    pipelineDescriptor.vertexFunction = vertFn;
    pipelineDescriptor.fragmentFunction = fragFn;
    pipelineDescriptor.colorAttachments[0].pixelFormat = fmt;
    
    _pipeline = [_device newRenderPipelineStateWithDescriptor:pipelineDescriptor
                                                        error:&err];
}

- (void) prepareTexturesWithCGSize:(CGSize)size {
    auto uw = static_cast<unsigned long>(size.width);
    auto uh = static_cast<unsigned long>(size.height);
    
    [self prepareTexturesWithSize:MTLSizeMake(uw, uh, 1)];
}

- (void) prepareTexturesWithSize:(MTLSize)size {
    auto descriptor = [[MTLTextureDescriptor alloc] init];
    
    // Indicate we're creating a 2D texture.
    descriptor.textureType = MTLTextureType2D;
    
    _viewportSize = size;
    
    // Indicate that each pixel has a Red, Blue, Green, and Alpha channel, each
    // in an 8-bit unnormalized format (0 maps 0.0 while 255 maps to 1.0.)
    descriptor.pixelFormat = _format;
    descriptor.width = size.width;
    descriptor.height = size.height;
    descriptor.depth = size.depth;
    descriptor.usage = MTLTextureUsageShaderWrite | MTLTextureUsageShaderRead;
    
    _texture = [_device newTextureWithDescriptor:descriptor];
}

- (void) resizeAndCopyTextureToSize:(MTLSize)size {
    auto descriptor = [[MTLTextureDescriptor alloc] init];
    
    descriptor.textureType = MTLTextureType2D;
    
    descriptor.pixelFormat = _format;
    descriptor.width = size.width;
    descriptor.height = size.height;
    descriptor.depth = size.depth;
    descriptor.usage = MTLTextureUsageShaderWrite | MTLTextureUsageShaderRead;
    
    auto tmp = [_device newTextureWithDescriptor:descriptor];
    auto buf = [_cmdQueue commandBufferWithUnretainedReferences];
    buf.label = @"Blit to new size";
    
    // Create and encode the texture blit command.
    // TODO: Resize down.
    auto fromWidth = _texture.width < tmp.width ? _texture.width : tmp.width;
    auto fromHeight = _texture.height < tmp.height ? _texture.height : tmp.height;
    auto blit = [buf blitCommandEncoder];
    [blit copyFromTexture:_texture
              sourceSlice:0 sourceLevel:0
             sourceOrigin:{0, 0, 0} sourceSize:{fromWidth, fromHeight, 1}
                toTexture:tmp
         destinationSlice:0 destinationLevel:0
        destinationOrigin:{0, 0, 0}];
    
    [blit endEncoding];
    
    // Commit the encoded blit command.
    [buf commit];
    [buf waitUntilCompleted];
    
    // Discard the old texture and assign the handle the new one.
    _texture = tmp;
}

- (void) updateToCGSize:(CGSize)size {
    auto uw = static_cast<unsigned long>(size.width);
    auto uh = static_cast<unsigned long>(size.height);
    
    [self updateToSize:MTLSizeMake(uw, uh, 1)];
}

- (void) updateToSize:(MTLSize)size {
    _viewportSize.width = size.width;
    _viewportSize.height = size.height;
    
    [self resizeAndCopyTextureToSize:size];
}

- (void) createCommandQueue {
    _cmdQueue = [_device newCommandQueue];
}

- (void) drawInView:(MTKView * _Nonnull)view {
    [PHXDrawer drawInView:view
                 withSize:_viewportSize
            usingPipeline:_pipeline
         withCommandQueue:_cmdQueue
         withInputTexture:_texture];
}

@end
