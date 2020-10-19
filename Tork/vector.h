#pragma once
#ifndef __VECTOR_H__
#define __VECTOR_H__

namespace vec
{
	// 2D Vector Class
	typedef class v2
	{
	public:
		float x = 0, y = 0;
	}         v2;

	typedef class p2
	{
	public:
		float x = 0, y = 0;
	}         p2;

	typedef class s2
	{
	public:
		float w = 0, h = 0;
	}         s2;

	// 3D Vector Class
	typedef class v3
	{
	public:
		float x = 0, y = 0, z = 0;
		     v3() = default;
		     v3(float lx, float ly, float lz);
		bool is_empty() const;
		void clear();
	}        v3;
}

typedef vec::v3 v3;
typedef vec::v2 v2;
typedef vec::p2 p2;
typedef vec::s2 s2;

#endif
