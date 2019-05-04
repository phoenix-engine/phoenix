//
//  PHXDrawer.mm
//  CocoaPhoenix
//
//  Created by Bodie Solomon on 5/3/19.
//

#import "CocoaPhoenix.hpp"

@implementation PHXDrawer

+ (void) drawInView:(MTKView* _Nonnull)view
           withSize:(MTLSize)size
      usingPipeline:(id<MTLRenderPipelineState> _Nonnull)pipeline
   withCommandQueue:(id<MTLCommandQueue> _Nonnull)cmdQueue
   withInputTexture:(id<MTLTexture> _Nonnull)texture {
    
    auto w = static_cast<double>(size.width);
    auto h = static_cast<double>(size.height);
    auto fw = float(w);
    auto fh = float(h);
    
    const PHXVertex fsQuad[] = {
        { {  fw, -fh }, { 1.f, 0.f } },
        { { -fw, -fh }, { 0.f, 0.f } },
        { { -fw,  fh }, { 0.f, 1.f } },
        
        { {  fw, -fh }, { 1.f, 0.f } },
        { { -fw,  fh }, { 0.f, 1.f } },
        { {  fw,  fh }, { 1.f, 1.f } },
    };
    
    // Create a new command buffer for each render pass to the current drawable.
    auto buf = [cmdQueue commandBuffer];
    buf.label = @"Draw command buffer";
    
    // Obtain a renderPassDescriptor generated from the view's drawable textures.
    auto descriptor = view.currentRenderPassDescriptor;
    
    if (descriptor == nil) {
        NSLog(@"Unable to get render pass descriptor!");
        [buf commit];
        return;
    }
    
    // Create a render command encoder so we can render into something.
    auto encoder = [buf renderCommandEncoderWithDescriptor:descriptor];
    encoder.label = @"Render command encoder";
    
    // Set the region of the drawable to which we'll draw (the whole thing.)
    [encoder setViewport:(MTLViewport){
        0.0, 0.0,
        w, h,
        -1.0, 1.0,
    }];
    
    [encoder setRenderPipelineState:pipeline];
    
    // TODO: Automate configuration of shader parameters as shader-bundled traits.
    
    // Send the bytes for the vertices.
    [encoder setVertexBytes:fsQuad
                     length:sizeof(fsQuad)
                    atIndex:PHXVertexInputIndexVertices];
    
    // Send the bytes defining the viewport size.
    [encoder setVertexBytes:&size
                     length:sizeof(size)
                    atIndex:PHXVertexInputIndexViewportSize];
    
    // Set the texture for the fragment shader.
    [encoder setFragmentTexture:texture
                        atIndex:PHXTextureIndexOutput];
    
    [encoder endEncoding];
    
    // Schedule presentation once the framebuffer is complete, using the current
    // drawable.
    [buf presentDrawable:view.currentDrawable];
    
    // Finalize rendering here and push the buffer to the GPU.
    [buf commit];
}

@end
