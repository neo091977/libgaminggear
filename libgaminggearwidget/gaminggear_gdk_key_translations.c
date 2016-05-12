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

#include "gaminggear/gdk_key_translations.h"
#include "gaminggear/key_translations.h"
#include "gaminggear/macro.h"
#include "gaminggear/hid_uid.h"
#include "gaminggear_helper.h"
#include "i18n-lib.h"

static guint gaminggear_xkeycode_to_keyval(guint keycode) {
	GdkKeymap *keymap;
	GdkKeymapKey key = {keycode, 0, 0};
	guint keyval;

	keymap = gdk_keymap_get_default();
	keyval = gdk_keymap_lookup_key(keymap, &key);
	if (keyval == 0)
		g_warning(_("Xkeycode 0x%04x has no corresponding keyval in keymap"), keycode);
	return keyval;
}

static gchar *gaminggear_keyval_to_keyname(guint keyval) {
	guint32 unicode;

	unicode = gdk_keyval_to_unicode(keyval);

	if (g_unichar_isgraph(unicode))
		return g_gaminggear_unichar_to_utf8(unicode);
	else
		return g_strdup(gdk_keyval_name(keyval));
}

gchar *gaminggear_xkeycode_to_keyname(guint keycode) {
	return gaminggear_keyval_to_keyname(gaminggear_xkeycode_to_keyval(keycode));
}

gchar *gaminggear_hid_to_keyname(guint8 usage_id) {
	gchar *string = NULL;

	switch (usage_id) {
	case GAMINGGEAR_MACRO_KEYSTROKE_KEY_BUTTON_LEFT:
		string = g_strdup(_("Button left"));
		break;
	case GAMINGGEAR_MACRO_KEYSTROKE_KEY_BUTTON_RIGHT:
		string = g_strdup(_("Button right"));
		break;
	case GAMINGGEAR_MACRO_KEYSTROKE_KEY_BUTTON_MIDDLE:
		string = g_strdup(_("Button middle"));
		break;
	default:
		if (usage_id >= GAMINGGEAR_MACRO_KEYSTROKE_KEY_BUTTON_LEFT)
			string = g_strdup_printf(_("Button %u"), usage_id - GAMINGGEAR_MACRO_KEYSTROKE_KEY_BUTTON_LEFT + 1);
		else
			string = gaminggear_xkeycode_to_keyname(gaminggear_hid_to_xkeycode(usage_id));
	}
	return string;
}

gchar *gaminggear_hid_to_name(guint8 usage_id) {
	gchar *text;

	switch(usage_id) {
	case HID_UID_KB_SPACE:
		text = g_strdup("Space");
		break;
	case HID_UID_KB_CAPS_LOCK:
		text = g_strdup("Caps lock");
		break;
	case HID_UID_KB_SCROLL_LOCK:
		text = g_strdup("Scroll lock");
		break;
	case HID_UID_KB_PAGE_UP:
		text = g_strdup("Page up");
		break;
	case HID_UID_KB_PAGE_DOWN:
		text = g_strdup("Page down");
		break;
	case HID_UID_KP_NUM_LOCK:
		text = g_strdup("Num lock");
		break;
	case HID_UID_KP_DIV:
		text = g_strdup("Keypad /");
		break;
	case HID_UID_KP_MUL:
		text = g_strdup("Keypad *");
		break;
	case HID_UID_KP_MINUS:
		text = g_strdup("Keypad -");
		break;
	case HID_UID_KP_PLUS:
		text = g_strdup("Keypad +");
		break;
	case HID_UID_KP_ENTER:
		text = g_strdup("Keypad Enter");
		break;
	case HID_UID_KP_1:
		text = g_strdup("Keypad 1");
		break;
	case HID_UID_KP_2:
		text = g_strdup("Keypad 2");
		break;
	case HID_UID_KP_3:
		text = g_strdup("Keypad 3");
		break;
	case HID_UID_KP_4:
		text = g_strdup("Keypad 4");
		break;
	case HID_UID_KP_5:
		text = g_strdup("Keypad 5");
		break;
	case HID_UID_KP_6:
		text = g_strdup("Keypad 6");
		break;
	case HID_UID_KP_7:
		text = g_strdup("Keypad 7");
		break;
	case HID_UID_KP_8:
		text = g_strdup("Keypad 8");
		break;
	case HID_UID_KP_9:
		text = g_strdup("Keypad 9");
		break;
	case HID_UID_KP_0:
		text = g_strdup("Keypad 0");
		break;
	case HID_UID_KB_LEFT_CONTROL:
		text = g_strdup("Left control");
		break;
	case HID_UID_KB_LEFT_SHIFT:
		text = g_strdup("Left shift");
		break;
	case HID_UID_KB_LEFT_ALT:
		text = g_strdup("Left alt");
		break;
	case HID_UID_KB_LEFT_GUI:
		text = g_strdup("Left gui");
		break;
	case HID_UID_KB_RIGHT_CONTROL:
		text = g_strdup("Right control");
		break;
	case HID_UID_KB_RIGHT_SHIFT:
		text = g_strdup("Right shift");
		break;
	case HID_UID_KB_RIGHT_ALT:
		text = g_strdup("Right alt");
		break;
	case HID_UID_KB_RIGHT_GUI:
		text = g_strdup("Right gui");
		break;
	default:
		text = gaminggear_hid_to_keyname(usage_id);
		break;
	}

	return text;
}
