## 포인터 정리
'''cpp

#include <bits/stdc++.h>

using namespace std;

//class Shape {
//
//public:
//	virtual void Print() {
//		cout << "Shape" << "\n";
//	}
//};
//
//class Circle : public Shape {
//
//public:
//	virtual void Print() {
//		cout << "circle" << "\n";
//	}
//};


//class Base {
//public:
//	int a = 10;
//
//	Base() {
//		cout << "Base called" << "\n";
//	}
//
//	virtual int getA() {
//		return a;
//	}
//
//};
//
//class Derived : public Base {
//public:
//	int a = 100;
//
//	Derived() {
//		cout << "Derived called" << "\n";
//	}
//
//	virtual int getA() {
//		return a;
//	}
//
//};


int main() {

	
	int numArr[3][4] = {   
		{ 11, 22, 33, 44 },       // << 
		{ 55, 66, 77, 88 },       // ptr + 1
		{ 99, 110, 121, 132 }      // ptr + 2
	};

	int(*ptr)[4] = numArr;

	int(* ptr2)[3][4] = &numArr;

	/*cout << *(*(ptr + 1) + 1) << "\n";

	cout << *(*(ptr + 1)) << "\n";
	cout << **(*ptr2 + 1) << "\n";

	cout << **(*ptr2) << "\n";*/

	//cout << ptr << "\n";
	//cout << ptr[0] << "\n";

	//cout << ptr + 1 << "\n";
	//cout << ptr[1] << "\n";

	cout << ptr << "\n";
	cout << *ptr << "\n";

	cout << numArr << "\n";
	cout << &numArr[0] << "\n";
	cout << numArr[0] << "\n";
	cout << *((ptr[2] + 3)) << "\n";

	cout << (*(&ptr[1] + 1)) << "\n";   //  99  ptr[1] 은 numArr[1][0] 의 주소 &numArr[1][0] 와 동일 거기에 &ptr[1]은 즉 전체 { 55, 66, 77, 88 }의 주소값을 거기에 +1 하면 ptr[2]의 시작 주소 거길 참조하면 99 
	cout << (ptr[1] + 1) << "\n";
	cout << ptr[3] << "\n";
	
	cout << (*ptr + 1)[3] << "\n";
	cout << (*ptr + 1) << "\n";
	cout << (*ptr)[3] << "\n";




	/*Shape* ptr = new Circle[5];

	Circle c;
	
	ptr[3] = c;

	ptr[0].Print();
	ptr[1].Print();
	ptr[2].Print();
	ptr[3].Print();*/


	return 0;
}


'''
