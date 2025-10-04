#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>

std::string turnstr(long long nu);
class Log {
public:
	enum info_list : int
	{
		unix_time	= 0x00001,
		run_time	= 0x00010,
		warning		= 0x00100,
		error		= 0x01000,
		static_string = 0x10000
	};
	Log() : filename(nullptr), st(time(NULL)) {
		this->setLogheadinfo();
	};
	Log(std::string lg) : filename(nullptr), st(time(NULL))
	{
		this->Buff = lg + "\n";
	};
	friend std::ostream& operator<<(std::ostream& io, Log& lg)
	{
		lg.Buff += lg.flash;
		io << lg.flash;
		lg.flash.clear();
		return io;
	};
	friend std::string& operator<<(Log& lg, long long& in) {
		lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
		return lg.flash += (std::string("[" + lg.logheadinfo + "]:") + turnstr(in) + '\n');
	};
	friend std::string& operator<<(Log& lg, long& in) {
		lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
		return lg.flash += (std::string("[" + lg.logheadinfo + "]:") + turnstr(in) + '\n');
	};
	friend std::string& operator<<(Log& lg, int& in) {
		lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
		return lg.flash += (std::string("[" + lg.logheadinfo + "]:") + turnstr(in) + '\n');
	};
	friend std::string& operator<<(Log& lg, short& in) {
		lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
		return lg.flash += (std::string("[" + lg.logheadinfo + "]:") + turnstr(in) + '\n');
	};
	friend std::string& operator<<(Log& lg, unsigned int& in) {
		lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
		return lg.flash += (std::string("[" + lg.logheadinfo + "]:") + turnstr(in) + '\n');
	};
	friend std::string& operator<<(Log& lg, unsigned long& in) {
		lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
		return lg.flash += (std::string("[" + lg.logheadinfo + "]:") + turnstr(in) + '\n');
	};
	friend std::string& operator<<(Log& lg, std::string& str) {
		lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
		return lg.flash += (std::string("[" + lg.logheadinfo + "]:") + str + '\n');
	};
	friend std::string& operator<<(Log& lg, char& in) {
		lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
		return lg.flash += (std::string("[" + lg.logheadinfo + "]:") + in + '\n');
	};
	friend std::string& operator<<(Log& lg, const std::string& str) {
		lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
		return lg.flash += (std::string("[" + lg.logheadinfo + "]:") + str + '\n');
	}
	friend std::string& operator<<(Log& lg, const char* str) {
		lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
		return lg.flash += (std::string("[" + lg.logheadinfo + "]:") + str + '\n');
	}
	friend std::string& operator<<(Log& lg, const char& in) {
		lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
		return lg.flash += (std::string("[" + lg.logheadinfo + "]:") + in + '\n');
	}
	friend std::string& operator<<(Log& lg, const int& in) {
		lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
		return lg.flash += (std::string("[" + lg.logheadinfo + "]:") + turnstr(in) + '\n');
	}
	friend std::string& operator<<(Log& lg, const long& in) {
		lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
		return lg.flash += (std::string("[" + lg.logheadinfo + "]:") + turnstr(in) + '\n');
	}
	friend std::string& operator<<(Log& lg, const long long& in) {
		lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
		return lg.flash += (std::string("[" + lg.logheadinfo + "]:") + turnstr(in) + '\n');
	}
	friend std::string& operator<<(Log& lg, const unsigned int& in) {
		lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
		return lg.flash += (std::string("[" + lg.logheadinfo + "]:") + turnstr(in) + '\n');
	}
	friend std::string& operator<<(Log& lg, const unsigned long& in) {
		lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
		return lg.flash += (std::string("[" + lg.logheadinfo + "]:") + turnstr(in) + '\n');
	}
	friend std::string& operator<<(Log& lg, const short& in) {
		lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
		return lg.flash += (std::string("[" + lg.logheadinfo + "]:") + turnstr(in) + '\n');
	}
	friend std::string& operator<<(std::string& cl, int& val)
	{
		return cl += turnstr(val);
	};
	Log& operator<<(Log& other) {
		other.out = false;
		other.Buff += other.flash;
		other.flash.clear();
		this->rw(other.Buff);
		return *this;
	};
	template<typename T, typename ...C>
	void LogWrite(T in, C... a);
	void LogWrite() {
		if (this->out) {
			std::clog << *this;
		}
		else
		{
			this->Buff += this->flash;
			this->flash.clear();
		}
		if ((this->filename != nullptr && tm != time(NULL)) || (olock && this->filename != nullptr)) {
			std::ofstream ofile{};
			ofile.open(this->filename);
			if (ofile.is_open())
			{
				ofile << this->getbuff();
			}
			ofile.close();
			tm = time(NULL);
		}
	};
	void SetLogName(const char* url = "log.txt");
	void AutoOut(bool stat = true)
	{
		this->out = stat;
	};
	void setLogheadinfo(int basic_info_list = Log::unix_time, std::string str = std::string())
	{
		this->infotype = basic_info_list;
		switch (basic_info_list)
		{
		case Log::unix_time:
			this->logheadinfo = turnstr(time(NULL));
			break;
		case Log::run_time:
			this->logheadinfo = turnstr((time(NULL) - this->st));
			break;
		case Log::warning:
			this->logheadinfo = "warning";
			break;
		case Log::error:
			this->logheadinfo = "error";
			break;
		case Log::static_string:
			this->logheadinfo = str;
			break;
		case Log::unix_time | Log::warning:
			this->logheadinfo = (turnstr(time(NULL)) + " warning");
			this->infotype = Log::static_string;
			break;
		case Log::unix_time | Log::error:
			this->logheadinfo = (turnstr(time(NULL)) + " error");
			this->infotype = Log::static_string;
			break;
		case Log::unix_time | Log::static_string:
			this->logheadinfo = (turnstr(time(NULL)) + " " + str);
			this->infotype = Log::static_string;
			break;
		case Log::run_time | Log::warning:
			this->logheadinfo = (turnstr((time(NULL) - this->st)) + " warning");
			this->infotype = Log::static_string;
			break;
		case Log::run_time | Log::error:
			this->logheadinfo = (turnstr((time(NULL) - this->st)) + " error");
			this->infotype = Log::static_string;
			break;
		case Log::run_time | Log::static_string:
			this->logheadinfo = (turnstr((time(NULL) - this->st)) + " " + str);
			this->infotype = Log::static_string;
			break;
		default:
			*this << "Not support this info type";
			*this << "using basic type";
			setLogheadinfo();
			break;
		}
	};
	virtual ~Log() {
		olock = true;
		LogWrite();
		if (filename != nullptr)
		{
			free(filename);
			filename = nullptr;
		}
	};
private:
	std::string Buff{};
	std::string flash{};
	char* filename{};
	bool olock = false;
	bool out = true;
	int infotype{};
	time_t tm{}, st{};
	void rw(std::string lg) {
		this->flash += lg;
	};
	const char* getbuff()
	{
		return Buff.c_str();
	};
	std::string logheadinfo{};
};

template<typename T, typename ...C>
inline void Log::LogWrite(T in, C... a)
{
	*this << in;
	if (sizeof...(a))
	{
		LogWrite(a...);
	}
	LogWrite();

}
