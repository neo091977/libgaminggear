#ifndef __GAMINGGEAR_XY_SCALES_H__
#define __GAMINGGEAR_XY_SCALES_H__

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

/*! \file gaminggear/gaminggear_xy_scales.h
 *  \brief .
 */

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GAMINGGEAR_XY_SCALES_TYPE (gaminggear_xy_scales_get_type())
#define GAMINGGEAR_XY_SCALES_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), GAMINGGEAR_XY_SCALES_TYPE, GaminggearXyScalesClass))
#define IS_GAMINGGEAR_XY_SCALES_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), GAMINGGEAR_XY_SCALES_TYPE))
#define GAMINGGEAR_XY_SCALES(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), GAMINGGEAR_XY_SCALES_TYPE, GaminggearXyScales))
#define IS_GAMINGGEAR_XY_SCALES(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), GAMINGGEAR_XY_SCALES_TYPE))

typedef struct _GaminggearXyScalesClass GaminggearXyScalesClass;
typedef struct _GaminggearXyScales GaminggearXyScales;
typedef struct _GaminggearXyScalesPrivate GaminggearXyScalesPrivate;

struct _GaminggearXyScalesClass {
	GtkTableClass parent_class;
};

struct _GaminggearXyScales {
	GtkTable parent;
	GaminggearXyScalesPrivate *priv;
};

GType gaminggear_xy_scales_get_type(void);

/*! \brief Creates new xy scale.
 *  \param min .
 *  \param max .
 *  \param step .
 *  \retval widget The xy scale.
 *  \since 1.0
 */
GtkWidget *gaminggear_xy_scales_new(gdouble min, gdouble max, gdouble step);

/*! \brief .
 *  \param scales A xy scale.
 *  \retval value .
 *  \since 1.0
 */
gdouble gaminggear_xy_scales_get_x_value(GaminggearXyScales *scales);

/*! \brief .
 *  \param scales A xy scale.
 *  \param value .
 *  \since 1.0
 */
void gaminggear_xy_scales_set_x_value(GaminggearXyScales *scales, gdouble value);

/*! \brief .
 *  \param scales A xy scale.
 *  \retval value .
 *  \since 1.0
 */
gdouble gaminggear_xy_scales_get_y_value(GaminggearXyScales *scales);

/*! \brief .
 *  \param scales A xy scale.
 *  \param value .
 *  \since 1.0
 */
void gaminggear_xy_scales_set_y_value(GaminggearXyScales *scales, gdouble value);

/*! \brief .
 *  \param scales A xy scale.
 *  \retval value .
 *  \since 1.0
 */
gboolean gaminggear_xy_scales_get_linked(GaminggearXyScales *scales);

/*! \brief .
 *  \param scales A xy scale.
 *  \param value .
 *  \since 1.0
 */
void gaminggear_xy_scales_set_linked(GaminggearXyScales *scales, gboolean value);

/*! \brief .
 *  \param scales A xy scale.
 *  \param digits .
 *  \since 1.0
 */
void gaminggear_xy_scales_set_digits(GaminggearXyScales *scales, guint digits);

G_END_DECLS

#endif
