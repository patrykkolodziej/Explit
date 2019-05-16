#pragma once
#include "../sdk.hpp"

class c_math {
private:
	bool screen_transform(const Vector& in, Vector& out);
public:
	void vector_transform(const Vector& in1, const matrix3x4_t& in2, Vector& out);
	bool world_to_screen(const Vector& in, Vector& out);
	Vector angle_vectors(const Vector& in);
	void sin_cos(const float radians, float& sine, float& cosine);
	double deg_to_rad(const double deg);
};
extern c_math g_math;