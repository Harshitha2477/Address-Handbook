#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;
class Contact {
private:
    int entryNumber;
    string firstName;
    string lastName;
    string address;
    string contactNumber;

public:
    Contact() : entryNumber(0), firstName(""), lastName(""), address(""), contactNumber("") {}

    Contact(int entry, const string& first, const string& last, const string& addr, const string& contact)
        : entryNumber(entry), firstName(first), lastName(last), address(addr), contactNumber(contact) {}

    void display() const {
        cout << setw(3) << entryNumber << setw(18) << firstName << setw(25) << lastName
                  <<setw(25) << address << setw(30) << contactNumber << endl;
    }
    
    int getEntryNumber() const {
        return entryNumber;
    }

    friend ostream& operator<<(ostream& os, const Contact& contact);
};

ostream& operator<<(ostream& os, const Contact& contact) {
    os << contact.entryNumber << " " << contact.firstName << " " << contact.lastName << " " << contact.address << " "
       << contact.contactNumber;
    return os;
}

class AddressBook {
private:
   	vector<Contact> contacts;

public:
	string Fname, Lname, Address,Contact1, list, name, Fname2, Lname2, Address2, Contact2;
    double counter, number;
    void addContact() {
    Contact newContact;
    cout << "----------------------Address Book-----------------------------" << endl << endl;
    cout << "Do not use spaces if entry has 2 or more words  ex: KyleAdrian" << endl;
    cout << "Enter 'quit' at First name to quit" << endl << endl;
    cout << "Enter First Name: ";
    getline(cin, Fname);
    if (Fname == "quit")
     return;
    cout << "Enter Last Name: ";
    getline(cin, Lname);
    cout << "Enter Address: ";
    getline(cin, Address);
    cout << "Enter Contact Number: ";
    getline(cin, Contact1);
    
    ifstream asd("AddressBook.txt");
    while(asd >> counter >> Fname2 >> Lname2 >> Address2 >> Contact2)
	{
        if (contacts.size() >= 100) {
            cout << "Invalid! Maximum number of contacts reached (100)." <<endl;
            return;
        }

        newContact = Contact(contacts.size() + 1, newContact.firstName, newContact.lastName, newContact.address, newContact.contactNumber);
        contacts.push_back(newContact);

        saveToFile();
        cout << "Contact added successfully!" << endl;
    }

    void viewContacts() const {
        cout << "Entry #" << setw(17) << "First Name" << setw(23) << "Last Name" << setw(23)
                  << "Address" << setw(29) << "Contact" << endl << endl;

        for (const auto& contact : contacts) {
            contact.display();
        }
        cout << endl;
    }

    void searchContact() const {
        int choice;
        cout << "1.) First name" << endl;
        cout << "2.) Last name" << endl;
        cout << "3.) Address" << endl;
        cout << "4.) Contact " <<endl;
        cout << "Enter Choice: ";
        cin >> choice;

        string searchTerm;
        cout << "Enter search term: ";
        cin >> searchTerm;

        cout << "Search Results:" << endl;

        switch (choice) {
            case 1:
                searchByFirstName(searchTerm);
                break;
            case 2:
                searchByLastName(searchTerm);
                break;
            case 3:
                searchByAddress(searchTerm);
                break;
            case 4:
                searchByContact(searchTerm);
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    }

private:
    void searchByFirstName(const string& term) const {
        for (const auto& contact : contacts) {
            if (contact.firstName == term) {
                printContact(contact);
            }
        }
    }
    void searchByLastName(const string& term) const {
        for (const auto& contact : contacts) {
            if (contact.lastName == term) {
                printContact(contact);
            }
        }
    }
    void searchByAddress(const string& term) const {
        for (const auto& contact : contacts) {
            if (contact.address == term) {
                printContact(contact);
            }
        }
    }
    void searchByContact(const string& term) const {
        for (const auto& contact : contacts) {
            if (contact.contactNumber == term) {
                printContact(contact);
            }
        }
    }
};

    void editContact() {
        int choice;
        cout << "Please type the Entry number that you wish to edit: ";
        cin >> choice;
        cout << endl;

        auto it = find_if(contacts.begin(), contacts.end(),
                               [choice](const Contact& contact) { return contact.getEntryNumber() == choice; });

        if (it != contacts.end()) {
            printContact(*it);
            cout << "Is this the contact that you wish to edit? (y or n) ";
            char choice3;
            cin >> choice3;
            cout << endl;

            if (choice3 == 'y') {
                cout << "Enter New First name: ";
                cin >> it->firstName;
                cout << "Enter New Last name: ";
                cin >> it->lastName;
                cout << "Enter New Address: ";
                cin >> it->address;
                cout << "Enter New Contact: ";
                cin >> it->contactNumber;

                saveToFile();
                cout << "Contact edited successfully!" <<endl;
            } else {
                cout << "Editing canceled." <<endl;
            }
        } else {
            cout << "Entry not found." << endl;
        }
    }

    void deleteContact() {
        int choice;
        cout << "Please type the Entry number that you wish to delete: ";
        cin >> choice;
        cout << endl;

        auto it = remove_if(contacts.begin(), contacts.end(),
                                 [choice](const Contact& contact) { return contact.getEntryNumber() == choice; });

        if (it != contacts.end()) {
            contacts.erase(it, contacts.end());
            cout << "Contact deleted successfully!" << endl;
            saveToFile();
        } else {
            cout << "Entry not found." << endl;
        }
    }

private:
    void saveToFile() const {
        ofstream outFile("AddressBook.txt");
        for (const auto& contact : contacts) {
            outFile << contact << endl;
        }
        outFile.close();
    }
};

int main() {
    AddressBook addressBook;

    bool run = true;
    do {
        int option;
       	cout << "----------------------Address Book-----------------------------" << endl;
        cout << "\n";
        cout << "What would you like to do?" <<endl;
        cout << "1.) Add Contact" << endl;
        cout << "2.) Edit Contact" << endl;
        cout << "3.) Delete Contact" << endl;
        cout << "4.) View All Contacts" << endl;
        cout << "5.) Search Address Book" << endl;
        cout << "6.) Exit" << endl << endl;
        cout << "Choose an option: ";
        cin >> option;
        cin.ignore();

        switch (option) {
            case 1:
                addressBook.addContact();
                break;
            case 2:
                addressBook.editContact();
                break;
            case 3:
                addressBook.deleteContact();
                break;
            case 4:
                addressBook.viewContacts();
                break;
            case 5:
                addressBook.searchContact();
                break;
            case 6:
                run = false;
                break;
            default:
                std::cout << "Please choose between 1 to 6" << endl;
        }
    } while (run);
    cout << "Program Terminated";
    return 0;
}
