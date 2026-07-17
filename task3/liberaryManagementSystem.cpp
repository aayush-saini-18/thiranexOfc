#include <iostream>
#include <vector>
#include <string>
using namespace std;

// -------------------- Book Class --------------------
class Book {
public:
    int bookID;
    string title;
    string author;
    bool issued;

    Book(int id, string t, string a) {
        bookID = id;
        title = t;
        author = a;
        issued = false;
    }

    void display() {
        cout << "\nBook ID : " << bookID;
        cout << "\nTitle   : " << title;
        cout << "\nAuthor  : " << author;
        cout << "\nStatus  : " << (issued ? "Issued" : "Available") << endl;
    }
};

// -------------------- Member Class --------------------
class Member {
public:
    int memberID;
    string name;

    Member(int id, string n) {
        memberID = id;
        name = n;
    }

    void display() {
        cout << "Member ID : " << memberID << endl;
        cout << "Name      : " << name << endl;
    }
};

// -------------------- Library Class --------------------
class Library {
private:
    vector<Book> books;
    vector<Member> members;

public:
    // Add Book
    void addBook() {
        int id;
        string title, author;

        cout << "\nEnter Book ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        books.push_back(Book(id, title, author));
        cout << "Book added successfully!\n";
    }

    // Add Member
    void addMember() {
        int id;
        string name;

        cout << "\nEnter Member ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Member Name: ";
        getline(cin, name);

        members.push_back(Member(id, name));
        cout << "Member added successfully!\n";
    }

    // Display Books
    void displayBooks() {
        if (books.empty()) {
            cout << "\nNo books available.\n";
            return;
        }

        cout << "\n------ Book List ------\n";
        for (Book &b : books)
            b.display();
    }

    // Issue Book
    void issueBook() {
        int id;
        cout << "\nEnter Book ID to issue: ";
        cin >> id;

        for (Book &b : books) {
            if (b.bookID == id) {
                if (!b.issued) {
                    b.issued = true;
                    cout << "Book issued successfully.\n";
                } else {
                    cout << "Book is already issued.\n";
                }
                return;
            }
        }

        cout << "Book not found.\n";
    }

    // Return Book
    void returnBook() {
        int id;
        cout << "\nEnter Book ID to return: ";
        cin >> id;

        for (Book &b : books) {
            if (b.bookID == id) {
                if (b.issued) {
                    b.issued = false;
                    cout << "Book returned successfully.\n";
                } else {
                    cout << "Book was not issued.\n";
                }
                return;
            }
        }

        cout << "Book not found.\n";
    }

    // Search by Title
    void searchByTitle() {
        string title;
        cin.ignore();

        cout << "\nEnter Title: ";
        getline(cin, title);

        bool found = false;

        for (Book &b : books) {
            if (b.title == title) {
                b.display();
                found = true;
            }
        }

        if (!found)
            cout << "No matching book found.\n";
    }

    // Search by Author
    void searchByAuthor() {
        string author;
        cin.ignore();

        cout << "\nEnter Author Name: ";
        getline(cin, author);

        bool found = false;

        for (Book &b : books) {
            if (b.author == author) {
                b.display();
                found = true;
            }
        }

        if (!found)
            cout << "No books found by this author.\n";
    }
};

// -------------------- Main Function --------------------
int main() {
    Library library;
    int choice;

    do {
        cout << "\n==============================";
        cout << "\n LIBRARY MANAGEMENT SYSTEM";
        cout << "\n==============================";
        cout << "\n1. Add Book";
        cout << "\n2. Add Member";
        cout << "\n3. Display Books";
        cout << "\n4. Issue Book";
        cout << "\n5. Return Book";
        cout << "\n6. Search Book by Title";
        cout << "\n7. Search Book by Author";
        cout << "\n8. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                library.addBook();
                break;

            case 2:
                library.addMember();
                break;

            case 3:
                library.displayBooks();
                break;

            case 4:
                library.issueBook();
                break;

            case 5:
                library.returnBook();
                break;

            case 6:
                library.searchByTitle();
                break;

            case 7:
                library.searchByAuthor();
                break;

            case 8:
                cout << "\nThank you for using the Library Management System.\n";
                break;

            default:
                cout << "\nInvalid choice.\n";
        }

    } while (choice != 8);

    return 0;
}
