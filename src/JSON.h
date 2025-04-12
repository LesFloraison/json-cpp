#pragma once
#include <map>
#include <string>
#include <vector>
#include <any>
class JSON
{
public:
	JSON(std::string m_jsonStr);
	~JSON();
	std::vector<JSON*> subJsons;
	void normalize(std::string& str);
	std::vector<std::any> parseArray(std::string m_arrStr);
	std::map<std::string, std::any> key_value;
	std::string jsonStr;
};