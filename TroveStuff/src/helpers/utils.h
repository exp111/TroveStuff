#pragma once

#include <Windows.h>
#include <stdio.h>
#include <chrono>
#include <string>
#include <vector>
#include <cmath>
//#include "defs.h"

namespace Utils
{
	/*
	* @brief Create console
	*
	* Create and attach a console window to the current process
	*/
	void AttachConsole();

	/*
	* @brief Detach console
	*
	* Detach and destroy the attached console
	*/
	void DetachConsole();

	bool ConsolePrint(const char* fmt, ...);
	bool ConsolePrintDirect(const char* str);

	/*
	* @brief Blocks execution until a key is pressed on the console window
	*
	*/
	char ConsoleReadKey(bool writeMessage = true);

	/*
	 * @brief Scan for a given byte pattern on a module
	 *
	 * @param module    Base of the module to search
	 * @param signature IDA-style byte array pattern
	 *
	 * @returns Address of the first occurence
	 */
	std::uint8_t* PatternScan(void* module, const char* signature);

	const char* GetTimeString();
	const char* GetFullTimeDayString();
	double GetEpochTime();

	//Color GetRainbowColor(float speed = 0.001f);
}