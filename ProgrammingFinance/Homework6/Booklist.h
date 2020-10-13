#ifndef BOOKLIST_H
#define BOOKLIST_H

#include<string>
#include<iostream>

using namespace std;

struct BookInfo {
    int isbnNum;
    string title;
    string author;
};

class Booklist
{
private:
    BookInfo list[20];
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
    int Set_TestSet();
    int Get_totalBooks() const;
};

#endif