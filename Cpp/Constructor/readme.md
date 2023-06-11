### 생성자 정리

String 클래스를 정의하면서 c++에서의 객체 복사의 대해서 정리해보았습니다.
아래는 String 클래스의 기본 멤버 구조입니다.
```cpp
class String{
private:
    int len;
    char* str;
};
```
별건 없고 문자열의 길이와 문자열을 가지고 있는 공간을 가르키는 포인터 하나를 가지고 있습니다.
다음으론 기본적으로 게터와 세터를 정의할껀데 getter만 정의하겠습니다.

```cpp
class String{
private:
    int len;
    char* str;

public:
    int getLen() const {
		return len;
	}

	char* getStr() const {
		return str;
	}
};
```
기본적으로 문자열의 길이는 Length() 라던지 객체를 그대로 cout에 그대로 넣어줬을 떄 입출력 오버로딩을 통해서 문자열 그대로 출력하게 하면 좋겠지만 생성자 예제이기 때문에 그냥 대충 정의해보겠습니다.

위 사용자가 정의한 클래스를 사용한다면 아래와 같이 사용합니다.
```cpp
String s1;
String s2{};   // 유니폼 초기화
```

보통 생성자를 정의를 해주지 않으면 자동으로 디폴트 생성자가 정의가 되기 때문에 위 코드는 문제없이 동작합니다.
하지만 문자열을 넣어줘야 하기 때문에 문자열을 받을 수 있는 생성자를 정의해보겠습니다.

```cpp
String s2 = "Hello";
```
이런식으로 객체를 생성한다면 이에 맞는 생성자를 정의해줘야합니다.

```cpp
String(const char* strData){
    len = strlen(strData);
    str = new char[len + 1];
    strcpy(str, strData);
}
```

위에 String 타입에 s2 라는 객체에 "Hello" 라는 문자열 리터럴을 집어넣습니다. 이 때 저 "Hello" 라는 문자열은 
**data 영역에 rodata(read only data)** 영역에 수정할 수 없는 형태로 저장되어 있습니다. 이 때 이 데이터는 수정할 수 없는
역역에 있는 데이터이기 떄문에 const char* 형태로 받습니다. 사실 c언어에서는 이렇게 해주지 않아도 되지만 C++ 는 컴파일러 마다 경고 메세지나 에러를 냅니다.
위 객체를 출력해보면 결과가 잘 나올것입니다.

```cpp
std::cout << s2.getStr() << " : " << s2.getLen() << "\n";
```

여기까지는 별로 문제가 없습니다. 하지만 위 코드에선 동적할당을 사용하고 있습니다. 당연히 수동적으로 메모리를 해제 해야합니다. 여기서 저 str멤버가 가지고 있는 메모리를 해제시켜줄려면 다음과 같이 해제해줘도 됩니다.

```cpp
delete[] s2.getStr();
```

getStr()은 s2의 멤버 str이 가지고 있는 동적할당이 된 주소를 반환할겁니다. 하지만 이렇게 해제를 해준다면 상당히 번거롭습니다.
만약 String 객체가 한 50개 있다면 그걸 하나하나 메모리를 해제해줘야 할까요? 또한 개별적으로 작업한다면 실수할 여지가 있습니다. 동일한 메모리를 해제한다던지 뭘 하나 빠뜨린다던지 이 때 객체가 소멸될 때 호출되는 소멸자안에서 메모리를 해제해줍니다.

```cpp
~String() {
    delete[] str;
}
```

자 이렇게 된다면 객체가 소멸되는 시점에서 소멸자가 호출이 되어 동적할당한 자원들을 자동으로 해제해줄것입니다.
하지만 우리는 이 뿐만이 아니라 다른 방법으로도 객체를 생성할것입니다. 예를들면

```cpp
String s2 = "Hello";
String s3 = s2;
```
이러한 방식으로 객체를 생성할수도 있습니다. 위와 같이 생성을 해보면 에러가 발생할것입니다.
왜냐하면 우리는 복사생성자를 정의해주지 않았기 때문입니다. 복사생성자는 기본적으로 정의해주지 않는다면 디폴트 복사생성자가 정의되어서 얕은복사가 일어납니다.

```cpp
String s2 = "Hello";     // s2 가 가지고 있는 str 멤버는 100번지를 가르킴
String s3 = s2;     // 얕은 복사 발생     s3가 가지고 있는 str 멤버는 100번지를 가르킴
```
s3와 s2가 가지고 있는 str 포인터는 같은곳을 가르킵니다. 이 떄 이 s2 와 s3가 소멸되면서 소멸자가 호출되는데
이미 s3가 소멸되면서 해제한 100번지를 다시 s2가 소멸되면서 이미 해제가 되버린 메모리를 다시 해제합니다.
```cpp
~String() {
    delete[] str;       // 동일한 100번지를 해제함
}
```
이렇게 되면 이미 해제가 된 동일한 메모리를 해제하기 떄문에 문제가 발생합니다. 만약 소멸자를 주석처리하고
다음과 같이 한곳만 해제를 한다면 별 문제가 발생하지 않습니다.
```cpp
delete[] s2.getStr();
```
하지만 이렇게 되면 다시 하나하나 해제해줘야하는 상황에 놓이게 되고 개발자는 String인 독립적인 객체를 원하는데 의도한 방식이 아니라면 문제가 됩니다. 이 때 복사생성자를 정의해주면 됩니다.


```cpp
	String(String& rhs){
		len = strlen(rhs.str);
		str = new char[len + 1];
		strcpy(str, rhs.str);
	}
```
이렇게 해주면 끝입니다. 매개변수인 String 을 레퍼런스로 받는 이유는 매개변수로 들어오는 String 객체를 새로 만들 필요가 없기 때문입니다. 또한 이 매개변수는 수정되지 않는 녀석이기 때문에 다음과 같이 const 를 붙여주는게 좋습니다.
```cpp
	String(const String& rhs){
		len = strlen(rhs.str);
		str = new char[len + 1];
		strcpy(str, rhs.str);
	}
```

지금까지 작성한 코드는 다음과 같습니다.
```cpp
class String {

private:
	int len;
	char* str;

public:

	String() : len{ 0 }, str{ nullptr } {}
	String(const char* strData) {
		len = strlen(strData);
		str = new char[len + 1];
		strcpy(str, strData);
	}

	String(const String& rhs){
		len = strlen(rhs.str);
		str = new char[len + 1];
		strcpy(str, rhs.str);
	}

	~String() {
		delete[] str;
	}

	int getLen() const {
		return len;
	}

	char* getStr() const {
		return str;
	}
};
```

하지만 복사생성자를 호출하는 것이 아닌 기존에 이미 생성되어있는 객체에 대입을 하는 방식을 한다면 어떻게 될까요?

```cpp
String s1;
String s2 = "Hello";
s1 = s2;
```
다음과 같은 코드를 작성하게 된다면 에러가 발생합니다.
기본적으로 대입연산자는 디폴트 연산자가 사용되기 떄문에 위 코드에서 디폴트 대입연산자는 얕은 복사를 일으킵니다.
대입할땐 문제가 되지 않지만 소멸자를 호출할 떄 동일한 메모리를 두번 해제하기 때문에 문제가 발생합니다.(사실 사용자 또한 얕은복사를 원하는게 아니라면 동일한 곳을 가르키기 때문에 대입할 떄 또한 원하지 않는 동작을 야기합니다.)


```cpp
	String& operator=(String& rhs) {

		// this가 자기 자신이 아닐경우에
		if (this != &rhs) {
			delete[] str;

			len = rhs.len;
			str = new char[len + 1];
			strcpy(str, rhs.str);
		}
		return *this;
	}
```

위와 같이 구현해줍니다. 사실 위에서 s1 = s2 라는 구문은 아래구문과 동일합니다.

```cpp
s1.operator=(s2);
```

위에서 this != &rhs 를 하는 이유는 자기 자신을 대입했을때 문제가 발생하기 떄문입니다. 예를들어서

```cpp
s1 = s1;
``` 
이런식으로 작성해도 에러가 발생하지 않습니다. 하지만 기본적으로 delete[] str; 을 실행하면서 메모리를 지우고 아래 복사하는 구문을 실행하기 때문에 의도치 않은 동작이 발생합니다.

또한 반환값을 참조자로 하는 이유는 return *this 에서 자기 자신을 반환하면서 임시객체를 생성하게 되는데 이 때 참조값이 아닌 값 자체를 반환하게 되면 의미없는 복사생성이 일어나게 됩니다.



```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

static int cnt = 0;

class String {

private:
	int len;
	char* str;

public:

	String() : len{ 0 }, str{ nullptr } {}
	String(const char* strData) : String() {
		len = strlen(strData);
		str = new char[len + 1];
		strcpy(str, strData);
	}

	String(const String& rhs){
		len = strlen(rhs.str);
		str = new char[len + 1];
		strcpy(str, rhs.str);
		std::cout << "복사생성자 호출" << "\n";
	}

	String& operator=(String& rhs) {

		// this가 자기 자신이 아닐경우에
		if (this != &rhs) {
			delete[] str;

			len = rhs.len;
			str = new char[len + 1];
			strcpy(str, rhs.str);
		}
		return *this;
	}

	~String() {
		delete[] str;
		++cnt;
		std::cout << "소멸자 호출: " << cnt << "\n";
	}

	int getLen() const {
		return len;
	}

	char* getStr() const {
		return str;
	}
};

int main() {

	String s1;
	String s2 = "Hello";
	std::cout << s2.getStr() << " : " << s2.getLen() << "\n";

	String s3 = s2;
	std::cout << s3.getStr() << " : " << s3.getLen() << "\n";
	s1 = s2;
	std::cout << s1.getStr() << " : " << s1.getLen() << "\n";
	s1 = s1;	// 자기자신을 대입하면 아무일도 안하고 자기자신을 반환함
	std::cout << s1.getStr() << " : " << s1.getLen() << "\n";

	return 0;
}


```
