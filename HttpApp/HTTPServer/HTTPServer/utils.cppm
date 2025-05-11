export module utils;
import <unordered_map>;
import <string>;
import <vector>;

namespace http
{
	export std::vector<std::string> Split(const std::string& str, const std::string& separator);

	export std::unordered_map<std::string, std::string> ParseUrlArgs(const std::string& urlArgs);
}