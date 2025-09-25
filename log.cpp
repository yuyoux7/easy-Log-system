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
	this->filename = (char*)malloc(sizeof(url) + 2);
	if (this->filename != nullptr)
		strcpy_s(this->filename, sizeof(this->filename), url);
}

void Log::rmtime(Log* lg)
{
	std::string vflash{};
	for (size_t i = 0; i < lg->Buff.size(); i++)
	{
		if (lg->Buff[i] == '[')
		{
			while (true)
			{
				i++;
				if (lg->Buff[i - 1] == ']' && lg->Buff[i] == ':')
				{
					i++;
					break;
				}
			};
		}
		vflash += lg->Buff[i];
	}
	lg->Buff = vflash;
}
