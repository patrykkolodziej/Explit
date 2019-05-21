#include "utils.hpp"
c_utils g_utils;

uintptr_t c_utils::find_signature(const char* module, const char* signature)
{
	const char* pat = signature;
	DWORD firstmatch = 0;
	DWORD rangestart = (DWORD)GetModuleHandleA(module);
	MODULEINFO miModInfo;

	GetModuleInformation(GetCurrentProcess(), (HMODULE)rangestart, &miModInfo, sizeof(MODULEINFO));

	DWORD rangeEnd = rangestart + miModInfo.SizeOfImage;

	for (DWORD pCur = rangestart; pCur < rangeEnd; pCur++)
	{
		if (!*pat)
			return firstmatch;

		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == GET_BYTE(pat))
		{
			if (!firstmatch)
				firstmatch = pCur;

			if (!pat[2])
				return firstmatch;

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
				pat += 3;

			else
				pat += 2;
		}
		else
		{
			pat = signature;
			firstmatch = 0;
		}
	}

	return 0u;
}

bool c_utils::is_line_goes_through_smoke(Vector source, Vector destination)
{
	static auto offset = find_signature("client_panorama.dll", "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0");

	return reinterpret_cast<line_goes_through_smoke_fn>(offset)(source, destination, true);
}

std::string c_utils::weapon_config_name(const int i)
{
	switch (i)
	{
	case 1:
		return "deagle";
	case 2:
		return "elite";
	case 3:
		return "fiveseven";
	case 4:
		return "glock";
	case 7:
		return "ak47";
	case 8:
		return "aug";
	case 9:
		return "awp";
	case 10:
		return "famas";
	case 11:
		return "g3sg1";
	case 13:
		return "galil";
	case 14:
		return "m249";
	case 16:
		return "m4a4";
	case 17:
		return "mac10";
	case 19:
		return "p90";
	case 23:
		return "mp5sd";
	case 24:
		return "ump45";
	case 25:
		return "xm1014";
	case 26:
		return "bizon";
	case 27:
		return "mag7";
	case 28:
		return "negev";
	case 29:
		return "sawedoff";
	case 30:
		return "tec9";
	case 32:
		return "p2000";
	case 33:
		return "mp7";
	case 34:
		return "mp9";
	case 35:
		return "nova";
	case 36:
		return "p250";
	case 38:
		return "scar20";
	case 39:
		return "sg553";
	case 40:
		return "ssg08";
	case 60:
		return "m4a1s";
	case 61:
		return "usps";
	case 63:
		return "cz75";
	case 64:
		return "revolver";
	default:
		return "unknown";
	}
}