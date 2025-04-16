#pragma once
#include <map>
#include <string>
#include <vector>
#include <any>
#include <sstream>
class JSON
{
public:
	JSON(std::string m_jsonStr);
	~JSON();
	template <typename R>
	R getValue(std::string key)
	{
		std::istringstream iss(std::any_cast<std::string>(key_value[key]));
		R r;
		iss >> r;
		return r;
	}

	template <typename R>
	std::vector<R> getVector(std::string key)
	{
		std::vector<R> rVec;
		std::vector<std::any> aVec = std::any_cast<std::vector<std::any>>(key_value[key]);
		for (std::any& a : aVec) {
			std::istringstream iss(std::any_cast<std::string>(a));
			R element;
			iss >> element;
			rVec.push_back(element);
		}
		return rVec;
	}
	JSON getJSON(std::string key);
	std::vector<JSON*> subJsons;
	void normalize(std::string& str);
	std::vector<std::any> parseArray(std::string m_arrStr);
	std::map<std::string, std::any> key_value;
	std::string jsonStr;
};