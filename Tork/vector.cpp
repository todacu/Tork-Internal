#include "pch.h"
#include "vector.h"

namespace vec
{
	// Vector3 non default constructor 
	v3::v3(const float lx, const float ly, const float lz)
	{
		x = lx;
		y = ly;
		z = lz;
	}

	// Check if vector is empty 
	bool v3::is_empty() const
	{
		return x == 0.f && y == 0.f && z == 0.f;
	}

	// Empty the vector
	void v3::clear()
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
	}
};
