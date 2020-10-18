#include <iostream>

bool funcA() {
    int c;
    std::cout << "input(number) : ";
    std::cin >> c;
    if (c < 10) //Let's assume this is exception
        throw std::out_of_range("");

    return true;
}
int main() {
    try {
        funcA();
    }
    catch (std::exception& e) {
        std::cout << "Exception : Invalid Input!!" << std::endl;
    }
    
    /*if (funcA())
    {
    }
    else {
        std::cout << "Exception : Invalid Input!!" << std::endl;
    }
    return 0;*/
}
