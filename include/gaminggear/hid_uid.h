#ifndef __HID_UID_H__
#define __HID_UID_H__

/*
 * This file is part of libgaminggear.
 *
 * libgaminggear is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libgaminggear is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libgaminggear. If not, see <http://www.gnu.org/licenses/>.
 */

 /*! \file gaminggear/hid_uid.h
  *  \brief HID usage id definitions.
  */

typedef enum {
	HID_UID_KB_A = 0x04,
	HID_UID_KB_B = 0x05,
	HID_UID_KB_C = 0x06,
	HID_UID_KB_D = 0x07,
	HID_UID_KB_E = 0x08,
	HID_UID_KB_F = 0x09,
	HID_UID_KB_G = 0x0a,
	HID_UID_KB_Q = 0x14,
	HID_UID_KB_R = 0x15,
	HID_UID_KB_S = 0x16,
	HID_UID_KB_T = 0x17,
	HID_UID_KB_V = 0x19,
	HID_UID_KB_W = 0x1a,
	HID_UID_KB_X = 0x1b,
	HID_UID_KB_Z = 0x1d,
	HID_UID_KB_1 = 0x1e,
	HID_UID_KB_2 = 0x1f,
	HID_UID_KB_3 = 0x20,
	HID_UID_KB_4 = 0x21,
	HID_UID_KB_5 = 0x22,
	HID_UID_KB_ENTER = 0x28,
	HID_UID_KB_ESCAPE = 0x29,
	HID_UID_KB_CAPSLOCK = 0x39,
	HID_UID_KB_F1 = 0x3a,
	HID_UID_KB_F2 = 0x3b,
	HID_UID_KB_F3 = 0x3c,
	HID_UID_KB_F4 = 0x3d,
	HID_UID_KB_F5 = 0x3e,
	HID_UID_KB_F6 = 0x3f,
	HID_UID_KB_F7 = 0x40,
	HID_UID_KB_F8 = 0x41,
	HID_UID_KB_F9 = 0x42,
	HID_UID_KB_F10 = 0x43,
	HID_UID_KB_F11 = 0x44,
	HID_UID_KB_F12 = 0x45,
	HID_UID_KB_PRINT_SCREEN = 0x46,
	HID_UID_KB_SCROLL_LOCK = 0x47,
	HID_UID_KB_PAUSE = 0x48,
	HID_UID_KB_LEFT_CONTROL = 0xe0,
	HID_UID_KB_LEFT_SHIFT = 0xe1,
	HID_UID_KB_LEFT_ALT = 0xe2,
	HID_UID_KB_LEFT_GUI = 0xe3,
	HID_UID_KB_RIGHT_ALT = 0xe6,
	HID_UID_KB_RIGHT_GUI = 0xe7,
} HidUsageIdKeyboard;

#endif
