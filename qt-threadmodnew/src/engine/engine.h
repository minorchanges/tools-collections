#pragma once

#include <functional>

namespace engine
{
    void process(int cycles, std::function<void(int)> progressHandler = {});
}
