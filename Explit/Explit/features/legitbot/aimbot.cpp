#include "aimbot.hpp"
c_aimbot g_aimbot;

Vector c_aimbot::curve_angle(const Vector calced_angle)
{
	Vector view_angle;
	g_interfaces.p_engine->get_view_angles(view_angle);

	auto curve_delta = calced_angle - view_angle;

	curve_delta += Vector(curve_delta.y / g_config.settings.legitbot.aimbot[weapon_id].curve_x, curve_delta.x / g_config.settings.legitbot.aimbot[weapon_id].curve_y, 0.f);

	const auto return_angle = view_angle + curve_delta;

	return_angle.Clamp();

	return return_angle;
}

Vector c_aimbot::smooth_angle(const Vector calced_angle)
{
	Vector view_angle;
	g_interfaces.p_engine->get_view_angles(view_angle);

	const auto smooth_delta = view_angle - calced_angle;
	const auto return_angle = Vector(view_angle.x - smooth_delta.x / g_config.settings.legitbot.aimbot[weapon_id].smooth, view_angle.x - smooth_delta.x / g_config.settings.legitbot.aimbot[weapon_id].smooth, 0.f);

	return_angle.Clamp();
	return return_angle;
}

Vector c_aimbot::error_angle(const Vector calced_angle)
{
	Vector random;

	random.x = g_math.random(-1.0f, 1.0f);
	random.y = g_math.random(-1.0f, 1.0f);
	random.z = 0;

	random *= g_config.settings.legitbot.aimbot[weapon_id].error_amount;

	const auto return_angle = calced_angle + random;

	return_angle.Clamp();
	return return_angle;
}

