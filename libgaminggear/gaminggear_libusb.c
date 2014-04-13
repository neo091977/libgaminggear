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

#include "gaminggear/libusb.h"
#include <libusb.h>

static gboolean detach_kernel_driver(libusb_device_handle *handle, int interface) {
	int err;

	err = libusb_kernel_driver_active(handle, interface);
	switch (err) {
	case 0:
	case LIBUSB_ERROR_NOT_SUPPORTED:
		break;
	case 1:
		err = libusb_detach_kernel_driver(handle, interface);
		if (err) {
			g_critical("error detaching kernel driver: %i\n", err);
			return FALSE;
		}
		break;
	default:
		g_critical("error trying to detach kernel driver %i\n", err);
		return FALSE;
	}

	return TRUE;
}

static gboolean attach_kernel_driver(libusb_device_handle *handle, int interface) {
	int err;

	err = libusb_attach_kernel_driver(handle, interface);
	switch (err) {
	case 0:
	case LIBUSB_ERROR_NOT_SUPPORTED:
		break;
	default:
		g_critical("error attaching kernel driver: %i\n", err);
		return FALSE;
	}

	return TRUE;
}

gboolean gaminggear_libusb_claim_interface(libusb_device_handle *handle, int interface) {
	gboolean retval;
	int err;

	retval = detach_kernel_driver(handle, interface);
	if (!retval)
		return FALSE;


	err = libusb_claim_interface(handle, interface);
	if (err) {
		g_critical("error claiming interface: %i\n", err);
		attach_kernel_driver(handle, interface);
		return FALSE;
	}

	return TRUE;
}

gboolean gaminggear_libusb_release_interface(libusb_device_handle *handle, int interface) {
	gboolean retval;
	int err;

	if (!handle)
		return FALSE;

	err = libusb_release_interface(handle, interface);
	if (err) {
		g_critical("error releasing interface: %i\n", err);
		return FALSE;
	}

	retval = attach_kernel_driver(handle, interface);
	if (!retval)
		return FALSE;

	return TRUE;
}
