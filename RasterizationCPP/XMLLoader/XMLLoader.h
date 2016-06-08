#ifndef XMLLOADER_H
#define XMLLOADER_H

#include <assert.h>

#include <string>
using std::string;
using std::getline;

#include <fstream>
using std::ifstream;

#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

#include <map>
using std::map;

#include <vector>
using std::vector;

#include <stack>
using std::stack;

#include <memory>
using std::shared_ptr;
using std::make_shared;

#include <regex>
using std::regex;
using std::regex_match;
using std::regex_search;

/////////////
// �������� //
/////////////

//��̬��̬
#define PTR_CONVERT(shared_ptr, type) (dynamic_cast<type*>(shared_ptr.get()))

//�����м�������
enum TYPE {
	TYPE_EMPTY,
	TYPE_BASE,
	TYPE_NUMBER,
	TYPE_STRING,
	TYPE_VALUE,
	TYPE_OBJECT
};

//���ڷ�����ǰ������ʲô
enum STRINGTYPE {
	ST_EMPTY,
	ST_START,
	ST_END,
	ST_VALUE
};

//����
//���㴫������
class Base {
public:
	TYPE type;

	Base() {
		type = TYPE_BASE;
	}

	virtual TYPE getType() {
		return TYPE_BASE;
	}

	//�麯��
	//���������
	friend ostream& operator << (ostream& os, Base& t) {
		os << "TYPE_BASE";
		return os;
	}
};

//��������
class Number :public Base {
public:
	double val;

	Number() {
		type = TYPE_NUMBER;
		val = 0;
	}
	//���캯��
	Number(double _val) :Number() {
		val = _val;
	}

	TYPE getType() {
		return type;
	}

	//���������
	friend ostream& operator << (ostream& os, Number& t) {
		os << "TYPE_NUMBER : " << t.val;
		return os;
	}
};

//�����ַ���
class String :public Base {
public:
	string val;

	String() {
		type = TYPE_STRING;
	}
	//���캯��
	String(string _val) :String() {
		val = _val;
	}

	TYPE getType() {
		return type;
	}

	//���������
	friend ostream& operator << (ostream& os, String& t) {
		os << "TYPE_STRING : " << t.val;
		return os;
	}

};

//����һ��Number����String
class Value : public Base {
private:
	shared_ptr<Base> val;

public:
	Value() {
		type = TYPE_EMPTY;
	}

	Value(double _val) :Value() {
		type = TYPE_NUMBER;
		val = make_shared<Number>(_val);
	}

	Value(string _val) :Value() {
		type = TYPE_STRING;
		val = make_shared<String>(_val);
	}

	TYPE getType() {
		return type;
	}

	//todo
	//get set
	//��ȡ����
	Number* const getNumber() {
		assert(type == TYPE_NUMBER);
		return PTR_CONVERT(val, Number);
	}

	String* const getString() {
		assert(type == TYPE_STRING);
		return PTR_CONVERT(val, String);
	}

	void set(double _val) {
		if (type != TYPE_NUMBER) {
			type = TYPE_NUMBER;
			auto newValue = new Number(_val);
			val.reset(newValue);
		}
		else {
			PTR_CONVERT(val, Number)->val = _val;
		}
	}

	void set(string _val) {
		if (type != TYPE_STRING) {
			type = TYPE_STRING;
			auto newValue = new String(_val);
			val.reset(newValue);
		}
		else {
			PTR_CONVERT(val, String)->val = _val;
		}
	}

	//���������
	friend ostream& operator << (ostream& os, Value& t) {
		switch (t.type) {
		case TYPE_NUMBER:
			os << *t.getNumber();
			break;
		case TYPE_STRING:
			os << *t.getString();
			break;
		case TYPE_EMPTY:
			os << "Nothing stored yet";
			break;
		default:
			break;
		}
		return os;
	}
};

//ÿһ�Լ����ž���һ��Object
//�ɵ�һ��object���������
//A. ����object
//B. ����
class Object : public Base {
public:
	string name;

private:
	//true������������
	//false������������object
	TYPE storedType;
	Value val;
	vector<Object> list;

public:
	//���캯��
	Object() {
		type = TYPE_OBJECT;
		storedType = TYPE_EMPTY;
	}

	//�жϵ�ǰobject�洢������
	TYPE getType() {
		return type;
	}

	//��ֵ
	void set(Value& t) {
		storedType = TYPE_VALUE;
		val = t;
	}
	void set(Object& t) {
		//���ԭ�ȴ���Ĳ���object
		if (storedType != TYPE_OBJECT) {
			storedType = TYPE_OBJECT;
			list.clear();
		}
		list.push_back(t);
	}

	//ȡֵ
	Value& getValue() {
		assert(storedType == TYPE_VALUE);
		return val;
	}
	vector<Object>& getList() {
		assert(storedType == TYPE_OBJECT);
		return list;
	}

	//���������
	friend ostream& operator << (ostream& os, Object &t) {
		os << "Object";
		return os;
	}
};

//��ǰ��Ҫô�Ǳ�ǩ�����ַ�������
//Ҫô������
struct ANALYSE_RESULT {
	STRINGTYPE type;

	String str;
	Value value;

	friend ostream& operator << (ostream& os, ANALYSE_RESULT& t) {
		switch (t.type) {
		case ST_START:
			os << "ST_START " << t.str;
			break;
		case ST_END:
			os << "ST_END " << t.str;
			break;
		case ST_VALUE:
			os << "ST_VALUE " << t.value;
			break;
		case ST_EMPTY:
			os << "ST_EMPTY";
			break;
		}
	}
};


class XMLLoader {
///////////
//��Ա����//
//////////
public:
	string fileName;
	ifstream fileStream;
private:
	bool is_open;
	Object root;
///////////
//��Ա����//
//////////
public:
	//���캯��
	XMLLoader();
	XMLLoader(string);

	~XMLLoader();

	//��ȡ�ļ�
	//��ȡ�ɹ�������true
	//��ȡʧ�ܣ�����false
	bool loadFile(string);

	//�����ȡ���ļ�����
	XMLLoader& read();

private:
	//��������

	//����ַ�����ͷ�Ŀո�
	void clearSpace(string&);

	//������ȡ�ĵ�ǰ����ʲô
	ANALYSE_RESULT analyseString(string);


	//��Ҫ����
	//�����ļ�
	void analyse();
};

#endif