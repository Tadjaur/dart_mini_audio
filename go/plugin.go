package mini_player

import (
	flutter "github.com/go-flutter-desktop/go-flutter"
	"github.com/go-flutter-desktop/go-flutter/plugin"
)

const channelName = "mini_player"

// MiniPlayerPlugin implements flutter.Plugin and handles method.
type MiniPlayerPlugin struct{}

var _ flutter.Plugin = &MiniPlayerPlugin{} // compile-time type check

// InitPlugin initializes the plugin.
func (p *MiniPlayerPlugin) InitPlugin(messenger plugin.BinaryMessenger) error {
	channel := plugin.NewMethodChannel(messenger, channelName, plugin.StandardMethodCodec{})
	channel.HandleFunc("getPlatformVersion", p.handlePlatformVersion)
	return nil
}

func (p *MiniPlayerPlugin) handlePlatformVersion(arguments interface{}) (reply interface{}, err error) {
	return "go-flutter " + flutter.PlatformVersion, nil
}
