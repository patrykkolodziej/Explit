#pragma once
#include "../../sdk/sdk.hpp"

class c_triggerbot
{
public:
	void start(c_user_cmd* p_cmd);
};
extern c_triggerbot g_triggerbot;