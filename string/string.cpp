#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include "string.h"

class String {
public:

	// 构造函数
	String(const char* str = "")
		:_str(new char[strlen(str) + 1])
	{
		strcpy(_str, str);
	}
	// 拷贝构造
	String(const String& s) {
		String tmp(s._str);//调用构造函数
		swap(_str, tmp._str);
	}

	String& operator= (String s) {
		swap(_str, s._str);
		return *this;
	}

private:
	char* _str;
};
int main() {
	//yz717::test1();
	//yz717::test2();
	//yz717::test3();
	//yz717::test4();
	//yz717::test5();
	yz717::test6();
	return 0;
}