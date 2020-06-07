#include "Film.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int Film::setId()
{
    int id;
    string str;
    fstream file;
    file.open("id.txt", fstream::out | fstream::in);
    ifstream temp;
    while (!file.eof())
    {
        getline(file, str);
        id = atoi(str.c_str());
    }
    ++id;
    file.close();
    file.open("id.txt", fstream::out | fstream::in);
    file << id;
    file.close();
    return id;
}
int Film::getId()
{
    return id;
}

void Film::create()
{
    cin.ignore(10, '\n');
    cout << "\n�����: "; cin >> name;
    cout << "���� ������: "; cin >> premiere;
    cout << "����: "; cin >> ganre;
    id = setId();
}

void Film ::print()
{
    cout << "\nid: " << id << endl;
    cout << "�����: " << name << endl;
    cout << "���� ������: " << premiere << endl;
    cout << "����: " << ganre << endl;
}

void Film::read(int pn)
{
    ifstream ifile;
    ifile.open("Film.dat", ios::binary | ios::out | ios::in);
    ifile.seekg(0);
    ifile.seekg(pn * sizeof(Film));
    ifile.read((char*)this, sizeof(*this));
    ifile.close();
}

void Film::write()
{
    ofstream ofile;
    ofile.open("Film.dat", ios::app | ios::binary | ios::out | ios::in);
    ofile.write((char*)this, sizeof(*this));
    ofile.close();
}

int Film::count()
{
    ifstream ifile;
    ifile.open("Film.dat ", ios::binary);
    ifile.seekg(0, ios::end);
    return (int)ifile.tellg() / sizeof(Film);
    ifile.close();
}

#pragma region SearchCitizen

int Film::search(int variant)
{
    if (variant == 0)
        return 0;
    Film film;
    ifstream ifile;
    char str[40];
    ifile.open("Film.dat", ios::binary | ios::out | ios::in);
    ifile.seekg(0);
    cout << "\n������ ��� ��� ������: ";
    cin >> str;
    for (int i = 0; i < count(); i++)
    {
        ifile.seekg(i * sizeof(Film));
        ifile.read(reinterpret_cast<char*>(&film), sizeof(Film));

        switch (variant)
        {
        case 1:
            if (0 == strcmp(str, film.name))
            {
                film.print();
            }
            break;

        case 2:
            if (0 == strcmp(str, film.premiere))
            {
                film.print();
            }
            break;
        case 3:
            if (0 == strcmp(str, film.ganre))
            {
                film.print();
            }
            break;
        case 4:

            if (atoi(str) == film.id)
            {
                film.print();
            }
            break;
        default:
            cout << "������� �����. ������ �� ���\n";
            break;
        }
    }
    ifile.close();
}



void Film::deleteData()
{
    bool del = false;
    Film film;
    int str;
    cout << "������ ����� ��������� ��� ���������: ";
    cin >> str;
    ifstream file;
    file.open("Film.dat", ios::binary | ios::out | ios::in);
    ofstream temp;
    temp.open("temp.dat", ios::app | ios::binary | ios::out | ios::in);
    file.read(reinterpret_cast<char*>(&film), sizeof(Film));
    while (!file.eof())
    {

        if (film.id != str)
        {
            temp.write(reinterpret_cast<char*>(&film), sizeof(Film));
        }

        else
        {
            del = true;
        }
        file.read(reinterpret_cast<char*>(&film), sizeof(Film));
    }
    temp.close();
    file.close();
    if (remove("Film.dat") != 0)
    {
        cout << "\n�������. ���� ��������� ��������\n";
    }
    if (rename("temp.dat", "Film.dat") != 0)
    {
        cout << "\n�������. ���� ��������� �������������\n";
    }
    if (del == true)
        cout << "\n����� ��������\n";
    else
        cout << "\n�� ������� �������� ����. ��������� �� ���.\n";
}

void Film::editData()
{
    bool edit = false;
    Film film;
    int str;
    cout << "������ ����� ��������� ��� �����������: ";
    cin >> str;
    ifstream file;
    file.open("Film.dat", ios::binary | ios::out | ios::in);
    ofstream temp;
    temp.open("temp.dat", ios::app | ios::binary | ios::out | ios::in);
    file.seekg(0);
    file.read(reinterpret_cast<char*>(&film), sizeof(Film));
    while (!file.eof())
    {

        if (film.id != str)
        {
            temp.write(reinterpret_cast<char*>(&film), sizeof(Film));
        }

        else
        {
            film.create();
            temp.write(reinterpret_cast<char*>(&film), sizeof(Film));
            edit = true;
        }
        file.read(reinterpret_cast<char*>(&film), sizeof(Film));
    }
    temp.close();
    file.close();
    if (remove("Film.dat") != 0)
    {
        cout << "\n�������. ���� ��������� ��������\n";
    }
    if (rename("temp.dat", "Film.dat") != 0)
    {
        cout << "\n�������. ���� ��������� �������������\n";
    }
    if (edit == true)
        cout << "\n����� ������\n";
    else
        cout << "\n������� ��� ��� ������ ��������� �� ���.\n";
}