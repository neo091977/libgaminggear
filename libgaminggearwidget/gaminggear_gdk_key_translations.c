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
#include "gaminggear_helper.h"

static guint gaminggear_xkeycode_to_keyval(guint keycode) {
	GdkKeymap *keymap;
	GdkKeymapKey key = {keycode, 0, 0};
	guint keyval;

	keymap = gdk_keymap_get_default();
	keyval = gdk_keymap_lookup_key(keymap, &key);
	if (keyval == 0)
		g_warning("in gaminggear_xkeycode_to_keyval: keycode %i has no keyval!\n", keycode);
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
		string = g_strdup("Button left");
		break;
	case GAMINGGEAR_MACRO_KEYSTROKE_KEY_BUTTON_RIGHT:
		string = g_strdup("Button right");
		break;
	case GAMINGGEAR_MACRO_KEYSTROKE_KEY_BUTTON_MIDDLE:
		string = g_strdup("Button middle");
		break;
	default:
		if (usage_id > GAMINGGEAR_MACRO_KEYSTROKE_KEY_BUTTON_LEFT)
			string = g_strdup_printf("Button %u", usage_id - GAMINGGEAR_MACRO_KEYSTROKE_KEY_BUTTON_LEFT + 1);
		else
			string = gaminggear_xkeycode_to_keyname(gaminggear_hid_to_xkeycode(usage_id));
	}
	return string;
}
