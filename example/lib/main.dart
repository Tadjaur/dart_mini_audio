import 'dart:async';

import 'package:flutter/material.dart';
import 'package:mini_player/mini_player.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatefulWidget {
  @override
  _MyAppState createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  bool _metaData;

  @override
  void initState() {
    super.initState();
  }

  // Platform messages are asynchronous, so we initialize in an async method.
  Future<void> initPlatformState() async {
    bool metaData;
    // Platform messages may fail, so we use a try/catch PlatformException.
    try {
      final mp = MiniPlayer();
      metaData =
          await mp.init(["/home/twork/Downloads/Music/alan walker/Alan Walker ft. Gavin James - Tired - YouTube.MP3"]);
      mp.sendEvent(AudioEvent.play);
    } finally {
      //pass
    }

    // If the widget was removed from the tree while the asynchronous platform
    // message was in flight, we want to discard the reply rather than calling
    // setState to update our non-existent appearance.
    if (!mounted) return;

    setState(() {
      _metaData = metaData;
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: Center(
          child: () {
            Timer(Duration(seconds: 2), initPlatformState);
            return Text('Meta data:\n$_metaData\n');
          }(),
        ),
      ),
    );
  }
}
