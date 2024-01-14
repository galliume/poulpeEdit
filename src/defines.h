#pragma once

//@todo def with debug or not
#ifndef PLP_RELEASE
#define PLP_RELEASE = 0
#endif

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

typedef float f32;
typedef double f64;

//booleans
typedef int b32;
typedef char b8;

#if defined(WIN32) || defined (_WIN32) || defined(__WIN32__)
  #define PLPPLATFORM_WINDOWS 1
#elif defined(__linux__) || defined(__gnu_linux__)
  #define PLPPLATFORM_LINUX 1
#endif

#ifdef PLPEXPORT
  #ifdef _MSC_VER
    #define PLPAPI __declspec(dllexport)
  #else
    #define PLPAPI __attribute__((visibility("default")))
  #endif
  #else
  #ifdef _MSC_VER
    #define PLPAPI __declspec(dllimport)
  #else
    #define PLPAPI
  #endif
#endif