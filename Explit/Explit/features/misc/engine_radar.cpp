#include "engine_radar.hpp"
c_engine_radar g_engine_radar;

void c_engine_radar::start()
{
	static auto offset = c.netvar->get_offset("DT_BaseEntity", "m_bSpotted");

	for (int i = 1; i <= g_interfaces.p_engine->get_max_clients(); i++) 
	{
		const auto p_entity = reinterpret_cast<c_base_entity*>(g_interfaces.p_entity_list->get_client_entity((i)));
		if (!p_entity)
			continue;
		if (p_entity->is_dormant())
			continue;

		//p_entity + offset = true;
	}
}