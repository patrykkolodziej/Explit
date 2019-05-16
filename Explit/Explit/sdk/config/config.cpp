#include "config.hpp"

c_config g_config("C:/Explit/Configs");

c_config::c_config(const std::string path)
{
	directory_path = path;

	if (!std::filesystem::exists(directory_path))
		std::filesystem::create_directories(directory_path);

	refresh();
}

void c_config::refresh()
{
	settings.config_list.clear();

	for (const auto & entry : std::filesystem::directory_iterator(directory_path))
		if (entry.path().string().find(".json"))
		{
			const auto length = entry.path().string().erase(0, 18).length();
			settings.config_list.emplace_back(entry.path().string().erase(0, 18).erase(length - 5,5));
		}

	if (settings.config_list.empty())
	{
		save("default");
		refresh();
	}
}

void c_config::save(const std::string name)
{
	const auto path = directory_path + "/" + name;

	std::ofstream out(path);

	if (!out.is_open())
	{
		return;
	}

	Json::Value save;

	save["Explit - Config"]["Visuals"]["Esp"]["Enable"] = settings.visuals.esp.esp;
	save["Explit - Config"]["Visuals"]["Esp"]["Ammo"] = settings.visuals.esp.ammo;
	save["Explit - Config"]["Visuals"]["Esp"]["Armor"] = settings.visuals.esp.armor;
	save["Explit - Config"]["Visuals"]["Esp"]["Box"] = settings.visuals.esp.box;
	save["Explit - Config"]["Visuals"]["Esp"]["Box Type"] = settings.visuals.esp.box_type;
	save["Explit - Config"]["Visuals"]["Esp"]["Chickens"] = settings.visuals.esp.chickens;
	save["Explit - Config"]["Visuals"]["Esp"]["Distance"] = settings.visuals.esp.distance;
	save["Explit - Config"]["Visuals"]["Esp"]["Enemies"] = settings.visuals.esp.enemies;
	save["Explit - Config"]["Visuals"]["Esp"]["Fill Box"] = settings.visuals.esp.fill_box;
	save["Explit - Config"]["Visuals"]["Esp"]["Health"] = settings.visuals.esp.health;
	save["Explit - Config"]["Visuals"]["Esp"]["Local"] = settings.visuals.esp.local;
	save["Explit - Config"]["Visuals"]["Esp"]["Money"] = settings.visuals.esp.money;
	save["Explit - Config"]["Visuals"]["Esp"]["Name"] = settings.visuals.esp.name;
	save["Explit - Config"]["Visuals"]["Esp"]["Outlined Box"] = settings.visuals.esp.outline_box;
	save["Explit - Config"]["Visuals"]["Esp"]["Skeleton"] = settings.visuals.esp.skeletons;
	save["Explit - Config"]["Visuals"]["Esp"]["Snaplines"] = settings.visuals.esp.snaplines;
	save["Explit - Config"]["Visuals"]["Esp"]["Visible"] = settings.visuals.esp.visible;
	save["Explit - Config"]["Visuals"]["Esp"]["Weapon"] = settings.visuals.esp.weapon;
	save["Explit - Config"]["Visuals"]["Esp"]["Dropped Weapons"] = settings.visuals.esp.weapons;
	save["Explit - Config"]["Visuals"]["Esp"]["Vulnerability"] = settings.visuals.esp.vulnerability;
	save["Explit - Config"]["Visuals"]["Esp"]["Team"] = settings.visuals.esp.team;

	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Team Invisible"][0] = settings.visuals.esp.colors.team_invisible[0];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Team Invisible"][1] = settings.visuals.esp.colors.team_invisible[1];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Team Invisible"][2] = settings.visuals.esp.colors.team_invisible[2];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Team Invisible"][3] = settings.visuals.esp.colors.team_invisible[3];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Team Visible"][0] = settings.visuals.esp.colors.team_visible[0];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Team Visible"][1] = settings.visuals.esp.colors.team_visible[1];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Team Visible"][2] = settings.visuals.esp.colors.team_visible[2];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Team Visible"][3] = settings.visuals.esp.colors.team_visible[3];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Enemy Invisible"][0] = settings.visuals.esp.colors.enemy_invisible[0];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Enemy Invisible"][1] = settings.visuals.esp.colors.enemy_invisible[1];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Enemy Invisible"][2] = settings.visuals.esp.colors.enemy_invisible[2];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Enemy Invisible"][3] = settings.visuals.esp.colors.enemy_invisible[3];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Enemy Visible"][0] = settings.visuals.esp.colors.enemy_visible[0];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Enemy Visible"][1] = settings.visuals.esp.colors.enemy_visible[1];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Enemy Visible"][2] = settings.visuals.esp.colors.enemy_visible[2];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Enemy Visible"][3] = settings.visuals.esp.colors.enemy_visible[3];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Chickens"][0] = settings.visuals.esp.colors.chickens[0];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Chickens"][1] = settings.visuals.esp.colors.chickens[1];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Chickens"][2] = settings.visuals.esp.colors.chickens[2];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Chickens"][3] = settings.visuals.esp.colors.chickens[3];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Dropped Weapons"][0] = settings.visuals.esp.colors.weapons[0];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Dropped Weapons"][1] = settings.visuals.esp.colors.weapons[1];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Dropped Weapons"][2] = settings.visuals.esp.colors.weapons[2];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Dropped Weapons"][3] = settings.visuals.esp.colors.weapons[3];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Vulnerability"][0] = settings.visuals.esp.colors.vulnerability[0];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Vulnerability"][1] = settings.visuals.esp.colors.vulnerability[1];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Vulnerability"][2] = settings.visuals.esp.colors.vulnerability[2];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Vulnerability"][3] = settings.visuals.esp.colors.vulnerability[3];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Local"][0] = settings.visuals.esp.colors.local[0];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Local"][1] = settings.visuals.esp.colors.local[1];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Local"][2] = settings.visuals.esp.colors.local[2];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Local"][3] = settings.visuals.esp.colors.local[3];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Skeleton"][0] = settings.visuals.esp.colors.skeleton[0];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Skeleton"][1] = settings.visuals.esp.colors.skeleton[1];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Skeleton"][2] = settings.visuals.esp.colors.skeleton[2];
	save["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Skeleton"][3] = settings.visuals.esp.colors.skeleton[3];

	save["Explit - Config"]["Visuals"]["Glow"]["Enable"] = settings.visuals.glow.glow;
	save["Explit - Config"]["Visuals"]["Glow"]["Chickens"] = settings.visuals.glow.chickens;
	save["Explit - Config"]["Visuals"]["Glow"]["Enemies"] = settings.visuals.glow.enemy;
	save["Explit - Config"]["Visuals"]["Glow"]["Local"] = settings.visuals.glow.local;
	save["Explit - Config"]["Visuals"]["Glow"]["Style"] = settings.visuals.glow.style;
	save["Explit - Config"]["Visuals"]["Glow"]["Team"] = settings.visuals.glow.team;
	save["Explit - Config"]["Visuals"]["Glow"]["Visible"] = settings.visuals.glow.visible;
	save["Explit - Config"]["Visuals"]["Glow"]["Dropped Weapons"] = settings.visuals.glow.weapons;
	save["Explit - Config"]["Visuals"]["Glow"]["Vulnerability"] = settings.visuals.glow.vulnerability;

	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Team Invisible"][0] = settings.visuals.glow.colors.team_invisible[0];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Team Invisible"][1] = settings.visuals.glow.colors.team_invisible[1];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Team Invisible"][2] = settings.visuals.glow.colors.team_invisible[2];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Team Invisible"][3] = settings.visuals.glow.colors.team_invisible[3];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Team Visible"][0] = settings.visuals.glow.colors.team_visible[0];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Team Visible"][1] = settings.visuals.glow.colors.team_visible[1];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Team Visible"][2] = settings.visuals.glow.colors.team_visible[2];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Team Visible"][3] = settings.visuals.glow.colors.team_visible[3];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Enemy Invisible"][0] = settings.visuals.glow.colors.enemy_invisible[0];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Enemy Invisible"][1] = settings.visuals.glow.colors.enemy_invisible[1];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Enemy Invisible"][2] = settings.visuals.glow.colors.enemy_invisible[2];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Enemy Invisible"][3] = settings.visuals.glow.colors.enemy_invisible[3];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Enemy Visible"][0] = settings.visuals.glow.colors.enemy_visible[0];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Enemy Visible"][1] = settings.visuals.glow.colors.enemy_visible[1];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Enemy Visible"][2] = settings.visuals.glow.colors.enemy_visible[2];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Enemy Visible"][3] = settings.visuals.glow.colors.enemy_visible[3];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Chickens"][0] = settings.visuals.glow.colors.chickens[0];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Chickens"][1] = settings.visuals.glow.colors.chickens[1];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Chickens"][2] = settings.visuals.glow.colors.chickens[2];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Chickens"][3] = settings.visuals.glow.colors.chickens[3];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Dropped Weapons"][0] = settings.visuals.glow.colors.weapons[0];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Dropped Weapons"][1] = settings.visuals.glow.colors.weapons[1];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Dropped Weapons"][2] = settings.visuals.glow.colors.weapons[2];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Dropped Weapons"][3] = settings.visuals.glow.colors.weapons[3];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Vulnerability"][0] = settings.visuals.glow.colors.vulnerability[0];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Vulnerability"][1] = settings.visuals.glow.colors.vulnerability[1];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Vulnerability"][2] = settings.visuals.glow.colors.vulnerability[2];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Vulnerability"][3] = settings.visuals.glow.colors.vulnerability[3];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Local"][0] = settings.visuals.glow.colors.local [0];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Local"][1] = settings.visuals.glow.colors.local[1];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Local"][2] = settings.visuals.glow.colors.local[2];
	save["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Local"][3] = settings.visuals.glow.colors.local[3];

	save["Explit - Config"]["Visuals"]["DLights"]["Enable"] = settings.visuals.dlights.enable;
	save["Explit - Config"]["Visuals"]["DLights"]["Enemies"] = settings.visuals.dlights.enemy;
	save["Explit - Config"]["Visuals"]["DLights"]["Local"] = settings.visuals.dlights.local;
	save["Explit - Config"]["Visuals"]["DLights"]["Team"] = settings.visuals.dlights.team;
	save["Explit - Config"]["Visuals"]["DLights"]["Radius"] = settings.visuals.dlights.radius;

	save["Explit - Config"]["Visuals"]["DLights"]["Colors"]["Local"][0] = settings.visuals.dlights.colors.local[0];
	save["Explit - Config"]["Visuals"]["DLights"]["Colors"]["Local"][1] = settings.visuals.dlights.colors.local[1];
	save["Explit - Config"]["Visuals"]["DLights"]["Colors"]["Local"][2] = settings.visuals.dlights.colors.local[2];
	save["Explit - Config"]["Visuals"]["DLights"]["Colors"]["Team"][0] = settings.visuals.dlights.colors.team[0];
	save["Explit - Config"]["Visuals"]["DLights"]["Colors"]["Team"][1] = settings.visuals.dlights.colors.team[1];
	save["Explit - Config"]["Visuals"]["DLights"]["Colors"]["Team"][2] = settings.visuals.dlights.colors.team[2];
	save["Explit - Config"]["Visuals"]["DLights"]["Colors"]["Enemy"][0] = settings.visuals.dlights.colors.enemy[0];
	save["Explit - Config"]["Visuals"]["DLights"]["Colors"]["Enemy"][1] = settings.visuals.dlights.colors.enemy[1];
	save["Explit - Config"]["Visuals"]["DLights"]["Colors"]["Enemy"][2] = settings.visuals.dlights.colors.enemy[2];


	save["Explit - Config"]["Visuals"]["Others"]["Watermark"] = settings.visuals.others.watermark;

	save["Explit - Config"]["Misc"]["Movement"]["Bunnyhop"] = settings.misc.movement.bunnyhop;

	for (int i = 1; i <= 64; i++)
	{
		const auto weapon_name = g_utils.weapon_config_name(i);

		if (weapon_name == "unknown")
			continue;

		save["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Enable"] = settings.legitbot.triggerbot[i].enable;
		save["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Key 1"] = settings.legitbot.triggerbot[i].key_1;
		save["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Key 2"] = settings.legitbot.triggerbot[i].key_2;
		save["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Flash Check"] = settings.legitbot.triggerbot[i].flash;
		save["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Smoke Check"] = settings.legitbot.triggerbot[i].smoke;
		save["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Jump Check"] = settings.legitbot.triggerbot[i].jump;
		save["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Scope Check"] = settings.legitbot.triggerbot[i].scope;
		save["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Sleep Before Shot"] = settings.legitbot.triggerbot[i].sleep_before;
		save["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Sleep Between Shots"] = settings.legitbot.triggerbot[i].sleep_between;
		save["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Hitbox Head"] = settings.legitbot.triggerbot[i].hit_head;
		save["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Hitbox Body"] = settings.legitbot.triggerbot[i].hit_body;
		save["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Hitbox Arms"] = settings.legitbot.triggerbot[i].hit_arms;
		save["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Hitbox Legs"] = settings.legitbot.triggerbot[i].hit_legs;
	}

	out << save;

	out.close();
}

void c_config::load(const std::string name)
{
	const auto path = directory_path + "/" + name;

	std::ifstream in(path);

	if (!in.good())
	{
		save(name);
	}

	if (!in.is_open())
	{
		return;
	}

	Json::Value load;

	in >> load;

	settings.visuals.esp.esp = load["Explit - Config"]["Visuals"]["Esp"]["Enable"].asBool();
	settings.visuals.esp.ammo = load["Explit - Config"]["Visuals"]["Esp"]["Ammo"].asBool();
	settings.visuals.esp.armor = load["Explit - Config"]["Visuals"]["Esp"]["Armor"].asInt();
	settings.visuals.esp.box = load["Explit - Config"]["Visuals"]["Esp"]["Box"].asBool();
	settings.visuals.esp.box_type = load["Explit - Config"]["Visuals"]["Esp"]["Box Type"].asInt();
	settings.visuals.esp.chickens = load["Explit - Config"]["Visuals"]["Esp"]["Chickens"].asBool();
	settings.visuals.esp.distance = load["Explit - Config"]["Visuals"]["Esp"]["Distance"].asBool();
	settings.visuals.esp.enemies = load["Explit - Config"]["Visuals"]["Esp"]["Enemies"].asBool();
	settings.visuals.esp.fill_box = load["Explit - Config"]["Visuals"]["Esp"]["Fill Box"].asBool();
	settings.visuals.esp.health = load["Explit - Config"]["Visuals"]["Esp"]["Health"].asInt();
	settings.visuals.esp.local = load["Explit - Config"]["Visuals"]["Esp"]["Local"].asBool();
	settings.visuals.esp.money = load["Explit - Config"]["Visuals"]["Esp"]["Money"].asBool();
	settings.visuals.esp.name = load["Explit - Config"]["Visuals"]["Esp"]["Name"].asBool();
	settings.visuals.esp.outline_box = load["Explit - Config"]["Visuals"]["Esp"]["Outlined Box"].asBool();
	settings.visuals.esp.skeletons = load["Explit - Config"]["Visuals"]["Esp"]["Skeleton"].asBool();
	settings.visuals.esp.snaplines = load["Explit - Config"]["Visuals"]["Esp"]["Snaplines"].asBool();
	settings.visuals.esp.visible = load["Explit - Config"]["Visuals"]["Esp"]["Visible"].asBool();
	settings.visuals.esp.weapon = load["Explit - Config"]["Visuals"]["Esp"]["Weapon"].asBool();
	settings.visuals.esp.weapons = load["Explit - Config"]["Visuals"]["Esp"]["Dropped Weapons"].asBool();
	settings.visuals.esp.vulnerability = load["Explit - Config"]["Visuals"]["Esp"]["Vulnerability"].asBool();
	settings.visuals.esp.team = load["Explit - Config"]["Visuals"]["Esp"]["Team"].asBool();

	settings.visuals.esp.colors.team_invisible[0] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Team Invisible"][0].asInt();
	settings.visuals.esp.colors.team_invisible[1] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Team Invisible"][1].asInt();
	settings.visuals.esp.colors.team_invisible[2] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Team Invisible"][2].asInt();
	settings.visuals.esp.colors.team_invisible[3] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Team Invisible"][3].asInt();
	settings.visuals.esp.colors.team_visible[0] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Team Visible"][0].asInt();
	settings.visuals.esp.colors.team_visible[1] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Team Visible"][1].asInt();
	settings.visuals.esp.colors.team_visible[2] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Team Visible"][2].asInt();
	settings.visuals.esp.colors.team_visible[3] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Team Visible"][3].asInt();
	settings.visuals.esp.colors.enemy_invisible[0] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Enemy Invisible"][0].asInt();
	settings.visuals.esp.colors.enemy_invisible[1] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Enemy Invisible"][1].asInt();
	settings.visuals.esp.colors.enemy_invisible[2] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Enemy Invisible"][2].asInt();
	settings.visuals.esp.colors.enemy_invisible[3] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Enemy Invisible"][3].asInt();
	settings.visuals.esp.colors.enemy_visible[0] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Enemy Visible"][0].asInt();
	settings.visuals.esp.colors.enemy_visible[1] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Enemy Visible"][1].asInt();
	settings.visuals.esp.colors.enemy_visible[2] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Enemy Visible"][2].asInt();
	settings.visuals.esp.colors.enemy_visible[3] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Enemy Visible"][3].asInt();
	settings.visuals.esp.colors.chickens[0] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Chickens"][0].asInt();
	settings.visuals.esp.colors.chickens[1] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Chickens"][1].asInt();
	settings.visuals.esp.colors.chickens[2] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Chickens"][2].asInt();
	settings.visuals.esp.colors.chickens[3] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Chickens"][3].asInt();
	settings.visuals.esp.colors.weapons[0] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Dropped Weapons"][0].asInt();
	settings.visuals.esp.colors.weapons[1] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Dropped Weapons"][1].asInt();
	settings.visuals.esp.colors.weapons[2] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Dropped Weapons"][2].asInt();
	settings.visuals.esp.colors.weapons[3] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Dropped Weapons"][3].asInt();
	settings.visuals.esp.colors.vulnerability[0] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Vulnerability"][0].asInt();
	settings.visuals.esp.colors.vulnerability[1] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Vulnerability"][1].asInt();
	settings.visuals.esp.colors.vulnerability[2] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Vulnerability"][2].asInt();
	settings.visuals.esp.colors.vulnerability[3] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Vulnerability"][3].asInt();
	settings.visuals.esp.colors.local[0] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Local"][0].asInt();
	settings.visuals.esp.colors.local[1] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Local"][1].asInt();
	settings.visuals.esp.colors.local[2] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Local"][2].asInt();
	settings.visuals.esp.colors.local[3] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Local"][3].asInt();
	settings.visuals.esp.colors.skeleton[0] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Skeleton"][0].asInt();
	settings.visuals.esp.colors.skeleton[1] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Skeleton"][1].asInt();
	settings.visuals.esp.colors.skeleton[2] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Skeleton"][2].asInt();
	settings.visuals.esp.colors.skeleton[3] = load["Explit - Config"]["Visuals"]["Esp"]["Colors"]["Skeleton"][3].asInt();

	settings.visuals.glow.glow = load["Explit - Config"]["Visuals"]["Glow"]["Enable"].asBool();
	settings.visuals.glow.chickens= load["Explit - Config"]["Visuals"]["Glow"]["Chickens"].asBool();
	settings.visuals.glow.enemy= load["Explit - Config"]["Visuals"]["Glow"]["Enemies"].asBool();
	settings.visuals.glow.local= load["Explit - Config"]["Visuals"]["Glow"]["Local"].asBool();
	settings.visuals.glow.style = load["Explit - Config"]["Visuals"]["Glow"]["Style"].asInt();
	settings.visuals.glow.team =load["Explit - Config"]["Visuals"]["Glow"]["Team"].asBool();
	settings.visuals.glow.visible= load["Explit - Config"]["Visuals"]["Glow"]["Visible"].asBool();
	settings.visuals.glow.weapons=load["Explit - Config"]["Visuals"]["Glow"]["Dropped Weapons"].asBool();
	settings.visuals.glow.vulnerability =load["Explit - Config"]["Visuals"]["Glow"]["Vulnerability"].asBool();

	settings.visuals.glow.colors.team_invisible[0] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Team Invisible"][0].asInt();
	settings.visuals.glow.colors.team_invisible[1] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Team Invisible"][1].asInt();
	settings.visuals.glow.colors.team_invisible[2] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Team Invisible"][2].asInt();
	settings.visuals.glow.colors.team_invisible[3] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Team Invisible"][3].asInt();
	settings.visuals.glow.colors.team_visible[0] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Team Visible"][0].asInt();
	settings.visuals.glow.colors.team_visible[1] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Team Visible"][1].asInt();
	settings.visuals.glow.colors.team_visible[2] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Team Visible"][2].asInt();
	settings.visuals.glow.colors.team_visible[3] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Team Visible"][3].asInt();
	settings.visuals.glow.colors.enemy_invisible[0] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Enemy Invisible"][0].asInt();
	settings.visuals.glow.colors.enemy_invisible[1] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Enemy Invisible"][1].asInt();
	settings.visuals.glow.colors.enemy_invisible[2] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Enemy Invisible"][2].asInt();
	settings.visuals.glow.colors.enemy_invisible[3] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Enemy Invisible"][3].asInt();
	settings.visuals.glow.colors.enemy_visible[0] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Enemy Visible"][0].asInt();
	settings.visuals.glow.colors.enemy_visible[1] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Enemy Visible"][1].asInt();
	settings.visuals.glow.colors.enemy_visible[2] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Enemy Visible"][2].asInt();
	settings.visuals.glow.colors.enemy_visible[3] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Enemy Visible"][3].asInt();
	settings.visuals.glow.colors.chickens[0] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Chickens"][0].asInt();
	settings.visuals.glow.colors.chickens[1] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Chickens"][1].asInt();
	settings.visuals.glow.colors.chickens[2] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Chickens"][2].asInt();
	settings.visuals.glow.colors.chickens[3] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Chickens"][3].asInt();
	settings.visuals.glow.colors.weapons[0] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Dropped Weapons"][0].asInt();
	settings.visuals.glow.colors.weapons[1] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Dropped Weapons"][1].asInt();
	settings.visuals.glow.colors.weapons[2] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Dropped Weapons"][2].asInt();
	settings.visuals.glow.colors.weapons[3] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Dropped Weapons"][3].asInt();
	settings.visuals.glow.colors.vulnerability[0] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Vulnerability"][0].asInt();
	settings.visuals.glow.colors.vulnerability[1] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Vulnerability"][1].asInt();
	settings.visuals.glow.colors.vulnerability[2] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Vulnerability"][2].asInt();
	settings.visuals.glow.colors.vulnerability[3] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Vulnerability"][3].asInt();
	settings.visuals.glow.colors.local[0] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Local"][0].asInt();
	settings.visuals.glow.colors.local[1] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Local"][1].asInt();
	settings.visuals.glow.colors.local[2] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Local"][2].asInt();
	settings.visuals.glow.colors.local[3] = load["Explit - Config"]["Visuals"]["Glow"]["Colors"]["Local"][3].asInt();

	settings.visuals.dlights.enable = load["Explit - Config"]["Visuals"]["DLights"]["Enable"].asBool();
	settings.visuals.dlights.enemy =load["Explit - Config"]["Visuals"]["DLights"]["Enemies"].asBool();
	settings.visuals.dlights.local=load["Explit - Config"]["Visuals"]["DLights"]["Local"].asBool();
	settings.visuals.dlights.team=load["Explit - Config"]["Visuals"]["DLights"]["Team"].asBool();
	settings.visuals.dlights.radius = load["Explit - Config"]["Visuals"]["DLights"]["Radius"].asFloat();

	settings.visuals.dlights.colors.local[0] = load["Explit - Config"]["Visuals"]["DLights"]["Colors"]["Local"][0].asInt();
	settings.visuals.dlights.colors.local[1] = load["Explit - Config"]["Visuals"]["DLights"]["Colors"]["Local"][1].asInt();
	settings.visuals.dlights.colors.local[2] = load["Explit - Config"]["Visuals"]["DLights"]["Colors"]["Local"][2].asInt();
	settings.visuals.dlights.colors.team[0] = load["Explit - Config"]["Visuals"]["DLights"]["Colors"]["Team"][0].asInt();
	settings.visuals.dlights.colors.team[1] = load["Explit - Config"]["Visuals"]["DLights"]["Colors"]["Team"][1].asInt();
	settings.visuals.dlights.colors.team[2] = load["Explit - Config"]["Visuals"]["DLights"]["Colors"]["Team"][2].asInt();
	settings.visuals.dlights.colors.enemy[0] = load["Explit - Config"]["Visuals"]["DLights"]["Colors"]["Enemy"][0].asInt();
	settings.visuals.dlights.colors.enemy[1] = load["Explit - Config"]["Visuals"]["DLights"]["Colors"]["Enemy"][1].asInt();
	settings.visuals.dlights.colors.enemy[2] = load["Explit - Config"]["Visuals"]["DLights"]["Colors"]["Enemy"][2].asInt();

	settings.visuals.others.watermark = load["Explit - Config"]["Visuals"]["Others"]["Watermark"].asBool();

	settings.misc.movement.bunnyhop = load["Explit - Config"]["Misc"]["Movement"]["Bunnyhop"].asBool();

	for (int i = 1; i <= 64; i++)
	{
		const auto weapon_name = g_utils.weapon_config_name(i);

		if (weapon_name == "unknown")
			continue;

		settings.legitbot.triggerbot[i].enable = load["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Enable"].asBool();
		settings.legitbot.triggerbot[i].key_1 = load["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Key 1"].asInt();
		settings.legitbot.triggerbot[i].key_2 = load["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Key 2"].asInt();
		settings.legitbot.triggerbot[i].flash = load["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Flash Check"].asBool();
		settings.legitbot.triggerbot[i].smoke = load["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Smoke Check"].asBool();
		settings.legitbot.triggerbot[i].jump = load["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Jump Check"].asBool();
		settings.legitbot.triggerbot[i].scope = load["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Scope Check"].asBool();
		settings.legitbot.triggerbot[i].sleep_before = load["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Sleep Before Shot"].asInt();
		settings.legitbot.triggerbot[i].sleep_between=load["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Sleep Between Shots"].asInt();
		settings.legitbot.triggerbot[i].hit_head=load["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Hitbox Head"].asBool();
		settings.legitbot.triggerbot[i].hit_body=load["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Hitbox Body"].asBool();
		settings.legitbot.triggerbot[i].hit_arms=load["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Hitbox Arms"].asBool();
		settings.legitbot.triggerbot[i].hit_legs=load["Explit - Config"]["Legitbot"]["Triggerbot"][weapon_name]["Hitbox Legs"].asBool();
	}

	in.close();
}