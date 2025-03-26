
module;

#include <filesystem>
#include <algorithm>

#if LUMINE_WIN64
    #include <windows.h>
#else
    #error no supported platform
#endif

#include "TLogger.h"

module Path;


namespace lumine
{

Path::Path(const char* initPath) :
    m_Handle(initPath)
{ }


Path::Path(std::initializer_list<const char*> appendElems)
{
    Append(*this, appendElems);
}


Path::Path(Path initPath, const char* appendElem)
{
    initPath.Append(appendElem);
    m_Handle = initPath.m_Handle;
}


Path::Path(Path initPath, std::initializer_list<const char*> appendElems)
{
    initPath.Append(appendElems);
    m_Handle = initPath.m_Handle;
}


bool Path::Exists() const
{
    return Exists(*this);
}


bool Path::Exists(const Path& path)
{
    return std::filesystem::exists(path.m_Handle);
}


bool Path::Exists(const char* path)
{
    return std::filesystem::exists(path);
}


void Path::Append(const char* appendElem)
{
    Append(*this, appendElem);
}


void Path::Append(std::initializer_list<const char*> appendElems)
{
    Append(*this, appendElems);
}


void Path::Append(Path& current, const char* appendElem)
{
    current.m_Handle /= std::filesystem::path(appendElem);
}


void Path::Append(Path& current, std::initializer_list<const char*> appendElems)
{
    std::ranges::for_each(appendElems, [&current](const char* appendElem)
        {
            Append(current, appendElem);
        });
}


Path Path::GetExecutableFilePath()
{
    if constexpr (LUMINE_WIN64)
    {
        char ownPath[MAX_PATH];

        // When NULL is passed to GetModuleHandle, the handle of the exe itself is returned
        HMODULE hModule = GetModuleHandle(nullptr);
        if (not hModule)
        {
            const char* errorCode = "Could not find hModule for WIN32 API during executable path retrieval!";
            TERROR(errorCode);
            throw std::runtime_error(errorCode);
        }

        // Use GetModuleFileName() with module handle to get the path
        GetModuleFileName(hModule, ownPath, sizeof(ownPath));
        return Path{ ownPath };
    }
    else
    {
        const char* errorCode = "No supported platform!";
        TCRITICAL(errorCode);
        throw std::runtime_error(errorCode);
    }
}


Path Path::GetExecutablePath()
{
    auto filePath = GetExecutableFilePath();
    filePath.m_Handle = filePath.m_Handle.parent_path();
    return filePath;
}


Path Path::GetCurrentDir()
{
    return Path(std::filesystem::current_path().string().c_str());
}


std::string Path::GetString() const
{
    return m_Handle.string();
}


Path::operator std::string() const
{
    return GetString();
}

}
