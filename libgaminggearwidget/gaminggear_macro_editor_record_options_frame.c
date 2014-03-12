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

#include "gaminggear_macro_editor_record_options_frame.h"
#include "gaminggear_macro_editor_advanced_list_store.h"

#define GAMINGGEAR_MACRO_EDITOR_RECORD_OPTIONS_FRAME_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), GAMINGGEAR_MACRO_EDITOR_RECORD_OPTIONS_FRAME_TYPE, GaminggearMacroEditorRecordOptionsFrameClass))
#define IS_GAMINGGEAR_MACRO_EDITOR_RECORD_OPTIONS_FRAME_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), GAMINGGEAR_MACRO_EDITOR_RECORD_OPTIONS_FRAME_TYPE))
#define GAMINGGEAR_MACRO_EDITOR_RECORD_OPTIONS_FRAME_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), GAMINGGEAR_MACRO_EDITOR_RECORD_OPTIONS_FRAME_TYPE, GaminggearMacroEditorRecordOptionsFramePrivate))

typedef struct _GaminggearMacroEditorRecordOptionsFrameClass GaminggearMacroEditorRecordOptionsFrameClass;
typedef struct _AbsoluteKeystroke AbsoluteKeystroke;

struct _GaminggearMacroEditorRecordOptionsFrameClass {
	GtkFrameClass parent_class;
	void (*started)(GaminggearMacroEditorRecordOptionsFrame *record_options_frame);
	void (*paste)(GaminggearMacroEditorRecordOptionsFrame *record_options_frame);
};

struct _GaminggearMacroEditorRecordOptionsFramePrivate {
	GtkToggleButton *record_button;
	GtkToggleButton *delay_button;
	GtkButton *paste_button;
};

G_DEFINE_TYPE(GaminggearMacroEditorRecordOptionsFrame, gaminggear_macro_editor_record_options_frame, GTK_TYPE_FRAME);

enum {
	STARTED,
	PASTE,
	LAST_SIGNAL
};

static guint signals[LAST_SIGNAL] = { 0 };

GtkWidget *gaminggear_macro_editor_record_options_frame_new(void) {
	GaminggearMacroEditorRecordOptionsFrame *record_options_frame;

	record_options_frame = g_object_new(GAMINGGEAR_MACRO_EDITOR_RECORD_OPTIONS_FRAME_TYPE,
			"label", "Record options",
			NULL);

	return GTK_WIDGET(record_options_frame);
}

static void started(GaminggearMacroEditorRecordOptionsFrame *record_options_frame) {
	g_signal_emit((gpointer)record_options_frame, signals[STARTED], 0);
}

static void paste(GaminggearMacroEditorRecordOptionsFrame *record_options_frame) {
	g_signal_emit((gpointer)record_options_frame, signals[PASTE], 0);
}

static void record_button_clicked_cb(GtkButton *button, gpointer user_data) {
	GaminggearMacroEditorRecordOptionsFrame *record_options_frame = GAMINGGEAR_MACRO_EDITOR_RECORD_OPTIONS_FRAME(user_data);
	if (gaminggear_macro_editor_record_options_frame_is_record_on(record_options_frame))
		started(record_options_frame);
}

static void paste_button_clicked_cb(GtkButton *button, gpointer user_data) {
	GaminggearMacroEditorRecordOptionsFrame *record_options_frame = GAMINGGEAR_MACRO_EDITOR_RECORD_OPTIONS_FRAME(user_data);
	paste(record_options_frame);
}

static void gaminggear_macro_editor_record_options_frame_init(GaminggearMacroEditorRecordOptionsFrame *record_options_frame) {
	GaminggearMacroEditorRecordOptionsFramePrivate *priv = GAMINGGEAR_MACRO_EDITOR_RECORD_OPTIONS_FRAME_GET_PRIVATE(record_options_frame);
	GtkWidget *vbox;

	record_options_frame->priv = priv;

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(record_options_frame), vbox);

	priv->record_button = GTK_TOGGLE_BUTTON(gtk_toggle_button_new_with_label("Record"));
	g_object_ref_sink(priv->record_button);
	gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(priv->record_button), FALSE, FALSE, 0);
	g_signal_connect(G_OBJECT(priv->record_button), "clicked", G_CALLBACK(record_button_clicked_cb), record_options_frame);

	priv->delay_button = GTK_TOGGLE_BUTTON(gtk_check_button_new_with_label("Record delays"));
	g_object_ref_sink(priv->delay_button);
	gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(priv->delay_button), FALSE, FALSE, 0);

	priv->paste_button = GTK_BUTTON(gtk_button_new_with_label("Paste"));
	g_object_ref_sink(priv->paste_button);
	gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(priv->paste_button), FALSE, FALSE, 10);
	g_signal_connect(G_OBJECT(priv->paste_button), "clicked", G_CALLBACK(paste_button_clicked_cb), record_options_frame);

	gtk_widget_show_all(GTK_WIDGET(vbox));
}

static void gaminggear_macro_editor_record_options_frame_finalize(GObject *object) {
	GaminggearMacroEditorRecordOptionsFramePrivate *priv = GAMINGGEAR_MACRO_EDITOR_RECORD_OPTIONS_FRAME(object)->priv;
	g_object_unref(priv->record_button);
	g_object_unref(priv->delay_button);
	G_OBJECT_CLASS(gaminggear_macro_editor_record_options_frame_parent_class)->finalize(object);
}

static void gaminggear_macro_editor_record_options_frame_class_init(GaminggearMacroEditorRecordOptionsFrameClass *klass) {
	GObjectClass *gobject_class;

	gobject_class = G_OBJECT_CLASS(klass);

	gobject_class->finalize = gaminggear_macro_editor_record_options_frame_finalize;

	g_type_class_add_private(klass, sizeof(GaminggearMacroEditorRecordOptionsFramePrivate));

	signals[STARTED] = g_signal_new("started",
			G_TYPE_FROM_CLASS(klass),
			G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION,
			G_STRUCT_OFFSET(GaminggearMacroEditorRecordOptionsFrameClass, started),
			NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);

	signals[PASTE] = g_signal_new("paste",
			G_TYPE_FROM_CLASS(klass),
			G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION,
			G_STRUCT_OFFSET(GaminggearMacroEditorRecordOptionsFrameClass, paste),
			NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
}

gboolean gaminggear_macro_editor_record_options_frame_should_record_delays(GaminggearMacroEditorRecordOptionsFrame *record_options_frame) {
	return gtk_toggle_button_get_active(record_options_frame->priv->delay_button);
}

gboolean gaminggear_macro_editor_record_options_frame_is_record_on(GaminggearMacroEditorRecordOptionsFrame *record_options_frame) {
	return gtk_toggle_button_get_active(record_options_frame->priv->record_button);
}
