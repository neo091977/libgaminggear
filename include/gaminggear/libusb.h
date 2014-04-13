#ifndef __GAMINGGEAR_LIBUSB_H__
#define __GAMINGGEAR_LIBUSB_H__

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

/*! \file gaminggear/libusb.h
 *  \brief Libsusb helpers.
 */

#include <glib.h>
#include <libusb.h>

G_BEGIN_DECLS

/*! \brief Claim interface
 *
 *  Tries to detach kernel driver before claiming interface.
 *
 *  \param handle libusb device handle.
 *  \param interface Interface.
 *  \retval boolean \c TRUE if interface was successfully claimed.
 *  \since 1.0
 */
gboolean gaminggear_libusb_claim_interface(libusb_device_handle *handle, int interface);

/*! \brief Release interface
 *
 *  Tries to reattach kernel driver after releasing interface.
 *
 *  \param handle libusb device handle.
 *  \param interface Interface.
 *  \retval boolean \c TRUE if interface was successfully released.
 *  \since 1.0
 */
gboolean gaminggear_libusb_release_interface(libusb_device_handle *handle, int interface);

G_END_DECLS

#endif
