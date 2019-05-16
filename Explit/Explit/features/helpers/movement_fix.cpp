#include "movement_fix.hpp"
c_movement_fix g_movement_fix;

void c_movement_fix::start(const Vector angle, c_user_cmd* p_cmd, const float forward_move, const float side_move)
{
	float delta_view, f1, f2;

	if (angle.y < 0.f)
		f1 = 360.0f + angle.y;
	else
		f1 = angle.y;

	if (p_cmd->view_angles.y < 0.0f)
		f2 = 360.0f + p_cmd->view_angles.y;
	else
		f2 = p_cmd->view_angles.y;

	if (f2 < f1)
		delta_view = abs(f2 - f1);
	else
		delta_view = 360.0f - abs(f1 - f2);

	delta_view = 360.0f - delta_view;

	p_cmd->forward_move = cos(g_math.deg_to_rad(delta_view)) * forward_move + cos(g_math.deg_to_rad(delta_view + 90.f)) * side_move;
	p_cmd->side_move = sin(g_math.deg_to_rad(delta_view)) * forward_move + sin(g_math.deg_to_rad(delta_view + 90.f)) * side_move;
}