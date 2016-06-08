#include "Scheduler.hpp"
#include "SequenceStrategy.hpp"
#include "Grain.hpp"
#include <QDebug>

namespace Granulation {
namespace Synthesis {

Scheduler::Scheduler() {}
Scheduler::Scheduler(SequenceStrategy *strategy) :
    m_grains{std::vector<Grain> ()},
    m_strategy{strategy}
{}

float Scheduler::synthetize() {
    //qDebug() << "scheduler is synthetizing from" << m_grains.size() << "grains";
    int nactive = 0;
    int ncompleted = 0;
    float amp = 0.f;
    for (auto it = m_grains.begin(); it != m_grains.end(); ++it) {
        Grain grain = *it;
        if (grain.isActive() && !grain.completed()) {
            amp += grain.synthetize();
            ++it;
            ++nactive;
        }
        if (grain.completed())
            ++ncompleted;
    }
    removeCompleted();
    if (nactive > 0)
        qDebug() << nactive << "grains were active and" << ncompleted << "grains completed for a synthetized value of" << amp;
    return amp;
}

void Scheduler::setStrategy(SequenceStrategy *strategy) {
    m_strategy = strategy;
}

void Scheduler::addGrain(Envelope& e, Source& s) {
    qDebug() << "adding new grain";
    m_grains.push_back(Grain(e, s));
}

void Scheduler::activateNext() {
    auto it = m_grains.begin();
    for (; it != m_grains.end() && it->isActive(); ++it) {}
    if (it != m_grains.end()) {
        it->activate(m_strategy->nextDuration());
        qDebug() << "grain was activated";
    }
}

void Scheduler::removeCompleted() {
    int n = 0;
    for (int i = 0; i < m_grains.size();) {
        Grain g = m_grains[i];
        if (g.completed()) {
            m_grains.erase(std::next(m_grains.begin(), i));
            ++n;
        }
        else {
            ++i;
        }
    }
    if (n > 0)
        qDebug() << "removed" << n << "grains out of" << grainCount();
}

int Scheduler::grainCount() const {
    return m_grains.size();
}

void Scheduler::updateTime(double streamTime) {
    if (m_grains.size() > 0 && m_strategy->update(streamTime))
        activateNext();
}

}
}
