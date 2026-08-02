#pragma once

#include <random>
#include <type_traits>
#include <cassert>

namespace tools
{

template<typename T>
class random
{
    static_assert(std::is_arithmetic_v<T>, "tools::random<T> requires an arithmetic type.");

    using DistroT = std::conditional_t<
        std::is_floating_point_v<T>,
        std::uniform_real_distribution<T>,
        std::uniform_int_distribution<T>
    >;

public:
    explicit random(T min, T max)
        : _generator(initGenerator())
        , _distro(min, max)
    {
        assert(max >= min && "max must be greater than or equal to min");
    }

    [[nodiscard]]
    T operator()()
    {
        return _distro(_generator);
    }

private:
    static std::mt19937 initGenerator()
    {
        std::random_device rd;

        std::seed_seq seed{
            rd(), rd(), rd(), rd(),
            rd(), rd(), rd(), rd()
        };

        return std::mt19937{ seed };
    }

    std::mt19937 _generator;
    DistroT _distro;
};

}
