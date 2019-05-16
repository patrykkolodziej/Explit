#include "c_base_weapon.hpp"

weapon_data_t* c_base_weapon::get_weapon_info()
{
	if (!this || this == NULL)
		return NULL;
	 
	return vfunc<454, weapon_data_t*>(this);
}

int c_base_weapon::m_iclip1()
{
	static auto offset = c.netvar->get_offset("DT_BaseCombatWeapon", "m_iClip1");
	return *reinterpret_cast<int*>((uintptr_t)this + offset);
}

float c_base_weapon::m_flnextprimaryattack()
{
	static auto offset = c.netvar->get_offset("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
	return *reinterpret_cast<float*>((uintptr_t)this + offset);
}

short c_base_weapon::get_weapon_id()
{
	static auto offset = c.netvar->get_offset("DT_BaseAttributableItem", "m_iItemDefinitionIndex");
	return *reinterpret_cast<short*>((uintptr_t)this + offset);
}

bool c_base_weapon::is_useable_weapon()
{
	if (!this)
		return false;

	switch (get_weapon_id())
	{
	case weapon_deagle:
	case weapon_elite:
	case weapon_fiveseven:
	case weapon_glock:
	case weapon_ak47:
	case weapon_aug:
	case weapon_awp:
	case weapon_famas:
	case weapon_g3sg1:
	case weapon_galil:
	case weapon_m249:
	case weapon_m4a4:
	case weapon_mac10:
	case weapon_p90:
	case weapon_ump45:
	case weapon_xm1014:
	case weapon_bizon:
	case weapon_mag7:
	case weapon_negev:
	case weapon_sawedoff:
	case weapon_tec9:
	case weapon_p2000:
	case weapon_mp7:
	case weapon_mp9:
	case weapon_nova:
	case weapon_p250:
	case weapon_scar20:
	case weapon_sg553:
	case weapon_ssg08:
	case weapon_m4a1s:
	case weapon_usps:
	case weapon_cz75:
	case weapon_revolver:
		return true;
	default:
		return false;
	}
}

bool c_base_weapon::is_sniper()
{
	if (!this)
		return false;

	switch (get_weapon_id())
	{
	case weapon_awp:
	case weapon_scar20:
	case weapon_ssg08:
	case weapon_g3sg1:
		return true;
	default:
		return false;
	}
}

bool c_base_weapon::can_shoot()
{
	if (!this)
		return false;

	if (m_iclip1() < 1)
		return false;
	
	const auto server_time = g_interfaces.g_local_player->m_ntickbase() * g_interfaces.p_global_vars->interval_per_tick;
	
	if (m_flnextprimaryattack() > server_time)
		return false;

	return true;
}