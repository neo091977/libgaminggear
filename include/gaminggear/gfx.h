#ifndef __GAMINGGEAR_FX_H__
#define __GAMINGGEAR_FX_H__

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

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct {
	unsigned char brightness;
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} GfxColor;

typedef struct {
	unsigned char x;
	unsigned char y;
	unsigned char z;
} GfxPosition;

typedef enum {
	GFX_SUCCESS,
	GFX_FAILURE,
	GFX_ERROR_NODEVS,
	GFX_ERROR_NOLIGHTS,
	GFX_ERROR_NOINIT,
} GfxResult;

typedef enum {
	GFX_DEVTYPE_MOUSE,
	GFX_DEVTYPE_KEYBOARD,
} GfxDevtype;

typedef enum {
	GFX_LOCATION_FRONT_LOWER_LEFT =     0b000000000000000000000000001,
	GFX_LOCATION_FRONT_LOWER_MIDDLE =   0b000000000000000000000000010,
	GFX_LOCATION_FRONT_LOWER_RIGHT =    0b000000000000000000000000100,
	GFX_LOCATION_FRONT_MIDDLE_LEFT =    0b000000000000000000000001000,
	GFX_LOCATION_FRONT_MIDDLE_MIDDLE =  0b000000000000000000000010000,
	GFX_LOCATION_FRONT_MIDDLE_RIGHT =   0b000000000000000000000100000,
	GFX_LOCATION_FRONT_UPPER_LEFT =     0b000000000000000000001000000,
	GFX_LOCATION_FRONT_UPPER_MIDDLE =   0b000000000000000000010000000,
	GFX_LOCATION_FRONT_UPPER_RIGHT =    0b000000000000000000100000000,
	GFX_LOCATION_MIDDLE_LOWER_LEFT =    0b000000000000000001000000000,
	GFX_LOCATION_MIDDLE_LOWER_MIDDLE =  0b000000000000000010000000000,
	GFX_LOCATION_MIDDLE_LOWER_RIGHT =   0b000000000000000100000000000,
	GFX_LOCATION_MIDDLE_MIDDLE_LEFT =   0b000000000000001000000000000,
	GFX_LOCATION_MIDDLE_MIDDLE_MIDDLE = 0b000000000000010000000000000,
	GFX_LOCATION_MIDDLE_MIDDLE_RIGHT =  0b000000000000100000000000000,
	GFX_LOCATION_MIDDLE_UPPER_LEFT =    0b000000000001000000000000000,
	GFX_LOCATION_MIDDLE_UPPER_MIDDLE =  0b000000000010000000000000000,
	GFX_LOCATION_MIDDLE_UPPER_RIGHT =   0b000000000100000000000000000,
	GFX_LOCATION_REAR_LOWER_LEFT =      0b000000001000000000000000000,
	GFX_LOCATION_REAR_LOWER_MIDDLE =    0b000000010000000000000000000,
	GFX_LOCATION_REAR_LOWER_RIGHT =     0b000000100000000000000000000,
	GFX_LOCATION_REAR_MIDDLE_LEFT =     0b000001000000000000000000000,
	GFX_LOCATION_REAR_MIDDLE_MIDDLE =   0b000010000000000000000000000,
	GFX_LOCATION_REAR_MIDDLE_RIGHT =    0b000100000000000000000000000,
	GFX_LOCATION_REAR_UPPER_LEFT =      0b001000000000000000000000000,
	GFX_LOCATION_REAR_UPPER_MIDDLE =    0b010000000000000000000000000,
	GFX_LOCATION_REAR_UPPER_RIGHT =     0b100000000000000000000000000,
	GFX_LOCATION_ALL_LEFT =             0b001001001001001001001001001,
	GFX_LOCATION_ALL_RIGHT =            0b100100100100100100100100100,
	GFX_LOCATION_ALL_LOWER =            0b000000111000000111000000111,
	GFX_LOCATION_ALL_UPPER =            0b111000000111000000111000000,
	GFX_LOCATION_ALL_FRONT =            0b000000000000000000111111111,
	GFX_LOCATION_ALL_REAR =             0b111111111000000000000000000,
	GFX_LOCATION_ALL =                  0b111111111111111111111111111,
} GfxLocation;

GfxResult gfx_initialize(void);
GfxResult gfx_release(void);

GfxResult gfx_get_num_devices(unsigned int * const num_devices);

GfxResult gfx_get_device_description(unsigned int const device_index, char * const device_description,
		unsigned int const device_description_size, GfxDevtype * const device_type);
GfxResult gfx_get_num_lights(unsigned int const device_index, unsigned int *const num_lights);
GfxResult gfx_get_light_description(unsigned int const device_index, unsigned int const light_index,
		char * const light_description, unsigned int const light_description_size);
GfxResult gfx_get_light_position(unsigned int const device_index, unsigned int const light_index,
		GfxPosition * const light_position);
GfxResult gfx_get_light_color(unsigned int const device_index, unsigned int const light_index, GfxColor * const color);
GfxResult gfx_set_light_color(unsigned int const device_index, unsigned int const light_index, GfxColor const * const color);

GfxResult gfx_reset(void);
GfxResult gfx_update(void);
GfxResult gfx_light(unsigned int const location_mask, GfxColor const * const color);

#ifdef  __cplusplus
}
#endif

#endif
