#include "c_base_entity.hpp"

const matrix3x4_t& c_base_entity::m_rgflcoordinateframe()
{
	static auto offset = c.netvar->get_offset("DT_BaseEntity","m_CollisionGroup", -0x30);
	return *(matrix3x4_t*)((uintptr_t)this + offset);
}

Vector c_base_entity::m_vecorigin()
{
	static auto offset = c.netvar->get_offset("DT_BaseEntity", "m_vecOrigin");
	return *reinterpret_cast<Vector*>((uintptr_t)this + offset);
}

int c_base_entity::get_index()
{
	return *reinterpret_cast<int*>((uintptr_t)this + 0x64);
}

std::string c_base_entity::get_name()
{
	player_info_t info;
	g_interfaces.p_engine->getplayerinfo(this->get_index(), &info);
	return info.szname;
}

int c_base_entity::m_howner()
{
	return *reinterpret_cast<int*>((uintptr_t)this + 0x148);
}

int c_base_entity::m_iteamnum()
{
	static auto offset = c.netvar->get_offset("DT_BaseEntity", "m_iTeamNum");
	return *reinterpret_cast<int*>((uintptr_t)this + offset);
}

int c_base_entity::m_ihealth()
{
	static auto offset = c.netvar->get_offset("DT_BasePlayer", "m_iHealth");
	return *reinterpret_cast<int*>((uintptr_t)this + offset);
}

int c_base_entity::m_iaccount()
{
	static auto offset = c.netvar->get_offset("DT_CSPlayer", "m_iAccount");
	return *reinterpret_cast<int*>((uintptr_t)this + offset);
}

int c_base_entity::get_distance()
{
	const auto local_origin = g_interfaces.g_local_player->m_vecorigin();
	const auto player_origin = this->m_vecorigin();
	return static_cast<int>(sqrt(pow(local_origin.x - player_origin.x, 2) + pow(local_origin.y - player_origin.y, 2) + pow(local_origin.z - player_origin.z, 2)) * 0.0254f);
}

bool c_base_entity::m_bhashelmet()
{
	static auto offset = c.netvar->get_offset("DT_CSPlayer", "m_bHasHelmet");
	return *reinterpret_cast<bool*>((uintptr_t)this + offset);
}

c_base_handle c_base_entity::m_hactiveweapon()
{
	static auto offset = c.netvar->get_offset("DT_BasePlayer", "m_hActiveWeapon");
	return *reinterpret_cast<c_base_handle*>((uintptr_t)this + offset);
}

c_base_weapon* c_base_entity::get_weapon()
{
	return (c_base_weapon*)g_interfaces.p_entity_list->get_client_entity_from_handle((c_base_handle)m_hactiveweapon());
}

int c_base_entity::m_armorvalue()
{
	static auto offset = c.netvar->get_offset("DT_CSPlayer", "m_ArmorValue");
	return *reinterpret_cast<int*>((uintptr_t)this + offset);
}

int c_base_entity::m_ntickbase()
{
	static auto offset = c.netvar->get_offset("DT_BasePlayer", "m_nTickBase");
	return *reinterpret_cast<int*>((uintptr_t)this + offset);
}

int32_t c_base_entity::m_ilifestate()
{
	static auto offset = c.netvar->get_offset("DT_BasePlayer", "m_lifeState");
	return *reinterpret_cast<int32_t*>((uintptr_t)this + offset);
}

bool c_base_entity::is_valid()
{
	return (is_player() && !is_dormant() && m_ilifestate() == life_alive);
}

bool c_base_entity::is_player()
{
	return vfunc<155, bool>(this);
}

bool c_base_entity::is_weapon()
{
	return vfunc<163, bool>(this) && m_howner() == -1;
}

bool c_base_entity::is_nade()
{
	return false;
}

bool c_base_entity::is_chicken()
{
	return get_client_class()->class_id == class_id::cchicken;
}

bool c_base_entity::is_c4()
{
	return get_client_class()->class_id == class_id::cplantedc4 || get_client_class()->class_id == class_id::cc4;
}

int32_t c_base_entity::get_move_type()
{
	return *reinterpret_cast<int32_t*>((uintptr_t)this + 0x258);
}

int c_base_entity::m_fflags()
{
	static auto offset = c.netvar->get_offset("DT_BasePlayer", "m_fFlags");
	return *reinterpret_cast<int*>((uintptr_t)this + offset);
}

Vector c_base_entity::m_vecviewoffset()
{
	static auto offset = c.netvar->get_offset("DT_CSPlayer", "m_vecViewOffset[0]");
	return *reinterpret_cast<Vector*>((uintptr_t)this + offset);
}

Vector c_base_entity::get_bone_position(const int bone)
{
	matrix3x4_t bone_matrix[MAXSTUDIOBONES];

	if (setup_bones(bone_matrix, MAXSTUDIOBONES, BONE_USED_BY_ANYTHING, 0.0f)) {
		return Vector(bone_matrix[bone][0][3], bone_matrix[bone][1][3], bone_matrix[bone][2][3]);
	}

	return Vector{};
}

Vector c_base_entity::get_hitbox_position(const int hitbox)
{
	matrix3x4_t bone_matrix[MAXSTUDIOBONES];

	if (setup_bones(bone_matrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.0f)) 
	{
		if (const auto studio_model = g_interfaces.p_model_info_client->getstudiomodel(get_model()); studio_model)
		{
			if (const auto p_hitbox = studio_model->phitboxset(0)->phitbox(hitbox); p_hitbox)
			{
				Vector min, max;

				g_math.vector_transform(p_hitbox->bbmin, bone_matrix[p_hitbox->bone], min);
				g_math.vector_transform(p_hitbox->bbmax, bone_matrix[p_hitbox->bone], max);

				return (min + max) / 2.0f;
			}
		}
	}
	return Vector{};
}

bool c_base_entity::is_visible(c_base_entity* p_player)
{
	c_game_trace game_trace;
	ray_t ray;
	c_trace_filter filter;
	filter.pskip = this;

	auto visible = false;

	for (int i = 0; i < hitbox_max; i++)
	{
		const auto trace_pos = p_player->get_hitbox_position(i);
		const auto smoke = g_utils.is_line_goes_through_smoke(get_eye_position(), trace_pos);

		ray.init(get_eye_position(), trace_pos);
		g_interfaces.p_engine_trace->trace_ray(ray, mask_shot | contents_grate, &filter, &game_trace);

		visible = (game_trace.hit_entity == p_player && !smoke) || (game_trace.fraction > 0.97f && !smoke);
	}

	return visible;
}

Vector c_base_entity::get_eye_position()
{
	return m_vecorigin() + m_vecviewoffset();
}

int c_base_entity::m_ishotsfired()
{
	static auto offset = c.netvar->get_offset("DT_CSPlayer", "m_iShotsFired");
	return *reinterpret_cast<int*>((uintptr_t)this + offset);
}

float c_base_entity::m_flflashduration()
{
	static auto offset = c.netvar->get_offset("DT_CSPlayer", "m_flFlashDuration");
	return *reinterpret_cast<float*>((uintptr_t)this + offset);
}

bool c_base_entity::m_bisscoped()
{
	static auto offset = c.netvar->get_offset("DT_CSPlayer", "m_bIsScoped");
	return *reinterpret_cast<bool*>((uintptr_t)this + offset);
}

Vector c_base_entity::m_vecvelocity()
{
	static auto offset = c.netvar->get_offset("DT_CSPlayer", "m_vecVelocity[0]");
	return *reinterpret_cast<Vector*>((uintptr_t)this + offset);
}