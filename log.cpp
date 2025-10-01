#include "log.hpp"
std::string turnstr(long long nu)
{
	if (nu == 0)
	{
		return "0";
	}
	std::string flash{};
	for (long long s = nu; s != 0; s /= 10)
	{
		flash += ((s % 10) ^ 48);
	};
	std::reverse(flash.begin(), flash.end());
	return std::string(flash);
}

void Log::SetLogName(const char* url)
{
	this->filename = (char*)malloc(strlen(url) + 2);
	if (this->filename != nullptr)
		strcpy_s(this->filename, (strlen(url) + 2), url);
}

