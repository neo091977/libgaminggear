#ifndef __GAMINGGEAR_THREADS_H__
#define __GAMINGGEAR_THREADS_H__

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

/*! \file gaminggear/threads.h
 *  \brief Wrappers around glib thread synchronization primitives.
 *
 *  Glib changed it's api with version 2.32.0. These wrappers provide a
 *  consistent api for all glib-2 versions.
 *  
 *  For details please consult the appropriate glib documentation.
 *  [< 2.32.0](https://developer.gnome.org/glib/2.30/glib-Threads.html)
 *  [>= 2.32.0](https://developer.gnome.org/glib/2.32/glib-Threads.html)
 */

#include <glib.h>

G_BEGIN_DECLS

/*! \typedef GaminggearMutex
 *  \brief A mutex.
 */

/*! \typedef GaminggearCond
 *  \brief A condition.
 */

/*! \typedef GaminggearRecMutex
 *  \brief A recursive mutex.
 */

#if (GLIB_CHECK_VERSION(2, 32, 0))
	typedef GMutex GaminggearMutex;
	typedef GCond GaminggearCond;
	typedef GRecMutex GaminggearRecMutex;
#else
	typedef GMutex *GaminggearMutex;
	typedef GCond *GaminggearCond;
	typedef GStaticRecMutex GaminggearRecMutex;
#endif

/*! \brief Create new thread.
 *  \since 1.0
 */
static inline GThread *gaminggear_thread_try_new(G_GNUC_UNUSED gchar const *name, GThreadFunc func, gpointer data, GError **error) {
#if (GLIB_CHECK_VERSION(2, 32, 0))
	return g_thread_try_new(name, func, data, error);
#else
	return g_thread_create(func, data, TRUE, error);
#endif
}

/*! \brief Initializes a GaminggearMutex.
 *  \since 1.0
 */
static inline void gaminggear_mutex_init(GaminggearMutex *mutex) {
#if (GLIB_CHECK_VERSION(2, 32, 0))
	g_mutex_init(mutex);
#else
	*mutex = g_mutex_new();
#endif
}

/*! \brief Frees resources of a GaminggearMutex.
 *  \since 1.0
 */
static inline void gaminggear_mutex_clear(GaminggearMutex *mutex) {
#if (GLIB_CHECK_VERSION(2, 32, 0))
	g_mutex_clear(mutex);
#else
	g_mutex_free(*mutex);
#endif
}

/*! \brief Locks a GaminggearMutex.
 *  \since 1.0
 */
static inline void gaminggear_mutex_lock(GaminggearMutex *mutex) {
#if (GLIB_CHECK_VERSION(2, 32, 0))
	g_mutex_lock(mutex);
#else
	g_mutex_lock(*mutex);
#endif
}

/*! \brief Unlocks a GaminggearMutex.
 *  \since 1.0
 */
static inline void gaminggear_mutex_unlock(GaminggearMutex *mutex) {
#if (GLIB_CHECK_VERSION(2, 32, 0))
	g_mutex_unlock(mutex);
#else
	g_mutex_unlock(*mutex);
#endif
}

/*! \brief Initializes a GaminggearCond.
 *  \since 1.0
 */
static inline void gaminggear_cond_init(GaminggearCond *cond) {
#if (GLIB_CHECK_VERSION(2, 32, 0))
	g_cond_init(cond);
#else
	*cond = g_cond_new();
#endif
}

/*! \brief Frees resources of a GaminggearCond.
 *  \since 1.0
 */
static inline void gaminggear_cond_clear(GaminggearCond *cond) {
#if (GLIB_CHECK_VERSION(2, 32, 0))
	g_cond_clear(cond);
#else
	g_cond_free(*cond);
#endif
}

/*! \brief Waits for a signal.
 *  \since 1.0
 */
static inline void gaminggear_cond_wait(GaminggearCond *cond, GaminggearMutex *mutex) {
#if (GLIB_CHECK_VERSION(2, 32, 0))
	g_cond_wait(cond, mutex);
#else
	g_cond_wait(*cond, *mutex);
#endif
}

/*! \brief Wake up a waiting thread.
 *  \since 1.0
 */
static inline void gaminggear_cond_signal(GaminggearCond *cond) {
#if (GLIB_CHECK_VERSION(2, 32, 0))
	g_cond_signal(cond);
#else
	g_cond_signal(*cond);
#endif
}

/*! \brief Initializes a GaminggearRecMutex.
 *  \since 1.0
 */
static inline void gaminggear_rec_mutex_init(GaminggearRecMutex *mutex) {
#if (GLIB_CHECK_VERSION(2, 32, 0))
	g_rec_mutex_init(mutex);
#else
	g_static_rec_mutex_init(mutex);
#endif
}

/*! \brief Frees resources of a GaminggearRecMutex.
 *  \since 1.0
 */
static inline void gaminggear_rec_mutex_clear(GaminggearRecMutex *mutex) {
#if (GLIB_CHECK_VERSION(2, 32, 0))
	g_rec_mutex_clear(mutex);
#else
	g_static_rec_mutex_free(mutex);
#endif
}

/*! \brief Locks a GaminggearRecMutex.
 *  \since 1.0
 */
static inline void gaminggear_rec_mutex_lock(GaminggearRecMutex *mutex) {
#if (GLIB_CHECK_VERSION(2, 32, 0))
	g_rec_mutex_lock(mutex);
#else
	g_static_rec_mutex_lock(mutex);
#endif
}

/*! \brief Unlocks a GaminggearRecMutex.
 *  \since 1.0
 */
static inline void gaminggear_rec_mutex_unlock(GaminggearRecMutex *mutex) {
#if (GLIB_CHECK_VERSION(2, 32, 0))
	g_rec_mutex_unlock(mutex);
#else
	g_static_rec_mutex_unlock(mutex);
#endif
}

G_END_DECLS

#endif
