# mini_player

This Go package implements the host-side of the Flutter [mini_player](https://github.com/tadjaur/mini_player) plugin.

## Usage

Import as:

```go
import mini_player "github.com/tadjaur/mini_player/go"
```

Then add the following option to your go-flutter [application options](https://github.com/go-flutter-desktop/go-flutter/wiki/Plugin-info):

```go
flutter.AddPlugin(&mini_player.MiniPlayerPlugin{}),
```
