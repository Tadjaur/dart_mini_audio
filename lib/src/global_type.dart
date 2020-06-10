part of mini_player;

// FFI signature of the a_init C function
typedef _native_init_func = ffi.Uint32 Function(ffi.Pointer<ffi.Pointer<pkg_ffi.Utf8>> mediasPath, ffi.Uint32 count);
// FFI signature of the other function a_play, a_pause, a_next, a_prev, a_replay, a_stop C function
typedef _native_action_func = ffi.Uint32 Function();
// FFI signature of the a_meta C function
// TODO: this not work on android only create other project for tag reading.
// typedef _audio_meta_func = ffi.Pointer<pkg_ffi.Utf8> Function(ffi.Pointer<pkg_ffi.Utf8> mediaPath);

// Dart signature of the a_init C function
typedef _PlatformInit = int Function(ffi.Pointer<ffi.Pointer<pkg_ffi.Utf8>> mediasPath, int count);
// Dart signature of the other function a_play, a_pause, a_next, a_prev, a_replay, a_stop C function
typedef _PlatformAction = int Function();

const String _FUNCTION_CALL = "func";
const String _FUNCTION_PARAMS = "params";
const String _FUNCTION_RESPONSE = "response";

mixin _NativeF {
//  static const meta = "mp_meta"; // TODO: uncomment this after adding metadata reader
  static const init = "mp_init";
  static const next = "mp_next";
  static const pause = "mp_pause";
  static const play = "mp_play";
  static const prev = "mp_prev";
  static const replay = "mp_replay";
  static const stop = "mp_stop";

  static var actionValues = [next, pause, play, prev, replay, stop];
}

enum AudioEvent {
  next,
  pause,
  play,
  previous,
  replay,
  stop,
}
