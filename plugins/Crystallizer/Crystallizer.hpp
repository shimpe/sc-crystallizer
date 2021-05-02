// PluginCrystallizer.hpp
// Stefaan Himpe (manifest.heap@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"

namespace Crystallizer {

class Crystallizer : public SCUnit {
public:
    Crystallizer();

    // Destructor
    // ~Crystallizer();

private:
    // Calc function
    void next(int nSamples);
    void next_control_mult(int nSamples);
    void next_scalar_mult(int nSamples);

    // Member variables
    float m_Previous;
    float m_ScalarMult;
};

} // namespace Crystallizer
