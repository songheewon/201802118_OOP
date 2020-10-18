#include <iostream>
#include <stdexcept>
class Test {
public:
    Test(char id) : id_(id) {}
    ~Test() {
        std::cout << "Destructor execution: "
            << id_ << std::endl;
    }
private:
    char id_;
};
int funcB() {
    Test r('B');
    throw std::runtime_error("Exception from funcB!\n");
    std::cout << "Executed in B" << std::endl;
    return 0;
}
int funcA() {
    Test r('A');
    funcB();
    std::cout << "Executed in A" << std::endl;
    return 0;
}
int main() {
    try {
        funcA();
    }
    catch (std::exception& e) {
        std::cout << "Exception : " << e.what();
    }
}
/* (실습 1-1) 분석결과 :

< 출력 결과 >
Executed in B
Destructor execution: B
Executed in A
Destructor execution: A

< 코드 분석 >
우선, main()에서 funcA()를 호출합니다.
funcA()에 들어가게 되면, id가 A인 Test클래스의 객체를 하나 생성합니다.
그리고 나서 funcB()를 호출하고, funcB()에 들어가게 되면 id가 B인 Test클래스의 객체를 하나 생성합니다.
객체를 생성하고 나면 "Executed in B" 라는 메시지를 출력합니다.
메시지를 출력한 후, "return 0;" 에 의해 funcB()는 종료되고 소멸자가 실행됩니다.
소멸자에 의해 "Destructor execution: B"라는 메시지가 출력됩니다.
funcB()가 종료되었으므로 다시 funcA()로 돌아와서 funcB()호출 이후의 명령문들이 실행됩니다.
그러므로 "Executed in A" 라는 메시지가 출력됩니다.
그리고 나서 "return 0;" 에 의해 funcA()는 종료되고 소멸자가 실행됩니다.
소멸자에 의해 "Destructor execution: A"라는 메시지가 출력됩니다.
*/

/* (실습 1-2) 분석결과 : 

< 출력 결과 >
Destructor execution: B
Destructor execution: A
Exception : Exception from funcB!

< 코드 분석 >
실행 순서는 실습 1-1과 동일합니다.
이 떄, main()에서 try-catch문이 있는데, 실행 도중 예외가 발생할 경우 예외가 전파되어 catch
안으로 넘어가게됩니다.
즉, 주석을 해제할 경우, 예외가 발생되어 catch문으로 점프하게 됩니다.
** 이 시점에서 예외 발생 이후의 코드들은 실행이 안 됩니다. **
가장 가까운 catch문을 찾으면서 함수 내에서 사용된 지역변수 및 객체들을 해제해가며,
catch문을 만나기 전까지 스택을 정리해가며 자신의 호출원을 찾아가는데 이를 stack winding이라합니다.
*/

