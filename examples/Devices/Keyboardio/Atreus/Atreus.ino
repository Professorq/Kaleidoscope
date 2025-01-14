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
#include "Kaleidoscope-AutoShift.h"

#define MO(n) ShiftToLayer(n)
#define TG(n) LockLayer(n)

enum {
  MACRO_QWERTY,
  MACRO_VERSION_INFO,
  MACRO_OSL_UP,
  MACRO_OSL_DOWN,
  MACRO_SHIFT_UP,
  MACRO_SHIFT_DOWN,
  MACRO_TG_UP,
  MACRO_TG_DOWN,
  MACRO_INCREASE_TIMEOUT,
  MACRO_DECREASE_TIMEOUT,
  MACRO_TOGGLE_AUTOSHIFT,
  MACRO_FORCE_QUIT,
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

enum {
  TD_SPACE,
  TD_BACKTICK,
  TD_ENTER,
  TD_BACKSLASH,
  TD_NUMFUN,
};

// TapDance custom keys
#define TD_Space     TD(TD_SPACE)
#define TD_Backtick  TD(TD_BACKTICK)
#define TD_Enter     TD(TD_ENTER)
#define TD_Backslash TD(TD_BACKSLASH)
#define TD_NumFun    TD(TD_NUMFUN)

enum {
  QWERTY,
  QWERTY_WIN,
  NUM,
  FUN,
  NOITA
};

#define TAP_SLOW        M(MACRO_INCREASE_TIMEOUT)
#define TAP_FAST        M(MACRO_DECREASE_TIMEOUT)
#define TG_AUTO         M(MACRO_TOGGLE_AUTOSHIFT)

// Tap Dance layer customizations
enum {
  LTHUMBIN,
  LTHUMBREST,
  LTHUMBOUT,
  RTHUMBOUT,
  RTHUMBREST,
  RTHUMBIN,
  LSHIFTP,
  RSHIFTP,
  TICKESC,
  PIPECAD,
};

// clang-format off
KEYMAPS(
  [QWERTY] = KEYMAP_STACKED
  (
       Key_Q   ,Key_W       ,Key_E       ,Key_R         ,Key_T
      ,Key_A   ,Key_S       ,Key_D       ,Key_F         ,Key_G
      ,Key_Z   ,Key_X       ,Key_C       ,Key_V         ,Key_B     ,TD(TICKESC)
      ,TD(LSHIFTP) ,Key_LeftBracket ,Key_RightBracket ,TD(LTHUMBIN) ,TD(LTHUMBREST) ,TD(LTHUMBOUT)

                    ,Key_Y     ,Key_U      ,Key_I     ,Key_O      ,Key_P
                    ,Key_H     ,Key_J      ,Key_K     ,Key_L      ,Key_Semicolon
      ,TD(PIPECAD)  ,Key_N     ,Key_M      ,Key_Comma ,Key_Period ,Key_Slash
      ,TD(RTHUMBOUT),TD(RTHUMBREST),TD(RTHUMBIN),Key_Minus ,Key_Quote  ,TD(RSHIFTP)
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
       M(MACRO_QWERTY),Key_Home  ,Key_UpArrow             ,Key_End                 ,Key_PageUp
      ,TAP_FAST   ,Key_LeftArrow ,Key_DownArrow           ,Key_RightArrow          ,Key_PageDown
      ,TAP_SLOW   ,TG_AUTO       ,Consumer_VolumeIncrement,Consumer_VolumeDecrement,Consumer_Mute ,___
      ,___        ,___           ,___                     ,M(MACRO_QWERTY)         ,___           ,___

            ,Key_Quote ,Key_7 ,Key_8      ,Key_9 ,M(MACRO_QWERTY)
            ,Key_Equals,Key_4 ,Key_5      ,Key_6 ,___
      ,___  ,Key_Minus ,Key_1 ,Key_2      ,Key_3 ,___
      ,___  ,___       ,Key_0 ,Key_Period ,Key_0 ,___
   ),
  /*
  [FUN] = KEYMAP_STACKED
  (
     TAP_FAST  ,Key_LeftParen,     ,Key_RightParen   ,___ ,Key_Paste
    ,TAP_SLOW ,Key_LeftBracket     ,Key_RightBracket ,___ ,Key_Copy
    ,TG_AUTO  ,Key_LeftCurlyBracket,Key_RightCurlyBracket ,___ ,Key_Insert ,Key_Delete
    ,M(MACRO_QWERTY)  ,TG(NUM) ,Key_LGui ,Key_LCtrl ,___ ,MoveToLayer(NOITA)

                ,Key_UpArrow   ,Key_F7   ,Key_F8 ,Key_F9 ,Key_F10
                ,Key_DownArrow ,Key_F4   ,Key_F5 ,Key_F6 ,Key_F11
      ,Key_Esc  ,___           ,Key_F1   ,Key_F2 ,Key_F3 ,Key_F12
      ,___      ,___           ,TG(NUM)  ,___    ,___    ,M(MACRO_QWERTY)
   ),
*/
  /*
  [NOITA] = KEYMAP_STACKED
  (
       Key_1   ,Key_I   ,Key_W       ,Key_E         ,Key_Esc
      ,Key_2   ,Key_A   ,Key_S       ,Key_D         ,Key_F
      ,Key_3   ,Key_5   ,Key_6       ,Key_7         ,Key_8         ,Key_Esc
      ,Key_4   ,Key_7   ,Key_8       ,XXX           ,XXX           ,Key_Esc

                           ,Key_VolumeUp  ,XXX           ,XXX           ,XXX ,M(MACRO_QWERTY)
                           ,Key_VolumeDown,Key_DownArrow ,Key_UpArrow   ,XXX ,MoveToLayer(FUN)
       ,XXX                ,Key_Mute      ,Key_LeftArrow ,Key_RightArrow,XXX ,MoveToLayer(NUM)
       ,M(MACRO_QWERTY)    ,XXX           ,XXX           ,XXX           ,XXX ,M(MACRO_QWERTY)
  )
  */
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

  HostOS,

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
  // SpaceCadet,
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

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  // MouseKeys,
  // MouseKeysConfig  //,

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

void enterModifier(uint8_t tap_count, kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  tapDanceActionKeys(tap_count, tap_dance_action, Key_RightControl, Key_RightAlt, ML(LeftGui, NUM));
}

void handleTapDanceEnter(uint8_t tap_count, kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_action) {
  case kaleidoscope::plugin::TapDance::ActionType::Hold:
    enterModifier(tap_count, tap_dance_action);
    break;
  case kaleidoscope::plugin::TapDance::ActionType::Interrupt:
    if (tap_count > 1) {
      enterModifier(tap_count, tap_dance_action);
      break;
    }
  case kaleidoscope::plugin::TapDance::ActionType::Timeout:
    tapDanceActionKeys(tap_count, tap_dance_action, Key_Enter);
    break;
  }
}

void handleTapDanceBacktick(uint8_t tap_count, kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_action) {
  case kaleidoscope::plugin::TapDance::ActionType::Hold:
    if (tap_count == 4) {  // Beethoven's 5th
      AutoShift.toggle();
    } else {
      tapDanceActionKeys(tap_count, tap_dance_action, LSHIFT(Key_Backtick), ML(LeftControl, NUM), ML(LeftAlt, NUM));
    }
    break;
  case kaleidoscope::plugin::TapDance::ActionType::Interrupt:
  case kaleidoscope::plugin::TapDance::ActionType::Timeout:
    tapDanceActionKeys(tap_count, tap_dance_action, Key_Backtick, Key_Esc, M(MACRO_FORCE_QUIT));
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
    tapDanceActionKeys(tap_count, tap_dance_action, MO(NUM), MO(FUN));
    break;
  case kaleidoscope::plugin::TapDance::ActionType::Interrupt:
  case kaleidoscope::plugin::TapDance::ActionType::Timeout:
    tapDanceActionKeys(tap_count, tap_dance_action, Key_0, TG(NUM));
    break;
  }
}

void backspaceModifier(uint8_t tap_count, kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  tapDanceActionKeys(tap_count, tap_dance_action, Key_LeftGui, ML(LeftGui, NUM));
}

void handleTapDanceBackspace(uint8_t tap_count, kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
    switch (tap_dance_action) {
    case kaleidoscope::plugin::TapDance::Hold:
      backspaceModifier(tap_count, tap_dance_action);
      break;
    case kaleidoscope::plugin::TapDance::Interrupt:
      if (tap_count > 1) {
	backspaceModifier(tap_count, tap_dance_action);
	break;
      }
      // else fallthrough
    case kaleidoscope::plugin::TapDance::Timeout:
      tapDanceActionKeys(tap_count, tap_dance_action, Key_Backspace);
      break;
    }
  }

void tapDanceAction(uint8_t tap_dance_index, KeyAddr key_addr, uint8_t tap_count,
                    kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  // Immediately cancel any in-progress AutoShift delay
  // If you don't do this, hanging stickiness upper-cases letters at the ends of words
  // before whitespace characters that this configuration uses as TapDance items.
  // e.g. SentenceS maY looK likE this>
  KeyEvent escape{key_addr, IS_PRESSED | INJECTED, Key_Esc};
  AutoShift.onKeyswitchEvent(escape);

  switch (tap_dance_index) {
  case LTHUMBIN:
    handleTapDanceNumFun(tap_count, tap_dance_action);
    break;
   case LTHUMBREST:
    handleTapDanceSpace(tap_count, tap_dance_action);
    break;
  case LTHUMBOUT:
    handleTapDanceBackspace(tap_count, tap_dance_action);
    break;
  case RTHUMBOUT:
    switch (tap_dance_action) {
    case kaleidoscope::plugin::TapDance::Hold:
    case kaleidoscope::plugin::TapDance::Timeout:
      tapDanceActionKeys(tap_count, tap_dance_action, Key_Tab, LSHIFT(Key_Tab));
      break;
    case kaleidoscope::plugin::TapDance::Interrupt:
      tapDanceActionKeys(tap_count, tap_dance_action, Key_RightGui);
      break;
    }
    break;
  case RTHUMBREST:
    handleTapDanceEnter(tap_count, tap_dance_action);
    break;
  case RTHUMBIN:
    handleTapDanceNumFun(tap_count, tap_dance_action);
    break;
  case LSHIFTP:
    switch (tap_dance_action) {
    case kaleidoscope::plugin::TapDance::Timeout:
      tapDanceActionKeys(tap_count, tap_dance_action, LSHIFT(Key_9), M(MACRO_TG_UP), M(MACRO_TG_DOWN));
      break;
    case kaleidoscope::plugin::TapDance::Interrupt:
    case kaleidoscope::plugin::TapDance::Hold:
      tapDanceActionKeys(tap_count, tap_dance_action, Key_LeftShift);
      break;
    } 
    break;
  case RSHIFTP:
    switch (tap_dance_action) {
    case kaleidoscope::plugin::TapDance::Timeout:
      tapDanceActionKeys(tap_count, tap_dance_action, LSHIFT(Key_0), M(MACRO_TG_UP), M(MACRO_TG_DOWN));
      break;
    case kaleidoscope::plugin::TapDance::Interrupt:
    case kaleidoscope::plugin::TapDance::Hold:
      tapDanceActionKeys(tap_count, tap_dance_action, Key_RightShift);
      break;
    } 
    break;
  case TICKESC:
    handleTapDanceBacktick(tap_count, tap_dance_action);
    break;
  case PIPECAD:
    switch (tap_dance_action) {
    case kaleidoscope::plugin::TapDance::Timeout:
    case kaleidoscope::plugin::TapDance::Interrupt:
      tapDanceActionKeys(tap_count, tap_dance_action, Key_Backslash, Key_CapsLock);
      break;
    case kaleidoscope::plugin::TapDance::Hold:
      tapDanceActionKeys(tap_count, tap_dance_action, LSHIFT(Key_Backslash), LSHIFT(Key_Backslash), LSHIFT(Key_Backslash), M(MACRO_FORCE_QUIT));
      break;
    } 
    break;
  default:
    break;
  }
}

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    auto currentLayer = Layer.mostRecent();
    auto layerUp = min(currentLayer + 1, MAX_ACTIVE_LAYERS);
    auto layerDown = currentLayer == 0 ? 0 : currentLayer - 1;
    auto slower = AutoShift.timeout() + 5;
    auto faster = AutoShift.timeout() - 5;

    KeyEvent keyEvent{KeyAddr::none(), IS_PRESSED | INJECTED, Key_Undefined};

    switch (macro_id) {
    case MACRO_QWERTY:
      Layer.move(EEPROMSettings.default_layer());
      break;
    case MACRO_VERSION_INFO:
      Macros.type(PSTR("Keyboardio Atreus - Kaleidoscope "));
      Macros.type(PSTR(BUILD_INFORMATION));
      break;
    case MACRO_OSL_UP:
      keyEvent.key = OSL(layerUp);
      break;
    case MACRO_OSL_DOWN:
      keyEvent.key = OSL(layerDown);
      break;
    case MACRO_SHIFT_UP:
      keyEvent.key = ShiftToLayer(layerUp);
      break;
    case MACRO_SHIFT_DOWN:
      keyEvent.key = ShiftToLayer(layerDown);
      break;
    case MACRO_TG_UP:
      Layer.activate(layerUp);
      break;
    case MACRO_TG_DOWN:
      Layer.deactivate(currentLayer);
      break;
    case MACRO_INCREASE_TIMEOUT:
      // Should these always be in lock-step, or do we need to speed up TapDance without changing AutoShift?
      // SpaceCadet allows for individual key timeouts, but that is limited to a single tap/hold
      TapDance.setTimeout(slower);
      AutoShift.setTimeout(slower);
      break;
    case MACRO_DECREASE_TIMEOUT:
      TapDance.setTimeout(faster);
      AutoShift.setTimeout(faster);
      break;
    case MACRO_TOGGLE_AUTOSHIFT:
      AutoShift.toggle();
      break;
    case MACRO_FORCE_QUIT:
      if (HostOS.os() == kaleidoscope::hostos::WINDOWS) {
	Macros.press(Key_LeftControl);
	Macros.press(Key_LeftAlt);
	Macros.press(Key_Delete);
	Macros.clear();
      } else {
	Macros.press(Key_LeftGui);
	Macros.press(Key_LeftAlt);
	Macros.press(Key_Esc);
	Macros.clear();
      }
      break;
    default:
      break;
    }
    if (keyEvent.key != Key_Undefined) {
      Kaleidoscope.handleKeyEvent(keyEvent);
    }
  }
  return MACRO_NONE;
}

namespace kaleidoscope {
namespace plugin {
bool AutoShift::isAutoShiftable(Key key) {
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

  Layer.move(EEPROMSettings.default_layer());

  AutoShift.setTimeout(135); // Default is intolerable 200
  TapDance.setTimeout(AutoShift.timeout()); 
  AutoShift.enable(AutoShift.printableKeys());
}

void loop() {
  Kaleidoscope.loop();
}
