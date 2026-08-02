#pragma once

#include <chrono>

namespace tools
{

class timer
{
    using clock = std::chrono::steady_clock;

public:
    timer() noexcept = default;

    void reset() noexcept
    {
        m_ref = clock::now();
    }

    template<class Duration = std::chrono::milliseconds>
    [[nodiscard]]
    Duration elapsed() const noexcept
    {
        return std::chrono::duration_cast<Duration>(clock::now() - m_ref);
    }

private:
    clock::time_point m_ref{clock::now()};
};

} // namespace tools
