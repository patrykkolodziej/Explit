#pragma once
#include "../sdk.hpp"

class c_base_weapon;

class c_base_entity : public i_client_entity
{
private:
	c_base_handle m_hactiveweapon();
public:
	const matrix3x4_t& m_rgflcoordinateframe();
	int get_index();
	c_base_weapon* get_weapon();
	std::string get_name();
	bool is_valid();
	int m_ihealth();
	int32_t m_ilifestate();
	int m_iaccount();
	int get_distance();
	bool m_bhashelmet();
	int m_armorvalue();
	int m_howner();
	int m_iteamnum();
	bool is_player();
	bool is_weapon();
	bool is_nade();
	bool is_chicken();
	Vector m_vecviewoffset();
	int m_fflags();
	bool is_c4();
	Vector m_vecorigin();
	Vector get_bone_position(const int bone);
	Vector get_hitbox_position(const int hitbox);
	bool is_visible(c_base_entity* p_player);
	int32_t get_move_type();
};