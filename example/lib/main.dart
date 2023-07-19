import 'dart:async';
import 'dart:io';

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
  MiniPlayer mp;

  @override
  void initState() {
    super.initState();
  }

  // Platform messages are asynchronous, so we initialize in an async method.
  Future<void> initPlatformState() async {
    bool metaData;
    if (mp == null) {
      mp = MiniPlayer();
      final List<String> listName = [];
      final Directory directory = Directory("/sdcard/Music/sam smith");
      for (final fse in directory.listSync()) {
        if (fse is File) {
          listName.add(fse.absolute.path);
        }
      }
      try {
        metaData = await mp.init(listName);
      } finally {
        //pass
      }
    }
    mp.sendEvent(AudioEvent.play);

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
