#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <malloc.h>
#include <string.h>
#include <ctime>

namespace Logger {
	class Log {
	public:
		enum info_list : char const
		{
			unix_time = 0b001,
			run_time = 0b010,
			warning = 0b100,
			error = 0b1000,
			static_string = 0b10000
		};
		Log() : filename(nullptr), st(time(NULL)) {
			this->setLogheadinfo();
		};
		Log(const char* lg) : filename(nullptr), st(time(NULL))
		{
			this->setLogheadinfo();
			this->SetLogName(lg);
		};
		Log(Log&) = delete;
		friend std::ostream& operator<<(std::ostream& io, Log& lg)
		{
			lg.Buff += lg.flash;
			io << lg.flash;
			lg.flash.clear();
			return io;
		};
		friend Log& operator<<(Log& lg, long long& in) {
			lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
			lg.flash += lg.addInfo() + (std::to_string(in) + (char)('\n'));
			return lg;
		};
		friend Log& operator<<(Log& lg, long& in) {
			lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
			lg.flash += lg.addInfo() + (std::to_string(in) + (char)('\n'));
			return lg;
		};
		friend Log& operator<<(Log& lg, int& in) {
			lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
			lg.flash += lg.addInfo() + (std::to_string(in) + (char)('\n'));
			return lg;
		};
		friend Log& operator<<(Log& lg, short& in) {
			lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
			lg.flash += lg.addInfo() + (std::to_string(in) + (char)('\n'));
			return lg;
		};
		friend Log& operator<<(Log& lg, unsigned int& in) {
			lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
			lg.flash += lg.addInfo() + (std::to_string(in) + (char)('\n'));
			return lg;
		};
		friend Log& operator<<(Log& lg, unsigned long& in) {
			lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
			lg.flash += lg.addInfo() + (std::to_string(in) + (char)('\n'));
			return lg;
		};
		friend Log& operator<<(Log& lg, std::string& str) {
			lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
			lg.flash += lg.addInfo() + (str + (char)('\n'));
			return lg;
		};
		friend Log& operator<<(Log& lg, char& in) {
			lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
			(lg.flash += lg.addInfo() + (in)) += ((char)('\n'));
			return lg;
		};
		friend Log& operator<<(Log& lg, const std::string& str) {
			lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
			lg.flash += lg.addInfo() + (str + (char)('\n'));
			return lg;
		}
		friend Log& operator<<(Log& lg, const char* str) {
			lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
			lg.flash += lg.addInfo() + (std::string(str) + (char)('\n'));
			return lg;
		}
		friend Log& operator<<(Log& lg, const char& in) {
			lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
			(lg.flash += lg.addInfo() + (in)) += ((char)('\n'));
			return lg;
		}
		friend Log& operator<<(Log& lg, const int& in) {
			lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
			lg.flash += lg.addInfo() + (std::to_string(in) + (char)('\n'));
			return lg;
		}
		friend Log& operator<<(Log& lg, const long& in) {
			lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
			lg.flash += lg.addInfo() + (std::to_string(in) + (char)('\n'));
			return lg;
		}
		friend Log& operator<<(Log& lg, const long long& in) {
			lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
			lg.flash += lg.addInfo() + (std::to_string(in) + (char)('\n'));
			return lg;
		}
		friend Log& operator<<(Log& lg, const unsigned int& in) {
			lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
			lg.flash += lg.addInfo() + (std::to_string(in) + (char)('\n'));
			return lg;
		}
		friend Log& operator<<(Log& lg, const unsigned long& in) {
			lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
			lg.flash += lg.addInfo() + (std::to_string(in) + (char)('\n'));
			return lg;
		}
		friend Log& operator<<(Log& lg, const short& in) {
			lg.setLogheadinfo(lg.infotype, lg.logheadinfo);
			lg.flash += lg.addInfo() + (std::to_string(in) + (char)('\n'));
			return lg;
		}
		friend Logger::Log& operator<<(Logger::Log& lg, Logger::Log& ((*)(Logger::Log&)))
		{
			lg.LogWrite();
			lg.hd = true;
			return lg;
		}
		Log& operator<<(Log& other) {
			other.out = false;
			other.Buff += other.flash;
			other.flash.clear();
			other.data += other.Buff;
			this->flash += other.data;
			this->ct++;
			this->ct += other.ct;
			return *this;
		};
		Log& operator=(Log&) = delete;
		template<typename T, typename ...C>
		void LogWrite(T in, C... a) noexcept;
		void LogWrite() noexcept {
			if (this->out) {
				std::clog << *this;
			}
			else
			{
				this->Buff += this->flash;
				this->flash.clear();
			}
			if ((this->filename != nullptr && this->tm != time(NULL)) || (this->olock && this->filename != nullptr)) {
				std::ofstream ofile{};
				ofile.open(this->filename, std::ios::app);
				if (ofile.is_open())
				{
					ofile << this->Buff.c_str();
					this->data += this->Buff;
					this->Buff.clear();
				}
				ofile.close();
				this->tm = time(NULL);
			}
		};
		void SetLogName(const char* url = "log.txt") noexcept;
		constexpr void AutoOut(bool stat = true) noexcept
		{
			this->out = stat;
		};
		constexpr void setLogheadinfo(int basic_info_list = Log::unix_time, std::string str = std::string()) noexcept
		{
			this->infotype = basic_info_list;
			switch (basic_info_list)
			{
			case Log::unix_time:
				this->logheadinfo = std::to_string(time(NULL));
				break;
			case Log::run_time:
				this->logheadinfo = std::to_string((time(NULL) - this->st));
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
				this->logheadinfo = (std::to_string(time(NULL)) + " warning");
				this->infotype = Log::static_string;
				break;
			case Log::unix_time | Log::error:
				this->logheadinfo = (std::to_string(time(NULL)) + " error");
				this->infotype = Log::static_string;
				break;
			case Log::unix_time | Log::static_string:
				this->logheadinfo = (std::to_string(time(NULL)) + " " + str);
				this->infotype = Log::static_string;
				break;
			case Log::run_time | Log::warning:
				this->logheadinfo = (std::to_string((time(NULL) - this->st)) + " warning");
				this->infotype = Log::static_string;
				break;
			case Log::run_time | Log::error:
				this->logheadinfo = (std::to_string((time(NULL) - this->st)) + " error");
				this->infotype = Log::static_string;
				break;
			case Log::run_time | Log::static_string:
				this->logheadinfo = (std::to_string((time(NULL) - this->st)) + " " + str);
				this->infotype = Log::static_string;
				break;
			default:
				setLogheadinfo();
				*this << "Not support this info type";
				*this << "using basic type";
				break;
			}
		};
		virtual ~Log() {
			this->olock = true;
			LogWrite();
			if (this->filename != nullptr)
			{
				free(filename);
				this->filename = nullptr;
			}
		};
	private:
		std::string Buff{};
		std::string flash{};
		std::string logheadinfo{};
		std::string data{};
		time_t tm{}, st{};
		char infotype{};
		bool olock = false;
		bool out = true;
		bool hd = true;
		int ct{};
		char* filename{};
		constexpr std::string addInfo() noexcept
		{
			if (this->hd) {
				this->hd = false;
				return (std::string("[" + this->logheadinfo + "]:"));
			}
			else
				this->flash.pop_back();
			return std::string();
		};
	};

	Log& lendl(Log& L) noexcept
	{
		return L;
	};

	template<typename T, typename ...C>
	inline void Log::LogWrite(T in, C... a) noexcept
	{
		*this << in;
		if (sizeof...(a))
		{
			this->LogWrite(a...);
		}
		this->LogWrite();
		this->hd = true;
	};

	inline void Log::SetLogName(const char* url) noexcept
	{
		if (this->filename) {
			this->olock = true;
			this->LogWrite();
			this->olock = false;
			free(this->filename);
		}
		this->filename = nullptr;
		this->filename = (char*)malloc(strlen(url) + 2);
		if (this->filename != nullptr) {
#if defined(_MSC_VER)
			strcpy_s(this->filename, (strlen(url) + 2), url);
#else
			strcpy(this->filename, url);
#endif
			std::ofstream a(this->filename);
			a.close();
		}
	};
}