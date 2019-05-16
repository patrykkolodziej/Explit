#pragma once
#include "../../sdk.hpp"

constexpr auto in_attack = (1 << 0);
constexpr auto in_jump = (1 << 1);
constexpr auto in_duck = (1 << 2);
constexpr auto in_forward = (1 << 3);
constexpr auto in_back = (1 << 4);
constexpr auto in_use = (1 << 5);
constexpr auto in_cancel = (1 << 6);
constexpr auto in_left = (1 << 7);
constexpr auto in_right = (1 << 8);
constexpr auto in_moveleft = (1 << 9);
constexpr auto in_moveright = (1 << 10);
constexpr auto in_attack2 = (1 << 11);
constexpr auto in_run = (1 << 12);
constexpr auto in_reload = (1 << 13);
constexpr auto in_alt1 = (1 << 14);
constexpr auto in_alt2 = (1 << 15);
constexpr auto in_score = (1 << 16);
constexpr auto in_speed = (1 << 17);
constexpr auto in_walk = (1 << 18);
constexpr auto in_zoom = (1 << 19);
constexpr auto in_weapon1 = (1 << 20);
constexpr auto in_weapon2 = (1 << 21);
constexpr auto in_bullrush = (1 << 22);
constexpr auto in_grenade1 = (1 << 23);
constexpr auto in_grenade2 = (1 << 24);
constexpr auto in_lookspin = (1 << 25);

class c_user_cmd
{
public:
	virtual ~c_user_cmd() {};
	int       command_number;    
	int       tick_count;        
	Vector    view_angles;
	Vector    aim_direction;       
	float     forward_move;       
	float     side_move;           
	float     up_move;             
	int       buttons;          
	byte      impulse;          
	int       weapon_select;       
	int       weapon_sub_type;      
	int       random_seed;      
	short     mouse_dx;           
	short     mouse_dy;           
	bool      has_been_predicted;   
	char      pad_0x4c[0x18];

};