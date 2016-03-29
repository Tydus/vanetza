#include "runtime.hpp"
#include <cassert>

namespace vanetza
{

void Runtime::schedule(Clock::time_point tp, const Callback& cb, const std::string& name)
{
    m_queue.insert(queue_bimap::value_type { tp, name, cb });
}

void Runtime::schedule(Clock::duration d, const Callback& cb, const std::string& name)
{
    schedule(m_now + d, cb, name);
}

Clock::time_point Runtime::next()
{
    Clock::time_point next_tp = Clock::time_point::max();
    if (!m_queue.empty()) {
        next_tp = m_queue.left.begin()->first;
    }
    return next_tp;
}

const Clock::time_point& Runtime::now() const
{
    return m_now;
}

void Runtime::trigger(Clock::time_point tp)
{
    // require monotonic clock
    assert(tp >= m_now);
    m_now = tp;
    trigger();
}

void Runtime::trigger(Clock::duration d)
{
    m_now += d;
    trigger();
}

void Runtime::trigger()
{
    // process queue elements separately because callback might modify runtime
    while (!m_queue.empty()) {
        auto top = m_queue.left.begin();
        const auto& deadline = top->first;
        if (deadline <= m_now) {
            Callback cb = top->info;
            m_queue.left.erase(top);
            // callback invocation has to be last action because it might modify runtime
            cb(m_now);
        } else {
            break;
        }
    }
}

void Runtime::reset(Clock::time_point tp)
{
    m_now = tp;
    m_queue.clear();
}

} // namespace vanetza
