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

#include "gaminggear/gfx.h"
#include <glib.h>
#include <stdlib.h>

static gboolean parameter_color = FALSE;
static gint64 parameter_color1 = 0;

static GOptionEntry entries[] = {
	{ "color", 'c', 0, G_OPTION_ARG_NONE, &parameter_color, "set plain color", NULL },
	{ "color1", '1', 0, G_OPTION_ARG_INT64, &parameter_color1, "COLOR", "COLOR" },
	{ NULL }
};

static gboolean post_parse_func(GOptionContext *context, GOptionGroup *group, gpointer data, GError **error) {
	return TRUE;
}

static GOptionContext *commandline_parse(int *argc, char ***argv) {
	GOptionContext *context = NULL;
	GError *error = NULL;

	context = g_option_context_new("- control Gaminggear FX");
	g_option_context_add_main_entries(context, entries, NULL);

	g_option_group_set_parse_hooks(g_option_context_get_main_group(context), NULL, post_parse_func);

	if (!g_option_context_parse(context, argc, argv, &error)) {
		g_critical("option parsing failed: %s", error->message);
		exit(EXIT_FAILURE);
	}
	return context;
}

static void convert_int_to_color(gint64 value, GfxColor *color) {
	color->brightness = (value & 0xff000000) >> 24;
	color->red = (value & 0x00ff0000) >> 16;
	color->green = (value & 0x0000ff00) >> 8;
	color->blue = (value & 0x000000ff) >> 0;
}

static void commandline_free(GOptionContext *context) {
}

int main(int argc, char **argv) {
	GOptionContext *context;
	GfxResult gfx_result;
	int retval = EXIT_FAILURE;
	GfxColor color1;

	context = commandline_parse(&argc, &argv);

	gfx_result = gfx_initialize();
	if (gfx_result != GFX_SUCCESS) {
		g_warning("There was an error initializing the fx system");
		goto exit_1;
	}

	convert_int_to_color(parameter_color1, &color1);

	if (parameter_color) {
		gfx_result = gfx_light(GFX_LOCATION_ALL, &color1);
		if (gfx_result != GFX_SUCCESS) {
			g_warning("There was an error setting color");
			goto exit_2;
		}
	}

	if (parameter_color) {
		gfx_result = gfx_update();
		if (gfx_result != GFX_SUCCESS) {
			g_warning("There was an error updating");
			goto exit_2;
		}
	}

	retval = EXIT_SUCCESS;
exit_2:
	gfx_result = gfx_release();
	if (gfx_result != GFX_SUCCESS) {
		g_warning("There was an error releasing the fx system");
		retval = EXIT_FAILURE;
		goto exit_1;
	}
exit_1:
	commandline_free(context);
	return retval;
}
