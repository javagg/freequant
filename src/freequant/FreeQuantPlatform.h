#ifndef FQ_PLATFORM_H
#define FQ_PLATFORM_H

#ifdef _MSC_VER
#  define FQ_COMPILER_MSVC
#endif

#ifdef __clang__
#  define FQ_COMPILER_CLANG
#endif

#ifdef __GNUC__
#  define FQ_COMPILER_GCC
#endif

#if defined(_WIN32) || defined(WIN32)
#  define FQ_PLATFORM_WIN
#endif

#ifdef APPLE_CC
#  define FQ_PLATFORM_MAC
#endif

#ifdef FQ_STATIC
#endif

#ifdef FQ_SHARED
#endif

#ifdef FQ_DEBUG
#endif

#ifdef _MSC_VER
#  define FQ_EXPORT __declspec(dllexport)
#else
#  define FQ_EXPORT __declspec(dllimport)
#endif

#endif // FQ_PLATFORM_H
