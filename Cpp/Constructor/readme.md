```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>


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

	String(String& rhs){
		len = strlen(rhs.str);
		str = new char[len + 1];
		strcpy(str, rhs.str);
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
	s1 = s1;
	std::cout << s1.getStr() << " : " << s1.getLen() << "\n";

	return 0;
}


```
