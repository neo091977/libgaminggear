#ifndef __GAMINGGEAR_EVDEV_H__
#define __GAMINGGEAR_EVDEV_H__

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

/*! \file gaminggear/evdev.h
 *  \brief Event device access
 */

#include <glib.h>

G_BEGIN_DECLS

/*! \brief Opens uinput device supporting mouse buttons and multimedia keys.
 *
 *  It takes some time until device is created.
 *
 *  \retval descriptor If successful returns file descriptor that has to be closed
 *          with \c gaminggear_close_misc_evdev(), -1 on error.
 *  \since 1.0
 */
int gaminggear_open_misc_evdev(gchar const * identifier, guint vendor, guint product, GError **error);

/*! \brief Closes uinput device.
 *  \since 1.0
 */
void gaminggear_close_misc_evdev(int fd, GError **error);

/*! \brief Write an event to evdev.
 *  \since 1.0
 */
void gaminggear_input_event_write_with_sync(int fd, int code, int value);

/*! \brief Write press and release event to evdev.
 *  \since 1.0
 */
void gaminggear_input_event_write_single(int fd, int code);

G_END_DECLS

#endif
