#include "math.hpp"
c_math g_math;

bool c_math::screen_transform(const Vector& in, Vector& out)
{
	static auto& w2smatrix = g_interfaces.p_engine->world_to_screen_matrix();

	out.x = w2smatrix.m[0][0] * in.x + w2smatrix.m[0][1] * in.y + w2smatrix.m[0][2] * in.z + w2smatrix.m[0][3];
	out.y = w2smatrix.m[1][0] * in.x + w2smatrix.m[1][1] * in.y + w2smatrix.m[1][2] * in.z + w2smatrix.m[1][3];
	out.z = 0.0f;

	float w = w2smatrix.m[3][0] * in.x + w2smatrix.m[3][1] * in.y + w2smatrix.m[3][2] * in.z + w2smatrix.m[3][3];

	if (w < 0.001f) {
		out.x *= 100000;
		out.y *= 100000;
		return false;
	}

	out.x /= w;
	out.y /= w;

	return true;
}

bool c_math::world_to_screen(const Vector& in, Vector& out)
{
	if (screen_transform(in, out)) {
		int w, h;
		g_interfaces.p_engine->get_screen_size(w, h);

		out.x = (w / 2.0f) + (out.x * w) / 2.0f;
		out.y = (h / 2.0f) - (out.y * h) / 2.0f;

		return true;
	}
	return false;
}
void c_math::vector_transform(const Vector& in1, const matrix3x4_t& in2, Vector& out)
{
	out[0] = in1.Dot(in2[0]) + in2[0][3];
	out[1] = in1.Dot(in2[1]) + in2[1][3];
	out[2] = in1.Dot(in2[2]) + in2[2][3];
}
void c_math::sin_cos(const float radians, float& sine, float& cosine)
{
	sine = sin(radians);
	cosine = cos(radians);
}
double c_math::deg_to_rad(const double deg)
{
	return deg * static_cast<float>(PI) / 180;
}
Vector c_math::angle_vectors(const Vector& in)
{
	const auto x = cos(deg_to_rad(in.x)) * cos(deg_to_rad(in.y));
	const auto y = cos(deg_to_rad(in.x)) * sin(deg_to_rad(in.y));
	const auto z = -sin(deg_to_rad(in.x));
	return Vector(x, y, z);
}