#ifndef __GAMINGGEAR_HELPER_H__
#define __GAMINGGEAR_HELPER_H__

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

#include <glib.h>

G_BEGIN_DECLS

#define G_GAMINGGEAR_MSEC_PER_SEC 1000
#define G_GAMINGGEAR_USEC_PER_MSEC 1000
#define G_GAMINGGEAR_NSEC_PER_MSEC 1000000
#define G_GAMINGGEAR_NSEC_PER_SEC (G_GAMINGGEAR_MSEC_PER_SEC * G_GAMINGGEAR_NSEC_PER_MSEC)

/*!
 * \brief converts hex string from key_file to binary data
 * \retval If successful returns pointer to data, that has to be freed with g_free().
 *         On error returns +NULL+ with error set.
 */
gpointer g_gaminggear_key_file_get_binary(GKeyFile *key_file, gchar const *group_name, gchar const *key, gsize size, GError **error);

/*!
 * \brief converts binary data to hex string and puts it in key_file
 */
void g_gaminggear_key_file_set_binary(GKeyFile *key_file, gchar const *group_name, gchar const *key, gconstpointer data, gsize size);

gchar *g_gaminggear_unichar_to_utf8(gunichar c);

gboolean gaminggear_create_dir_if_needed(gchar const *dir, GError **error);

gchar *gaminggear_create_filename_with_extension(gchar const *filename, gchar const *extension);

G_END_DECLS

#endif