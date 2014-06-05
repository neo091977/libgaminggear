/*
 * This file is part of gaminggear-tools.
 *
 * gaminggear-tools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * gaminggear-tools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gaminggear-tools. If not, see <http://www.gnu.org/licenses/>.
 */

#include "gaminggear/gaminggear_device.h"
#include "gaminggear/threads.h"
#include "gaminggear/evdev.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define GAMINGGEAR_DEVICE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), GAMINGGEAR_DEVICE_TYPE, GaminggearDevicePrivate))

struct _GaminggearDevicePrivate {
	gchar *identifier; // unique per device, not interface
	guint product_id;
	GaminggearRecMutex lock;
};

enum {
	PROP_0,
	PROP_IDENTIFIER,
	PROP_PRODUCT_ID,
};

G_DEFINE_TYPE(GaminggearDevice, gaminggear_device, G_TYPE_OBJECT);

static gchar *create_fd_string(gchar const *key) {
	return g_strconcat("fd_", key, NULL);
}

static void gaminggear_device_set_fd(GaminggearDevice *gaminggear_device, gchar const *key, gint fd) {
	gchar *fd_key;
	fd_key = create_fd_string(key);
	g_object_set_data(G_OBJECT(gaminggear_device), fd_key, GINT_TO_POINTER(fd));
	g_free(fd_key);
}

static int gaminggear_device_get_fd(GaminggearDevice *gaminggear_device, gchar const *key) {
	gchar *fd_key;
	int fd;

	fd_key = create_fd_string(key);
	fd = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(gaminggear_device), fd_key));
	g_free(fd_key);

	return fd;
}

int gaminggear_device_open(GaminggearDevice *gaminggear_device, gchar const *key, gint flags, GError **error) {
	gchar const *path;
	int fd;

	/* fd is only valid if path is set */
	path = gaminggear_device_get_path(gaminggear_device, key);
	if (!path) {
		g_set_error(error, G_FILE_ERROR, G_FILE_ERROR_INVAL, "Error opening file: no path");
		return -1;
	}

	fd = gaminggear_device_get_fd(gaminggear_device, key);
	if (fd >= 0)
		return fd;

	fd = open(path, flags, 0);
	if (fd < 0)
		g_set_error(error, G_FILE_ERROR, g_file_error_from_errno(errno), "Error opening %s: %s", path, g_strerror(errno));

	gaminggear_device_set_fd(gaminggear_device, key, fd);
	return fd;
}

gboolean gaminggear_device_close(GaminggearDevice *gaminggear_device, gchar const *key, GError **error) {
	gchar const *path;
	int fd;

	/* fd is only valid if path is set */
	path = gaminggear_device_get_path(gaminggear_device, key);
	if (!path) {
		g_set_error(error, G_FILE_ERROR, G_FILE_ERROR_INVAL, "Error closing file: no path");
		return FALSE;
	}

	fd = gaminggear_device_get_fd(gaminggear_device, key);
	if (fd >= 0) {
		if (close(fd) < 0) {
			g_set_error(error, G_FILE_ERROR, g_file_error_from_errno(errno), "Error closing %s: %s", path, g_strerror(errno));
			return FALSE;
		}
		gaminggear_device_set_fd(gaminggear_device, key, -1);
	}
	return TRUE;
}

void gaminggear_device_set_path(GaminggearDevice *gaminggear_device, gchar const *key, gchar const *path) {
	gchar *old_path;

	old_path = (gchar *)g_object_get_data(G_OBJECT(gaminggear_device), key);
	if (old_path) {
		gaminggear_device_close(gaminggear_device, key, NULL);
		g_free(old_path);
	}

	g_object_set_data(G_OBJECT(gaminggear_device), key, g_strdup(path));
	gaminggear_device_set_fd(gaminggear_device, key, -1);
}

gchar const *gaminggear_device_get_path(GaminggearDevice *gaminggear_device, gchar const *key) {
	return (gchar const *)g_object_get_data(G_OBJECT(gaminggear_device), key);
}

void gaminggear_device_lock(GaminggearDevice *gaminggear_dev) {
	gaminggear_rec_mutex_lock(&gaminggear_dev->priv->lock);
}

void gaminggear_device_unlock(GaminggearDevice *gaminggear_dev) {
	gaminggear_rec_mutex_unlock(&gaminggear_dev->priv->lock);
}

gchar const *gaminggear_device_get_identifier(GaminggearDevice const *gaminggear_dev) {
	return gaminggear_dev->priv->identifier;
}

guint gaminggear_device_get_product_id(GaminggearDevice const *gaminggear_dev) {
	return gaminggear_dev->priv->product_id;
}

GaminggearDevice *gaminggear_device_new(gchar const *identifier, guint product_id) {
	return GAMINGGEAR_DEVICE(g_object_new(GAMINGGEAR_DEVICE_TYPE,
			"identifier", identifier,
			"product-id", product_id,
			NULL));
}

static void gaminggear_device_init(GaminggearDevice *gaminggear_dev) {
	GaminggearDevicePrivate *priv = GAMINGGEAR_DEVICE_GET_PRIVATE(gaminggear_dev);
	gaminggear_dev->priv = priv;

	gaminggear_rec_mutex_init(&priv->lock);
}

static void set_property(GObject *object, guint prop_id, GValue const *value, GParamSpec *pspec) {
	GaminggearDevicePrivate *priv = GAMINGGEAR_DEVICE(object)->priv;

	switch(prop_id) {
	case PROP_IDENTIFIER:
		priv->identifier = g_strdup(g_value_get_string(value));
		break;
	case PROP_PRODUCT_ID:
		priv->product_id = g_value_get_uint(value);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void gaminggear_device_finalize(GObject *object) {
	GaminggearDevicePrivate *priv = GAMINGGEAR_DEVICE(object)->priv;

	g_free(priv->identifier);
	gaminggear_rec_mutex_clear(&priv->lock);

	G_OBJECT_CLASS(gaminggear_device_parent_class)->finalize(object);
}

static void gaminggear_device_class_init(GaminggearDeviceClass *klass) {
	GObjectClass *gobject_class;

	gobject_class = (GObjectClass*)klass;

	gobject_class->set_property = set_property;
	gobject_class->finalize = gaminggear_device_finalize;

	g_type_class_add_private(klass, sizeof(GaminggearDevicePrivate));

	g_object_class_install_property(gobject_class, PROP_IDENTIFIER,
			g_param_spec_string("identifier",
					"identifier",
					"Identifier",
					"unknown",
					G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));

	g_object_class_install_property(gobject_class, PROP_PRODUCT_ID,
			g_param_spec_uint("product-id",
					"product-id",
					"Product ID",
					0, G_MAXUINT, 0,
					G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
}

gboolean gaminggear_device_equal(GaminggearDevice const *one, GaminggearDevice const *other) {
	return (strcmp(one->priv->identifier, other->priv->identifier)) ? FALSE : TRUE;
}
