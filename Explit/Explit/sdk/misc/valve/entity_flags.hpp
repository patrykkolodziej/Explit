#pragma once
enum entity_flags
{
	fl_on_ground = (1 << 0),
	fl_ducking = (1 << 1),
	fl_water_jump = (1 << 2),
	fl_on_train = (1 << 3),
	fl_in_rain = (1 << 4),
	fl_frozen = (1 << 5),
	fl_atcontrols = (1 << 6),
	fl_client = (1 << 7),
	fl_fakeclient = (1 << 8),
	max_entity_flags
};