part of mini_player;

class _AudioPlayerBinder {
  static const INVALID_FUNCTION = -1;
  ffi.DynamicLibrary _dylib;

  _AudioPlayerBinder();

  Future<void> _loadNativeLib() async {
    var path;
    final architecture = ffi.sizeOf<ffi.IntPtr>() == 4 ? '32' : '64';
    String system, extension;
    if (io.Platform.isMacOS) {
      system = "macos";
      extension = "dylib";
    } else if (io.Platform.isIOS) {
      system = "macos";
      extension = "dylib";
    } else if (io.Platform.isWindows) {
      system = "wimdows";
      extension = "dll";
    } else if (io.Platform.isAndroid) {
      _dylib ??= ffi.DynamicLibrary.open("libnative_player.so");
    } else {
      system = "linux";
      extension = "so";
    }
    path = join(io.Directory.systemTemp.absolute.path, "mini_player",
        "native_platform_player-$system.$architecture.$extension");
    _dylib ??= ffi.DynamicLibrary.open(path);
  }

  int _init(List<String> mediasPath) {
    final ln = mediasPath.length;
    final stringPointer = pkg_ffi.allocate<ffi.Pointer<pkg_ffi.Utf8>>(count: ln);
    for (int id = 0; id < ln; id++) {
      stringPointer[id] = pkg_ffi.Utf8.toUtf8(mediasPath[id]);
    }
    final aInit = _dylib.lookup<ffi.NativeFunction<_native_init_func>>(_NativeF.init).asFunction<_PlatformInit>();
    return aInit(stringPointer, ln);
  }

  int _action(String nativeFunc) {
    if (!_NativeF.actionValues.contains(nativeFunc)) return INVALID_FUNCTION;
    final func = _dylib.lookup<ffi.NativeFunction<_native_action_func>>(nativeFunc).asFunction<_PlatformAction>();
    return func();
  }
/*
// NOT WORK NOW
// TODO: uncomment this after adding metadata reader
  String _meta(String path) {
    final func = _dylib.lookup<ffi.NativeFunction<_audio_meta_func>>(_NativeF.meta).asFunction<_audio_meta_func>();
    final charPointer = pkg_ffi.Utf8.toUtf8(path);
    final response = func(charPointer);
    return pkg_ffi.Utf8.fromUtf8(response);
  }*/
}
