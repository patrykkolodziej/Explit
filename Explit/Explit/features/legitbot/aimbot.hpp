#pragma once
#include "../../sdk/sdk.hpp"

class c_aimbot 
{
public:
	void start(c_user_cmd* p_cmd);
private:
	c_base_entity* best_target;
	int best_hitbox;
	Vector curve_angle(const Vector calced_angle);
	Vector smooth_angle(const Vector smooth_angle);
	Vector error_ange(const Vector calc_angle);
};
extern c_aimbot g_aimbot;