#pragma once
#include "Film.h"
enum cinemaHall
{
	IMAX = 1,
	_3D,
	_2D,
};

class MovieSession
{
private:
	int id;
	char time[6];
	char date[12];
	cinemaHall hall;	
	Film film;
	int filmId;
public:
	void showHall(int);
	void setHall();
	void create();
	void print();
	void read(int);
	void write();
	static int count();
	int search(int);
	void deleteData();
	int  setId();
	void editData();
	int getFilm();
};

