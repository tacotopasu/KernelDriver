#include <iostream>
#include "kernelinterface.hpp"

int main()
{
    KernelInterface Driver = KernelInterface("\\\\.\\tacohacking");
    ULONG address = Driver.GetClientAddress();
    std::cout << "yolo > " << address << std::endl;

    while (true)
    {

    }
}
