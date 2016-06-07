#ifndef XMLLOADER_H
#define XMLLOADER_H

#include <assert.h>

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <stack>

using std::string;
using std::ifstream;
using std::cout;
using std::endl;
using std::map;
using std::vector;
using std::stack;

//��������
class Value {
private:
	//������
	//number��string
	string type;

	float valNumber;
	string valString;

public:
	Value() {}
	//���캯��
	Value(float _val) {
		type = "number";
		valNumber = _val;
	}
	Value(string _val) {
		type = "string";
		valString = _val;
	}

	string getType() {
		return type;
	}

	//ȡ������
	string& getString() {
		assert(type == "string");
		return valString;
	}

	float& getNumber() {
		assert(type == "number");
		return valNumber;
	}

	//�������
	void store(float newData) {
		type = "number";
		valNumber = newData;
	}
	void store(string newData) {
		type = "string";
		valString = newData;
	}
};

//ÿһ�Լ����ž���һ��Object
//�ɵ�һ��object���������
//A. ����object
//B. ����
class Object {
public:
	string name;

private:
	//true������������
	//false������������object
	bool isVal;
	Value val;
	vector<Object> list;

public:
	//���캯��
	Object() {
		isVal = true;
		val.store("");
	}

	//�жϵ�ǰobject�洢������
	bool isVal() {
		return isVal;
	}

	//ȡֵ
	Value& getValue() {
		assert(isVal);
		return val;
	}
	vector<Object>& getList() {
		assert(!isVal);
		return list;
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
	//�����ļ�
	void analyse();
};

#endif