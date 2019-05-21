#include "bunny_hop.hpp"
c_bunny_hop g_bunny_hop;

void c_bunny_hop::start(c_user_cmd* p_cmd)
{
	if (g_config.settings.misc.movement.bunnyhop)
	{
		switch (g_config.settings.misc.movement.bunnyhop_mode)
		{
		case 0:
		{
			if (p_cmd->buttons & in_jump && !(g_interfaces.g_local_player->m_fflags() & fl_on_ground) && g_interfaces.g_local_player->get_move_type() != move_type_noclip)
			{
				p_cmd->buttons &= ~in_jump;
			}
		}
		case 1:
		{
			static int hops_restricted = 0;
			static int hops_hit = 0;
			if (!(p_cmd->buttons & in_jump)
				|| (g_interfaces.g_local_player->get_move_type() & move_type_ladder))
				return;
			if (!(g_interfaces.g_local_player->m_fflags() & fl_on_ground))
			{
				p_cmd->buttons &= ~in_jump;
				hops_restricted = 0;
			}
			else if ((rand() % 100 > 80	&& hops_restricted < 6)|| (6 > 0&& hops_hit > 6))
			{
				p_cmd->buttons &= ~in_jump;
				hops_restricted++;
				hops_hit = 0;
			}
			else
				hops_hit++;
		}
		}
	}
}