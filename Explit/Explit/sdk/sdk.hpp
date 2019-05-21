#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>
#include <memory>
#include <thread>
#include <chrono>
#include <map>
#include <string>
#include <algorithm>
#include <windows.h>
#include <stdio.h>
#include <filesystem>
#include <Psapi.h>
#include <fstream> 
#include <intrin.h>
#include <random>
#include <thread>
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include "../json/json.hpp"
#include "../json/json-forwards.hpp"
#include "utils/vfunc/vfunc.hpp"
#include "config/config.hpp"
#include "math/spoint.hpp"
#include "math/srect.hpp"
#include "../zgui/zgui.hpp"
#include "misc/valve/i_app_system.hpp"
#include "math/vector2d.hpp"
#include "misc/valve/life_state.hpp"
#include "misc/color.hpp"
#include "math/QAngle.hpp"
#include "math/vector.hpp"
#include "math/vector2d.hpp"
#include "math/VMatrix.hpp"
#include "math/vector4d.hpp"
#include "math/math.hpp"
#include "utils/utils.hpp"
#include "misc/valve/class_id.hpp"
#include "misc/valve/client_class.hpp"
#include "misc/valve/i_client_networkable.hpp"
#include "misc/valve/recv.hpp"
#include "misc/valve/c_base_handle.hpp"
#include "misc/valve/i_client_entity.hpp"
#include "misc/valve/i_client_mode.hpp"
#include "misc/valve/i_client_networkable.hpp"
#include "misc/valve/i_client_renderable.hpp"
#include "misc/valve/i_client_thinkable.hpp"
#include "misc/valve/i_client_unknown.hpp"
#include "misc/valve/i_collideable.hpp"
#include "misc/valve/item_definition_index.hpp"
#include "misc/valve/i_handle_entity.hpp"
#include "misc/valve/move_type.hpp"
#include "misc/valve/c_user_cmd.hpp"
#include "misc/valve/entity_flags.hpp"
#include "misc/valve/studio.hpp"
#include "misc/valve/i_material.hpp"
#include "netvarmanager/netvar_manager.hpp"
#include "misc/c_base_entity.hpp"
#include "misc/c_base_weapon.hpp"
#include "misc/valve/c_glow_manager.hpp"

#include "interfaces/valve/i_global_vars.hpp"
#include "interfaces/valve/i_panel.hpp"
#include "interfaces/valve/i_surface.hpp"
#include "utils/drawmanager/draw_manager.hpp"
#include "menu/menu.hpp"
#include "interfaces/valve/i_base_client_dll.hpp"
#include "interfaces/valve/iv_engine_client.hpp"
#include "interfaces/valve/i_client_entity_list.hpp"
#include "interfaces/valve/i_engine_trace.hpp"
#include "interfaces/valve/iv_model_info_client.hpp"
#include "interfaces/valve/iv_model_render.hpp"
#include "interfaces/valve/i_render_view.hpp"
#include "interfaces/valve/iv_engine_effects.hpp"
#include "interfaces/valve/i_material_system.hpp"
#include "interfaces/interfaces.hpp"
#include "utils/vmt/vmt.hpp"
#include "../features/visuals/esp.hpp"
#include "../features/visuals/glow.hpp"
#include "../features/visuals/dlight.hpp"
#include "../features/visuals//chams.hpp"
#include "../features/misc/bunny_hop.hpp"
#include "../features/helpers/movement_fix.hpp"
#include "../features/misc/auto_strafe.hpp"
#include "../features/misc/engine_radar.hpp"
#include "../features/legitbot/triggerbot.hpp"

#include "hooks/hooks.hpp"


class c_sdk {
public:
	void on_inject();
	void un_inject();
	bool unhook = false;
	bool esp = false;
};
extern c_sdk g_sdk;






