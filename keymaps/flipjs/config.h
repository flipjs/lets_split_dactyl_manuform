/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
//#include "../../config.h"

/* Use I2C or Serial, not both */

#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */

//#define MASTER_LEFT
//#define MASTER_RIGHT
#define EE_HANDS



#define MOUSEKEY_DELAY             150 //200
#define MOUSEKEY_INTERVAL          60 //50
#define MOUSEKEY_MAX_SPEED         4 //10
#define MOUSEKEY_TIME_TO_MAX       7 //20
#define MOUSEKEY_WHEEL_MAX_SPEED   5	//8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40

// AK20190524 - this timing is required - the default one is too long for me
#define TAPPING_TERM 200 //90 //200 // how long before a tap becomes a hold

// does not seem doing any good... #define PREVENT_STUCK_MODIFIERS //when switching layers, this will release all mods

// This is to make Shift/Space keys to work as wanted:
// This is to make Shift/Space keys to work as wanted:
// AK20190523 - since shift/space is no longer combined this is not required
// #define INGNORE_MOD_TAP_INTERRUPT
// #undef PERMISSIVE_HOLD
// #define  PREVENT_STUCK_MODIFIERS



// As per a reply to my post at reddit:
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2500

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD
