#pragma once

#if defined(_WIN32)
#define SE_API __declspec(dllimport)
#pragma warning(disable : 4251)

#else
#define SE_API __attribute__((__visibility__("default")))
#endif

const bool oldUI = true;
static bool isEditing = false;