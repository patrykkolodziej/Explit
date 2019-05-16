#pragma once
#include "../../sdk/sdk.hpp"

class c_movement_fix
{
public:
	void start(const Vector angle, c_user_cmd* p_cmd, const float forward_move, const float side_move);
};
extern c_movement_fix g_movement_fix;