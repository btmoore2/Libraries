#include "MathEngine.h"
#include "MathApp.h"

namespace EngineSpace
{
	void QuatApp::Slerp(Quat& result, const Quat& src, const Quat& tar, const float slerpFactor)
	{
		Quat tSrc = src;
		Quat tTar = tar;

		float tCos = tSrc.dot(tTar);

		if (tCos < 0)
		{
			tCos = -tCos;
			tTar = -tTar;
		}

		if (tCos == 1)
		{
			result = tSrc + slerpFactor * (tTar - tSrc);
			return;
		}

		float angle = Trig::acos(tCos);

		result = tSrc * Trig::sin((1.0f - slerpFactor) * angle) / Trig::sin(angle) + tTar * Trig::sin(slerpFactor * angle) / Trig::sin(angle);
	};

	void QuatApp::SlerpArray(Quat* out, const Quat* source, const Quat* target, const float slerpFactor, const int numQuats)
	{
		for (int i = 0; i < numQuats; i++)
		{
			Slerp(out[i], source[i], target[i], slerpFactor);
		}
	};
}