//
//  PHXShaders.h
//  CocoaPhoenix
//
//  Created by Bodie Solomon on 2/7/19.
//

#ifndef PHX_PHXMetal_Shaders_h
#define PHX_PHXMetal_Shaders_h

#include <simd/simd.h>

// Buffer index values shared between shader and C code to ensure Metal shader buffer inputs match
//   Metal API buffer set calls
typedef enum PHXVertexInputIndex
{
    PHXVertexInputIndexVertices     = 0,
    PHXVertexInputIndexViewportSize = 1,
} PHXVertexInputIndex;

// Texture index values shared between shader and C code to ensure Metal shader buffer inputs match
//   Metal API texture set calls
typedef enum PHXTextureIndex
{
    PHXTextureIndexInput  = 0,
    PHXTextureIndexOutput = 1,
    PHXTextureIndexTime   = 2,
} PHXTextureIndex;

//  This structure defines the layout of each vertex in the array of vertices set as an input to our
//    Metal vertex shader.  Since this header is shared between our .metal shader and C code,
//    we can be sure that the layout of the vertex array in the code matches the layout that
//    our vertex shader expects
typedef struct
{
    // Positions in pixel space (i.e. a value of 100 indicates 100 pixels from the origin/center)
    vector_float2 position;
    
    // 2D texture coordinate
    vector_float2 textureCoordinate;
} PHXVertex;

#endif /* PHX_PHXMetal_Shaders_h */
