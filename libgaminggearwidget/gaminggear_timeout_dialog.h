#ifndef __GAMINGGEAR_TIMEOUT_DIALOG_H__
#define __GAMINGGEAR_TIMEOUT_DIALOG_H__

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

#define GAMINGGEAR_TIMEOUT_DIALOG_TYPE (gaminggear_timeout_dialog_get_type())
#define GAMINGGEAR_TIMEOUT_DIALOG(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), GAMINGGEAR_TIMEOUT_DIALOG_TYPE, GaminggearTimeoutDialog))
#define IS_GAMINGGEAR_TIMEOUT_DIALOG(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), GAMINGGEAR_TIMEOUT_DIALOG_TYPE))

typedef struct _GaminggearTimeoutDialog GaminggearTimeoutDialog;
typedef struct _GaminggearTimeoutDialogPrivate GaminggearTimeoutDialogPrivate;

struct _GaminggearTimeoutDialog {
	GtkDialog dialog;
	GaminggearTimeoutDialogPrivate *priv;
};

GType gaminggear_timeout_dialog_get_type(void);
GtkWidget *gaminggear_timeout_dialog_new(GtkWindow *parent, gchar const *title, gchar const *text);
gboolean gaminggear_timeout_dialog_run(GaminggearTimeoutDialog *timeout_dialog, guint timeout);
gboolean gaminggear_timeout_dialog(GtkWindow *parent, gchar const *title, gchar const *text, guint timeout);

G_END_DECLS

#endif
