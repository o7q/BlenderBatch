#pragma once

#include <string>

const std::string VERSION = "v2.0.0";

struct QueueConfig
{
	std::string BLEND_FILE;
	std::string RENDER_ENGINE;
	std::string RENDER_MODE;
	std::string START_FRAME;
	std::string END_FRAME;
};