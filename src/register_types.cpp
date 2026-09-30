////////////////////////////////////////////////////////////////////////////
// OpenVR GDExtension module for Godot
//
// Written by Bastiaan "Mux213" Olij,
// with loads of help from Thomas "Karroffel" Herzog

#include "register_types.h"

#include <gdextension_interface.h>

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/xr_server.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "OpenVRSkeleton.h"
#include "openvr_event_handler.h"
#include "openvr_overlay_container.h"
#include "xr_interface_openvr.h"

using namespace godot;

// The interface is added to the XR server on extension load, so no GDScript
// autoload is needed. XRServer may not be live yet at scene-init on some builds
// (godot#64975); when it is missing we add on the first frame via a deferred
// call, by which time the server exists.
static Ref<XRInterfaceOpenVR> openvr_interface;

static void add_openvr_interface() {
	XRServer *xr_server = XRServer::get_singleton();
	if (xr_server != nullptr && !openvr_interface.is_valid()) {
		openvr_interface.instantiate();
		xr_server->add_interface(openvr_interface);
	}
}

void initialize_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<XRInterfaceOpenVR>();
	ClassDB::register_class<OpenVROverlayContainer>();
	ClassDB::register_class<OpenVRSkeleton>();

	// Virtual classes
	ClassDB::register_class<OpenVREventHandler>(true);

	if (XRServer::get_singleton() != nullptr) {
		add_openvr_interface();
	} else {
		callable_mp_static(add_openvr_interface).call_deferred();
	}
}

void uninitialize_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	if (openvr_interface.is_valid()) {
		XRServer *xr_server = XRServer::get_singleton();
		if (xr_server != nullptr) {
			xr_server->remove_interface(openvr_interface);
		}
		openvr_interface.unref();
	}
}

extern "C" {
GDExtensionBool GDE_EXPORT openvr_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
	init_obj.register_initializer(initialize_gdextension_types);
	init_obj.register_terminator(uninitialize_gdextension_types);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
