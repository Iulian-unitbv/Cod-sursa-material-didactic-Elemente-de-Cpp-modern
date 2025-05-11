module utils;

using namespace http;

std::vector<std::string> http::Split(const std::string& str, const std::string& separator) 
{
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = 0;

    while ((end = str.find(separator, start)) != std::string::npos) 
    {
        result.push_back(str.substr(start, end - start));
        start = end + separator.length();
    }
    result.push_back(str.substr(start));
    return result;
}


std::unordered_map<std::string, std::string> http::ParseUrlArgs(const std::string& urlArgs) 
{
    std::unordered_map<std::string, std::string> result;

    auto pairs = Split(urlArgs, "&");

    for (const auto& pair : pairs)
    {
        auto keyValue = Split(pair, "=");
        if (keyValue.size() == 2) 
            result[keyValue[0]] = keyValue[1];
    }

    return result;
}