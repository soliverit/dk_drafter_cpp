#pragma once
/*===
	Includes
===*/
// Native
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

// Project

/*
	Print Helper - because writing to the console sucks.

	A class for making it easier to print stuff to the console. Check any 
	of 
*/
struct PrintHelper {
	static void PrintTable(std::vector<std::pair<std::string,std::vector<std::string>>> cells);
	static void SpamLine(std::string line, std::string splitter, int count);
	static void PrintHeader(std::string header);
	/*=== Formatters === */
	//static std::vector<std::tuple<std::string, std::string>> PadTable(std::vector<std::tuple<std::string, std::string>> cells);
	/* Pad a string to a set size */
	static std::string Pad(std::string value, int size, std::string padChar);

	static std::pair<std::string, std::vector<std::string>>CreateColumn(std::string header, std::vector<std::string> values);
};