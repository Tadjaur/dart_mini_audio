library mini_player;

import 'dart:async';
import 'dart:ffi' as ffi;
import 'dart:io' as io show Platform, Directory;
import 'dart:isolate' as iso;
import 'dart:math' as m;

import 'package:ffi/ffi.dart' as pkg_ffi;
import 'package:flutter/services.dart';
import 'package:path/path.dart' as p;

part 'src/c_channel.dart';

part 'src/global_type.dart';
//part 'src/audio_meta.dart'; // TODO: uncomment this after adding metadata reader

/// represent the audio metadata
abstract class MiniPlayer {
  static const MethodChannel _channel = const MethodChannel('mini_player');
  static MiniPlayer _instance;

  static Future<String> get platformVersion async {
    final String version = await _channel.invokeMethod('getPlatformVersion');
    return version;
  }

  factory MiniPlayer() {
    if (_instance == null)
      _instance = _MiniPlayerImpl();
    return _instance;
  }

/*
  // TODO: uncomment this after adding metadata reader
  /// retrieve as possible the meta data of the current audio file
  ///
  /// param [mediaPath] contain the absolute path of the media
  ///
  /// return the [AudioMetaData] retrieved
  /// ```dart
  ///   final player = AudioPlayer();
  ///   final audioMeta = await player.getMeta(absolutePath);
  ///   if (audioMeta == null) {
  ///     print("failed to retrieve metadata of $absolutePath");
  ///   }
  ///   print
  /// ```
  Future<AudioMetaData> getMeta(String mediaPath);
*/

  /// initialize the device to start a playback
  ///
  /// param [mediasPath] contain the list of absolute path of the media of your playlist
  /// ```dart
  ///   final player = AudioPlayer();
  ///   final done = await player.init(playList);
  ///   if (!done) {
  ///     print("initialisation failed");
  ///   }
  /// ```
  Future<bool> init(List<String> mediasPath);

  /// Send an [AudioEvent] to the player
  ///
  /// return the future that complete with the [bool] `true` when done
  /// ```dart
  ///   final player = AudioPlayer();
  ///   final done = await player.init(playList);
  ///   if (!done) {
  ///     print("initialisation failed");
  ///   }
  ///   if (!player.sendEvent(AudioEvent.play)){
  ///     print("failed to start player");
  ///   }
  /// ```
  Future<bool> sendEvent(AudioEvent event);

  ///return the properties of the audio of the given path
  Future<AudioProperties> getAudioProp(String mediaPath);

  /// add the current [mediasPath] to the list of audio to the current playlist
  Future<bool> playNext(List<String> mediasPath); // todo: implement this method
}

class _MiniPlayerImpl implements MiniPlayer {
  static final _isolateResponse = <String, dynamic>{};

  static iso.Isolate _isolate;
  static iso.SendPort _isolateSendPort;
  static const ISOLATE_DEBUG_NAME = "PlatformPlayer-Backend";

//  Future<void> unlockResponseCtrl() async {
//    while (_isolateResponse != null && !_isolateResponse.isClosed) {
//      await Future.delayed(Duration(milliseconds: 50));
//    }
//  }

  static void _backPlayer(iso.SendPort sendPort) {
    iso.ReceivePort receivePort =
    iso.ReceivePort(); //port for the created isolate to receive messages.
    sendPort.send(receivePort.sendPort);
    final audioPlayer = _AudioPlayerBinder();
    audioPlayer._loadNativeLib().then((_) {
      receivePort.listen((message) {
        if (!(message is Map)) return;
        final msg = message as Map;
        if (!msg.containsKey(_FUNCTION_CALL)) return;
        final nativeFunc = msg[_FUNCTION_CALL];
        dynamic response;
        if (_NativeF.actionValues.contains(nativeFunc)) {
          response = audioPlayer._action(nativeFunc);
        } else if (nativeFunc == _NativeF.init &&
            msg.containsKey(_FUNCTION_PARAMS)) {
          response = audioPlayer._init(msg[_FUNCTION_PARAMS]);
        } else if (nativeFunc == _NativeF.mediaProperties &&
            msg.containsKey(_FUNCTION_PARAMS)) {
          response = audioPlayer._mediaProperties(msg[_FUNCTION_PARAMS]);
        }
        /* TODO: uncomment this after adding metadata reader
        else if (nativeFunc == _NativeF.meta && msg.containsKey(_FUNCTION_PARAMS)) {
          response = audioPlayer._meta(msg[_FUNCTION_PARAMS]);
        }*/
        sendPort.send(<String, dynamic>{
          _FUNCTION_CALL: nativeFunc,
          _FUNCTION_RESPONSE: response,
          _RESPONSE_ID: msg[_RESPONSE_ID]
        });
      });
    });
  }

  Future<void> _createIsolate() async {
    // TODO: check if the isolate creation success or fail.
    iso.ReceivePort receivePort =
    iso.ReceivePort(); //port for this main isolate to receive messages.
    _isolate = await iso.Isolate.spawn(_backPlayer, receivePort.sendPort,
        debugName: ISOLATE_DEBUG_NAME);
    final stream = receivePort.asBroadcastStream();
    _isolateSendPort ??= await stream.first;
    stream.listen((data) {
      if (data != _isolateSendPort) {
        _isolateResponse[data[_RESPONSE_ID]] = data[_FUNCTION_RESPONSE];
      }
    });
  }

  Future<bool> init(List<String> mediasPath) async {
    if (_isolate == null) await _createIsolate();
    final ResponseId = "init-R-${m.Random().nextInt(100000)}";
    _isolateResponse[ResponseId] = "";
    _isolateSendPort.send(<String, dynamic>{
      _FUNCTION_CALL: _NativeF.init,
      _FUNCTION_PARAMS: mediasPath,
      _RESPONSE_ID: ResponseId
    });
    while (_isolateResponse[ResponseId] == "") {
      await Future.delayed(Duration(milliseconds: 10));
    }
    return (_isolateResponse[ResponseId] as int) != 0;
  }

  Future<AudioProperties> getAudioProp(String mediaPath) async {
    if (_isolate == null) await _createIsolate();
    final ResponseId = "getAudioProp-R-${m.Random().nextInt(100000)}";
    _isolateResponse[ResponseId] = "";
    _isolateSendPort.send(<String, dynamic>{
      _FUNCTION_CALL: _NativeF.mediaProperties,
      _FUNCTION_PARAMS: mediaPath,
      _RESPONSE_ID: ResponseId
    });
    while (_isolateResponse[ResponseId] == "") {
      await Future.delayed(Duration(milliseconds: 10));
    }
    return _isolateResponse[ResponseId] as AudioProperties;
  }

  Future<bool> sendEvent(AudioEvent event) async {
    String caller;

    final ResponseId = "sendEvent-R-${m.Random().nextInt(100000)}";
    _isolateResponse[ResponseId] = "";
    switch (event) {
      case AudioEvent.next:
        caller = _NativeF.next;
        break;
      case AudioEvent.pause:
        caller = _NativeF.pause;
        break;
      case AudioEvent.play:
        caller = _NativeF.play;
        break;
      case AudioEvent.previous:
        caller = _NativeF.prev;
        break;
      case AudioEvent.replay:
        caller = _NativeF.replay;
        break;
      case AudioEvent.stop:
        caller = _NativeF.stop;
        break;
    }
    _isolateSendPort.send(<String, String>{_FUNCTION_CALL: caller, _RESPONSE_ID: ResponseId
    });


    while (_isolateResponse[ResponseId] == "") {
      await Future.delayed(Duration(milliseconds: 10));
    }
    return (_isolateResponse[ResponseId] as int) != 0;
  }

  Future<bool> playNext(List<String> mediasPath) async => false; // todo: implement this method

/*
// TODO: uncomment this after adding metadata reader
  @override
  Future<AudioMetaData> getMeta(String mediasPath) async {
    if (_isolate == null) await _createIsolate();
    _isolateSendPort.send(<String, dynamic>{_FUNCTION_CALL: _NativeF.meta, _FUNCTION_PARAMS: mediasPath});
    _isolateResponse = StreamController();
    _isolateResponse = _isolateResponse.stream;
    AudioMetaData response;
    try {
      final data = (await _isolateResponse.first);
      final decoded = cv.json.decode(data);
      if (decoded is Map && decoded.containsKey("tags") && decoded.containsKey("properties")) {
        response = _AudioMetaDataImpl.fromMap(decoded);
      } else {
        print("unknow type retrieved");
      }
    } finally {
      //pass
    }
    return response;
  }*/
}
