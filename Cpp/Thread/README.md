
# [C++] Thread

```cpp
void func(int cnt) {
	for (int i = 0; i < cnt; i++) {
		cout << " i / count " << i << " / " << cnt << "\n";
	}
}
```

다음과 같은 함수를 메인 함수에서 두번 실행을 하면 순차적으로 하나의 함수가 시작되고 종료되고
다시 함수가 시작되고 종료되고 순차적으로 실행된다. 이것이 하나의 프로세스의 흐름인데

```cpp
int main() {

	func(10);                  // 이 함수가 끝나고
	func(10);                  // 이 함수가 실행된다

    return 0;
}
```

실행결과는 너무 당연하게 

```sh
 i / count 0 / 10
 i / count 1 / 10
 i / count 2 / 10
 i / count 3 / 10
 i / count 4 / 10
 i / count 5 / 10
 i / count 6 / 10
 i / count 7 / 10
 i / count 8 / 10
 i / count 9 / 10
 i / count 0 / 10
 i / count 1 / 10
 i / count 2 / 10
 i / count 3 / 10
 i / count 4 / 10
 i / count 5 / 10
 i / count 6 / 10
 i / count 7 / 10
 i / count 8 / 10
 i / count 9 / 10
```

이와 같이 나온다


하지만 이처리를 동시에 처리하고 싶을 때가있다. 즉 첫번째 함수 호출이 끝나기를 기다리는 것이아닌

func처리를 넘기고 넘기고 메인처리를 하는 방식입니다.

```cpp
void thread_func(int cnt) {
	for (int i = 0; i < cnt; i++) {
		cout << " i - " << i << " / " << cnt << "\n";
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}

int main() {

	// 쓰레드 생성
	thread t1(thread_func, 10);
	thread t2(thread_func, 10);

	cout << "--------------thread 시작" << "\n";

    // thread가 종료될때까지 메인함수를 종료시키지 않음
	t1.join();
	t2.join();

	return 0;
}
```

실행결과는

```sh
--------------thread 시작
 i - 0 / 10
 i - 0 / 10
 i - 1 / 10
 i - 1 / 10
 i - 2 / 10
 i - 2 / 10
 i - 3 / 10
 i - 3 / 10
 i - 4 / 10
 i - 4 / 10
 i - 5 / 10
 i - 5 / 10
 i - 6 / 10
 i - 6 / 10
 i - 7 / 10
 i - 7 / 10
 i - 8 / 10
 i - 8 / 10
 i - 9 / 10
 i - 9 / 10

```


