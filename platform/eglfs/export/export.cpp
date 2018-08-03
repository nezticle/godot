/*************************************************************************/
/*  export.cpp                                                           */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2018 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2018 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "export.h"

#include "editor/editor_export.h"
#include "editor/editor_node.h"
#include "editor/editor_settings.h"
#include "platform/eglfs/logo.gen.h"
#include "scene/resources/texture.h"

class EditorExportPlatformEGLFS : public EditorExportPlatform {

	GDCLASS(EditorExportPlatformEGLFS, EditorExportPlatform);

    int version_code;
	Ref<ImageTexture> logo;

protected:
	virtual void get_preset_features(const Ref<EditorExportPreset> &p_preset, List<String> *r_features);
	virtual void get_export_options(List<ExportOption> *r_options);

public:
	virtual String get_name() const { return "EGLFS"; }
	virtual String get_os_name() const { return "Linux"; }
	virtual Ref<Texture> get_logo() const { return logo; }

	virtual Error export_project(const Ref<EditorExportPreset> &p_preset, bool p_debug, const String &p_path, int p_flags = 0);

	virtual bool can_export(const Ref<EditorExportPreset> &p_preset, String &r_error, bool &r_missing_templates) const;

	virtual void get_platform_features(List<String> *r_features) {

		// r_features->push_back("mobile");
		// r_features->push_back("");
	}

	EditorExportPlatformEGLFS();
	~EditorExportPlatformEGLFS();
};

EditorExportPlatformEGLFS::EditorExportPlatformEGLFS() {
    Ref<Image> img = memnew(Image(_eglfs_logo));
	logo.instance();
	logo->create_from_image(img);
}

EditorExportPlatformEGLFS::~EditorExportPlatformEGLFS {

}

void EditorExportPlatformEGLFS::get_preset_features(const Ref<EditorExportPreset> &p_preset, List<String> *r_features) {

}

void EditorExportPlatformEGLFS::get_export_options(List<ExportOption> *r_options) {

}

Error EditorExportPlatformEGLFS::export_project(const Ref<EditorExportPreset> &p_preset, bool p_debug, const String &p_path, int p_flags) {
    // ### Just Zip things up and ship 'em
    return OK;
}

bool EditorExportPlatformEGLFS::can_export(const Ref<EditorExportPreset> &p_preset, String &r_error, bool &r_missing_templates) const {
    return true;
}

void register_eglfs_exporter() {

	Ref<EditorExportPlatformEGLFS> platform;
	platform.instance();

	EditorExport::get_singleton()->add_export_platform(platform);
}
