/* -*- mode: c++ -*-
 * Atreus -- Chrysalis-enabled Sketch for the Keyboardio Atreus
 * Copyright (C) 2018-2022  Keyboard.io, Inc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built on " __DATE__ " at " __TIME__
#endif

#include "Kaleidoscope.h"
#include "Kaleidoscope/keyswitch_state.h"
#include "Kaleidoscope/Runtime.h"
#include "Kaleidoscope-AutoShift.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-Escape-OneShot.h"
#include "Kaleidoscope-FirmwareVersion.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-HostOS.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Qukeys.h"
#include "Kaleidoscope-SpaceCadet.h"
#include "Kaleidoscope-TapDance.h"
#include "Kaleidoscope-DynamicMacros.h"
#include "Kaleidoscope-LayerNames.h"

#define MO(n) ShiftToLayer(n)
#define TG(n) LockLayer(n)

enum {
  MACRO_QWERTY,
  MACRO_VERSION_INFO
};

#define Key_Exclamation LSHIFT(Key_1)
#define Key_At          LSHIFT(Key_2)
#define Key_Hash        LSHIFT(Key_3)
#define Key_Dollar      LSHIFT(Key_4)
#define Key_Percent     LSHIFT(Key_5)
#define Key_Caret       LSHIFT(Key_6)
#define Key_And         LSHIFT(Key_7)
#define Key_Star        LSHIFT(Key_8)
#define Key_Plus        LSHIFT(Key_Equals)

// TapDance custom keys
#define TD_Space     TD(0)
#define TD_Backtick  TD(1)
#define TD_Enter     TD(2)
#define TD_Backslash TD(3)
#define TD_NumFun    TD(4)

enum {
  QWERTY,
  QWERTY_WIN,
  NUM,
  UPPER,
  NOITA
};

// clang-format off
KEYMAPS(
  [QWERTY] = KEYMAP_STACKED
  (
       Key_Q   ,Key_W   ,Key_E       ,Key_R         ,Key_T
      ,Key_A   ,Key_S   ,Key_D       ,Key_F         ,Key_G
      ,Key_Z   ,Key_X   ,Key_C       ,Key_V         ,Key_B    ,TD_Backtick
      ,Key_LeftShift ,Key_LeftBracket ,Key_RightBracket ,TG(NUM) ,TD_Space ,Key_LeftGui

                     ,Key_Y     ,Key_U      ,Key_I     ,Key_O      ,Key_P
                     ,Key_H     ,Key_J      ,Key_K     ,Key_L      ,Key_Semicolon
       ,TD_Backslash ,Key_N     ,Key_M      ,Key_Comma ,Key_Period ,Key_Slash
       ,Key_Tab      ,TD_Enter  ,TD_NumFun  ,Key_Minus ,Key_Quote  ,Key_RightShift
  ),
  [QWERTY_WIN] = KEYMAP_STACKED
  (
       Key_Q   ,Key_W   ,Key_E       ,Key_R         ,Key_T
      ,Key_A   ,Key_S   ,Key_D       ,Key_F         ,Key_G
      ,Key_Z   ,Key_X   ,Key_C       ,Key_V         ,Key_B    ,TD_Backtick
      ,Key_LeftShift ,Key_LeftBracket ,Key_RightBracket ,TG(NUM) ,TD_Space ,Key_LeftControl

                     ,Key_Y     ,Key_U      ,Key_I     ,Key_O      ,Key_P
                     ,Key_H     ,Key_J      ,Key_K     ,Key_L      ,Key_Semicolon
       ,TD_Backslash ,Key_N     ,Key_M      ,Key_Comma ,Key_Period ,Key_Slash
       ,Key_Tab      ,TD_Enter  ,TD_NumFun  ,Key_Minus ,Key_Quote  ,Key_RightShift
  ),

  [NUM] = KEYMAP_STACKED
  (
       Key_PageUp   ,Key_Home      ,Key_UpArrow   ,Key_End        ,Key_Copy
      ,Key_PageDown ,Key_LeftArrow ,Key_DownArrow ,Key_RightArrow ,Key_Paste
      ,Key_Home     ,Key_End       ,Consumer_VolumeDecrement ,Consumer_VolumeIncrement      ,Consumer_Mute ,___
      ,TG(UPPER)    ,___       ,___           ,___        ,___         ,___

              ,Key_And    ,Key_7 ,Key_8      ,Key_9 ,LSHIFT(Key_9)
              ,Key_Equals ,Key_4 ,Key_5      ,Key_6 ,LSHIFT(Key_0)
      ,___    ,Key_Star   ,Key_1 ,Key_2     ,Key_3 ,___
      ,___         ,___   ,Key_0 ,Key_Period ,Key_Minus  ,___
   ),

  [UPPER] = KEYMAP_STACKED
  (
       ___ ,___ ,___ ,___ ,___
      ,___ ,___ ,___ ,___ ,___
      ,___ ,___ ,___ ,___ ,___ ,___
      ,M(MACRO_QWERTY) ,___ ,___ ,___ ,___ ,MoveToLayer(NOITA)

                ,Key_UpArrow   ,Key_F7           ,Key_F8          ,Key_F9         ,Key_F10
                ,Key_DownArrow ,Key_F4           ,Key_F5          ,Key_F6         ,Key_F11
      ,___      ,___           ,Key_F1           ,Key_F2          ,Key_F3         ,Key_F12
      ,___      ,___           ,___ ,___ ,___ ,M(MACRO_QWERTY)
   ),

  [NOITA] = KEYMAP_STACKED
  (
       Key_1   ,Key_I   ,Key_W       ,Key_E         ,Key_Esc
      ,Key_2   ,Key_A   ,Key_S       ,Key_D         ,Key_F
      ,Key_3   ,Key_5   ,Key_6       ,Key_7         ,Key_8         ,Key_Esc
      ,Key_4   ,Key_7   ,Key_8       ,XXX           ,XXX           ,Key_Esc

                           ,Key_VolumeUp  ,XXX           ,XXX           ,XXX ,M(MACRO_QWERTY)
                           ,Key_VolumeDown,Key_DownArrow ,Key_UpArrow   ,XXX ,MoveToLayer(UPPER)
       ,XXX                ,Key_Mute      ,Key_LeftArrow ,Key_RightArrow,XXX ,MoveToLayer(NUM)
       ,M(MACRO_QWERTY)    ,XXX           ,XXX           ,XXX           ,XXX ,M(MACRO_QWERTY)
  )
)
// clang-format on

KALEIDOSCOPE_INIT_PLUGINS(
  // ----------------------------------------------------------------------
  // Chrysalis plugins

  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
  EEPROMSettings,
  // EEPROMKeymap,

  // Focus allows bi-directional communication with the host, and is the
  // interface through which the keymap in EEPROM can be edited.
  Focus,

  // FocusSettingsCommand adds a few Focus commands, intended to aid in
  // changing some settings of the keyboard, such as the default layer (via the
  // `settings.defaultLayer` command)
  FocusSettingsCommand,

  // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
  // both debugging, and in backing up one's EEPROM contents.
  FocusEEPROMCommand,

  // The FirmwareVersion plugin lets Chrysalis query the version of the firmware
  // programmatically.
  FirmwareVersion,

  // The LayerNames plugin allows Chrysalis to display - and edit - custom layer
  // names, to be shown instead of the default indexes.
  // LayerNames,

  // ----------------------------------------------------------------------
  // Keystroke-handling plugins

  // The Qukeys plugin enables the "Secondary action" functionality in
  // Chrysalis. Keys with secondary actions will have their primary action
  // performed when tapped, but the secondary action when held.
  // Qukeys,

  // SpaceCadet can turn your shifts into parens on tap, while keeping them as
  // Shifts when held. SpaceCadetConfig lets Chrysalis configure some aspects of
  // the plugin.
  SpaceCadet,
  // SpaceCadetConfig,

  // Enables the "Sticky" behavior for modifiers, and the "Layer shift when
  // held" functionality for layer keys.
  // OneShot,
  // OneShotConfig,
  // EscapeOneShot,
  // EscapeOneShotConfig,

  // The macros plugin adds support for macros
  Macros,

  // Enables dynamic, Chrysalis-editable macros.
  // DynamicMacros

  TapDance,
  AutoShift

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  // MagicCombo,

  // Enables the GeminiPR Stenography protocol. Unused by default, but with the
  // plugin enabled, it becomes configurable - and then usable - via Chrysalis.
  // GeminiPR,
);

void setDefaultLayerForHostOS() {
  switch (HostOS.os()) {
  case kaleidoscope::hostos::WINDOWS:
    EEPROMSettings.default_layer(QWERTY_WIN);
    break;
  default:
    EEPROMSettings.default_layer(QWERTY);
    break;
  }
}

void toggleHostOsAndReset() {
  switch (HostOS.os()) {
  case kaleidoscope::hostos::WINDOWS:
    HostOS.os(kaleidoscope::hostos::MACOS);
    break;
  default:
    HostOS.os(kaleidoscope::hostos::WINDOWS);
    break;
  }
  kaleidoscope::Runtime.rebootBootloader();
}

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    switch (macro_id) {
    case MACRO_QWERTY:
      Layer.move(EEPROMSettings.default_layer());
      break;
    case MACRO_VERSION_INFO:
      Macros.type(PSTR("Keyboardio Atreus - Kaleidoscope "));
      Macros.type(PSTR(BUILD_INFORMATION));
      break;
    default:
      break;
    }
  }
  return MACRO_NONE;
}

void tapDanceSpaceModifier(uint8_t tap_count, kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
      tapDanceActionKeys(tap_count, tap_dance_action, Key_LeftControl, Key_LeftAlt, LSHIFT(ML(LeftGui, NUM)));
}

void handleTapDanceSpace(uint8_t tap_count, kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_action) {
  case kaleidoscope::plugin::TapDance::ActionType::Hold:
    tapDanceSpaceModifier(tap_count, tap_dance_action);
    break;
  case kaleidoscope::plugin::TapDance::ActionType::Interrupt:
    if (tap_count > 1) {
      tapDanceSpaceModifier(tap_count, tap_dance_action);
      break;
    }
    // else: fallthrough!
  case kaleidoscope::plugin::TapDance::ActionType::Timeout:
    tapDanceActionKeys(tap_count, tap_dance_action, Key_Space);
    break;
  }
}

void handleTapDanceEnter(uint8_t tap_count, kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_action) {
  case kaleidoscope::plugin::TapDance::ActionType::Hold:
  case kaleidoscope::plugin::TapDance::ActionType::Interrupt:
    tapDanceActionKeys(tap_count, tap_dance_action, Key_RightControl, Key_RightAlt, ML(LeftGui, NUM));
    break;
  case kaleidoscope::plugin::TapDance::ActionType::Timeout:
    tapDanceActionKeys(tap_count, tap_dance_action, Key_Enter);
    break;
  }
}

void handleTapDanceBacktick(uint8_t tap_count, kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_action) {
  case kaleidoscope::plugin::TapDance::ActionType::Hold:

    tapDanceActionKeys(tap_count, tap_dance_action, LSHIFT(Key_Backtick), ML(LeftControl, NUM), ML(LeftAlt, NUM));

    if (tap_count == 4) {  // Beethoven's 5th
      AutoShift.toggle();
    }
    break;
  case kaleidoscope::plugin::TapDance::ActionType::Interrupt:
  case kaleidoscope::plugin::TapDance::ActionType::Timeout:
    tapDanceActionKeys(tap_count, tap_dance_action, Key_Backtick, Key_Esc, LCTRL(LALT(Key_Delete)));
    break;
  default:
    return;
  }
}

void handleTapDanceBackslash(uint8_t tap_count, kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_action) {
  case kaleidoscope::plugin::TapDance::ActionType::Hold:
    if (tap_count == 4) {  // Beethoven's 5th
      toggleHostOsAndReset();
    }
    tapDanceActionKeys(tap_count, tap_dance_action, LSHIFT(Key_Backslash), LGUI(Key_LeftAlt));
    break;
  case kaleidoscope::plugin::TapDance::ActionType::Interrupt:
  case kaleidoscope::plugin::TapDance::ActionType::Timeout:
    tapDanceActionKeys(tap_count, tap_dance_action, Key_Backslash, Key_CapsLock);
    break;
  }
}

void handleTapDanceNumFun(uint8_t tap_count, kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_action) {
  case kaleidoscope::plugin::TapDance::ActionType::Hold:
    tapDanceActionKeys(tap_count, tap_dance_action, MO(NUM), MO(UPPER));
    break;
  case kaleidoscope::plugin::TapDance::ActionType::Interrupt:
  case kaleidoscope::plugin::TapDance::ActionType::Timeout:
    tapDanceActionKeys(tap_count, tap_dance_action, Key_0, TG(NUM));
    break;
  }
}

void tapDanceAction(uint8_t tap_dance_index, KeyAddr key_addr, uint8_t tap_count, kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  if (tap_dance_action == kaleidoscope::plugin::TapDance::ActionType::Tap) {
    // Immediately cancel any in-progress AutoShift delay
    // If you don't do this, hanging stickiness upper-cases letters at the ends of words
    // before whitespace characters that this configuration uses as TapDance items.
    // e.g. SentenceS maY looK likE this>
    KeyEvent event{key_addr, IS_PRESSED, Key_Esc};
    AutoShift.onKeyswitchEvent(event);
  }
  switch (tap_dance_index) {
  case 0:
    handleTapDanceSpace(tap_count, tap_dance_action);
    break;
  case 1:
    handleTapDanceBacktick(tap_count, tap_dance_action);
    break;
  case 2:
    handleTapDanceEnter(tap_count, tap_dance_action);
    break;
  case 3:
    handleTapDanceBackslash(tap_count, tap_dance_action);
    break;
  case 4:
    handleTapDanceNumFun(tap_count, tap_dance_action);
    break;
  }
}

void setupSpaceCadet() {
  if (EEPROMSettings.default_layer() == QWERTY) {
    static kaleidoscope::plugin::SpaceCadet::KeyBinding bindings[] = {
      {Key_LeftShift, Key_LeftParen, 120},
      {Key_RightShift, Key_RightParen, 120},
      {Key_LeftGui, Key_Backspace, 110},
      SPACECADET_MAP_END};
    SpaceCadet.setMap(bindings);
  } else {
    static kaleidoscope::plugin::SpaceCadet::KeyBinding bindings[] = {
      {Key_LeftShift, Key_LeftParen, 120},
      {Key_RightShift, Key_RightParen, 120},
      {Key_LeftControl, Key_Backspace, 110},
      SPACECADET_MAP_END};
    SpaceCadet.setMap(bindings);
  }
}

namespace kaleidoscope {
namespace plugin {
bool AutoShift::isAutoShiftable(Key key) {
  if (key == Key_Tab) {
    return true;  // I like an easy back-tab, ok?
  }

  // These interfere with TapDance - interrupting keys will get dropped
  switch (key.getKeyCode()) {
  case Key_Backtick.getKeyCode():
  case Key_Backslash.getKeyCode():
  case Key_Space.getKeyCode():
  case Key_Enter.getKeyCode():
  case Key_0.getKeyCode():
    return false;
  }

  if (Layer.isActive(NOITA))
  {
    return false;
  }

  return enabledForKey(key);
}
}  // namespace plugin
}  // namespace kaleidoscope

void setup() {
  Kaleidoscope.setup();

  setDefaultLayerForHostOS();
  // EEPROMKeymap.setup(9);
  // DynamicMacros.reserve_storage(48);
  // LayerNames.reserve_storage(63);

  Layer.move(EEPROMSettings.default_layer());

  TapDance.setTimeout(145);  // -- default is 200...
  AutoShift.enable(AutoShift.printableKeys());
  AutoShift.setTimeout(145);

  setupSpaceCadet();
}

void loop() {
  Kaleidoscope.loop();
}
