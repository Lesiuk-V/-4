#pragma once
class Film
{
private:
	int id;
	char name[40];
	char premiere[11];
	char ganre[20];
public:
	void create();
	void print();
	void read(int);
	void write();
	static int count();
	int search(int);
	void deleteData();
	int  setId();
	void editData();
};

