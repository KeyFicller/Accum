#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string>
split_by_semicolon(const std::string& _value)
{
    std::vector<std::string> tokens;
    std::istringstream iss(_value);
    std::string token;

    while (std::getline(iss, token, ';')) {
        tokens.push_back(token);
    }

    return tokens;
}

std::string
proc_str(const std::string& _declare, const std::string& _class)
{
    auto left_bracket_pos = _declare.find('(');
    auto pre_fix = _declare.substr(0, left_bracket_pos + 1);
    auto blank_pos = pre_fix.find_last_of(' ');
    auto fn_name = pre_fix.substr(blank_pos + 1, left_bracket_pos - blank_pos - 1);
    pre_fix.insert(blank_pos + 1, std::string(_class) + "::");
    auto right_bracket_pos = _declare.find_last_of(')');
    auto param_str = _declare.substr(left_bracket_pos + 1, right_bracket_pos - left_bracket_pos);

    std::vector<std::string> params;
    std::istringstream iss(param_str);
    std::string word;

    while (iss >> word) {
        if (!word.empty() && (word[0] == '_' || (word[0] == '&' && word[1] == '_'))) {
            if (word.back() == ')' || word.back() == ',')
                word.pop_back();
            if (word.front() == '&')
                word.erase(word.begin());
            params.push_back(word);
        }
    }

    std::string result = pre_fix + param_str;
    result += "\n";
    result += "{\n";
    result += "    return IMPL(";
    result += _class;
    result += ")->";
    result += fn_name;
    result += "(";
    for (int i = 0; i < params.size(); i++) {
        result += params[i];
        if (i != params.size() - 1)
            result += ",";
    }
    result += ");\n";
    result += "}\n";

    return result;
}

int
main()
{
    // 类名
    const std::string className = "load_proc";

    // 函数声明列表
    const std::string declarations = R"(bool begin();
        bool end();
        void begin_map();
        void end_map();
        void begin_sequence();
        void end_sequence();
        void out_key();
        void out_value();
        void out(std::string &_value);
        void out(const std::string &_value);
        void out(int &_value);
        void out(float &_value);
        void out(bool &_value);
        bool has_value() const;
        bool has_key(const std::string& _value) const;)";

    std::vector<std::string> tokens = split_by_semicolon(declarations);

    for (const auto& token : tokens)
        std::cout << proc_str(token, className);

    return 0;
}