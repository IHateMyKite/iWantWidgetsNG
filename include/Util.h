#pragma once

namespace IWW::Util
{
	using SKSE::stl::enumeration;
	using SKSE::stl::report_and_fail;
	using std::to_underlying;

	static const char* ws = " \t\n\r\f\v";

	inline std::vector<std::string> Split(const std::string& a_str, std::string_view a_delimiter)
	{
		auto range = a_str | std::ranges::views::split(a_delimiter) | std::ranges::views::transform([](auto&& r) { return std::string_view(r); });
		return { range.begin(), range.end() };
	}

	inline std::string Join(const std::vector<std::string>& a_vec, std::string_view a_delimiter)
	{
		return std::accumulate(a_vec.begin(), a_vec.end(), std::string{},
			[a_delimiter](const auto& str1, const auto& str2) {
				return str1.empty() ? str2 : str1 + a_delimiter.data() + str2;
			});
	}

	inline std::string str_toupper(std::string s)
	{
		std::transform(
			s.begin(),
			s.end(),
			s.begin(),
			[](unsigned char c) {
				return static_cast<char>(std::toupper(c));
			});
		return s;
	}

	inline std::string& rtrim(std::string& s, const char* t = ws)
	{
		s.erase(s.find_last_not_of(t) + 1);
		return s;
	}

	inline std::string& ltrim(std::string& s, const char* t = ws)
	{
		s.erase(0, s.find_first_not_of(t));
		return s;
	}

	inline std::string& trim(std::string& s, const char* t = ws)
	{
		return ltrim(rtrim(s, t), t);
	}

	template <typename T = RE::TESForm>
	inline T* GetFormFromString(const std::string& s)
	{
		if (auto form = RE::TESForm::LookupByEditorID(s)) {
			return form->As<T>();
		}

		const auto splits = Split(s, "|"sv);

		if (splits.size() != 2) {
			return nullptr;
		}

		char* p;
		const auto formId = std::strtol(splits[0].c_str(), &p, 16);

		if (*p != 0) {
			return nullptr;
		}

		return RE::TESDataHandler::GetSingleton()->LookupForm<T>(formId, splits[1]);
	}
}