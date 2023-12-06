#include <iostream>
#include "task1.hpp"
#include "task2.hpp"

int main() {
    std::cout << "Day2" << std::endl;
    task1 t1;
    t1.Run();

    task2 t2;
    //t2.Tests();
    t2.Run();

    return 0;
}
