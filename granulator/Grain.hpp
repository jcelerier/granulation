#pragma once
#include "Envelope.hpp"
#include "Source.hpp"

namespace Granulation {
namespace Synthesis {

class Grain {
public:
    Grain(Envelope& e, Source& s);
    Grain(const Grain&);

    bool completed() const;
    void activate(int duration);
    float synthetize();
    bool isActive() const;
    bool isReadBackwards() const;
    void operator=(const Grain&);

private:
    Envelope& m_envelope;
    Source& m_source;
    int m_index {0};
    float m_speedRatio {1.f};
    bool m_active {false};
    bool m_readBackwards {false};
};


}
}
