#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <d3d9.h>

#define ALIGNED __declspec(align(16))

#define fPi 3.14159265359f
#define DegToRad(_angle) \
	((_angle) * fPi / 180.0f)

typedef int8_t int8;
typedef uint8_t uint8;

typedef int16_t int16;
typedef uint16_t uint16;

typedef int32_t int32;
typedef uint32_t uint32;

typedef int64_t int64;
typedef uint64_t uint64;

typedef intptr_t intptr;
typedef uintptr_t uintptr;

struct SVector {
	float x, y, z, w;
};

struct SSphere {
	float x, y, z, radius;
};

struct SAabb {
	SVector sup, inf;
};

struct Triangle {
	uint16 indices[3];
	int16  matIndex;
};

struct RGBA {
	uint8 red, green, blue, alpha;
};

struct IMVertex {
	float x, y, z;
	RGBA  color;
	float u, v;
};

enum IMPrimitiveType {
	PRIM_LINES,
	PRIM_TRIANGLES,
	PRIM_TRIANGLE_STRIP,
	PRIM_TRIANGLE_FAN,
	PRIM_QUADS
};

struct Link {
	Link* next, * prev;
};

#define LinkInitialize(_link) \
	((_link)->next = nullptr, (_link)->next = nullptr)

#define LinkAttached(_link) \
	((_link)->next != nullptr)

#define LinkGetData(_link, _type, _member) \
	reinterpret_cast<_type*>(reinterpret_cast<uint8*>(_link) - \
	offsetof(_type, _member))

struct LinkList : Link {};

#define LinkListInitialize(_list) \
	((_list)->next = (_list), (_list)->prev = (_list))

#define LinkListAttachLink(_list, _link) \
	((_link)->next = (_list)->next, \
	 (_link)->prev = (_list), \
	 (_list)->next->prev = (_link), \
	 (_list)->next = (_link))

#define LinkListAppendLink(_list, _link) \
	((_link)->next = (_list), \
	 (_link)->prev = (_list)->prev, \
	 (_list)->prev->next = (_link), \
	 (_list)->prev = (_link))

#define LinkListDetachLink(_link) \
	((_link)->next->prev = (_link)->prev, \
	 (_link)->prev->next = (_link)->next)