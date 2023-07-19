part of mini_player;

/// represent the audio metadata
abstract class AudioMetaData {
  /// the title of the audio
  String get tagTitle;

  /// the artist
  String get tagArtist;

  /// the album
  String get tagAlbum;

  /// the publication year
  int get tagYear;

  /// the comment about the audio
  String get tagComment;

  /// the audio track id
  int get tagTrack;

  /// the genre
  String get tagGenre;

  /// the bit rate in Kb/s
  int get propertyBitrate;

  /// the sample rate in Hz
  int get propertySampleRate;

  /// the number of channel
  int get propertyChannels;

  /// the length of the audio in second
  int get propertyLength;

  @override
  String toString();
}

class _AudioMetaDataImpl implements AudioMetaData {
  final String tagTitle;
  final String tagArtist;
  final String tagAlbum;
  final int tagYear;
  final String tagComment;
  final int tagTrack;
  final String tagGenre;
  final int propertyBitrate;
  final int propertySampleRate;
  final int propertyChannels;
  final int propertyLength;
  final Map<String, dynamic> _map;

  _AudioMetaDataImpl.fromMap(Map<String, dynamic> map)
      : tagTitle = map["tags"]["title"],
        tagArtist = map["tags"]["artist"],
        tagAlbum = map["tags"]["album"],
        tagYear = map["tags"]["year"],
        tagComment = map["tags"]["comment"],
        tagTrack = map["tags"]["track"],
        tagGenre = map["tags"]["genre"],
        propertyBitrate = map["properties"]["bitrate"],
        propertySampleRate = map["properties"]["sampleRate"],
        propertyChannels = map["properties"]["channels"],
        propertyLength = map["properties"]["length"],
        _map = map;

  @override
  String toString() {
    return _map.toString();
  }
}
