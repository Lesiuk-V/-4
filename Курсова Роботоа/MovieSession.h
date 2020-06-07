#pragma once
#include "Film.h"
enum cinemaHall
{
	first,
	second,
	third,
};

class MovieSession
{
private:
	int id;
	char time[6];
	char date[12];
	cinemaHall hall;	
	Film film;
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

