#include "engine.h"

#include <chrono>
#include <thread>
#include <functional>
#include <atomic>
#include <iostream>

using std::this_thread::sleep_for;
using std::chrono::milliseconds;

namespace engine
{
    //Makes the engine do stuff
    void process(int cycles, std::function<void(int)> progressHandler, std::atomic_bool* cancelFlag)
    {
        for(int i = 1; i <= cycles; i++)
        {
            if(cancelFlag and *cancelFlag){std::cout << "Cancelled" << std::endl; return;}

            sleep_for(milliseconds(30));

            if(progressHandler)
            {
                int currentProgress = static_cast<int>((static_cast<double>(i) / static_cast<double>(cycles) * 100.0));
                progressHandler(currentProgress);
            }
        }
    }
}
