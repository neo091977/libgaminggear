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

#include "gaminggear/evdev.h"
#include "config.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/uinput.h>

int gaminggear_open_misc_evdev(gchar const * identifier, guint vendor, guint product, GError **error) {
	int fd;
	struct uinput_user_dev uidev;

	fd = open(UINPUT_DIR "/uinput", O_WRONLY | O_NONBLOCK);
	if (fd < 0) {
		g_set_error(error, G_FILE_ERROR, g_file_error_from_errno(errno), "Error opening misc evdev: %s", g_strerror(errno));
		goto error;
	}

	if (ioctl(fd, UI_SET_EVBIT, EV_KEY) < 0)
		g_warning("gaminggear_open_misc_evdev: %s", g_strerror(errno));
	if (ioctl(fd, UI_SET_KEYBIT, KEY_MUTE) < 0)
		g_warning("gaminggear_open_misc_evdev: %s", g_strerror(errno));
	if (ioctl(fd, UI_SET_KEYBIT, KEY_VOLUMEDOWN) < 0)
		g_warning("gaminggear_open_misc_evdev: %s", g_strerror(errno));
	if (ioctl(fd, UI_SET_KEYBIT, KEY_VOLUMEUP) < 0)
		g_warning("gaminggear_open_misc_evdev: %s", g_strerror(errno));
	if (ioctl(fd, UI_SET_KEYBIT, KEY_PREVIOUSSONG) < 0)
		g_warning("gaminggear_open_misc_evdev: %s", g_strerror(errno));
	if (ioctl(fd, UI_SET_KEYBIT, KEY_NEXTSONG) < 0)
		g_warning("gaminggear_open_misc_evdev: %s", g_strerror(errno));
	if (ioctl(fd, UI_SET_KEYBIT, KEY_PLAYPAUSE) < 0)
		g_warning("gaminggear_open_misc_evdev: %s", g_strerror(errno));
	if (ioctl(fd, UI_SET_KEYBIT, KEY_STOPCD) < 0)
		g_warning("gaminggear_open_misc_evdev: %s", g_strerror(errno));
	if (ioctl(fd, UI_SET_KEYBIT, BTN_LEFT) < 0)
		g_warning("gaminggear_open_misc_evdev: %s", g_strerror(errno));
	if (ioctl(fd, UI_SET_KEYBIT, BTN_RIGHT) < 0)
		g_warning("gaminggear_open_misc_evdev: %s", g_strerror(errno));
	if (ioctl(fd, UI_SET_KEYBIT, BTN_MIDDLE) < 0)
		g_warning("gaminggear_open_misc_evdev: %s", g_strerror(errno));

	memset(&uidev, 0, sizeof(uidev));

	snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "%s", identifier);
	uidev.id.bustype = BUS_USB;
	uidev.id.vendor = vendor;
	uidev.id.product = product;
	uidev.id.version = 1;

	if (write(fd, &uidev, sizeof(uidev)) < 0) {
		g_set_error(error, G_FILE_ERROR, g_file_error_from_errno(errno), "Error writing to misc evdev: %s", g_strerror(errno));
		goto close;
	}

	if (ioctl(fd, UI_DEV_CREATE) < 0) {
		g_set_error(error, G_FILE_ERROR, g_file_error_from_errno(errno), "Error creating uinput: %s", g_strerror(errno));
		goto close;
	}

	return fd;
close:
	close(fd);
error:
	return -1;
}

void gaminggear_close_misc_evdev(int fd, GError **error) {
	if (ioctl(fd, UI_DEV_DESTROY) < 0)
		g_set_error(error, G_FILE_ERROR, g_file_error_from_errno(errno), "Error closing misc evdev: %s", g_strerror(errno));
	close(fd);
}

void gaminggear_input_event_write_with_sync(int fd, int code, int value) {
	struct input_event event;
	int written;

	if (fd == -1)
		return;

	event.type = EV_KEY;
	event.code = code;
	event.value = value;

	written = write(fd, (const void*) &event, sizeof(event));
	if (written != sizeof(event))
		g_warning("error with event %d", written);

	event.type = EV_SYN;
	event.code = SYN_REPORT;
	event.value = 0;

	written = write(fd, (const void*) &event, sizeof(event));
	if (written != sizeof(event))
		g_warning("error with sync event %d", written);
}

void gaminggear_input_event_write_single(int fd, int code) {
	gaminggear_input_event_write_with_sync(fd, code, 1);
	gaminggear_input_event_write_with_sync(fd, code, 0);
}
