#include "bunnyhop.hpp"
c_bunny_hop g_bunny_hop;

void c_bunny_hop::start(c_user_cmd* p_cmd)
{
	if (g_interfaces.g_local_player->get_move_type() == move_type_noclip)
	{
		return;
	}
	if (p_cmd->buttons & in_jump && !(g_interfaces.g_local_player->m_fflags() & fl_on_ground)) 
	{
		p_cmd->buttons &= ~in_jump;
	}
}