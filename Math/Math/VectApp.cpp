#include "MathEngine.h"
#include "MathApp.h"

namespace EngineSpace
{
	void VectApp::Lerp(Vect& out, const Vect& a, const Vect& b, const float t)
	{
		Vect ta = a;
		Vect tb = b;

		out = ta + t * (tb - ta);
	}

	void VectApp::LerpArray(Vect* out, const Vect* a, const Vect* b, const float t, const int numVects)
	{
		for (int i = 0; i < numVects; i++)
		{
			Lerp(out[i], a[i], b[i], t);
		}
	}
}