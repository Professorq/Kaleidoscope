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
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-Escape-OneShot.h"
#include "Kaleidoscope-FirmwareVersion.h"
#include "Kaleidoscope-HostOS.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-MouseKeys.h"
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

#define TAP_SLOW        M(MACRO_INCREASE_TIMEOUT)
#define TAP_FAST        M(MACRO_DECREASE_TIMEOUT)
#define TG_AUTO         M(MACRO_TOGGLE_AUTOSHIFT)

enum {
  QWERTY,
  NUM,
  FUN,
};

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
  [NUM] = KEYMAP_STACKED
  (
       TG(QWERTY) ,Key_Home          ,Key_UpArrow            ,Key_End                  ,Key_PageUp
      ,TAP_FAST   ,Key_LeftArrow    ,Key_DownArrow           ,Key_RightArrow           ,Key_PageDown
      ,TAP_SLOW   ,TG_AUTO          ,Consumer_VolumeIncrement,Consumer_VolumeDecrement ,Consumer_Mute ,___
      ,TG(FUN)    ,___       ,___   ,___        ,___                   ,___

            ,___       ,Key_7 ,Key_8      ,Key_9 ,TG(QWERTY)
            ,Key_Equals,Key_4 ,Key_5      ,Key_6 ,___
      ,___  ,___       ,Key_1 ,Key_2      ,Key_3 ,___
      ,___  ,___       ,Key_0 ,Key_Period ,Key_0 ,TG(FUN)
   ),
  [FUN] = KEYMAP_STACKED
  (
       ___            ,___   ,___   ,Key_End        ,Key_PageUp
      ,___            ,___   ,___ ,Key_RightArrow ,Key_PageDown
      ,M(MACRO_VERSION_INFO) ,___ ,Consumer_VolumeIncrement,Consumer_VolumeDecrement ,Consumer_Mute ,___
      ,MoveToLayer(QWERTY)   ,___ ,___           ,___            ,___ ,___

                ,Key_UpArrow   ,Key_F7              ,Key_F8          ,Key_F9         ,Key_F10
                ,Key_DownArrow ,Key_F4              ,Key_F5          ,Key_F6         ,Key_F11
      ,___      ,XXX           ,Key_F1              ,Key_F2          ,Key_F3         ,Key_F12
      ,___      ,___           ,MoveToLayer(QWERTY) ,Key_PrintScreen ,Key_ScrollLock ,Consumer_PlaySlashPause
   )
)
// clang-format on

KALEIDOSCOPE_INIT_PLUGINS(
  // ----------------------------------------------------------------------
  // Chrysalis plugins

  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
  EEPROMSettings,
  EEPROMKeymap,

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
  OneShot,
  OneShotConfig,
  EscapeOneShot,
  EscapeOneShotConfig,

  // The macros plugin adds support for macros
  Macros,

  // Enables dynamic, Chrysalis-editable macros.
  DynamicMacros,

  AutoShift,
  TapDance,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,
  MouseKeysConfig  //,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  // MagicCombo,

  // Enables the GeminiPR Stenography protocol. Unused by default, but with the
  // plugin enabled, it becomes configurable - and then usable - via Chrysalis.
  // GeminiPR,
);

void tapDanceAction(uint8_t tap_dance_index, KeyAddr key_addr, uint8_t tap_count,
                    kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_index) {
  case LTHUMBIN:
    switch (tap_dance_action) {
    case kaleidoscope::plugin::TapDance::Timeout:
      tapDanceActionKeys(tap_count, tap_dance_action, M(MACRO_OSL_UP));
      break; 
    case kaleidoscope::plugin::TapDance::Interrupt:
    case kaleidoscope::plugin::TapDance::Hold:
      tapDanceActionKeys(tap_count, tap_dance_action, M(MACRO_SHIFT_UP));
      break;
    }
    break;
   case LTHUMBREST:
    switch (tap_dance_action) {
    case kaleidoscope::plugin::TapDance::Timeout:
    case kaleidoscope::plugin::TapDance::Interrupt:
      tapDanceActionKeys(tap_count, tap_dance_action, Key_Space);
      break;
    case kaleidoscope::plugin::TapDance::Hold:
      tapDanceActionKeys(tap_count, tap_dance_action, Key_LeftControl, Key_LeftAlt);
      break;
    }
    break;
  case LTHUMBOUT:
    switch (tap_dance_action) {
    case kaleidoscope::plugin::TapDance::Timeout:
    case kaleidoscope::plugin::TapDance::Interrupt:
      tapDanceActionKeys(tap_count, tap_dance_action, Key_Backspace);
      break;
    case kaleidoscope::plugin::TapDance::Hold:
      tapDanceActionKeys(tap_count, tap_dance_action, Key_LeftGui, Key_Backspace);
      break;
    }
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
    switch (tap_dance_action) {
    case kaleidoscope::plugin::TapDance::Timeout:
      tapDanceActionKeys(tap_count, tap_dance_action, Key_Enter);
      break;
    case kaleidoscope::plugin::TapDance::Interrupt:
    case kaleidoscope::plugin::TapDance::Hold:
      tapDanceActionKeys(tap_count, tap_dance_action, Key_RightControl);
      break;
    }
    break;
  case RTHUMBIN:
    switch (tap_dance_action) {
    case kaleidoscope::plugin::TapDance::Timeout:
    case kaleidoscope::plugin::TapDance::Interrupt:
      tapDanceActionKeys(tap_count, tap_dance_action, Key_0);
      break;
    case kaleidoscope::plugin::TapDance::Hold:
      tapDanceActionKeys(tap_count, tap_dance_action, ShiftToLayer(NUM), TG(NUM));
      break;
    } 
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
    switch (tap_dance_action) {
    case kaleidoscope::plugin::TapDance::Timeout:
      tapDanceActionKeys(tap_count, tap_dance_action, Key_Backtick, Key_Esc);
      break;
    case kaleidoscope::plugin::TapDance::Interrupt:
    case kaleidoscope::plugin::TapDance::Hold:
      tapDanceActionKeys(tap_count, tap_dance_action, LSHIFT(Key_Backtick));
      break;
    } 
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
      // This macro is currently unused, but is kept around for compatibility
      // reasons. We used to use it in place of `MoveToLayer(QWERTY)`, but no
      // longer do. We keep it so that if someone still has the old layout with
      // the macro in EEPROM, it will keep working after a firmware update.
      Layer.move(QWERTY);
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
      // Should these always be in lock-step, or do we need to speed up TapDance?
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

void setup() {
  Kaleidoscope.setup();
  EEPROMKeymap.setup(9);

  AutoShift.enable();
  TapDance.setTimeout(AutoShift.timeout()); 

  // DynamicMacros.reserve_storage(48);
  // LayerNames.reserve_storage();

  Layer.move(EEPROMSettings.default_layer());

  // To avoid any surprises, SpaceCadet is turned off by default. However, it
  // can be permanently enabled via Chrysalis, so we should only disable it if
  // no configuration exists.
  SpaceCadetConfig.disableSpaceCadetIfUnconfigured();
}

void loop() {
  Kaleidoscope.loop();
}
