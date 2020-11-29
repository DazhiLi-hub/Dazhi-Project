#include<limits>
#include "Booklist.h"

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

int main() {
    cout << "Do you want to use string type list or int type list?:"
        << endl << "(1 for string type, 2 for int type)";
    char type;
    cin >> type;
    if (type == '1')
    {
        Booklist<string> yourlist;
        int choice = 1;
        int op_result;

        //Creating a test datasets
        char preference;
        cout << "Do you prefer using the prepared testing booklist datasets?[y/n]:";
        cin >> preference;
        if (preference == 'Y' || preference == 'y')
        {
            op_result = yourlist.Set_TestSet_string();
            if (op_result != 0)
            {
                cerr << "System Error, Exit" << endl;
                return -1;
            }
        }

        while (choice != 0)
        {
            choice = Display_Menu(yourlist.Get_totalBooks());
            switch (choice)
            {
            case 1:
                op_result = yourlist.Insert();
                break;
            case 2:
                op_result = yourlist.Insert_at();
                break;
            case 3:
                op_result = yourlist.Linear_search();
                break;
            case 4:
                op_result = yourlist.Binary_search();
                break;
            case 5:
                op_result = yourlist.Delete_at();
                break;
            case 6:
                op_result = yourlist.Delete_by_ISBN();
                break;
            case 7:
                op_result = yourlist.Selection_sort();
                break;
            case 8:
                op_result = yourlist.Bubble_sort();
                break;
            case 9:
                yourlist.printBookList();
                //printBookList(bookList, 2);
                break;
            }
        }
    }
    else if (type == '2')
    {
        Booklist<int> yourlist;
        int choice = 1;
        int op_result;

        //Creating a test datasets
        char preference;
        cout << "Do you prefer using the prepared testing booklist datasets?[y/n]:";
        cin >> preference;
        if (preference == 'Y' || preference == 'y')
        {
            op_result = yourlist.Set_TestSet_int();
            if (op_result != 0)
            {
                cerr << "System Error, Exit" << endl;
                return -1;
            }
        }

        while (choice != 0)
        {
            choice = Display_Menu(yourlist.Get_totalBooks());
            switch (choice)
            {
            case 1:
                op_result = yourlist.Insert();
                break;
            case 2:
                op_result = yourlist.Insert_at();
                break;
            case 3:
                op_result = yourlist.Linear_search();
                break;
            case 4:
                op_result = yourlist.Binary_search();
                break;
            case 5:
                op_result = yourlist.Delete_at();
                break;
            case 6:
                op_result = yourlist.Delete_by_ISBN();
                break;
            case 7:
                op_result = yourlist.Selection_sort();
                break;
            case 8:
                op_result = yourlist.Bubble_sort();
                break;
            case 9:
                yourlist.printBookList();
                //printBookList(bookList, 2);
                break;
            }
        }
    }
    else
    {
        cerr << "Invalid input, please try again" << endl;
    }
    return 0;
}