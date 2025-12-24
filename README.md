# easy-Log-system
A easy Log system
# How to using
```C++
#include "log.hpp"
Logger::Log logger{};
int main() {
  logger << "Log info" << Logger::lendl;
}
```
# Func
<h4> Set Log Head Info </h4>

```C++
void setLogheadinfo(int basic_info_list = Log::unix_time, std::string user_str = std::string());
```
|info_list|system unix time|Log run timer|warning|error|user set info|
|:---:|:---:|:---:|:---:|:---:|:---:|
|Options|unix_time|run_time|warning|error|static_string|


<h4> Set Log Name </h4>

<p5>If you no need save in local can no set<p5>

```C++
void SetLogName(const char* url = "log.txt");
```

<h4> Log Write </h4>


<p5> swap buffers func </p5>

```C++
// If you no write anything is just swap buffers
void LogWrite(T in, C... next);
```
<p5> No swap buffers func </p5>

```C++
your_log_object << "your log" << Logger::lendl;
```

<h4> Auto Out </h4>

<p5> This is out to console </p5>

```C++
void AutoOut(bool stat = true);
```
