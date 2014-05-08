#ifndef __GAMINGGEAR_TIMEOUT_BAR_H__
#define __GAMINGGEAR_TIMEOUT_BAR_H__

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

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GAMINGGEAR_TIMEOUT_BAR_TYPE (gaminggear_timeout_bar_get_type())
#define GAMINGGEAR_TIMEOUT_BAR(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), GAMINGGEAR_TIMEOUT_BAR_TYPE, GaminggearTimeoutBar))
#define IS_GAMINGGEAR_TIMEOUT_BAR(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), GAMINGGEAR_TIMEOUT_BAR_TYPE))

typedef struct _GaminggearTimeoutBar GaminggearTimeoutBar;

GType gaminggear_timeout_bar_get_type(void);
GtkWidget *gaminggear_timeout_bar_new(void);
void gaminggear_timeout_bar_start(GaminggearTimeoutBar *timeout_bar, guint interval, guint timeout);
void gaminggear_timeout_bar_stop(GaminggearTimeoutBar *timeout_bar);

G_END_DECLS

#endif
