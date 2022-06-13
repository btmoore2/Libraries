#include "MathEngine.h"
#include <math.h>

namespace EngineSpace
{
	float Trig::cos(float in)
	{
		return cosf(in);
	}

	float Trig::sin(float in)
	{
		return sinf(in);
	}

	float Trig::tan(float in)
	{
		return tanf(in);
	}

	float Trig::atan(float in)
	{
		return atanf(in);
	}

	float Trig::atan2(float y, float x)
	{
		return atan2f(y, x);
	}

	float Trig::acos(float in)
	{
		return acosf(in);
	}

	float Trig::asin(float in)
	{
		return asinf(in);
	}

	void Trig::cossin(float& c, float& s, float angle)
	{
		c = cosf(angle);
		s = sinf(angle);
	}

	float Trig::sqrt(float in)
	{
		return sqrtf(in);
	}

	float Trig::rsqrt(float in)
	{
		return 1.0f / sqrtf(in);
	}

	float Trig::abs(float in)
	{
		return fabs(in);
	}
}
