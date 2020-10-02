#include <iostream>
#include <string>
#include<limits>
using namespace std;

struct BookInfo {
    int isbnNum;
    string title;
    string author;
};

void printBookList(BookInfo[], int);

int Display_Menu(int total_books)
{
    int choice;
    /* not working right
    cout << "(Press enter to continue)" << endl;
    cin.clear();
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    */
    cout << "\nWelcome to the book manage system!";
    if (total_books == 0)
    {
        cout << "Currently you don't have any book in your book list"
            << ", so you only have the following options:" << endl;
        cout << "0: Exit the system" << endl;
        cout << "1: Insert a new book at the begining of the list" << endl;
    }
    else
    {
        cout << "You have the following operations:" << endl;
        cout << "0: Exit the system" << endl;
        cout << "1: Insert a new book at the end of the list" << endl;
        cout << "2: Insert a new book at a certain position" << endl;
        cout << "3: Find a book using linear search" << endl;
        cout << "4: Find a book of a sorted list using binary search" << endl;
        cout << "5: Delete a book that is at a certain position" << endl;
        cout << "6: Delete a book by using its ISBN number" << endl;
        cout << "7: Sort the list by the ISBN numbers(selection sort)" << endl;
        cout << "8: Sort the list by the ISBN numbers(bubble sort)" << endl;
        cout << "9: Print out the list" << endl;
    }
    cout << "Please enter an your choice of operating your book list here:";
    cin >> choice;
    return choice;
}//End Display Menu

int Insert(BookInfo* books, int total_books)
{
    int ISBN;
    string book_name="\n", book_author="\n";
    if (total_books == 20)
    {
        cerr << "No more book could be inserted, please delete one first" << endl;
        return -1;
    }
    else
    {
        cout << "Please enter the ISBN number(integer): " ;
        cin >> ISBN;
        cout << "Please enter the title of book: ";
        getline(cin, book_name);
        getline(cin, book_name);
        cout << "Please enter the author's name of the book: ";
        getline(cin, book_author);
        (books + total_books)->isbnNum = ISBN;
        (books + total_books)->title = book_name;
        (books + total_books)->author = book_author;
        return 0;
    }
}

int Insert_at(BookInfo* books, int total_books)
{
    int ISBN,position;
    string book_name = "\n", book_author = "\n";
    if (total_books == 20)
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
        for (int i = total_books;i>=position;i--)
        {
            (books + i)->isbnNum = (books + i - 1)->isbnNum;
            (books + i)->title = (books + i - 1)->title;
            (books + i)->author = (books + i - 1)->author;
        }
        (books + position-1)->isbnNum = ISBN;
        (books + position-1)->title = book_name;
        (books + position-1)->author = book_author;
        return 0;
    }
}

int Linear_search(BookInfo* books, int total_books)
{
    int ISBN,position;
    bool found = false;
    cout << "Please enter a ISBN number for search:";
    cin >> ISBN;
    for (int i = 0;i < total_books;i++)
    {
        if ((books + i)->isbnNum == ISBN)
        {
            position = i + 1;
            found = true;
        }
    }
    if (found)
    {
        cout << "The book you are looking for is: " << endl;
        cout << "Book No." << position << ":"
            << " ----------ISBN number: " << (books + position-1)->isbnNum
            << " ----------Book Title: " << (books + position-1)->title
            << " ----------Book Author: " << (books + position-1)->author << endl;
        return 0;
    }
    else
    {
        cerr << "The book you are looking for does not exist" << endl;
        return-1;
    }
}

int Binary_search(BookInfo* books, int total_books)
{
    int ISBN,L=0,R=total_books-1,mid;
    bool found=false;
    cout << "Please enter a ISBN number you want to search:";
    cin >> ISBN;
    int interval = R-L;
    while (interval>=0)
    {
        if (interval == 0)
            mid = L;
        mid = L + (R - L) / 2;
        if ((books + mid)->isbnNum == ISBN)
        {
            found=true;
            interval = -1;
        }
        else if ((books + mid)->isbnNum > ISBN)
        {
            R = mid-1;
            interval = R - L;
        }
        else if ((books + mid)->isbnNum < ISBN)
        {
            L = mid+1;
            interval = R - L;
        }
    }
    if (found)
    {
        cout << "The book you are looking for is: " << endl;
        cout << "Book No." << mid+1 << ":"
            << " ----------ISBN number: " << (books + mid)->isbnNum
            << " ----------Book Title: " << (books + mid)->title
            << " ----------Book Author: " << (books + mid)->author << endl;
        return 0;
    }
    else
    {
        cerr << "No matches founded" << endl;
        return -1;
    }
}

int Delete_at(BookInfo* books, int total_books)
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
    else
    {
        for (int i = position - 1;i < total_books-1;i++)
        {
            (books + i)->isbnNum = (books + i + 1)->isbnNum;
            (books + i)->title = (books + i + 1)->title;
            (books + i)->author = (books + i + 1)->author;
        }
        (books + total_books - 1)->isbnNum = NULL;
        (books + total_books - 1)->title = "";
        (books + total_books - 1)->author = "";
        return 0;
    }
}

int Delete_by_ISBN(BookInfo* books, int total_books)
{
    int ISBN,position;
    bool found=false;
    cout << "Please enter a ISBN of a book you want to delete:";
    cin >> ISBN;
    for (int i = 0;i < total_books;i++)
    {
        if ((books + i)->isbnNum == ISBN)
        {
            position = i + 1;
            found = true;
        }
    }
    if (found)
    {
        for (int i = position - 1;i < total_books - 1;i++)
        {
            (books + i)->isbnNum = (books + i + 1)->isbnNum;
            (books + i)->title = (books + i + 1)->title;
            (books + i)->author = (books + i + 1)->author;
        }
        (books + total_books - 1)->isbnNum = NULL;
        (books + total_books - 1)->title = "";
        (books + total_books - 1)->author = "";
        return 0;
    }
    else if (!found)
    {
        cerr << "The ISBN does not exist in the current book list" << endl;
        return -1;
    }
}

int Selection_sort(BookInfo* books, int total_books)
{
    BookInfo tmp;
    int idx;
    for (int i = 0;i < total_books;i++)
    {
        int lowest = (books + i)->isbnNum;
        idx = i;
        for (int j = i;j < total_books;j++)
        {
            if ((books + j)->isbnNum < lowest)
            {
                lowest = (books + j)->isbnNum;
                idx = j;
            }
        }
        tmp.isbnNum = (books + i)->isbnNum;
        tmp.title = (books + i)->title;
        tmp.author = (books + i)->author;
        (books + i)->isbnNum = (books + idx)->isbnNum;
        (books + i)->title = (books + idx)->title;
        (books + i)->author = (books + idx)->author;
        (books + idx)->isbnNum = tmp.isbnNum;
        (books + idx)->title = tmp.title;
        (books + idx)->author = tmp.author;
    }
    return 0;
}

int Bubble_sort(BookInfo* books, int total_books)
{
    BookInfo tmp;
    for (int i = total_books-1;i >= 1;i--)
    {
        for (int j = 0;j < i;j++)
        {
            if ((books + j)->isbnNum > (books + j + 1)->isbnNum)
            {
                tmp.isbnNum = (books + j)->isbnNum;
                tmp.title = (books + j)->title;
                tmp.author = (books + j)->author;
                (books + j)->isbnNum = (books + j+1)->isbnNum;
                (books + j)->title = (books + j+1)->title;
                (books + j)->author = (books + j+1)->author;
                (books + j + 1)->isbnNum = tmp.isbnNum;
                (books + j + 1)->title = tmp.title;
                (books + j + 1)->author = tmp.author;
            }
        }
    }
    return 0;
}

int main() {
    BookInfo bookList[20];
    BookInfo* bookPtr = bookList;
    int totalBooks = 0;
    int choice = 1;
    int op_result;
    bool is_sorted = false;

    //Creating a test datasets
    char preference;
    cout << "Do you prefer using the prepared testing booklist datasets?[y/n]:";
    cin >> preference;
    if (preference == 'Y' || preference == 'y')
    {
        bookList[0].isbnNum = 47625;
        bookList[0].title = "The Game of Math";
        bookList[0].author = "Alexandar";
        bookList[1].isbnNum = 95624;
        bookList[1].title = "What Life Brings";
        bookList[1].author = "Jessica Mori";
        bookList[2].isbnNum = 55484;
        bookList[2].title = "Through the days";
        bookList[2].author = "Michael Millan";
        bookList[3].isbnNum = 67854;
        bookList[3].title = "Nightmare";
        bookList[3].author = "Mr.Freak";
        bookList[4].isbnNum = 33696;
        bookList[4].title = "Best Friends";
        bookList[4].author = "Amy";
        totalBooks = 5;
    }

    while(choice != 0)
    {
        choice=Display_Menu(totalBooks);
        switch (choice)
        {
        case 1:
            op_result = Insert(bookPtr, totalBooks);
            if (op_result == 0)
            {
                totalBooks++;
                is_sorted = false;
            }
            break;
        case 2:
            op_result = Insert_at(bookPtr, totalBooks);
            if (op_result == 0)
            {
                totalBooks++;
                is_sorted = false;
            }
            break;
        case 3:
            op_result = Linear_search(bookPtr, totalBooks);
            break;
        case 4:
            if (is_sorted)
            {
                op_result = Binary_search(bookPtr,totalBooks);
            }
            else if (!is_sorted)
            {
                cerr << "Your book list has not been sorted, please sort it first" << endl;
            }
            break;
        case 5:
            op_result = Delete_at(bookPtr, totalBooks);
            if (op_result == 0)
                totalBooks--;
            break;
        case 6:
            op_result = Delete_by_ISBN(bookPtr, totalBooks);
            if (op_result == 0)
                totalBooks--;
            break;
        case 7:
            op_result = Selection_sort(bookPtr, totalBooks);
            if (op_result == 0)
                is_sorted = true;
            break;
        case 8:
            op_result = Bubble_sort(bookPtr, totalBooks);
            if (op_result == 0)
                is_sorted = true;
            break;
        case 9:
            printBookList(bookPtr, totalBooks);
            //printBookList(bookList, 2);
            break;
        }
    }
    return 0;
}

// void printBookList(BookInfo books[], int size) {
void printBookList(BookInfo* books, int size) {
    for (int idx = 0; idx < size; idx++) 
    {
        cout << "Book No."<<(idx+1)<<":"
            << " ----------ISBN number: "<< (books + idx)->isbnNum 
            << " ----------Book Title: " << (books + idx)->title
            << " ----------Book Author: "<< (books + idx)->author<<endl;
    }
    return;
}