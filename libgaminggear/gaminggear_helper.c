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

#include "gaminggear_helper.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>

gpointer g_gaminggear_key_file_get_binary(GKeyFile *key_file, gchar const *group_name, gchar const *key, gsize size, GError **error) {
	gchar *string, *source;
	gpointer result;
	guint8 *target;
	char hex[3] = { 0, 0, 0 };
	guint i;

	string = g_key_file_get_value(key_file, group_name, key, error);

	if (!string)
		return NULL;

	if (strlen(string) != size * 2) {
		g_set_error(error, G_KEY_FILE_ERROR, G_KEY_FILE_ERROR_INVALID_VALUE, "Data has wrong length %lu instead of %lu", (gulong)strlen(string), (gulong)(size * 2));
		g_free(string);
		return NULL;
	}

	source = string;

	result = g_malloc(size);
	target = result;

	for (i = 0; i < size; ++i, ++target) {
		hex[0] = *source++;
		hex[1] = *source++;
		*target = strtoul(hex, NULL, 16);
	}

	g_free(string);
	return result;
}

void g_gaminggear_key_file_set_binary(GKeyFile *key_file, gchar const *group_name, gchar const *key, gconstpointer data, gsize size) {
	gchar *string, *new_string, *element;
	guint8 const *source = data;
	guint i;

	string = g_malloc(1);
	*string = 0;

	for (i = 0; i < size; ++i, ++source) {
		element = g_strdup_printf("%02X", *source);
		new_string = g_strconcat(string, element, NULL);
		g_free(string);
		g_free(element);
		string = new_string;
	}

	g_key_file_set_value(key_file, group_name, key, string);
	g_free(string);
}

static gboolean gaminggear_create_dir_if_needed_with_mode(gchar const *dir, int mode, GError **error) {
	if (!g_file_test(dir, G_FILE_TEST_IS_DIR)) {
		if (g_mkdir_with_parents(dir, mode)) {
			g_set_error(error, G_FILE_ERROR, g_file_error_from_errno(errno), "Error creating directory: %s", g_strerror(errno));
			return FALSE;
		}
	}
	return TRUE;
}

gboolean gaminggear_create_dir_if_needed(gchar const *dir, GError **error) {
	return gaminggear_create_dir_if_needed_with_mode(dir, 0700, error);
}

gchar *g_gaminggear_unichar_to_utf8(gunichar c) {
	gchar *outbuf;
	outbuf = g_malloc0(6);
	g_unichar_to_utf8(c, outbuf);
	return outbuf;
}

gchar *gaminggear_create_filename_with_extension(gchar const *filename, gchar const *extension) {
	gchar *result;
	gchar *suffix;

	suffix = g_strconcat(".", extension, NULL);

	if (g_str_has_suffix(filename, suffix))
		result = g_strdup(filename);
	else
		result = g_strconcat(filename, suffix, NULL);

	g_free(suffix);

	return result;
}