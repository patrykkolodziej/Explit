#include "auto_strafe.hpp"
c_auto_strafe g_auto_strafe;

void c_auto_strafe::start(c_user_cmd* p_cmd)
{
	if (g_config.settings.misc.movement.auto_strafe)
	{
		switch (g_config.settings.misc.movement.autostrafe_mode)
		{
			case 0:
			{
				if (g_interfaces.g_local_player->m_fflags() & fl_on_ground)
					return;

				if (p_cmd->buttons & in_forward || p_cmd->buttons & in_back || p_cmd->buttons & in_moveleft || p_cmd->buttons & in_moveright)
					return;

				if (p_cmd->mouse_dx <= 1 && p_cmd->mouse_dx >= -1)
					return;

				p_cmd->side_move = p_cmd->mouse_dx < 0.f ? -250.f : 250.f;
			}
			case 1:
			{
				static bool left_right;
				bool in_move = p_cmd->buttons & in_forward || p_cmd->buttons & in_back || p_cmd->buttons & in_moveleft || p_cmd->buttons & in_moveright;

				if (p_cmd->buttons & in_forward && g_interfaces.g_local_player->m_vecvelocity().Length() <= 50.0f)
					p_cmd->forward_move = 250.0f;

				float yaw_change = 0.0f;

				if (g_interfaces.g_local_player->m_vecvelocity().Length() > 50.f)
					yaw_change = 30.0f * fabsf(30.0f / g_interfaces.g_local_player->m_vecvelocity().Length());


				Vector view_angles;
				g_interfaces.p_engine->get_view_angles(view_angles);

				if (!(g_interfaces.g_local_player->m_fflags() & fl_on_ground) && !in_move)
				{
					if (left_right || p_cmd->mouse_dx > 1)
					{
						view_angles.y += yaw_change;
						p_cmd->side_move = 250.0f;
					}
					else if (!left_right || p_cmd->mouse_dx < 1)
					{
						view_angles.y -= yaw_change;
						p_cmd->side_move = -250.0f;
					}

					left_right = !left_right;
				}

				g_movement_fix.start(view_angles, p_cmd, p_cmd->forward_move, p_cmd->side_move);
			}
		}

	}
}