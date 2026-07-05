#include "engine.h"

#include <chrono>
#include <thread>
#include <functional>
// #include <iostream>

using std::this_thread::sleep_for;
using std::chrono::milliseconds;

namespace engine
{
    //Makes the engine do stuff
    void process(int cycles, std::function<void(int)> progressHandler)
    {
        for(int i = 1; i <= cycles; i++)
        {
            sleep_for(milliseconds(30));

            if(progressHandler)
            {
                int currentProgress = static_cast<int>((static_cast<double>(i) / static_cast<double>(cycles) * 100.0));
                progressHandler(currentProgress);
            }
            // else
            // {
            //     std::cout << "Nothing to do!" << std::endl;
            // }
        }
    }
}
