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

    // Member variables
    float m_Previous;
};

} // namespace Crystallizer
