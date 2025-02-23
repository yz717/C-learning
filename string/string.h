//#pragma once
//#include <string.h>
//
//namespace yz717 {
//	class string {
//	public:
//		// 构造函数
//		// 分开写
//		//string()
//		//	:_str(new char[1])
//		//{
//		//	_str[0] = '\0';
//		//}
//		//string(const char* str)
//		//	:_str(new char[strlen(str + 1)])// 最后一个字符是'\0'
//		//{
//		//	strcpy(_str, str);
//		//}
//
//		// 注意缺省值为空字符串
//		string(const char* str = "")
//			:_str(new char[strlen(str) + 1])
//		{
//			strcpy(_str, str);
//		}
//
//		// 拷贝构造函数
//		// string s2(s1);
//		// string s2 = s1;
//		string(const string& s)
//			:_str(new char[strlen(s._str) + 1])
//		{
//			strcpy(_str, s._str);
//		}
//
//		// 赋值运算符重载
//		// s2 = s1;
//		string& operator=(const string& s) {
//			if (this != &s) { // 防止自赋值
//				delete[] _str; // 释放原有空间
//				_str = new char[strlen(s._str) + 1];
//				strcpy(_str, s._str);
//			}
//			return *this;
//		}
//
//
//		// 析构函数
//		~string() {
//			delete[] _str;
//			_str = nullptr;
//		}
//
//		// c格式字符串
//		const char* c_str() {
//			return _str;
//		}
//
//
//		size_t size() {
//			return strlen(_str);
//		}
//		char& operator[](size_t index) {
//			return _str[index];
//		}
//	private:
//		char* _str;
//	};
//
//	void test1() {
//
//		string s1("hello");
//		string s2;
//
//		for (size_t i = 0; i < s1.size(); ++i) {
//			s1[i] += 1;
//			cout << s1[i] << " ";
//		}
//		cout << endl;
//	}
//
//	void test2() {
//		string s1("hello");
//		string s2(s1);
//		string s3("world");
//		string s4;
//		s4 = s3;
//		cout << s1.c_str() << endl;
//		cout << s2.c_str() << endl;
//	}
//}

#pragma once
#include <string.h>
#include <assert.h>
namespace yz717 {
	class string
	{
	public:
		// 迭代器
		typedef char* iterator;
		iterator begin() {
			return _str;
		}
		iterator end() {
			return _str + _size;
		}


		// 构造函数
		string(const char* str = "") {
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];// 多一个\0
			strcpy(_str, str);
		}
		// 拷贝构造
		//string(const string& s) {
		//	_size = s._size;
		//	_capacity = _size;
		//	_str = new char[_capacity + 1];
		//	strcpy(_str, s._str);
		//}

		string(const string& s) 
			:_str(nullptr),
			_size(0),
			_capacity(0)
		{
			string tmp(s._str);
			swap(tmp);
		}

		// 赋值运算重载
		//string& operator=(const string& s) {
		//	if (this != &s) {
		//		delete _str;
		//		_size = s._size;
		//		_capacity = s._capacity;
		//		_str = new char[_capacity + 1];
		//		strcpy(_str, s._str);
		//	}
		//	return *this;
		//}

		string& operator=(string s) {
			swap(s);
			return *this;
		}
		~string() {
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
		size_t size() const{
			return _size;
		}
		size_t capacity() const{
			return _capacity;
		}
		char& operator[](size_t i) {
			assert(i < _size);
			return _str[i];
		}
		const char& operator[](size_t i)const {
			assert(i < _size);
			return _str[i];
		}
		const char* c_str() {
			return _str;
		}


		void reserve(size_t n) {
			if (n > _capacity) {
				char* newstr = new char[n + 1];
				strcpy(newstr, _str);
				delete[] _str;
				_str = newstr;
				_capacity = n;
			}
		}

		void push_back(char ch) {
			// 空间满了则增容
			if (_size == _capacity) {
				size_t newcapcity = _capacity == 0 ? 2 : _capacity * 2;
				reserve(newcapcity);
			}
			_str[_size++] = ch;
			_str[_size] = '\0';
		}

		void append(const char* str) {
			size_t len = strlen(str);
			// 空间满了则增容
			if (_size + len > _capacity) {
				reserve(_size + len);
			}
			strcpy(_str + _size, str);
			_size += len;
		}
		
		// s1 += 'a'
		string& operator+=(char ch) {
			this->push_back(ch);
			return *this;
		}

		// s1 += "aaa"
		string& operator+=(const char* str) {
			this->append(str);
			return *this;
		}



		string& insert(size_t pos, char ch) {
			assert(pos <= _size);
			if (_size == _capacity) {
				size_t newcapcity = _capacity == 0 ? 2 : _capacity * 2;
				reserve(newcapcity);
			}
			size_t end = _size + 1;
			while (end > pos) {
				_str[end] = _str[end - 1];
				--end;
			}
			_str[pos] = ch;
			++_size;
			return *this;
		}
		string& insert(size_t pos, const char* str) {
			assert(pos <= _size);
			size_t len = strlen(str);
			if (_size + len > _capacity) {
				reserve(_size + len);
			}
			//int end = _size;
			//while (end >= (int)pos)/*注意需要强转*/{
			//	_str[end + len] = _str[end];
			//	--end;
			//}
			size_t end = _size + len;
			while (end > pos + len - 1)
			{
				_str[end] = _str[end - len];
				--end;
			}
			strncpy(_str + pos, str, len);
			_size += len;
			return *this;
		}

		void resize(size_t n, char ch = '\0') {
			if (n > _size) {
				if (n > _capacity) {
					reserve(n);
				}
				memset(_str + _size, ch, n - _size);
			}
			_size = n;
			_str[_size] = '\0';
		}
		string& erase(size_t pos, size_t len = npos) {
			assert(pos < _size);
			if (len > _size - pos) {
				_str[pos] = '\0';
				_size = pos;
			}
			else {
				size_t i = pos + len;
				while (i <= _size) {
					_str[pos++] = _str[i++];
				}
				_size -= len;
			}
			return *this;
		}
		size_t find(char ch, size_t pos = 0) {
			for (size_t i = pos; i < _size; ++i) {
				if (_str[i] == ch) {
					return i;
				}
			}
			return npos;
		}
		size_t find(const char* str, size_t pos = 0) {
			char* p = strstr(_str + pos, str);
			return p == nullptr ? npos : p - _str;
		}


		bool operator<(const string& s) {
			int ret = strcmp(_str, s._str);
			return ret < 0;
		}

		bool operator==(const string& s) {
			int ret = strcmp(_str, s._str);
			return ret == 0;
		}

		bool operator!=(const string& s) {
			return !(*this == s);
		}

		bool operator<=(const string& s) {
			return *this < s || *this == s;
		}
		
		bool operator>(const string& s) {
			return !(*this <= s);
		}

		bool operator>=(const string& s) {
			return !(*this < s);
		}

		void swap(string& s) {
			::swap(_str, s._str);
			::swap(_size, s._size);
			::swap(_capacity, s._capacity);
		}

	private:
		char* _str;
		size_t _size; // 已有元素个数
		size_t _capacity;// 能存多少个有效字符，\0不算

		static size_t npos;
	};
	size_t string::npos = -1;

	// 重载输入输出运算符
	istream& operator>>(istream& in, string& s) {
		char ch;
		ch = in.get();
		while (ch != ' ' && ch != '\n') {
			s.push_back(ch);
			ch = in.get();
		}
		return in;
	}

	istream& getline(istream& in, string& s) {
		char ch;
		ch = in.get();
		while (ch != '\n') {
			s.push_back(ch);
			ch = in.get();
		}
		return in;
	}

	ostream& operator<<(ostream& out, const string& s) {
		for (size_t i = 0; i < s.size(); ++i) {
			out << s[i];
		}
		return out;
	}	
	void test1() {
		string s1;
		string s2("hello");
		cout << s1 << endl;
		cout << s2 << endl;
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;

		// 三种遍历方式
		// 1.
		for (size_t i = 0; i < s2.size(); ++i) {
			s2[i] += 1;
			cout << s2[i] << " ";
		}
		cout << endl;

		// 2.
		string::iterator it2 = s2.begin();
		while (it2 != s2.end()) {
			*it2 -= 1;
			cout << *it2 << " ";
			++it2;
		}
		cout << endl;

		// 3.范围for由迭代器支持
		// 这段代码最终会被替换成迭代器
		// iterator begin() end()
		for (auto ch : s2) {
			cout << ch << " ";
		}
		cout << endl;
	}

	void test2() {
		string s1("hello");
		s1.push_back(' ');
		s1.push_back('w');
		s1.append("orld!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
		cout << s1;

		string s2;
		s2 += "hello";
		s2 += ' ';
		s2 += "world!!!";
		cout << s2;
	}

	void test3() {
		string s1;
		s1.insert(0, 'a');
		cout << s1 << endl;
		s1.insert(0, "aasdfg");
		cout << s1 << endl;

		string s2("hello");
		s2.reserve(10);
		cout << s2 << endl;
		cout << s2.size() << endl;
		cout << s2.capacity() << endl;
		cout << endl;

		s2.resize(7, '7');
		cout << s2 << endl;
		cout << s2.size() << endl;
		cout << s2.capacity() << endl;
		cout << endl;

		s2.resize(20, 'a');
		cout << s2 << endl;
		cout << s2.size() << endl;
		cout << s2.capacity() << endl;
		cout << endl;

		s2.resize(2);
		cout << s2 << endl;
		cout << s2.size() << endl;
		cout << s2.capacity() << endl;
	}

	void test4() {
		string s1("abcdabcdefg");
		cout << s1.find("cde");
		cout << endl;
		cout << s1.find("cdeg", 5);
	}
	void test5() {
		string s1;
		cin >> s1;
		cout << s1;
		cout << endl;
		string s2;
		getline(cin, s2);
		cout << s2;
		cout << endl;
	}

	void test6() {
		string s1("hello");
		string s2(s1);
		cout << s2 << endl;
		string s3;
		s3 = s1;
		cout << s3 << endl;
	}
}