#include "JSON.h"

JSON::JSON(std::string m_jsonStr)
{
    jsonStr = m_jsonStr;
    normalize(jsonStr);
    jsonStr = jsonStr.substr(1, jsonStr.length() - 2); //remove {}
    while (jsonStr.find_first_of(":") != std::string::npos) {
        jsonStr = jsonStr.substr(jsonStr.find_first_of("\"") + 1);
        std::string key = jsonStr.substr(0, jsonStr.find_first_of("\""));
        jsonStr = jsonStr.substr(jsonStr.find_first_of("\"") + 2);
        if (jsonStr[0] == '{') { //next JSON Layer
            int leftBrace = 1;
            int rightBrace = 0;
            int i = 1;
            for (i = 1; leftBrace != rightBrace; i++) {
                if (jsonStr[i] == '{') {
                    leftBrace++;
                }
                if (jsonStr[i] == '}') {
                    rightBrace++;
                }
            }
            std::string subJsonStr = jsonStr.substr(0, i);
            jsonStr = jsonStr.substr(i);
            JSON* subJson = new JSON(subJsonStr);
            subJsons.push_back(subJson);
            key_value[key] = subJson;
        }
        else if (jsonStr[0] == '[') { //next Array Layer
            int leftBracket = 1;
            int rightBracket = 0;
            int i = 1;
            for (i = 1; leftBracket != rightBracket; i++) {
                if (jsonStr[i] == '[') {
                    leftBracket++;
                }
                if (jsonStr[i] == ']') {
                    rightBracket++;
                }
            }
            std::string subArrStr = jsonStr.substr(0, i);
            std::any subArr = parseArray(subArrStr);
            key_value[key] = subArr;
            jsonStr = jsonStr.substr(i + 1);
        }
        else if (jsonStr[0] == '\"') { //string
            jsonStr = jsonStr.substr(1);
            int i = jsonStr.find_first_of('\"');
            std::string value = jsonStr.substr(0, i);
            key_value[key] = value;
            jsonStr = jsonStr.substr(i + 1);
        }
        else { //others
            int i = jsonStr.find_first_of(',');
            std::string value = jsonStr.substr(0, i);
            key_value[key] = value;
            jsonStr = jsonStr.substr(i);
        }
    }
}

JSON::~JSON()
{
    for (JSON*& j : subJsons) {
        if (j) {
            delete j;
            j = nullptr;
        }
    }
}

void JSON::normalize(std::string& str) {
    str.erase(std::remove_if(str.begin(), str.end(),
        [](unsigned char c) { return c == ' ' || c == '\n' || c == '\r'; }),
        str.end());
}

std::vector<std::any> JSON::parseArray(std::string m_arrStr)
{
    std::vector<std::any> arr;
    std::string arrStr = m_arrStr.substr(1, m_arrStr.length() - 2);
    arrStr += ',';
    while (arrStr.find_first_of(",") != std::string::npos) {
        if (arrStr[0] == '[') { //sub Array Layer
            int leftBracket = 1;
            int rightBracket = 0;
            int i = 1;
            for (i = 1; leftBracket != rightBracket; i++) {
                if (arrStr[i] == '[') {
                    leftBracket++;
                }
                if (arrStr[i] == ']') {
                    rightBracket++;
                }
            }

            std::string nextArr = arrStr.substr(0, i);
            arrStr = arrStr.substr(i + 1);
            arr.push_back(parseArray(nextArr));
            continue;
        }

        if (arrStr[0] == '{') { //sub JSON Layer
            int leftBrace = 1;
            int rightBrace = 0;
            int i = 1;
            for (i = 1; leftBrace != rightBrace; i++) {
                if (arrStr[i] == '{') {
                    leftBrace++;
                }
                if (arrStr[i] == '}') {
                    rightBrace++;
                }
            }

            std::string subJsonStr = arrStr.substr(0, i);
            arrStr = arrStr.substr(i + 1);
            JSON* subJson = new JSON(subJsonStr);
            subJsons.push_back(subJson);
            arr.push_back(subJson);
            continue;
        }

        std::string element = arrStr.substr(0, arrStr.find_first_of(","));
        element.erase(std::remove_if(element.begin(), element.end(), [](unsigned char c) { return c == '\"'; }), element.end());
        arr.push_back(element);
        arrStr = arrStr.substr(arrStr.find_first_of(",") + 1);
    }
    return arr;
}