#pragma once

#ifdef _std11_
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#define exists__(d) fs::exists(d)

#else

#include <filesystem>
namespace fs = std::filesystem;
#define exists__(d) d.exists()
#endif