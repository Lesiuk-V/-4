#include <iostream>
#include "Film.h"
#include "MovieSession.h"

using namespace std;

void print_Film_menu()
{
    system("cls");
    cout << "          Фільми\n" << endl;
    cout << "1.  Дадати дані" << endl;
    cout << "2.  Переглянути всі фільми" << endl;
    cout << "3.  Пошук фільмів" << endl;
    cout << "4.  Редагування данних " << endl;
    cout << "5.  Видалення даних " << endl;
    cout << "6. Вихід" << endl;
    cout << "->";
}

void print_MovieSession_menu()
{
    system("cls");
    cout << "          Сеанси\n" << endl;
    cout << "1.  Дадати данні" << endl;
    cout << "2.  Переглянути данні" << endl;
    cout << "3.  Пошук" << endl;
    cout << "4.  Редагування даних" << endl;
    cout << "5.  Видалення даних" << endl;
    cout << "6. Вихід" << endl;
    cout << "->";
}

void print_menu()
{
    system("cls");
    cout << "          Кінотеатр\n" << endl;
    cout << "1.  Фільми" << endl;
    cout << "2.  Сеанси " << endl;
    cout << "3. Вихід" << endl;
    cout << "->";
}

void printSearchFilmMenu()
{
    cout << "\n\nПошук за полем: \n";
    cout << "1. Назва фільму" << endl;
    cout << "2. Прем'єра" << endl;
    cout << "3. Жанр" << endl;
    cout << "4. id" << endl;
    cout << "->";
}
void printSearchMovieSessionMenu()
{
    cout << "\n\nПошук за полем: \n";
    cout << "1. Тип залу (IMAX: 1, 3D: 2, 2D: 3)" << endl;
    cout << "2. Час сеансу" << endl;
    cout << "3. Дата сеансу" << endl;
    cout << "4. id" << endl;
    cout << "->";
}
int get_variant(int max) {
    int input = -1;
    bool valid = false;
    do
    {
        cin >> input;
        if (cin.good())
        {
            valid = true;
            if (input > 0 && input <= max)
                return input;
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
    return input;
}
int main()
{
    system("chcp 1251>nul");
    int variant;
    int searchVar;
    Film film;
    int n;
    MovieSession movieSession;
    do {
        print_menu();
        char ch;
        variant = get_variant(3);
        switch (variant)
        {
        case 1:

            do
            {
                print_Film_menu();
                variant = get_variant(6);
                switch (variant)
                {
                case 1:

                    do
                    {

                        cout << "Введіть дані фільму: ";
                        film.create();
                        film.write();
                        cout << "Продовжити ввід?(т/н)?";
                        cin >> ch;
                    } while (ch == 'т');
                    break;
                case 2:
                    n = Film::count();
                    cout << "У файлі " << n << " фільм\n";
                    for (int j = 1; j < n + 1; j++)
                    {
                        cout << "\n Фільм " << j << endl;
                        film.read(j - 1);
                        film.print();
                        cout << endl;
                    }
                    cout << endl;
                    break;
                case 3:
                    do
                    {
                        printSearchFilmMenu();
                        searchVar = get_variant(4);
                        film.search(searchVar);
                        break;
                        system("pause");
                    } while (searchVar != 5);
                    break;
                case 4:
                    film.editData();
                    break;
                case 5:

                    film.deleteData();
                    break;
                }
                if (variant != 6)
                    system("pause");
            } while (variant != 6);

            break;

        case 2:
            do
            {
                print_MovieSession_menu();
                variant = get_variant(6);
                switch (variant)
                {
                case 1:
                    do
                    {
                        cout << "Введіть дані сеансу: ";
                        movieSession.create();
                        movieSession.write();
                        cout << "Породивжити(т/н)?";
                        cin >> ch;
                    } while (ch == 'т');
                    break;
                case 2:
                    n = MovieSession::count();
                    cout << "У файлі " << n << "сеансів";
                    for (int j = 1; j < n + 1; j++)
                    {
                        cout << "\n Сеанс" << j << endl;
                        movieSession.read(j - 1);
                        movieSession.print();
                        cout << endl;
                    }
                    cout << endl;
                    break;
                case 3:
                    do
                    {
                        printSearchMovieSessionMenu();
                        searchVar = get_variant(4);
                        movieSession.search(searchVar);
                        break;
                        system("pause");
                    } while (searchVar != 5);
                    break;
                case 4:
                    movieSession.editData();
                    break;
                case 5:
                    movieSession.deleteData();
                    break;
                }
                if (variant != 6)
                    system("pause");
            } while (variant != 6);
            break;
        }
        if (variant != 3)
            system("pause");
    } while (variant != 3);
    return 0;
}
