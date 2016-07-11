#pragma once
#include <iostream>
#include <assert.h>

#include <set>
#include <map>
#include <hash_map>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <string>

using namespace std;

#define STATIC_ASSERT(exp, name) typedef int dummy##name [(exp) ? 1 : -1]
#define STATIC_ASSERT_ARRAY_LENGTH(arr, len) STATIC_ASSERT(sizeof(arr)/sizeof(arr[0])==(len), ___sizeErr##arr)
#define STATIC_ASSERT_ARRAY_ARRAY(arrA, arrB) STATIC_ASSERT(sizeof(arrA)/sizeof(arrA[0])==sizeof(arrB)/sizeof(arrB[0]), ___sizeErr##arr)

typedef unsigned char       byte;
typedef unsigned short      WORD;
typedef unsigned long       DWORD;
typedef const char			*LPCSTR, *PCSTR;