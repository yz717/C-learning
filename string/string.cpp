#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include "string.h"

class String {
public:

	// ���캯��
	String(const char* str = "")
		:_str(new char[strlen(str) + 1])
	{
		strcpy(_str, str);
	}
	// ��������
	String(const String& s) {
		String tmp(s._str);//���ù��캯��
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