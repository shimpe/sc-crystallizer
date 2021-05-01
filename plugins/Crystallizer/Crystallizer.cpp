// PluginCrystallizer.cpp
// Stefaan Himpe (manifest.heap@gmail.com)

#include "SC_PlugIn.hpp"
#include "Crystallizer.hpp"

static InterfaceTable* ft;

namespace Crystallizer {

Crystallizer::Crystallizer() 
: m_Previous(0)
{
    mCalcFunc = make_calc_function<Crystallizer, &Crystallizer::next>();
    next(1);
}

void Crystallizer::next(int nSamples) {
    const float* input = in(0);
    const float* mult = in(1);
    float* dst = out(0);

    for (int i = 0; i < nSamples; ++i) { 
	float current = input[i];
	dst[i] = current + (current - m_Previous) * mult[i];
	if (dst[i] > 1) { dst[i] = 1; }
	else if (dst[i] < -1) { dst[i] = -1; }
	m_Previous = current;
    }
}

} // namespace Crystallizer

PluginLoad(CrystallizerUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<Crystallizer::Crystallizer>(ft, "Crystallizer", false);
}
