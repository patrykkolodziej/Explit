#include "triggerbot.hpp"
c_triggerbot g_triggerbot;

void c_triggerbot::start(c_user_cmd* p_cmd)
{
	if (g_config.settings.legitbot.triggerbotb)
	{
		if(g_interfaces.g_local_player->m_ilifestate() == life_alive)
		{ 
			const auto weapon = g_interfaces.g_local_player->get_weapon();

			if (weapon->is_useable_weapon())
			{
				const auto weapon_id = weapon->get_weapon_id();
				
				if (g_config.settings.legitbot.triggerbot[weapon_id].enable)
				{
					static auto last_time = 0.f;
					const auto now = g_interfaces.g_local_player->m_ntickbase() * g_interfaces.p_global_vars->interval_per_tick;
					auto active = false;

					if (last_time > now)
						last_time = 0.f;

					switch (g_config.settings.legitbot.trigger_mode)
					{
						case 0:
						{
							active = GetAsyncKeyState(g_config.settings.legitbot.triggerbot[weapon_id].key_1) || GetAsyncKeyState(g_config.settings.legitbot.triggerbot[weapon_id].key_2);
							break;
						}
						case 1:
						{
							active = true;
							break;
						}
					}

					if (active)
					{
						const auto delay = g_interfaces.g_local_player->m_ishotsfired() > 0 ? g_config.settings.legitbot.triggerbot[weapon_id].sleep_between : g_config.settings.legitbot.triggerbot[weapon_id].sleep_before;

						if (now - last_time >= delay / 1000.f)
						{
							if (weapon->is_sniper() && g_config.settings.legitbot.triggerbot[weapon_id].scope && !g_interfaces.g_local_player->m_bisscoped())
								return;
							if (g_interfaces.g_local_player->m_flflashduration() && g_config.settings.legitbot.triggerbot[weapon_id].flash)
								return;
							if (!(g_interfaces.g_local_player->m_fflags() & fl_on_ground) && g_config.settings.legitbot.triggerbot[weapon_id].jump)
								return;

							const auto range = g_math.angle_vectors(p_cmd->view_angles) * 8192.0f;

							if (g_config.settings.legitbot.triggerbot[weapon_id].smoke && g_utils.is_line_goes_through_smoke(g_interfaces.g_local_player->get_eye_position(), g_interfaces.g_local_player->get_eye_position() + range))
								return;

							c_game_trace game_trace;
							ray_t ray;
							c_trace_filter filter;
							filter.pskip = g_interfaces.g_local_player;

							const auto trace_destination = g_interfaces.g_local_player->get_eye_position() + range;
							ray.init(g_interfaces.g_local_player->get_eye_position(), trace_destination);
							g_interfaces.p_engine_trace->trace_ray(ray, mask_shot | contents_grate, &filter, &game_trace);
							if (!game_trace.hit_entity || !reinterpret_cast<c_base_entity*>(game_trace.hit_entity)->is_player())
								return;

							auto hit = false;

							switch (game_trace.hitgroup)
							{
							case hitgroup_head:
								if (g_config.settings.legitbot.triggerbot[weapon_id].hit_head) hit = true;
								break;
							case hitgroup_chest:
								if (g_config.settings.legitbot.triggerbot[weapon_id].hit_body) hit = true;
								break;
							case hitgroup_stomach:
								if (g_config.settings.legitbot.triggerbot[weapon_id].hit_body) hit = true;
								break;
							case hitgroup_leftarm:
								if (g_config.settings.legitbot.triggerbot[weapon_id].hit_arms) hit = true;
								break;
							case hitgroup_rightarm:
								if (g_config.settings.legitbot.triggerbot[weapon_id].hit_arms) hit = true;
								break;
							case hitgroup_leftleg:
								if (g_config.settings.legitbot.triggerbot[weapon_id].hit_legs) hit = true;
								break;
							case hitgroup_rightleg:
								if (g_config.settings.legitbot.triggerbot[weapon_id].hit_legs) hit = true;
								break;
							}

							if (hit && weapon->can_shoot())
							{
								p_cmd->buttons |= in_attack;
								last_time = 0;
							}
							else
							{
								last_time = now;
							}
						}
					}
				}
			}
		}
	}
}