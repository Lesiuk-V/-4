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
    file.open("idSession.txt", fstream::out | fstream::in);
    ifstream temp;
    while (!file.eof())
    {
        getline(file, str);
        id = atoi(str.c_str());
    }
    ++id;
    file.close();
    file.open("idSession.txt", fstream::out | fstream::in);
    file << id;
    file.close();
    return id;
}

int MovieSession::getFilm()
{

    Film film;
    ifstream ifile;
    int id;
    ifile.open("Film.dat", ios::binary | ios::out | ios::in);
    ifile.seekg(0);
    int ok = 0;
    int n;
    while (ok != 1)
    {
        cout << "Введіть id фільму: ";
        cin >> id;
        for (int i = 0; i < Film::count(); i++)
        {
            ifile.seekg(i * sizeof(Film));
            ifile.read(reinterpret_cast<char*>(&film), sizeof(Film));
            n = film.getId();
            if (id == n)
            {
                ok = 1;
                return film.getId();
            }
        }
        cout << "\nФільму з таким id немає. Введіть ще раз\n";
    }



}

void MovieSession ::showHall(int variant)
{
    switch (variant)
    {
    case 1:
        cout << " IMAX\n";
        break;
    case 2 :
        cout << " 3D\n";
        break;
    case 3:
        cout << " 2D\n";
        break;
    default:
        cout << "unknow\n";
        break;
    }
}

void MovieSession::setHall()
{
    cin.ignore(10, '\n');
    cout << "\nВиберіть зал(IMAX: 1, 3D: 2, 2D: 3): ";
    int input = -1;
    bool valid = false;
    do
    {
        cin >> input;
        if (cin.good())
        {

            if (input > 0 && input <= 4)
                valid = true;

            else
            {
                valid = false;
                cout << "Помилка вводу. Введіть ще раз" << endl;
            }

        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Помилка вводу. Введіть ще раз" << endl;
        }
    } while (!valid);

    switch (input)
    {
    case 1:
        hall = IMAX;
        break;
    case 2:
        hall = _3D;
        break;
    case 3:
        hall = _2D;
        break;
    }
}


void MovieSession::create()
{
    setHall();
    cin.ignore(10, '\n');
    cout << "Введіть час(години:хвилини): "; cin >> time;
    cout << "Введіть дату: "; cin >> date;
    //cout << "Введіть id фільму: "; 
    filmId =getFilm();
    id = setId();
}

void MovieSession::print()
{
    cout << "\nid: " << id << endl;
    cout << "Зал: "; showHall(hall);
    cout << "Час: " << time << endl;
    cout << "Дата: " << date << endl;
    cout << "id фільму:" << filmId << endl;
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
    cout << "\nВведіть дані для пошуку: ";
    cin >> str;
    for (int i = 0; i < count(); i++)
    {
        ifile.seekg(i * sizeof(MovieSession));
        ifile.read(reinterpret_cast<char*>(&movieSession), sizeof(MovieSession));

        switch (variant)
        {
        case 1:
            if (atoi(str) == movieSession.hall)
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
            cout << "Помилка вводу. Введіть ще раз\n";
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
    cout << "Введіть номер документа для видалення: ";
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
        cout << "\nПомилка. Файл неможливо видалити\n";
    }
    if (rename("temp.dat", "MovieSession.dat") != 0)
    {
        cout << "\nПомилка. Файл неможливо перейменувати\n";
    }
    if (del == true)
        cout << "\nЗапис видалено\n";
    else
        cout << "\nНе вдалося видалити файл. Спробуйте ще раз.\n";
}

void MovieSession::editData()
{
    bool edit = false;
    MovieSession movieSession;
    int str;
    cout << "Введіть номер документа для редагування: ";
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
        cout << "\nПомилка. Файл неможливо видалити\n";
    }
    if (rename("temp.dat", "MovieSession.dat") != 0)
    {
        cout << "\nПомилка. Файл неможливо перейменувати\n";
    }
    if (edit == true)
        cout << "\nЗапис змінено\n";
    else
        cout << "\nПомилка при зміні запису спробуйте ще раз.\n";
}
