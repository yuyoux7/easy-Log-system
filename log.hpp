#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
std::string turnstr(long long nu);
class Log {
public:
	enum info_list : int
	{
		unix_time,
		run_time,
		warning,
		error,
		static_string
	};
	Log() : filename(nullptr), st(time(NULL)) {
		this->setLogheadinfo();
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
		other;
		other.LogWrite();
		rmtime(&other);
		*this << other.Buff;
		return *this;
	};
	template<typename T, typename ...C>
	void LogWrite(T in, C... a);
	void LogWrite() {
		if (this->out) {
			std::clog << *this;
		}
		if ((this->filename != nullptr && tm != time(NULL)) || (olock && this->filename != nullptr)) {
			std::ofstream ofile{};
			ofile.open(this->filename);
			if (ofile.is_open())
			{
				ofile << this->Buff;
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
		default:
			break;
		}
	};
	virtual ~Log() {
		olock = true;
		LogWrite();
	};
private:
	std::string Buff{};
	std::string flash{};
	char* filename{};
	bool olock = false;
	bool out = true;
	int infotype{};
	time_t tm{}, st{};
	void rmtime(Log* lg);
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