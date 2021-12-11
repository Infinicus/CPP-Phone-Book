#include <iostream>
#include <string>
#include "ContactClass.h"

using namespace std;

void Contact::displayData(int i)                         //Daffa
{
    cout << endl << i+1 << endl;
    cout << "Nama:" << name << endl;
    cout << "Nomor telpon:" << phone_number << endl;
    cout << "Organisasi:" << organization << endl;
    cout << "Tags:" << tags << endl;
}

void Contact::addData()                                  //Gilbert
{
    cout << "Masukkan Nama: ";
    fflush(stdin);                              //dump \n in buffer
    getline(cin, name);

    cout << "Masukkan nomor telpon: ";
    getline(cin, phone_number);

    cout << "Masukkan organisasi: ";
    getline(cin, organization);

    cout << "Masukkan tag: ";
    getline(cin, tags);
}

void Contact::editContact()                              //Gilbert
{
    string pilihan;

    if(name == "")                              //if entry is empty then offers an option to add a new one
    {
        cout << "Entry ini kosong, apakah mau menambahkan kontak baru? (y/n)" << endl;
        cin >> pilihan;
        if(pilihan == "y" || pilihan == "Y")
            addData();
        else
            return;
    }
    else                                        //if entry is not empty then continue edit the existing contact
    {
        addData();
    }
}

void Contact::deleteData()
{
    if(name == "")
        cout << endl << "Entri kosong." << endl;
    else
    {
        name = "";
        phone_number = "";
        organization = "";
        tags = "";
        cout << endl << "Entri berhasil dihapus." << endl;
    }
}
