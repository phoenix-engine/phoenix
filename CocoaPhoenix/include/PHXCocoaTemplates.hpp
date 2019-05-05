//
//  PHXCocoaTemplates.hpp
//  CocoaPhoenix
//
// PHXCocoaTemplates defines names for instantiated Phoenix templates using
// CocoaPhoenix interfaces and protocols.  This reduces the need for
// CocoaPhoenix classes and their users to wrangle C++ template features.
//
//  Created by Bodie Solomon on 4/8/19.
//

#ifndef PHXCocoaTemplates_hpp
#define PHXCocoaTemplates_hpp

using MetalPhoenix = phx::Phoenix<
    input::Simple,
    mtlp::MetalRenderer,
    MTKView* _Nonnull
>;

typedef gfx::Graphics<mtlp::MetalRenderer, MTKView* _Nonnull> MetalGfx;
typedef input::Input<input::Simple> PHXInput;

#endif /* PHXCocoaTemplates_hpp */
