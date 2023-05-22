#include <iostream>

int main() {


	int arr[3]{ 1,2,3 };

	std::cout << arr[0] << "\n";
	std::cout << *(arr + 0) << "\n";
	
	// x + y  , y + x 는 정확히 같은표현
	// 1 + 2 , 2 + 1 는 같은 표현이다.
	// arr[0] 는 *(arr+0) 는 *(0+arr) 와 같으 표현이다.
	// 그러므로 0[arr]는 arr[0]이랑 같은표현입니다.

	std::cout << *(0 + arr) << "\n";

	if (*(0 + arr) == *(arr + 0))
		std::cout << "두개는 동일한 표현입니다." << "\n";

	if (arr[0] == 0[arr])
		std::cout << "arr[0] 이랑 [0]arr랑은 같은 표현입니다." << "\n";

	return 0;
}
