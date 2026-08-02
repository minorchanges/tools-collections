#pragma once

#include <functional>
#include <atomic>

namespace engine
{
void process(int cycles, std::function<void(int)> progressHandler = {}, std::atomic_bool* cancelFlag = nullptr);
}
