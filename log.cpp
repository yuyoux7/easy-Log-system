#include "log.hpp"
std::string turnstr(long long nu)
{
	std::string flash{};
	for (long long s = nu; s != 0; s /= 10)
	{
		flash += ((s % 10) ^ 48);
	};
	std::reverse(flash.begin(), flash.end());
	return std::string(flash);
}
void Log::SetLogName(std::string url)
{
	this->filename = url;
}
