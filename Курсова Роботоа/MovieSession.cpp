#include "MovieSession.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int MovieSession::setId()
{
    int id;
    string str;
    fstream file;
    file.open("idMovieSesseion.txt", fstream::out | fstream::in);
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

void MovieSession::create()
{
    cin.ignore(10, '\n');
    id = setId();
    cout << "\n�������� ���(IMAX - 1, 3D - 2, 2D- 3): ";
    cout << "������ ���(������:�������): "; cin >> time;
    cout << "������ ���: "; cin >> date;
    cout << "������ id ������: ";
}

void MovieSession::print()
{
    cout << "\nid: " << id << endl;
    cout << "���: ";// << hall << endl;
    cout << "���: " << time << endl;
    cout << "����: " << date << endl;
}

void MovieSession::read(int pn)
{
    ifstream ifile;
    ifile.open("MovieSession.dat", ios::binary | ios::out | ios::in);
    ifile.seekg(0);
    ifile.seekg(pn * sizeof(MovieSession));
    ifile.read((char*)this, sizeof(*this));
    ifile.close();
}

void MovieSession::write()
{
    ofstream ofile;
    ofile.open("MovieSession.dat", ios::app | ios::binary | ios::out | ios::in);
    ofile.write((char*)this, sizeof(*this));
    ofile.close();
}

int MovieSession::count()
{
    ifstream ifile;
    ifile.open("MovieSession.dat ", ios::binary);
    ifile.seekg(0, ios::end);
    return (int)ifile.tellg() / sizeof(MovieSession);
    ifile.close();
}


int MovieSession::search(int variant)
{
    if (variant == 0)
        return 0;
    MovieSession movieSession;
    ifstream ifile;
    char str[40];
    ifile.open("MovieSession.dat", ios::binary | ios::out | ios::in);
    ifile.seekg(0);
    cout << "\n������ ��� ��� ������: ";
    cin >> str;
    for (int i = 0; i < count(); i++)
    {
        ifile.seekg(i * sizeof(MovieSession));
        ifile.read(reinterpret_cast<char*>(&movieSession), sizeof(MovieSession));

        switch (variant)
        {
        case 1:
            if ((int)str == movieSession.hall)
            {
                movieSession.print();
            }
            break;

        case 2:
            if (0 == strcmp(str, movieSession.time))
            {
                movieSession.print();
            }
            break;
        case 3:
            if (0 == strcmp(str, movieSession.date))
            {
                movieSession.print();
            }
            break;
        case 4:

            if (atoi(str) == movieSession.id)
            {
                movieSession.print();
            }
            break;
        default:
            cout << "������� �����. ������ �� ���\n";
            break;
        }
    }
    ifile.close();
}



void MovieSession::deleteData()
{
    bool del = false;
    MovieSession movieSession;
    int str;
    cout << "������ ����� ��������� ��� ���������: ";
    cin >> str;
    ifstream file;
    file.open("MovieSession.dat", ios::binary | ios::out | ios::in);
    ofstream temp;
    temp.open("temp.dat", ios::app | ios::binary | ios::out | ios::in);
    file.read(reinterpret_cast<char*>(&movieSession), sizeof(MovieSession));
    while (!file.eof())
    {

        if (movieSession.id != str)
        {
            temp.write(reinterpret_cast<char*>(&movieSession), sizeof(MovieSession));
        }

        else
        {
            del = true;
        }
        file.read(reinterpret_cast<char*>(&movieSession), sizeof(MovieSession));
    }
    temp.close();
    file.close();
    if (remove("MovieSession.dat") != 0)
    {
        cout << "\n�������. ���� ��������� ��������\n";
    }
    if (rename("temp.dat", "MovieSession.dat") != 0)
    {
        cout << "\n�������. ���� ��������� �������������\n";
    }
    if (del == true)
        cout << "\n����� ��������\n";
    else
        cout << "\n�� ������� �������� ����. ��������� �� ���.\n";
}

void MovieSession::editData()
{
    bool edit = false;
    MovieSession movieSession;
    int str;
    cout << "������ ����� ��������� ��� �����������: ";
    cin >> str;
    ifstream file;
    file.open("MovieSession.dat", ios::binary | ios::out | ios::in);
    ofstream temp;
    temp.open("temp.dat", ios::app | ios::binary | ios::out | ios::in);
    file.seekg(0);
    file.read(reinterpret_cast<char*>(&movieSession), sizeof(MovieSession));
    while (!file.eof())
    {

        if (movieSession.id != str)
        {
            temp.write(reinterpret_cast<char*>(&movieSession), sizeof(MovieSession));
        }

        else
        {
            movieSession.create();
            temp.write(reinterpret_cast<char*>(&movieSession), sizeof(MovieSession));
            edit = true;
        }
        file.read(reinterpret_cast<char*>(&movieSession), sizeof(MovieSession));
    }
    temp.close();
    file.close();
    if (remove("MovieSession.dat") != 0)
    {
        cout << "\n�������. ���� ��������� ��������\n";
    }
    if (rename("temp.dat", "MovieSession.dat") != 0)
    {
        cout << "\n�������. ���� ��������� �������������\n";
    }
    if (edit == true)
        cout << "\n����� ������\n";
    else
        cout << "\n������� ��� ��� ������ ��������� �� ���.\n";
}
