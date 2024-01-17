#include "print_helper.h"

void PrintHelper::PrintTable(std::vector<std::pair<std::string, std::vector<std::string>>> rows) {
	std::vector<std::string> headers;
	std::unordered_map<std::string, std::vector<std::string>> headerValues;
	size_t maxLength = 0;
	for (size_t headerID = 0; headerID < rows.size(); headerID++) {
		std::string header = std::get<0>(rows[headerID]);
		headers.push_back(header);
		headerValues[header] = std::vector<std::string>();
		if (header.length() > maxLength)
			maxLength = header.length();
		std::vector<std::string> values = std::get<1>(rows[headerID]);
		for (size_t valueID = 0; valueID < values.size(); valueID++) {
			std::string value = values[valueID];
			headerValues[header].push_back(value);
			if (value.length() > maxLength)
				maxLength = value.length();
		}
	}
	for (size_t headerID = 0; headerID < headers.size(); headerID++) {
		std::string header	= headers[headerID];
		std::vector<std::string> values = headerValues[header];
		for (size_t valueID = 0; valueID < values.size(); valueID++)
			headerValues[header][valueID] = Pad(values[valueID], maxLength, " ");
	}
	std::string borderChunk		= "";
	for (size_t i = 0; i < maxLength + headers.size() * 2; i++)
		borderChunk += "-";
	std::string border			= "";
	std::string headerString	= "| ";
	for (size_t headerID = 0; headerID < headers.size(); headerID++) {
		headerString += Pad(headers[headerID], maxLength, " ") + " | ";
		border += borderChunk;
	}
	//Print stuff
	std::cout << "\n" << border;
	std::cout << "\n" << headerString;
	std::cout << "\n" << border;
	for (size_t valueID = 0; valueID < headerValues[headers[0]].size(); valueID++) {
		std::string valueString = "| ";
		for (size_t headerID = 0; headerID < headers.size(); headerID++)
			valueString += headerValues[headers[headerID]][valueID] + " | ";
		std::cout << "\n" << valueString;
	}
	std::cout << "\n" << border + "\n";
}
void PrintHelper::SpamLine(std::string line, std::string splitter, int count) {
	for (size_t i = 0; i < count; i++)
		std::cout << splitter << line;
}
void PrintHelper::PrintHeader(std::string header) { std::cout << "\n--- " << header << " ---\n"; }
std::string PrintHelper::Pad(std::string value, int length, std::string padChar) {
	while (value.length() < length)
		value += padChar;
	return value;
}
std::pair<std::string, std::vector<std::string>> PrintHelper::CreateColumn(std::string header, std::vector<std::string> values) {
	return std::pair<std::string, std::vector<std::string>>(header, values);
}
