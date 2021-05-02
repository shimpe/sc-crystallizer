// PluginCrystallizer.cpp
// Stefaan Himpe (manifest.heap@gmail.com)

#include "SC_PlugIn.hpp"
#include "Crystallizer.hpp"

static InterfaceTable* ft;

namespace Crystallizer {

Crystallizer::Crystallizer() 
: m_Previous(0)
{
    if (inRate(1) == calc_ScalarRate) {
        mCalcFunc = make_calc_function<Crystallizer, &Crystallizer::next_scalar_mult>();
    } else if (inRate(1) ==  calc_BufRate) {
        mCalcFunc = make_calc_function<Crystallizer, &Crystallizer::next_control_mult>();
    }
    else {
        mCalcFunc = make_calc_function<Crystallizer, &Crystallizer::next>();
    }
    
    m_ScalarMult = in0(1);
    
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

void Crystallizer::next_control_mult(int nSamples) {
    const float* input = in(0);
    float mult = in(1)[0];
    float* dst = out(0);

    for (int i = 0; i < nSamples; ++i) { 
        float current = input[i];
        dst[i] = current + (current - m_Previous) * mult;
        if (dst[i] > 1) { dst[i] = 1; }
        else if (dst[i] < -1) { dst[i] = -1; }
        m_Previous = current;
    }
}

void Crystallizer::next_scalar_mult(int nSamples) {
    const float* input = in(0);
    float* dst = out(0);

    for (int i = 0; i < nSamples; ++i) { 
        float current = input[i];
        dst[i] = current + (current - m_Previous) * m_ScalarMult;
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
