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

#include "config.h"
#include "gaminggear/gfx.h"
#include "gaminggear/gaminggear_fx_plugin.h"
#include <gmodule.h>
#include <glib.h>

typedef struct _PluginListData PluginListData;

struct _PluginListData {
	GModule *module;
	GaminggearFxPlugin *plugin;
};

GSList *plugins = NULL;
gboolean initialized = FALSE;

static PluginListData *plugin_list_data_new(gchar const * const filename) {
	GaminggearFxPlugin *(*gaminggear_fx_plugin_new)(void);
	GaminggearFxPlugin *plugin;
	PluginListData *list_data;
	GModule *module;

	module = g_module_open(filename, G_MODULE_BIND_LAZY);
	if (!module)
		goto exit_1;

	if (!g_module_symbol(module, "gaminggear_fx_plugin_new", (gpointer *)&gaminggear_fx_plugin_new))
		goto exit_2;

	plugin = gaminggear_fx_plugin_new();
	if (!plugin)
		goto exit_2;

	list_data = g_malloc0(sizeof(PluginListData));
	list_data->module = module;
	list_data->plugin = plugin;
	return list_data;

exit_2:
	g_module_close(module);
exit_1:
	return NULL;
}

GfxResult gfx_initialize(void) {
	GError *local_error = NULL;
	GDir *dir;
	GPatternSpec *pattern;
	gchar const *name;
	gchar *abs_name;
	PluginListData *list_data;

	if (!g_module_supported())
		return GFX_FAILURE;

	dir = g_dir_open(GAMINGGEAR_FX_PLUGIN_DIR, 0, &local_error);
	if (!dir) {
		g_warning("Error opening directory '%s': %s", GAMINGGEAR_FX_PLUGIN_DIR, local_error->message);
		g_clear_error(&local_error);
		return GFX_FAILURE;
	}

	pattern = g_pattern_spec_new("lib*gfxplugin.so");

	while ((name = g_dir_read_name(dir))) {
		if (g_pattern_match_string(pattern, name)) {
			g_debug("Trying plugin %s", name);
			abs_name = g_build_filename(GAMINGGEAR_FX_PLUGIN_DIR, name, NULL);
			list_data = plugin_list_data_new(abs_name);
			g_free(abs_name);
			if (list_data) {
				g_debug("Using plugin %s", name);
				plugins = g_slist_prepend(plugins, list_data);
			}
		}
	}

	g_pattern_spec_free(pattern);
	g_dir_close(dir);

	initialized = TRUE;

	if (!plugins) return GFX_ERROR_NODEVS;

	return GFX_SUCCESS;
}

static void plugin_list_data_free(gpointer data) {
	PluginListData *list_data = (PluginListData *)data;
	list_data->plugin->finalize(list_data->plugin);
	g_module_close(list_data->module);
	g_free(list_data);
}

GfxResult gfx_release(void) {
	if (!initialized) return GFX_ERROR_NOINIT;

#if (GLIB_CHECK_VERSION(2, 28, 0))
	g_slist_free_full(plugins, plugin_list_data_free);
#else
	g_slist_foreach(plugins, (GFunc)plugin_list_data_free, NULL);
	g_slist_free(plugins);
#endif

	plugins = NULL;
	initialized = FALSE;

	return GFX_SUCCESS;
}

GfxResult gfx_get_num_devices(unsigned int * const num_devices) {
	if (!initialized) return GFX_ERROR_NOINIT;
	if (!plugins) return GFX_ERROR_NODEVS;
	*num_devices = g_slist_length(plugins);
	return GFX_SUCCESS;
}

GfxResult gfx_get_device_description(unsigned int const device_index, char * const device_description,
		unsigned int const device_description_size, GfxDevtype * const device_type) {
	GaminggearFxPlugin *plugin;

	if (!initialized) return GFX_ERROR_NOINIT;

	plugin = ((PluginListData *)g_slist_nth_data(plugins, device_index))->plugin;

	if (!plugin) return GFX_ERROR_NODEVS;

	return plugin->get_device_description(plugin, device_description, device_description_size, device_type);
}

GfxResult gfx_get_num_lights(unsigned int const device_index, unsigned int *const num_lights) {
	GaminggearFxPlugin *plugin;

	if (!initialized) return GFX_ERROR_NOINIT;

	plugin = ((PluginListData *)g_slist_nth_data(plugins, device_index))->plugin;

	if (!plugin) return GFX_ERROR_NODEVS;

	return plugin->get_num_lights(plugin, num_lights);
}

GfxResult gfx_get_light_description(unsigned int const device_index, unsigned int const light_index,
		char * const light_description, unsigned int const light_description_size) {
	GaminggearFxPlugin *plugin;

	if (!initialized) return GFX_ERROR_NOINIT;

	plugin = ((PluginListData *)g_slist_nth_data(plugins, device_index))->plugin;

	if (!plugin) return GFX_ERROR_NODEVS;

	return plugin->get_light_description(plugin, light_index, light_description, light_description_size);
}

GfxResult gfx_get_light_position(unsigned int const device_index, unsigned int const light_index,
		GfxPosition * const light_position) {
	GaminggearFxPlugin *plugin;

	if (!initialized) return GFX_ERROR_NOINIT;

	plugin = ((PluginListData *)g_slist_nth_data(plugins, device_index))->plugin;

	if (!plugin) return GFX_ERROR_NODEVS;

	return plugin->get_light_position(plugin, light_index, light_position);
}

GfxResult gfx_get_light_color(unsigned int const device_index, unsigned int const light_index, uint32_t * const color) {
	GaminggearFxPlugin *plugin;

	if (!initialized) return GFX_ERROR_NOINIT;

	plugin = ((PluginListData *)g_slist_nth_data(plugins, device_index))->plugin;

	if (!plugin) return GFX_ERROR_NODEVS;

	return plugin->get_light_color(plugin, light_index, color);
}

GfxResult gfx_set_light_color(unsigned int const device_index, unsigned int const light_index, uint32_t const color) {
	GaminggearFxPlugin *plugin;

	if (!initialized) return GFX_ERROR_NOINIT;

	plugin = ((PluginListData *)g_slist_nth_data(plugins, device_index))->plugin;

	if (!plugin) return GFX_ERROR_NODEVS;

	return plugin->set_light_color(plugin, light_index, color);
}

GfxResult gfx_light(unsigned int const location_mask, uint32_t const color) {
	unsigned int num_devices;
	unsigned int num_lights;
	unsigned int device_index;
	unsigned int light_index;
	GfxResult gfx_result;

	if (!initialized) return GFX_ERROR_NOINIT;
	if (!plugins) return GFX_ERROR_NODEVS;

	gfx_result = gfx_get_num_devices(&num_devices);
	if (gfx_result != GFX_SUCCESS)
		return GFX_FAILURE;

	for (device_index = 0; device_index < num_devices; ++device_index) {
		gfx_result = gfx_get_num_lights(device_index, &num_lights);
		if (gfx_result != GFX_SUCCESS)
			return GFX_FAILURE;

		for (light_index = 0; light_index < num_lights; ++light_index) {
			if (TRUE) // FIXME conditional
				gfx_set_light_color(device_index, light_index, color);
		}
	}
	return GFX_SUCCESS;
}

GfxResult gfx_reset(void) {
	return gfx_light(GFX_LOCATION_ALL, 0);
}

GfxResult gfx_update(void) {
	GaminggearFxPlugin *plugin;
	GSList *iterator;
	GfxResult result;

	if (!initialized) return GFX_ERROR_NOINIT;
	if (!plugins) return GFX_ERROR_NODEVS;

	for (iterator = plugins; iterator; iterator = g_slist_next(iterator)) {
		plugin = ((PluginListData *)iterator->data)->plugin;
		result = plugin->update(plugin);
		if (result != GFX_SUCCESS)
			return result;
	}
	return GFX_SUCCESS;
}
