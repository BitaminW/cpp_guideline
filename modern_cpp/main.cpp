

void test() {
    static const int a = std::random_device{}();
    constexpr const int& ra = a; // OK: a is a glvalue constant expression
    constexpr int ia = a; // Error: a is not a prvalue constant expression
 
    const int b = 42;
    constexpr const int& rb = b; // Error: b is not a glvalue constant expression
    constexpr int ib = b; // OK: b is a prvalue constant expression
}

int main(){

  static size_t sz = sizeof(constexpr int); // 오류, constexpr int는 타입이 아닙니다.

  constexpr char* str = "Hello"; // 오류: "Hello"를 char *로 캐스팅 할 수 없습니다.
  constexpr const char* str = "Hello"; // 정상

  static int a = 0;
  constexpr int& ra = a; // 정상

  static const int b = 0;
  constexpr int& rb = b; // 오류, const int를 int&로 캐스팅 할 수 없습니다.

  class T;
  const T f();
  constexpr T (*pf) = f; // 오류: const T()를 T(*)()로 캐스팅
  constexpr const T (*pf) = f; // 정상

}
