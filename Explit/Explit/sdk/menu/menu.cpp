#include "menu.hpp"
c_menu g_menu;

void c_menu::draw()
{
	zgui::poll_input("Counter-Strike: Global Offensive");

	if (zgui::begin_window("Explit Framework | Beta", { 500, 350 }, g_draw.menu, zgui::zgui_window_flags_none))
	{
		if (zgui::tab_button("Legitbot", { 165,30 }, aimbot))
		{
			aimbot = true;
			visuals = false;
			misc = false;
		}

		zgui::same_line();

		zgui::next_column( -5,0 );

		if (zgui::tab_button("Visuals", { 165,30 }, visuals))
		{
			aimbot = false;
			visuals = true;
			misc = false;
		}
		zgui::same_line();	

		zgui::next_column( -5,0 );

		if (zgui::tab_button("Misc", { 166,30 }, misc))
		{
			aimbot = false;
			visuals = false;
			misc = true;
		}

		zgui::next_column( -327,34 );

		if (aimbot)draw_aimbot();
		if (visuals)draw_visuals();
		if (misc)draw_misc();

		zgui::end_window();
	}

	if(g_config.settings.visuals.others.watermark) draw_watermark();
}

void c_menu::draw_watermark()
{
	const auto chrono_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	const auto time = ctime(&chrono_time);
	auto fps = static_cast<int>(1.f / g_interfaces.p_global_vars->frame_time);

	int width, height;
	g_interfaces.p_engine->get_screen_size(width, height);
	
	g_draw.fill_rect(width - 280, 20, 260, 28, color(1, 1, 1, 255));
	g_draw.fill_rect(width - 279, 21, 258, 26, color(51, 51, 51, 255));
	g_draw.fill_rect(width - 278, 22, 256, 24, color(41, 41, 41, 255));
	g_draw.fill_rect(width - 277, 23, 254, 22, color(51, 51, 51, 255));
	g_draw.fill_rect(width - 276, 24, 252, 20, color(1, 1, 1, 255));
	g_draw.fill_rect(width - 275, 25, 250, 18, color(31, 31, 31, 255));
	g_draw.fill_rect(width - 275, 42, 250, 1, color(255, 85, 85, 255));

	const auto connected = g_interfaces.g_local_player && g_interfaces.p_engine->is_in_game() && g_interfaces.p_engine->is_connected();
	const auto ping_str = connected ? g_utils.stringer(static_cast<int>(g_interfaces.p_engine->get_net_channel_info()->get_avg_latency(0) * 1000)) : "0";

	g_draw.string(width - 271, 27, color(255, 255, 255), g_draw.menu, false , g_utils.stringer(time, "  FPS:", fps, "  PING:", ping_str, "ms"));
	
}

void c_menu::draw_misc()
{
	zgui::begin_groupbox("Misc");
	{
		zgui::checkbox("BunnyHop", g_config.settings.misc.movement.bunnyhop);
		zgui::combobox("BunnyHop Mode", std::vector<std::string>{"Rage", "Legit"}, g_config.settings.misc.movement.bunnyhop_mode);
		zgui::checkbox("Autostrafe", g_config.settings.misc.movement.auto_strafe);
		zgui::combobox("Autostrafe Mode", std::vector<std::string>{"Legit","Rage"}, g_config.settings.misc.movement.autostrafe_mode);
		if (zgui::button("Unhook"))
			g_sdk.unhook = true;
	}
	zgui::end_groupbox();

	zgui::next_column();

	zgui::begin_groupbox("Configs");
	{
		zgui::text_input("Config Name", g_config.settings.config_name);
		if (zgui::button("Create Config"))
		{
			if (!g_config.settings.config_name.empty())
			{
				g_config.save(g_utils.stringer(g_config.settings.config_name, ".json"));
				g_config.settings.config_name.clear();
				g_config.refresh();
			}
		}
		zgui::combobox("Config List", g_config.settings.config_list, g_config.settings.config_id);
		if (zgui::button("Refresh"))
			g_config.refresh();
		if (zgui::button("Save"))
			g_config.save(g_config.settings.config_list[g_config.settings.config_id]);
		if (zgui::button("Load"))
			g_config.load(g_config.settings.config_list[g_config.settings.config_id]);
	}
	zgui::end_groupbox();

}

void c_menu::draw_visuals()
{
	zgui::begin_groupbox("ESP");
	{
		zgui::checkbox("Enable#1", g_config.settings.visuals.esp.esp);
		zgui::checkbox("Box", g_config.settings.visuals.esp.box);
		zgui::combobox("Box Type", std::vector<std::string>{"Full Box", "Corner Box"}, g_config.settings.visuals.esp.box_type);
		zgui::checkbox("Filled Box", g_config.settings.visuals.esp.fill_box);
		zgui::checkbox("Outlined Box", g_config.settings.visuals.esp.outline_box);
		zgui::checkbox("Name", g_config.settings.visuals.esp.name);
		zgui::checkbox("Distance", g_config.settings.visuals.esp.distance);
		zgui::combobox("Health", std::vector<std::string>{"Off", "Bar", "Text", "Bar+Text"}, g_config.settings.visuals.esp.health);
		zgui::combobox("Armor", std::vector<std::string>{"Off", "Bar", "Text", "Bar+Text"}, g_config.settings.visuals.esp.armor);
		zgui::checkbox("Money", g_config.settings.visuals.esp.money);
		zgui::checkbox("Weapon", g_config.settings.visuals.esp.weapon);
		zgui::checkbox("Ammo", g_config.settings.visuals.esp.ammo);
		zgui::checkbox("Snaplines", g_config.settings.visuals.esp.snaplines);
		zgui::checkbox("Skeleton", g_config.settings.visuals.esp.skeletons);
		zgui::checkbox("Visible Only", g_config.settings.visuals.esp.visible);
		zgui::checkbox("Vulnerability", g_config.settings.visuals.esp.vulnerability);
		zgui::multi_combobox("Filter##1", std::vector< zgui::multi_select_item >{ { "Local", &g_config.settings.visuals.esp.local }, { "Enemy", &g_config.settings.visuals.esp.enemies }, { "Team", &g_config.settings.visuals.esp.team }, { "Weapons", &g_config.settings.visuals.esp.weapons }, { "Chickens", &g_config.settings.visuals.esp.chickens }});

	}
	zgui::end_groupbox();

	zgui::next_column();

	zgui::begin_groupbox("Chams", { 163, 150 });
	{
		zgui::checkbox("Enable#2", g_config.settings.visuals.chams.chams);
		zgui::checkbox("Visible Only#3", g_config.settings.visuals.chams.visible);
		zgui::multi_combobox("Filter#3", std::vector< zgui::multi_select_item >{ { "Local", &g_config.settings.visuals.chams.local }, { "Enemy", &g_config.settings.visuals.chams.enemy }, { "Team", &g_config.settings.visuals.chams.team }});
		zgui::combobox("Material", std::vector<std::string>{"Flat", "Glass",}, g_config.settings.visuals.chams.material);
		zgui::checkbox("Wireframe", g_config.settings.visuals.chams.wireframe);
		zgui::checkbox("Arms", g_config.settings.visuals.chams.arms);
		zgui::checkbox("Weapon#2", g_config.settings.visuals.chams.weapon);
	}
	zgui::end_groupbox();

	zgui::next_column( 0,168 );

	zgui::begin_groupbox("Glow", { 163, 156});
	{
		zgui::checkbox("Enable#3", g_config.settings.visuals.glow.glow);
		zgui::checkbox("Visible Only#2", g_config.settings.visuals.glow.visible);
		zgui::checkbox("Vulnerability#2", g_config.settings.visuals.glow.vulnerability);
		zgui::combobox("Glow Style", std::vector<std::string>{"0", "1", "2", "3"}, g_config.settings.visuals.glow.style);
		zgui::multi_combobox("Filter#2", std::vector< zgui::multi_select_item >{ { "Local", &g_config.settings.visuals.glow.local }, { "Enemy", &g_config.settings.visuals.glow.enemy }, { "Team", &g_config.settings.visuals.glow.team }, { "Weapons", &g_config.settings.visuals.glow.weapons }, { "Chickens", &g_config.settings.visuals.glow.chickens }});
	}
	zgui::end_groupbox();

	zgui::next_column();

	zgui::begin_groupbox("DLights", { 164, 77 });
	{
		zgui::checkbox("Enable#4", g_config.settings.visuals.dlights.enable);
		zgui::multi_combobox("Filter#4", std::vector< zgui::multi_select_item >{ { "Local", &g_config.settings.visuals.dlights.local }, { "Enemy", &g_config.settings.visuals.dlights.enemy }, { "Team", &g_config.settings.visuals.dlights.team }});
		zgui::slider_float("Radius", 0, 500, g_config.settings.visuals.dlights.radius);

	}
	zgui::end_groupbox();

	zgui::next_column(0, 112);

	zgui::begin_groupbox("Others", { 164, 212 });
	{
		zgui::checkbox("Watermark", g_config.settings.visuals.others.watermark);

	}
	zgui::end_groupbox();
}

void c_menu::draw_aimbot()
{
	const auto in_game = g_interfaces.g_local_player && g_interfaces.p_engine->is_in_game() && g_interfaces.p_engine->is_connected();
	zgui::begin_groupbox("Main");
	{
		zgui::checkbox("Aimbot", g_config.settings.legitbot.aimbotb);
		zgui::combobox("Aimbot Mode", std::vector<std::string>{"On Key", "On Shoot", "Always" }, g_config.settings.legitbot.aim_mode);
		zgui::checkbox("Triggerbot", g_config.settings.legitbot.triggerbotb);
		zgui::combobox("Triggerbot Mode", std::vector<std::string>{"On Key", "Always" }, g_config.settings.legitbot.trigger_mode);
		zgui::checkbox("Deathmatch", g_config.settings.legitbot.deathmatch);
		if (in_game && g_interfaces.g_local_player->m_ilifestate() == life_alive)
		{
			const auto weapon_id = g_interfaces.g_local_player->get_weapon()->get_weapon_id();
			const auto is_weapon = g_interfaces.g_local_player->get_weapon()->is_useable_weapon();
			zgui::text(is_weapon ? g_utils.stringer("Current weapon: ", g_utils.weapon_config_name(weapon_id)).c_str() : "No useable gun");
		}
		else 
		{
			zgui::text("Not in game");
		}
	}
	zgui::end_groupbox();
	
	zgui::next_column();

	zgui::begin_groupbox("Aimbot");
	{
		if (in_game && g_interfaces.g_local_player->m_ilifestate() == life_alive)
		{
			const auto weapon_id = g_interfaces.g_local_player->get_weapon()->get_weapon_id();
			if (g_interfaces.g_local_player->get_weapon()->is_useable_weapon())
			{
				zgui::checkbox("Enable#11", g_config.settings.legitbot.aimbot[weapon_id].enable);
				zgui::key_bind("Key 1#11", g_config.settings.legitbot.aimbot[weapon_id].key_1);
				zgui::key_bind("Key 2#11", g_config.settings.legitbot.aimbot[weapon_id].key_2);
				zgui::checkbox("Flash Check#11", g_config.settings.legitbot.aimbot[weapon_id].flash);
				zgui::checkbox("Smoke Check#11", g_config.settings.legitbot.aimbot[weapon_id].smoke);
				zgui::checkbox("Visible Check#11", g_config.settings.legitbot.aimbot[weapon_id].smoke);
				zgui::checkbox("Jump Check#11", g_config.settings.legitbot.aimbot[weapon_id].jump);
				if (g_interfaces.g_local_player->get_weapon()->is_sniper())
					zgui::checkbox("Scope Check#11", g_config.settings.legitbot.aimbot[weapon_id].scope);
				zgui::slider_float("Fov#11", 0, 180, g_config.settings.legitbot.aimbot[weapon_id].fov);
				zgui::combobox("Fov type", std::vector<std::string>{"Static", "Dynamic" }, g_config.settings.legitbot.aimbot[weapon_id].fov_type);
				zgui::slider_float("Smooth#11", 0, 100, g_config.settings.legitbot.aimbot[weapon_id].smooth);
				zgui::checkbox("Curve#11", g_config.settings.legitbot.aimbot[weapon_id].curve);
				zgui::slider_float("Curve X#11", 0, 7, g_config.settings.legitbot.aimbot[weapon_id].curve_x);
				zgui::slider_float("Curve Y#11", 0, 7, g_config.settings.legitbot.aimbot[weapon_id].curve_y);
				//zgui::listbox("Hitboxes#10", std::vector< zgui::multi_select_item >{ { "Head", &g_config.settings.legitbot.triggerbot[weapon_id].hit_head }, { "Body", &g_config.settings.legitbot.triggerbot[weapon_id].hit_body }, { "Arms", &g_config.settings.legitbot.triggerbot[weapon_id].hit_arms }, { "Legs", &g_config.settings.legitbot.triggerbot[weapon_id].hit_legs }});
			}
		}
	}
	zgui::end_groupbox();

	zgui::next_column();

	zgui::begin_groupbox("Triggerbot");
	{
		if (in_game && g_interfaces.g_local_player->m_ilifestate() == life_alive)
		{
			const auto weapon_id = g_interfaces.g_local_player->get_weapon()->get_weapon_id();
			if (g_interfaces.g_local_player->get_weapon()->is_useable_weapon())
			{
				zgui::checkbox("Enable#10", g_config.settings.legitbot.triggerbot[weapon_id].enable);
				zgui::key_bind("Key 1#10", g_config.settings.legitbot.triggerbot[weapon_id].key_1);
				zgui::key_bind("Key 2#10", g_config.settings.legitbot.triggerbot[weapon_id].key_2);
				zgui::checkbox("Flash Check#10", g_config.settings.legitbot.triggerbot[weapon_id].flash);
				zgui::checkbox("Smoke Check#10", g_config.settings.legitbot.triggerbot[weapon_id].smoke);
				zgui::checkbox("Jump Check#10", g_config.settings.legitbot.triggerbot[weapon_id].jump);
				if(g_interfaces.g_local_player->get_weapon()->is_sniper())
					zgui::checkbox("Scope Check#10", g_config.settings.legitbot.triggerbot[weapon_id].scope);
				zgui::slider_int("Sleep Before#10", 0, 500, g_config.settings.legitbot.triggerbot[weapon_id].sleep_before);
				zgui::slider_int("Sleep Between#10", 0, 500, g_config.settings.legitbot.triggerbot[weapon_id].sleep_between);
				zgui::listbox("Hitboxes#10", std::vector< zgui::multi_select_item >{ { "Head", &g_config.settings.legitbot.triggerbot[weapon_id].hit_head }, { "Body", &g_config.settings.legitbot.triggerbot[weapon_id].hit_body }, { "Arms", &g_config.settings.legitbot.triggerbot[weapon_id].hit_arms }, { "Legs", &g_config.settings.legitbot.triggerbot[weapon_id].hit_legs }});
			}
		}
	}
	zgui::end_groupbox();
}
