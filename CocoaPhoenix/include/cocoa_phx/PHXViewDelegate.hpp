//
//  PHXViewDelegate.hpp
//  CocoaPhoenix
//
//  Created by Bodie Solomon on 3/12/19.
//

#ifndef PHXViewDelegate_hpp
#define PHXViewDelegate_hpp

/// PHXViewDelegate responds to UI draw events by making the appropriate calls
/// into the Phoenix engine object.
@interface PHXViewDelegate : NSObject<MTKViewDelegate>

+ (instancetype _Nullable) makeWithPhoenix:(MetalPhoenix* _Nonnull)p;

@end

#endif /* PHXViewDelegate_hpp */
