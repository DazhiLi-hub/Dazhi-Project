#ifndef BOOKLIST_H
#define BOOKLIST_H

#include<string>
#include<iostream>

using namespace std;

template<class T>
class Booklist
{
private:
    T list[20];
    int total_books;
    bool is_sorted;
public:
    Booklist();
    void printBookList() const;
    int Insert();
    int Insert_at();
    int Linear_search();
    int Binary_search();
    int Delete_at();
    int Delete_by_ISBN();
    int Selection_sort();
    int Bubble_sort();
    int Set_TestSet_int();
    int Set_TestSet_string();
    int Get_totalBooks() const;
    bool is_existed(T) const;
};
template <class T>
Booklist<T>::Booklist()
{
    total_books = 0;
    is_sorted = false;
}

template <class T>
void Booklist<T>::printBookList() const
{
    for (int idx = 0; idx < total_books; idx++)
    {
        cout << "Book No." << (idx + 1) << ":"
            << " ----------Element: " << list[idx] << endl;
    }
    return;
}

template <class T>
int Booklist<T>::Insert()
{
    T ele;
    if (total_books >= 20)
    {
        cerr << "No more book could be inserted, please delete one first" << endl;
        return -1;
    }
    else
    {
        cout << "Please enter the book element: ";
        cin >> ele;
        if (is_existed(ele))
        {
            cout << "The element you want to insert has already existed, insert failed" << endl;
            return -1;
        }
        list[total_books] = ele;
        total_books++;
        is_sorted = false;
        return 0;
    }
}

template <class T>
int Booklist<T>::Insert_at()
{
    int position;
    T element;
    if (total_books >= 20)
    {
        cerr << "No more book could be inserted, please delete one first" << endl;
        return -1;
    }
    else
    {
        cout << "Please enter an position in the list you want to insert:";
        cin >> position;
        if (position > (total_books + 1))
        {
            cerr << "Your insert position is out of the bounds of the current book list" << endl;
            return -1;
        }
        else if (position <= 0)
        {
            cerr << "Your input position is not valid" << endl;
            return -1;
        }
        else
        {
            cout << "Please enter the book element: ";
            cin >> element;
        }
        if (is_existed(element))
        {
            cout << "The element you want to insert has already existed, insert failed" << endl;
            return -1;
        }
        //Moving the books after indicated position one position later
        for (int i = total_books;i >= position;i--)
        {
            list[i] = list[i - 1];
        }
        list[position - 1] = element;
        total_books++;
        is_sorted = false;
        return 0;
    }
}

template <class T>
int Booklist<T>::Linear_search()
{
    int position;
    T element;
    bool found = false;
    cout << "Please enter a book element for search:";
    cin >> element;
    for (int i = 0;i < total_books;i++)
    {
        if (list[i] == element)
        {
            position = i + 1;
            found = true;
        }
    }
    if (found)
    {
        cout << "The book you are looking for is: " << endl;
        cout << "Book No." << position << ":"
            << " ----------Element: " << list[position - 1] << endl;
        return 0;
    }
    else
    {
        cerr << "The book you are looking for does not exist" << endl;
        return -1;
    }
}

template <class T>
int Booklist<T>::Binary_search()
{
    if (!is_sorted)
    {
        cerr << "Your book list has not been sorted, please sort it first" << endl;
        return -1;
    }
    else
    {
        T element;
        int L = 0, R = total_books - 1, mid;
        bool found = false;
        cout << "Please enter a book element you want to search:";
        cin >> element;
        int interval = R - L;
        while (interval >= 0)
        {
            if (interval == 0)
                mid = L;
            mid = L + (R - L) / 2;
            if (list[mid] == element)
            {
                found = true;
                interval = -1;
            }
            else if (list[mid] > element)
            {
                R = mid - 1;
                interval = R - L;
            }
            else if (list[mid] < element)
            {
                L = mid + 1;
                interval = R - L;
            }
        }
        if (found)
        {
            cout << "The book you are looking for is: " << endl;
            cout << "Book No." << mid + 1 << ":"
                << " ----------Element: " << list[mid] << endl;
            return 0;
        }
        else
        {
            cerr << "No matches founded" << endl;
            return -1;
        }
    }
}

template <class T>
int Booklist<T>::Delete_at()
{
    int position;
    if (total_books <= 0)
    {
        cerr << "There is no book in the list, so nothing could be deleted" << endl;
        return -1;
    }
    else
    {
        cout << "Please enter a position of a book you want to delete:";
        cin >> position;
    }
    if (position > total_books)
    {
        cerr << "Your target is beyound the bounds of the current book list" << endl;
        return -1;
    }
    else if (position <= 0)
    {
        cerr << "Invalid input, please enter a positive integer" << endl;
        return -1;
    }
    else
    {
        for (int i = position - 1;i < total_books - 1;i++)
        {
            list[i] = list[i + 1];
        }
        //list[total_books - 1] = 0;
        total_books--;
        return 0;
    }
}

template <class T>
int Booklist<T>::Delete_by_ISBN()
{
    int position;
    T element;
    bool found = false;
    cout << "Please enter a book element you want to delete:";
    cin >> element;
    for (int i = 0;i < total_books;i++)
    {
        if (list[i] == element)
        {
            position = i + 1;
            found = true;
        }
    }
    if (found)
    {
        for (int i = position - 1;i < total_books - 1;i++)
        {
            list[i] = list[i + 1];
        }
        //list[total_books - 1] = 0;
        total_books--;
        return 0;
    }
    else if (!found)
    {
        cerr << "The book does not exist in the current book list" << endl;
        return -1;
    }
}

template <class T>
int Booklist<T>::Selection_sort()
{
    T tmp;
    int idx;
    for (int i = 0;i < total_books;i++)
    {
        T lowest = list[i];
        idx = i;
        for (int j = i;j < total_books;j++)
        {
            if (list[j] < lowest)
            {
                lowest = list[j];
                idx = j;
            }
        }
        tmp = list[i];
        list[i] = list[idx];
        list[idx] = tmp;
    }
    is_sorted = true;
    return 0;
}

template <class T>
int Booklist<T>::Bubble_sort()
{
    T tmp;
    for (int i = total_books - 1;i >= 1;i--)
    {
        for (int j = 0;j < i;j++)
        {
            if (list[j] > list[j + 1])
            {
                tmp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = tmp;
            }
        }
    }
    is_sorted = true;
    return 0;
}

template <class T>
int Booklist<T>::Set_TestSet_int()
{
    list[0] = 47625;
    list[1] = 95624;
    list[2] = 55484;
    list[3] = 67854;
    list[4] = 33696;
    total_books = 5;
    return 0;
}

template <class T>
int Booklist<T>::Set_TestSet_string()
{
    list[0] = "POLAND";
    list[1] = "SPRING";
    list[2] = "APPLE";
    list[3] = "HEALTH";
    list[4] = "JUICE";
    total_books = 5;
    return 0;
}

template <class T>
int Booklist<T>::Get_totalBooks() const
{
    return total_books;
}

template <class T>
bool Booklist<T>::is_existed(T A) const
{
    for (int i = 0;i < total_books;i++)
    {
        if (list[i] == A)
        {
            return true;
        }
    }
    return false;
}

#endif
