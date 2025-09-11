#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
std::string turnstr(long long nu);
class Log {
public:
	Log() {};
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
	friend std::string& operator<<(Log& lg, std::string str) {
		return lg.flash += (std::string("[" + (std::string)turnstr(time(NULL)) + "]:") + str + '\n');
	};
	friend std::string& operator<<(Log& lg, char& in) {
		return lg.flash += (std::string("[" + (std::string)turnstr(time(NULL)) + "]:") + in + '\n');
	};
	template<typename T>
	void LogWrite(T in);
	void LogWrite() {
		std::clog << *this;
		if ((this->filename != std::string() && tm != time(NULL)) || olock) {
			std::ofstream ofile{};
			ofile.open(this->filename);
			if (ofile.is_open())
			{
				ofile << Buff;
			}
			ofile.close();
			tm = time(NULL);
		}
	};
	void SetLogName(std::string url = "log.txt");
	virtual ~Log() {
		olock = true;
		LogWrite();
	};
private:
	std::string Buff{};
	std::string flash{};
	std::string filename = {};
	bool olock = false;
	time_t tm{};
};

template<typename T>
inline void Log::LogWrite(T in)
{
	*this << in;
	LogWrite();
}
