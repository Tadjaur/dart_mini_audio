#import "MiniPlayerPlugin.h"
#if __has_include(<mini_player/mini_player-Swift.h>)
#import <mini_player/mini_player-Swift.h>
#else
// Support project import fallback if the generated compatibility header
// is not copied when this plugin is created as a library.
// https://forums.swift.org/t/swift-static-libraries-dont-copy-generated-objective-c-header/19816
#import "mini_player-Swift.h"
#endif

@implementation MiniPlayerPlugin
+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
  [SwiftMiniPlayerPlugin registerWithRegistrar:registrar];
}
@end
