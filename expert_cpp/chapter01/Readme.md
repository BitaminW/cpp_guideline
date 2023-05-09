
## C++ 기초

### 모듈 임포트
C++20부터 새롭게 추가된 대표적인 기능 중 하나는 모듈이다. 모듈은 예전에 헤더 파일이라 부르던 메커니즘을 완전히 대체한다. 어떤 모듈에 담긴 기능을 사용하고 싶다면 그 모듈을 import 문으로 불러오면 된다.

```cpp
import <iostream>;
```

### 전처리 지시자
현재 사용하는 컴파일러가 아직 C++20 모듈 기능을 지원하지 않는다면 import 선언문을 다음과 같이 include 전처리 지시자로 변경해야한다.
```cpp
#include <iostream>
```
C++로 작성된 소스 코드를 프로그램으로 만드는 빌드 작업은 세 단계를 거친다. 먼저 전처리 단계에서는 소스 코드에 담긴 메타 정보를 처리한다. 이어서 컴파일 단계에서는 소스 코드를 머신이 읽을 수 있는 객체 파일로 변환한다.
마지막으로 링크 단계에서는 앞에서 변환한 여러 객체 파일을 애플리케이션으로 엮는다.

여기서 #include 지시자는 <iostream> 헤더 파일에 있는 내용을 현재 파일에서 사용할 수 있게 모두 가져오도록 전처리기에 지시한다. <iostream> 헤더는 C++에서 제공하는 입력과 출력 메커니즘을 선언한다.
헤더 파일의 주 용도는 소스 파일에서 정의할 함수를 선언하는 것이다. 이러한 함수 선언은 그 함수의 호출 방식, 매개변수의 개수와 타입, 리턴 타입 등을 컴파일러에 알려준다. C++ 모듈 기능이 도입되기 전에 선언문을 주로 확장가가 .h 인 헤더 파일에 작성하고 정의는 확장자가 .cpp인 소스 파일에 작성했다. 하지만 모듈 기능이 도입 되면서 더 이상 분리할 필요가 없어졌다.

>C 표준 라이브러리 헤더를 C++ 에서도 사용할 수 있다.
><stdio.h> 를 <cstdio> 로 .h 확장자 대신 c 접두어가 붙는다.

##### 자주 사용하는 전처리 지시자 정리
#
|`전처리 지시자`|
|------------|
|#include [file]|
|#define [키] [값]|
|#ifdef [키] #endif|
|#ifndef [키] #endif|
|#pragma [xyz] |

##### 중복 include를 막는 예시
```cpp
#ifndef MYHEADER_H  // 만약에 이 헤더파일을 define 하지 않았다면
#define MYGEADER_H  // << endif가 나오기 전까지 이 부분을 포함시켜라
// 헤더 내용
#endif
```

현재 사용하는 컴파일러에서 #pragma once 지시자를 사용할 수 있다.(최신 컴파일러는 대부분 지원한다.)
```cpp
#pragma once    // 1번만 컴파일 하고 그 뒤로부터 동일한 파일의 경우 읽기조차 하지 않는다.
```

### 네임스페이스
네임스페이스는 코드에서 이름이 서로 충돌하는 문제를 해결하기 위해 나온 개념이다. 예를 들어 foo() 함수를 정의해서 코드를 작성하다가 외부 라이브러리가 필요해서 추가했는데 그 라이브러리에도 동일한 이름에 foo()함수가 존재할 수도 있다. 이러한 문제를 방지하기 위해서 사용한다.
```cpp
namespace mycode{
    void foo(){
        std::cout << "foo() called in the mycode namespace" << std::endl;
    }
}

mycode::foo(); // mycode 네임스페이스에 정의된 foo() 함수를 호출한다.
```

mycode 네임스페이스 블록 안에서 접글할 때는 네임스페이스 접두어를 붙이지 않아도 된다. 또한 using 키워드로 네임스페이스 접두어를 생략할 수도 있다.

```cpp
using namespace mycode;

int main(){
    foo();  // mycode::foo(); 와 동일하다.
}
```

한 소스 파일에 using 지시자를 여러 개 지정할 수도 있다. 하지만 이 기능은 남용하지 않도록 주의 해야한다. 동일한 이름을 포함하는 두 개의 네임스페이스를 사용하는 경우에는 이름 충돌이 다시 발생할 것이다. 또한 실수로 엉뚱한 함수를 호출하지 않으려면
현재 코드에서 사용하는 네임스페이스를 명확히 파악해야 한다.

네임스페이스 안에 있는 특정한 항목만 가리키도록 using 문을 작성할 수 있다.
```cpp
#include <iostream>

using std::cout;

int main() {
	cout << "Hello world!";
}
```

### 중첩 네임스페이스
중첩 네임스페이스는 다른 네임스페이스 안에 있는 네임스페이스를 말한다.이 떄 각 네임스페이스는 더블 콜론(::)으로 구분한다.

C++17 이전에는 이러한 간결한 문법을 지원하지 않아서 아래와 같이 작성했다.
```cpp
namespace TestLibraries {
	namespace Networking {
		namespace FTP {
			// domsomething..
		}
	}
}
```

하지만 C++17부터 지원하는 중첩 네임스페이스를 사용하면 아래와 같이 사용할 수 있다.
```cpp
namespace TestLibraries::Networking::FTP {
	// dosomething
}
```

### 네임스페이스 앨리어스
네임스페이스 앨리어스를 사용하면 네임스페이스의 이름을 다르게 만들거나 또는 더 짧게 만들 수 있다.
```cpp
namespace TestLibraries::Networking::FTP {
	int test = 10;
}
namespace MyFTP = TestLibraries::Networking::FTP;   // 네임스페이스 별칭을 MyFTP라고 지정했다.

int main() {
	cout << MyFTP::test;
}
```

### 리터럴
리터럴은 코드에 표시한 숫자나 스프링과 같은 값을 의미한다. C++는 다양한 표준 리터럴을 제공한다. 숫자는 다음과 같은 리터럴로 표현할 수 있다.(아래 나온 값은 모두 숫자 123을 가르킨다.)

+ 10진수 리터럴: 123
+ 8진수 리터럴: 0173
+ 16진수 리터럴: 0x7B
+ 이진수 리터럴: 0b1111011

또한 C++에서는 다음과 같은 리터럴도 지원한다.

+ 부동소수점 값 (3.14f)
+ 배점도 부동소수점 값 (3.14)
+ 16진수 부동소수점 리터럴 (0x3.ABCp-10, 0xb.cp121)
+ 단일 문자 ('a')
+ \0으로 끝나는 문자 배뎔 ("Hello world")

리터럴 타입을 직접 정의할 수도 있다.

숫자 리터럴에서는 자릿수 구분자를 사용할 수 있다.
+ 23'465'789
+ 0.132'456f


### 균일 초기화(Uniform initaulization)
C++11 부터 지원하는 균일 초기화는 {}기호를 통해 사용한다.
```cpp
    int a = 10;
    int b {10};
```

C++11 이전에는 타입의 초기화 방식이 일정하지 않았다. 예를 들어 원을 구조체로 정의한 경우와 클래스로 작성한 경우를 살펴보자.

```cpp
struct CircleStruct {
	int x, y;
	double radius;
};

class CircleClass {
private:
	int x, y;
	double radius;

public:
	CircleClass(int x, int y, double radius) 
		: x{x}, y{y}, radius{ radius } {}
};
```

C++11 이전에는 구조체로 선언한 변수와 클래스로 선언한 변수를 초기화하는 방법이 서로 달랐다.

```cpp
	CircleStruct circle1 = { 10, 20, 2.5 };
    CircleClass circle2(10, 10, 2.5);
```

구조체에 대해서는 {}을 적용한 반면 클래스에 대해서는 함수 표기법인 ()로 생성자를 호출한다.하지만 C++11부터 타입을 초기화할 때 유니폼 초기화 문법을 사용하는 초기화 방식이 통일되었다.
또한 위 생성자를 작성할 때 사용한 멤버 이니셜라이저에서도 ()대신 {} 균일 초기화를 사용할 수 있다.

균일 초기화는 구조체와 클래스뿐 아니라 C++에 있는 모든 대상을 초기화하는데 적용할 수 있다.
```cpp
int a = 1;
int b(2);
int c = {3};    // 균일초기화
int d{4};       // 균일초기화
```

#### 축소 변환 방지
균일 초기화에서 큰 장점이 있다. 바로 축소 변환을 방지할 수 있다. 다음 코드를 살펴보자

```cpp
void func(int x) {
	cout << x << endl;
}

int main() {
	int x = 3.14;
	func(3.14);
	func(x);

}
```
코드를 살펴보면 x는 모두 int타입이기 때문에 들어간 3.14는 모두 값 손실이 일어난다. 하지만 C++11 표준을 완전히 지원하는 컴파일러를 사용하고 유니폼 초기화를 사용한다면 에러 메세지가 생성된다.

```cpp
    int x = {3.14};     // 에러메세지 'conversion form 'double' to 'int' requires a narrowing conversion
```

균일 초기화는 동적으로 할당되는 배열을 초기화할 떄도 적용할 수 있다.
```cpp
int* pArray = new int[4]{ 1,2,3,4 };
```

최신 C++20부터는 배열의 크기도 생략할 수 있다.

```cpp
int* pArray = new int[]{ 1,2,3,4 }; // C++ 20
```


### 열거 타입
상수는 사실 연속적으로 나열한 숫자 중 하나를 표현한 것이다. 열거 타입을 사용하면 숫자를 나열하는 방식과 범위를 마음대로 정의해서 변수를 선언하는 데 활용할 수 있다.예를 들어 체스 프로그램을 작성할  때 각 말의 종류를 다음과 같이 int 타입의 상수로 표기한다고 하자.
```cpp
const int PieceTypeKing{ 0 };
const int PieceTypeQueen{ 0 };
const int PieceTypeRook{ 0 };
const int PieceTypePawn{ 0 };
int currentPiece{ PieceTypeKing };
```

위처럼 하드코딩해도 되지만 여러 상황이 발생할 수 있는데 현재 말을 표현하는 currentPiece은 const가 아니기 때문에 값을 수정할 수도 있다. 또한 앞서 정의하지 않은 -1과 같은 값으로 지정하면 심각한 오류를 발생 시킬수도 있다.

이럴때 강타입 열거 타입을 적용하면 변수에 지정할 수 있는 값이 범위를 엄격하게 제한하기 떄문에 이러한 문제를 방지할 수 있다.
```cpp
enum class PieceType{King, Queen, Rook, Pawn};

PieceType piece{PieceType::King};
```

이 떄 enum 타입을 구성하는 멤버는 내부적으로 정숫값으로 표현된다. 위 값에 0부터 차례로 값이 카운트된다.
값의 범위를 별도로 지정할 수도 있다.

```cpp
enum class PieceType {
	King = 1, Queen = 10, Rook = 55, Pawn = 3
};
PieceType piece{ PieceType::Pawn };
```

하지만 enum 타입을 구성하는 멤버가 정숫값으로 표현된다고 해서 자동으로 정수로 형변환되지 않는다.
```cpp
PieceType piece{ PieceType::Pawn };

int main() {
	cout << static_cast<int>(piece) << "\n";
}
```
위와 같이 형변환을 실행해줘야한다. enum class 가 아닌 기본 enum 을 사용한다면 자동으로 정수로 형변환이 된다.
그렇기 때문에 서로 다른 열거 타입이 있어도 서로 비교가 가능했다.
```cpp
enum TestType1 {
	one = 1, two = 2, three = 3
};

enum TestType2 {
	four = 4, five = 5, six = 6
};

int main() {

	TestType1 num1{ TestType1::one };
	TestType2 num2{ TestType2::four };

	if (num1 != num2) {
		cout << "비교가 가능합니다." << endl;
	}

}
```
실제로 내부값이 정수로 취급하기 때문에 비교가 되지만 의미상으로 두 enum은 서로 다른 타입이라는것이 옳지않다.

C++20 부터는 using enum으로 선언하면 열것값을 길게 풀어 쓰지 않아도 된다.
```cpp
using enum PieceType;
PieceType piece{ King };    // using 을 사용하여 길게 쓰지 않아도됨
piece = PieceType::Queen;   // using 을 사용하지 않았기 때문에 길게 써야함
```
