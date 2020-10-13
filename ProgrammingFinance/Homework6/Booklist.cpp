#include "Booklist.h"

Booklist::Booklist()
{
	total_books = 0;
    is_sorted = false;
}

void Booklist::printBookList() const
{
    for (int idx = 0; idx < total_books; idx++)
    {
        cout << "Book No." << (idx + 1) << ":"
            << " ----------ISBN number: " << list[idx].isbnNum
            << " ----------Book Title: " << list[idx].title
            << " ----------Book Author: " << list[idx].author << endl;
    }
    return;
}

int Booklist::Insert()
{
    int ISBN;
    string book_name = "\n", book_author = "\n";
    if (total_books >= 20)
    {
        cerr << "No more book could be inserted, please delete one first" << endl;
        return -1;
    }
    else
    {
        cout << "Please enter the ISBN number(integer): ";
        cin >> ISBN;
        cout << "Please enter the title of book: ";
        getline(cin, book_name);
        getline(cin, book_name);
        cout << "Please enter the author's name of the book: ";
        getline(cin, book_author);
        list[total_books].isbnNum = ISBN;
        list[total_books].title = book_name;
        list[total_books].author = book_author;
        total_books++;
        is_sorted = false;
        return 0;
    }
}

int Booklist::Insert_at()
{
    int ISBN, position;
    string book_name = "\n", book_author = "\n";
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
            cerr << "Your inser position is out of the bounds of the current book list" << endl;
            return -1;
        }
        else if (position <= 0)
        {
            cerr << "Your input position is not valid" << endl;
            return -1;
        }
        else
        {
            cout << "Please enter the ISBN number(integer): ";
            cin >> ISBN;
            cout << "Please enter the title of book: ";
            getline(cin, book_name);
            getline(cin, book_name);
            cout << "Please enter the author's name of the book: ";
            getline(cin, book_author);
        }
        //Moving the books after indicated position one position later
        for (int i = total_books;i >= position;i--)
        {
            list[i].isbnNum = list[i-1].isbnNum;
            list[i].title = list[i-1].title;
            list[i].author = list[i-1].author;
        }
        list[position - 1].isbnNum = ISBN;
        list[position - 1].title = book_name;
        list[position - 1].author = book_author;
        total_books++;
        is_sorted = false;
        return 0;
    }
}

int Booklist::Linear_search()
{
    int ISBN, position;
    bool found = false;
    cout << "Please enter a ISBN number for search:";
    cin >> ISBN;
    for (int i = 0;i < total_books;i++)
    {
        if (list[i].isbnNum == ISBN)
        {
            position = i + 1;
            found = true;
        }
    }
    if (found)
    {
        cout << "The book you are looking for is: " << endl;
        cout << "Book No." << position << ":"
            << " ----------ISBN number: " << list[position-1].isbnNum
            << " ----------Book Title: " << list[position - 1].title
            << " ----------Book Author: " << list[position - 1].author << endl;
        return 0;
    }
    else
    {
        cerr << "The book you are looking for does not exist" << endl;
        return -1;
    }
}

int Booklist::Binary_search()
{
    if (!is_sorted)
    {
        cerr << "Your book list has not been sorted, please sort it first" << endl;
        return -1;
    }
    else
    {
        int ISBN, L = 0, R = total_books - 1, mid;
        bool found = false;
        cout << "Please enter a ISBN number you want to search:";
        cin >> ISBN;
        int interval = R - L;
        while (interval >= 0)
        {
            if (interval == 0)
                mid = L;
            mid = L + (R - L) / 2;
            if (list[mid].isbnNum == ISBN)
            {
                found = true;
                interval = -1;
            }
            else if (list[mid].isbnNum > ISBN)
            {
                R = mid - 1;
                interval = R - L;
            }
            else if (list[mid].isbnNum < ISBN)
            {
                L = mid + 1;
                interval = R - L;
            }
        }
        if (found)
        {
            cout << "The book you are looking for is: " << endl;
            cout << "Book No." << mid + 1 << ":"
                << " ----------ISBN number: " << list[mid].isbnNum
                << " ----------Book Title: " << list[mid].title
                << " ----------Book Author: " << list[mid].author << endl;
            return 0;
        }
        else
        {
            cerr << "No matches founded" << endl;
            return -1;
        }
    }
}

int Booklist::Delete_at()
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
            list[i].isbnNum = list[i+1].isbnNum;
            list[i].title = list[i + 1].title;
            list[i].author = list[i + 1].author;
        }
        list[total_books-1].isbnNum = 0;
        list[total_books - 1].title = "";
        list[total_books - 1].author = "";
        total_books--;
        return 0;
    }
}

int Booklist::Delete_by_ISBN()
{
    int ISBN, position;
    bool found = false;
    cout << "Please enter a ISBN of a book you want to delete:";
    cin >> ISBN;
    for (int i = 0;i < total_books;i++)
    {
        if (list[i].isbnNum == ISBN)
        {
            position = i + 1;
            found = true;
        }
    }
    if (found)
    {
        for (int i = position - 1;i < total_books - 1;i++)
        {
            list[i].isbnNum = list[i+1].isbnNum;
            list[i].title = list[i + 1].title;
            list[i].author = list[i + 1].author;
        }
        list[total_books-1].isbnNum = 0;
        list[total_books - 1].title = "";
        list[total_books - 1].author = "";
        total_books--;
        return 0;
    }
    else if (!found)
    {
        cerr << "The ISBN does not exist in the current book list" << endl;
        return -1;
    }
}

int Booklist::Selection_sort()
{
    BookInfo tmp;
    int idx;
    for (int i = 0;i < total_books;i++)
    {
        int lowest = list[i].isbnNum;
        idx = i;
        for (int j = i;j < total_books;j++)
        {
            if (list[j].isbnNum < lowest)
            {
                lowest = list[j].isbnNum;
                idx = j;
            }
        }
        tmp.isbnNum = list[i].isbnNum;
        tmp.title = list[i].title;
        tmp.author = list[i].author;
        list[i].isbnNum = list[idx].isbnNum;
        list[i].title = list[idx].title;
        list[i].author = list[idx].author;
        list[idx].isbnNum = tmp.isbnNum;
        list[idx].title = tmp.title;
        list[idx].author = tmp.author;
    }
    is_sorted = true;
    return 0;
}

int Booklist::Bubble_sort()
{
    BookInfo tmp;
    for (int i = total_books - 1;i >= 1;i--)
    {
        for (int j = 0;j < i;j++)
        {
            if (list[j].isbnNum > list[j+1].isbnNum)
            {
                tmp.isbnNum = list[j].isbnNum;
                tmp.title = list[j].title;
                tmp.author = list[j].author;
                list[j].isbnNum = list[j + 1].isbnNum;
                list[j].title = list[j + 1].title;
                list[j].author = list[j + 1].author;
                list[j+1].isbnNum = tmp.isbnNum;
                list[j + 1].title = tmp.title;
                list[j + 1].author = tmp.author;
            }
        }
    }
    is_sorted = true;
    return 0;
}

int Booklist::Set_TestSet()
{
    list[0].isbnNum = 47625;
    list[0].title = "The Game of Math";
    list[0].author = "Alexandar";
    list[1].isbnNum = 95624;
    list[1].title = "What Life Brings";
    list[1].author = "Jessica Mori";
    list[2].isbnNum = 55484;
    list[2].title = "Through the days";
    list[2].author = "Michael Millan";
    list[3].isbnNum = 67854;
    list[3].title = "Nightmare";
    list[3].author = "Mr.Freak";
    list[4].isbnNum = 33696;
    list[4].title = "Best Friends";
    list[4].author = "Amy";
    total_books = 5;
    return 0;
}

int Booklist::Get_totalBooks() const
{
    return total_books;
}