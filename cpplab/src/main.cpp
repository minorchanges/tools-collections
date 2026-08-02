#include "tools/random.h"
#include "tools/timer.h"

#include "HelperClass.hpp"

#include <iostream>

using std::cout;
using std::endl;

int main()
{
    tools::timer timer;
    tools::random<int> numberBetween0And10(0, 10);
    for(int i = 0; i < 10; i++)
    {
        cout << numberBetween0And10() << ", ";
    }
    cout << endl << timer.elapsed<std::chrono::microseconds>().count() << " us" << endl;

    HelperClass::print();
}
