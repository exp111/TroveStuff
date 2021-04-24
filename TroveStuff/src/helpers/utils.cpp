#include "utils.h"

HANDLE _out = NULL, _old_out = NULL;
HANDLE _err = NULL, _old_err = NULL;
HANDLE _in = NULL, _old_in = NULL;

#pragma warning(disable:4996)
namespace Utils
{
	/*
	* @brief Create console
	*
	* Create and attach a console window to the current process
	*/
	void AttachConsole()
	{
		_old_out = GetStdHandle(STD_OUTPUT_HANDLE);
		_old_err = GetStdHandle(STD_ERROR_HANDLE);
		_old_in = GetStdHandle(STD_INPUT_HANDLE);

		::AllocConsole() && ::AttachConsole(GetCurrentProcessId());

		_out = GetStdHandle(STD_OUTPUT_HANDLE);
		_err = GetStdHandle(STD_ERROR_HANDLE);
		_in = GetStdHandle(STD_INPUT_HANDLE);

		SetConsoleMode(_out,
			ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);

		SetConsoleMode(_in,
			ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS |
			ENABLE_PROCESSED_INPUT | ENABLE_QUICK_EDIT_MODE);
	}

	/*
	* @brief Detach console
	*
	* Detach and destroy the attached console
	*/
	void DetachConsole()
	{
		if (_out && _err && _in) {
			FreeConsole();

			if (_old_out)
				SetStdHandle(STD_OUTPUT_HANDLE, _old_out);
			if (_old_err)
				SetStdHandle(STD_ERROR_HANDLE, _old_err);
			if (_old_in)
				SetStdHandle(STD_INPUT_HANDLE, _old_in);
		}
	}

	bool ConsolePrint(const char* fmt, ...)
	{
		if (!_out)
			return false;

		char buf[1024];
		va_list va;

		va_start(va, fmt);
		_vsnprintf_s(buf, 1024, fmt, va);
		va_end(va);

		return WriteConsoleA(_out, buf, static_cast<DWORD>(strlen(buf)), nullptr, nullptr);
	}

	bool ConsolePrintDirect(const char* str)
	{
		if (!_out)
			return false;

		return WriteConsoleA(_out, str, static_cast<DWORD>(strlen(str)), nullptr, nullptr);
	}

	/*
	* @brief Blocks execution until a key is pressed on the console window
	*
	*/
	char ConsoleReadKey(bool writeMessage)
	{
		if (!_in)
			return false;

		auto key = char{ 0 };
		auto keysread = DWORD{ 0 };


		ConsolePrint("Press any key to continue...\n");
		ReadConsoleA(_in, &key, 1, &keysread, nullptr);

		return key;
	}

	/*
	 * @brief Scan for a given byte pattern on a module
	 *
	 * @param module    Base of the module to search
	 * @param signature IDA-style byte array pattern
	 *
	 * @returns Address of the first occurence
	 */
	std::uint8_t* PatternScan(void* module, const char* signature)
	{
		static auto pattern_to_byte = [](const char* pattern) {
			auto bytes = std::vector<int>{};
			auto start = const_cast<char*>(pattern);
			auto end = const_cast<char*>(pattern) + strlen(pattern);

			for (auto current = start; current < end; ++current) {
				if (*current == '?') {
					++current;
					if (*current == '?')
						++current;
					bytes.push_back(-1);
				}
				else {
					bytes.push_back(strtoul(current, &current, 16));
				}
			}
			return bytes;
		};

		auto dosHeader = (PIMAGE_DOS_HEADER)module;
		auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

		auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
		auto patternBytes = pattern_to_byte(signature);
		auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

		auto s = patternBytes.size();
		auto d = patternBytes.data();

		for (auto i = 0ul; i < sizeOfImage - s; ++i) {
			bool found = true;
			for (auto j = 0ul; j < s; ++j) {
				if (scanBytes[i + j] != d[j] && d[j] != -1) {
					found = false;
					break;
				}
			}
			if (found) {
				return &scanBytes[i];
			}
		}
		return nullptr;
	}

	const char * GetTimeString()
	{

		//Time related variables
		time_t current_time;
		struct tm *time_info;
		static char buffer[10];
		static char* timeString;

		//Get current time
		time(&current_time);
		time_info = localtime(&current_time);

		//Get current time as string
		strftime(buffer, sizeof(buffer), "%X", time_info);
		timeString = strdup(buffer);
		return timeString;

	}

	const char* GetFullTimeDayString()
	{
		time_t current_time;
		struct tm time_info;
		static char buffer[10];
		std::string bufferString = "";
		static char* timeString;

		time(&current_time);
		localtime_s(&time_info, &current_time);

		strftime(buffer, sizeof(buffer), "%X", &time_info);
		bufferString.append(buffer);
		bufferString.append(" ");

		strftime(buffer, sizeof(buffer), "%A", &time_info);
		bufferString.append(buffer);
		bufferString.append(" ");

		strftime(buffer, sizeof(buffer), "%d", &time_info);
		bufferString.append(buffer);
		bufferString.append(" ");

		strftime(buffer, sizeof(buffer), "%B", &time_info);
		bufferString.append(buffer);
		bufferString.append(" ");

		strftime(buffer, sizeof(buffer), "%Y", &time_info);
		bufferString.append(buffer);

		timeString = _strdup(bufferString.c_str());
		return timeString;
	}

	double GetEpochTime()
	{
		double now = (double)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		return now;
	}

	/*Color GetRainbowColor(float speed)
	{
		double now = GetEpochTime();
		Color color = Color(
			(int)(std::sin(speed*now + 0) * 127) + 128,
			(int)(std::sin(speed*now + 2) * 127) + 128,
			(int)(std::sin(speed*now + 4) * 127) + 128);

		return color;
	}*/
}