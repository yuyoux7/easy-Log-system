#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
std::string turnstr(long long nu);
class Log {
public:
	Log() : filename(nullptr) {};
	friend std::ostream& operator<<(std::ostream& io, Log& lg)
	{
		lg.Buff += lg.flash;
		io << lg.flash;
		lg.flash.clear();
		return io;
	};
	friend std::string& operator<<(Log& lg, long long& in) {
		return lg.flash += (std::string("[" + (std::string)turnstr(time(NULL)) + "]:") + turnstr(in) + '\n');
	};
	friend std::string& operator<<(Log& lg, long& in) {
		return lg.flash += (std::string("[" + (std::string)turnstr(time(NULL)) + "]:") + turnstr(in) + '\n');
	};
	friend std::string& operator<<(Log& lg, int& in) {
		return lg.flash += (std::string("[" + (std::string)turnstr(time(NULL)) + "]:") + turnstr(in) + '\n');
	};
	friend std::string& operator<<(Log& lg, short& in) {
		return lg.flash += (std::string("[" + (std::string)turnstr(time(NULL)) + "]:") + turnstr(in) + '\n');
	};
	friend std::string& operator<<(Log& lg, unsigned int& in) {
		return lg.flash += (std::string("[" + (std::string)turnstr(time(NULL)) + "]:") + turnstr(in) + '\n');
	};
	friend std::string& operator<<(Log& lg, unsigned long& in) {
		return lg.flash += (std::string("[" + (std::string)turnstr(time(NULL)) + "]:") + turnstr(in) + '\n');
	};
	friend std::string& operator<<(Log& lg, std::string& str) {
		return lg.flash += (std::string("[" + (std::string)turnstr(time(NULL)) + "]:") + str + '\n');
	};
	friend std::string& operator<<(Log& lg, char& in) {
		return lg.flash += (std::string("[" + (std::string)turnstr(time(NULL)) + "]:") + in + '\n');
	};
	friend std::string& operator<<(Log& lg, const std::string& str) {
		return lg.flash += (std::string("[" + (std::string)turnstr(time(NULL)) + "]:") + str + '\n');
	}
	friend std::string& operator<<(Log& lg, const char* str) {
		return lg.flash += (std::string("[" + (std::string)turnstr(time(NULL)) + "]:") + str + '\n');
	}
	friend std::string& operator<<(Log& lg, const char& in) {
		return lg.flash += (std::string("[" + (std::string)turnstr(time(NULL)) + "]:") + in + '\n');
	}
	friend std::string& operator<<(Log& lg, const int& in) {
		return lg.flash += (std::string("[" + (std::string)turnstr(time(NULL)) + "]:") + turnstr(in) + '\n');
	}
	friend std::string& operator<<(Log& lg, const long& in) {
		return lg.flash += (std::string("[" + (std::string)turnstr(time(NULL)) + "]:") + turnstr(in) + '\n');
	}
	friend std::string& operator<<(Log& lg, const long long& in) {
		return lg.flash += (std::string("[" + (std::string)turnstr(time(NULL)) + "]:") + turnstr(in) + '\n');
	}
	friend std::string& operator<<(Log& lg, const unsigned int& in) {
		return lg.flash += (std::string("[" + (std::string)turnstr(time(NULL)) + "]:") + turnstr(in) + '\n');
	}
	friend std::string& operator<<(Log& lg, const unsigned long& in) {
		return lg.flash += (std::string("[" + (std::string)turnstr(time(NULL)) + "]:") + turnstr(in) + '\n');
	}
	friend std::string& operator<<(Log& lg, const short& in) {
		return lg.flash += (std::string("[" + (std::string)turnstr(time(NULL)) + "]:") + turnstr(in) + '\n');
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
	time_t tm{};
	void rmtime(Log* lg);
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
