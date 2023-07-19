part of mini_player;

// FFI signature of the a_init C function
typedef _native_init_func = ffi.Uint32 Function(
    ffi.Pointer<ffi.Pointer<pkg_ffi.Utf8>> mediasPath, ffi.Uint32 count);
// FFI signature of the other function a_play, a_pause, a_next, a_prev, a_replay, a_stop C function
typedef _native_action_func = ffi.Uint32 Function();
// FFI signature of the a_meta C function
// TODO: this not work on android only create other project for tag reading.
// typedef _audio_meta_func = ffi.Pointer<pkg_ffi.Utf8> Function(ffi.Pointer<pkg_ffi.Utf8> mediaPath);

// FFI and Dart signature of the mp_media_properties C function
typedef _audio_properties_func = ffi.Pointer<StructAudioProperties> Function(
    ffi.Pointer<pkg_ffi.Utf8> mediaPath);

// Dart signature of the a_init C function
typedef _PlatformInit = int Function(
    ffi.Pointer<ffi.Pointer<pkg_ffi.Utf8>> mediasPath, int count);
// Dart signature of the other function a_play, a_pause, a_next, a_prev, a_replay, a_stop C function
typedef _PlatformAction = int Function();

const String _FUNCTION_CALL = "func";
const String _FUNCTION_PARAMS = "params";
const String _FUNCTION_RESPONSE = "response";
const String _RESPONSE_ID = "response_id";

mixin _NativeF {
  //  static const meta = "mp_meta"; // TODO: uncomment this after adding metadata reader
  static const init = "mp_init";
  static const next = "mp_next";
  static const pause = "mp_pause";
  static const play = "mp_play";
  static const prev = "mp_prev";
  static const replay = "mp_replay";
  static const stop = "mp_stop";
  static const mediaProperties = "mp_media_properties";

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

class StructAudioProperties extends ffi.Struct {
  @ffi.Int32()
  int bitrate;
  @ffi.Int32()
  int sample_rate;
  @ffi.Int32()
  int channels;
  @ffi.Int32()
  int length;

  factory StructAudioProperties.allocate(int bitrate, int sample_rate, int channels, int length) =>
      pkg_ffi
          .allocate<StructAudioProperties>()
          .ref
        ..bitrate = bitrate
        ..sample_rate = sample_rate
        ..channels = channels
        ..length = length;
}

class AudioProperties {
  final int bitrate;
  final int sampleRate;
  final int channels;
  final int length;

  AudioProperties({this.bitrate, this.sampleRate, this.channels, this.length})
      :assert(bitrate != null && sampleRate != null && channels != null && length != null);

  AudioProperties.fromMap(Map<String, int> map)
      : assert(map != null),
        assert(map["bitrate"] != null &&
            map["sample_rate"] != null &&
            map["channels"] != null &&
            map["length"] != null),
        bitrate = map["bitrate"],
        sampleRate = map["sample_rate"],
        channels = map["channels"],
        length = map["length"];
}
