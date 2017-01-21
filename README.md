# Akela-LED-ActiveModColor

![status][st:experimental]

 [st:stable]: https://img.shields.io/badge/stable-✔-black.png?style=flat&colorA=44cc11&colorB=494e52
 [st:broken]: https://img.shields.io/badge/broken-X-black.png?style=flat&colorA=e05d44&colorB=494e52
 [st:experimental]: https://img.shields.io/badge/experimental----black.png?style=flat&colorA=dfb317&colorB=494e52

With this plugin, any active modifier on the keyboard will have the LED under it
highlighted. No matter how the modifier got activated (a key press, a macro,
anything else), the coloring will apply.

## Using the plugin

To use the plugin, one needs to include the header, and activate the effect. It
is also possible to use a custom color instead of the white default.

```c++
#include <Akela-LED-ActiveModColor.h>

void setup () {
  Keyboardio.setup (KEYMAP_SIZE);

  Keyboardio.use (&ActiveModColorEffect, NULL);
  
  ActiveModColorEffect.configure ({0x00, 0xff, 0xff});
}
```

It is recommended to place the activation (the `Keyboardio.use` call) of the
plugin last, so that it can reliably override any other plugins that may work
with the LEDs, and apply the highlight over those.

## Plugin methods

The plugin provides the `ActiveModColorEffect` object, which has the following
method:

### `.configure(color)`

> Set the color to use for highlighting the modifiers. If unset, will use the
> default white color.
