
## 연산자 오버로딩
C++는 연산자 오버로딩(**operator overloading**)을 지원하는 언어이다.
다음과 같은 코드에서 

```cpp
int a = 10, b = 20;
int c = a + b;
```
위 원시타입같은 경우엔 기본적으로 연산할 수 있는 연산자를 제공한다. 하지만 사용자가 정의한 자료형이나 혹은 사용자가 정의한 자료형과 원시 자료형과의 연산같은 경우엔 이 연산자 오버로딩을 하지 않았을 경우 불가능하다.

다음과 같은 자료형을 만들었다고 가정해보자
```cpp
class Point {
private:
	int x;
	int y;

public:
	Point(int x = 0, int y = 0) : x{x}, y{y} {}

    void printXY() const {
		cout << x << "," << y << "\n";
	}
};
```
이 Point라는 객체를 사용하다가 문득 x 좌표와 y 좌표끼리의 연산을 하고 싶어서 다음과 같이 연산하게 될 경우 오류가 발생한다.

```cpp
    Point p1{1, 1};
	Point p2{2, 2};

	Point p3 = p1 + p2;
``` 
왜나하면 사용자가 정의한 객체는 더하기를 지원할지 곱하기를 지원할지 지원한다면 어떻게 지원할지 알 수가없기 때문이다.
다음과 같이 연산자 오버로딩을 작성하고
```cpp
	Point operator+(const Point& p) {
		Point result{*this};
		result.x += p.x;
		result.y += p.y;

		return result;
	}
```

p3의 printXY 메서드를 호출해 보면 3, 3이라는 결과가 잘 동작한다.
```cpp
    int main(){
        Point p1{1, 1};
        Point p2{2, 2};

        Point p3 = p1 + p2;
        p3.printXY();

        return 0;
    }
```

이 때 연산자 오버로딩의 반환값과 매개변수로 받는 형식이 중요하다. 위 클래스는 복사생성자를 정의하지 않았기 때문에 기본적으로 디폴트 복사생성자를 호출하게된다.이 때 얕은 복사가 일어나게 되는데 위 경우에서 operator+()에서 p1객체로 p1 역할을 하는 result라는 임시변수를 만들었고 이 result 와 오른쪽 피연사자의 x 와 y값을 연산 해준뒤에 result를 반환한다.
이 때 return result에서 임시객체가 생성되고 원래는 p1 + p2 평가식 후에 사라져야할 임시객체가 p3로 이식된다.

만약 += 연산자 라던지 *= 등 연산을 할 경우엔 반환값에 신경을 써야한다.
