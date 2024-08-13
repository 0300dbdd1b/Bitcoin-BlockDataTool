#ifndef PLATFORM_H
 #define PLATFORM_H

 #define CPP98 199711L
 #define CPP11 201103L
 #define CPP14 201402L
 #define CPP17 201703L
 #define CPP20 202002L

 #if __cplusplus == CPP98
    #define CPP_VERSION "C++98"
 #elif __cplusplus == CPP11
    #define CPP_VERSION "C++11"
 #elif __cplusplus == CPP14
    #define CPP_VERSION "C++14"
 #elif __cplusplus == CPP17
    #define CPP_VERSION "C++17"
 #elif __cplusplus == CPP20
    #define CPP_VERSION "C++20"
 #else
    #define CPP_VERSION "Unknown"
 #endif

 #if __cplusplus < CPP17
	#error "Unknown or too old C++ version"
 #endif

 #if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_WINDOWS
 #endif

 #if defined(__linux__)
    #define PLATFORM_LINUX
 #endif

 #if defined(__APPLE__) && defined(__MACH__)
    #define PLATFORM_DARWIN
 #endif

/********************************************************/

#ifdef PLATFORM_WINDOWS
    #include <windows.h>
#endif

#ifdef PLATFORM_LINUX
#endif

#ifdef PLATFORM_DARWIN
#endif

#endif // PLATFORM_H

