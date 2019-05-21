#pragma once
#include "../../sdk/sdk.hpp"

class c_aimbot 
{
public:
	void start(c_user_cmd* p_cmd);
private:
	c_base_entity* best_target;
	int best_hitbox;
	int weapon_id;
	Vector curve_angle(const Vector calced_angle);
	Vector smooth_angle(const Vector calced_angle);
	Vector error_angle(const Vector calced_angle);
};
extern c_aimbot g_aimbot;