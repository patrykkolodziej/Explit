#include "chams.hpp"
c_chams g_chams;

void c_chams::scene_end_start()
{
	if (g_config.settings.visuals.chams.chams)
	{
		static auto chams_material = g_interfaces.p_material_system->findmaterial("debug/debugdrawflat", TEXTURE_GROUP_MODEL);
		
		chams_material->setmaterialvarflag(material_var_ignorez, !g_config.settings.visuals.chams.visible);
		chams_material->alphamodulate(1.f);
		
		for (int i = 1; i <= g_interfaces.p_engine->get_max_clients(); i++)
		{
			const auto p_entity = reinterpret_cast<c_base_entity*>(g_interfaces.p_entity_list->get_client_entity((i)));
			if (!p_entity)
				continue;
			if (p_entity->is_dormant())
				continue;
			if (p_entity == g_interfaces.g_local_player && !g_config.settings.visuals.chams.local)
				continue;
			if (g_config.settings.visuals.chams.visible && !g_interfaces.g_local_player->is_visible(p_entity))
				continue;

			if (g_config.settings.visuals.chams.enemy && p_entity->m_iteamnum() != g_interfaces.g_local_player->m_iteamnum() && p_entity->is_valid())
			{
				chams_material->colormodulate(g_config.settings.visuals.chams.colors.enemy_visible[0] / 255.f, g_config.settings.visuals.chams.colors.enemy_visible[1] / 255.f, g_config.settings.visuals.chams.colors.enemy_visible[2] / 255.f);
				g_interfaces.p_render_view->setcolormodulation(g_config.settings.visuals.chams.colors.enemy_visible[0] / 255.f, g_config.settings.visuals.chams.colors.enemy_visible[1] / 255.f, g_config.settings.visuals.chams.colors.enemy_visible[2] / 255.f);
				g_interfaces.p_model_render->forcedmaterialoverride(chams_material);
				p_entity->draw_model(0x1, 255);
			}
			if (g_config.settings.visuals.chams.team && p_entity->m_iteamnum() == g_interfaces.g_local_player->m_iteamnum() && p_entity->is_valid())
			{
				chams_material->colormodulate(g_config.settings.visuals.chams.colors.team_visible[0] / 255.f, g_config.settings.visuals.chams.colors.team_visible[1] / 255.f, g_config.settings.visuals.chams.colors.team_visible[2] / 255.f);
				g_interfaces.p_render_view->setcolormodulation(g_config.settings.visuals.chams.colors.team_visible[0] / 255.f, g_config.settings.visuals.chams.colors.team_visible[1] / 255.f, g_config.settings.visuals.chams.colors.team_visible[2] / 255.f);
				g_interfaces.p_model_render->forcedmaterialoverride(chams_material);
				p_entity->draw_model(0x1, 255);
			}
			if (p_entity == g_interfaces.g_local_player)
			{
				chams_material->colormodulate(g_config.settings.visuals.chams.colors.local[0] / 255.f, g_config.settings.visuals.chams.colors.local[1] / 255.f, g_config.settings.visuals.chams.colors.local[2] / 255.f);
				g_interfaces.p_render_view->setcolormodulation(g_config.settings.visuals.chams.colors.local[0] / 255.f, g_config.settings.visuals.chams.colors.local[1] / 255.f, g_config.settings.visuals.chams.colors.local[2] / 255.f);
				g_interfaces.p_model_render->forcedmaterialoverride(chams_material);
				p_entity->draw_model(0x1, 255);
			}

			g_interfaces.p_model_render->forcedmaterialoverride(nullptr);
		}
	}
}
