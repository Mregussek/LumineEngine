
module;

#include <string>
#include <filesystem>

export module Path;


export namespace lumine
{

class Path
{
public:

	explicit Path(const char* initPath);
	explicit Path(std::initializer_list<const char*> appendElems);
	explicit Path(Path initPath, const char* appendElem);
	explicit Path(Path initPath, std::initializer_list<const char*> appendElems);

	void Append(const char* appendElem);
	void Append(std::initializer_list<const char*> appendElems);

	static void Append(Path& current, const char* appendElem);
	static void Append(Path& current, std::initializer_list<const char*> appendElems);

	[[nodiscard]] bool Exists() const;
	[[nodiscard]] static bool Exists(const Path& path);

	[[nodiscard]] static Path GetExecutableFilePath();
	[[nodiscard]] static Path GetExecutablePath();

	[[nodiscard]] static Path GetCurrentDir();

	[[nodiscard]] std::string GetString() const;
	operator std::string() const;

private:

	std::filesystem::path m_Handle{};

};

}
