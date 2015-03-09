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

static unsigned int const description_size = 255;

static void print_device_type(GfxDevtype device_type) {
	switch(device_type) {
	case GFX_DEVTYPE_MOUSE:
		g_print("  DevType: MOUSE\n");
		break;
	case GFX_DEVTYPE_KEYBOARD:
		g_print("  DevType: KEYBOARD\n");
		break;
	default:
		g_print("  DevType: INVALID (%u)\n", device_type);
		break;
	}
}

int main(int argc, char **argv) {
	GfxResult gfx_result;
	int retval = EXIT_FAILURE;
	char description[description_size];
	unsigned int num_devices;
	unsigned int num_lights;
	unsigned int device_index;
	unsigned int light_index;
	GfxDevtype device_type;
	GfxPosition light_position;
	uint32_t light_color;

	gfx_result = gfx_initialize();
	if (gfx_result != GFX_SUCCESS) {
		g_warning("There was an error initializing the fx system");
		goto exit_1;
	}

	gfx_result = gfx_get_num_devices(&num_devices);
	if (gfx_result != GFX_SUCCESS) {
		g_warning("There was an error getting devices");
		goto exit_2;
	}

	for (device_index = 0; device_index < num_devices; ++device_index) {
		g_print("Device[%u]\n", device_index);

		gfx_result = gfx_get_device_description(device_index, description, description_size, &device_type);
		if (gfx_result != GFX_SUCCESS) {
			g_warning("There was an error getting device description");
			goto exit_2;
		}

		g_print("  Description: %s\n", description);
		print_device_type(device_type);

		gfx_result = gfx_get_num_lights(device_index, &num_lights);
		if (gfx_result != GFX_SUCCESS) {
			g_warning("There was an error getting lights");
			goto exit_2;
		}

		for (light_index = 0; light_index < num_lights; ++light_index) {
			g_print("  Light[%u]\n", light_index);

			gfx_result = gfx_get_light_description(device_index, light_index, description, description_size);
			if (gfx_result != GFX_SUCCESS) {
				g_warning("There was an error getting light description");
				goto exit_2;
			}
			g_print("    Description: %s\n", description);

			gfx_result = gfx_get_light_position(device_index, light_index, &light_position);
			if (gfx_result != GFX_SUCCESS) {
				g_warning("There was an error getting light position");
				goto exit_2;
			}
			g_print("    Position: %u, %u, %u\n", light_position.x, light_position.y, light_position.z);

			gfx_result = gfx_get_light_color(device_index, light_index, &light_color);
			if (gfx_result != GFX_SUCCESS) {
				g_warning("There was an error getting light color");
				goto exit_2;
			}
			g_print("    Color: 0x%02x, 0x%02x, 0x%02x, 0x%02x\n",
					gfx_color_get_brightness_raw(light_color),
					gfx_color_get_red_raw(light_color),
					gfx_color_get_green_raw(light_color),
					gfx_color_get_blue_raw(light_color));
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
	return retval;
}
