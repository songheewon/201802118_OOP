#include <iostream>
#include <string>

template<typename T>
auto sum(T x) {
	return x;
}

template<typename T, typename...Args>
auto sum(T x, Args... args) {
	return x + sum(args...);
}

int main() {
	auto x = sum(42.5, 10, 11.1f);
	std::cout << x;
	getchar();
}

// 결과 화면
// 63.6

// 재귀가 반복되다가 나중에는 파라미터가 하나 남게 될 경우,
// 파라미터 하나만 받는 sum메소드가 없기 때문에 오류가 발생
// 그러므로 파라미터로 T x만을 받는 sum메소드를 작성해준다.
