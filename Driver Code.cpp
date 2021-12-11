#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "ContactClass.h"
#define LIMIT 100

using namespace std;

//Deklarasi global variable di sini
bool end_program;
int choice, entry, search_category;
string searched;
size_t matched;
Contact contact[LIMIT];              //Multiple objects at once
//=================================

void ignoreLine()                   //ignoreLine function untuk menghindari infinite loop karena input selain integer
{
    cin.clear();
    cin.ignore();
}

void readFile(ifstream &readData)
{
    int i = 0;
    int rownumber = 0, pos = 0;
    string tempstring, data;
    while(getline(readData, tempstring))
    {
        int decision = rownumber%6;
        pos = tempstring.find(":");
        if(pos == -1)
        {
            rownumber++;
            continue;
        }
        data = tempstring.substr(pos + 2);

        switch (decision)
        {
        case 0:
        case 1:
            contact[i].name = data;
            break;
        case 2:
            contact[i].phone_number = data;
            break;
        case 3:
            contact[i].organization = data;
            break;
        case 4:
            contact[i].tags = data;
            i++;
            break;
        case 5:
        default:
            break;
        }
        rownumber++;
    }
}

void writeFile(int i, ofstream &writeData)
{
    if(contact[i].name == "" && contact[i].phone_number == "")
        return;
    writeData << i+1 << endl;
    writeData << "Nama: " << contact[i].name << endl;
    writeData << "Nomor Telpon: " << contact[i].phone_number << endl;
    writeData << "Organisasi: " << contact[i].organization << endl;
    writeData << "Tags: " << contact[i].tags << endl;
    writeData << endl;
}

int searchFunc(string parameter, string searched, size_t matched, int i)    //Daffa
{
    bool found = 0;
    matched = parameter.find(searched);
    if(matched != string::npos)
    {
        contact[i].displayData(i);
        found = 1;
    }

    return found;
}

void invalidInput()
{
    cout << endl << "Input Anda tidak valid. Kembali ke menu utama." << endl;
}

void mainMenu()                     //Main Menu dari program
{
    int counter = 0, temp = 0;

    cout << endl << "==================================================================" << endl;
    cout << "Selamat datang di program buku telpon. Apa yang mau Anda lakukan?\n";
    cout << "1. Menampilkan seluruh kontak\n2. Mengubah info kontak\n3. Menambah kontak\n4. Menghapus kontak\n5. Mencari kontak\n6. Simpan dan keluar\n";
    cout << "==================================================================" << endl;
    cin >> choice;
    switch(choice)
    {
    case 1:
        cout << "Menampilkan seluruh kontak" << endl;
        for(int i = 0; i < LIMIT; i++)
        {
            if(contact[i].name != "")
            contact[i].displayData(i);
        }
        break;
    case 2:
        cout << "Mengubah info kontak" << endl << endl;
        cout << "Entri yang ingin diubah: ";
        cin >> entry;
        contact[entry-1].editContact();
        printf("\nKontak dengan kode entri %d berhasil diubah.\n", entry);
        break;
    case 3:
        cout << "Menambahkan kontak baru" << endl << endl;
        for(int i = 0; i < LIMIT; i++)
        {
            if(contact[i].name == "")
            {
                contact[i].addData();
                printf("\nKontak berhasil ditambahkan dengan kode entri: %d.\n", i+1);
                break;
            }
            else if(i == LIMIT-1 && contact[LIMIT].name != "")
                printf("Jumlah kontak sudah mencapai batasnya (%d).\n", LIMIT);
        }
        break;
    case 4:
        cout << "Menghapus kontak" << endl << endl;
        cout << "Entri yang mau dihapus nomor: ";
        cin >> entry;
        contact[entry-1].deleteData();
        break;
    case 5:
        cout << "Mencari kontak" << endl;
        cout << "Cari berdasarkan:\n1. Nama\n2. Nomor telpon\n3. Organisasi\n4. Tags\nNomor: ";
        cin >> search_category;
        cout << "Cari: ";
        fflush(stdin);
        getline(cin, searched);
        switch(search_category)
        {
        case 1:
            for(int i = 0; i < LIMIT; i++)
            {
                temp = searchFunc(contact[i].name, searched, matched, i);
                counter += temp;
            }
            printf("\nBerhasil menemukan %d hasil yang sesuai.\n", counter);
            break;
        case 2:
            for(int i = 0; i < LIMIT; i++)
            {
                temp = searchFunc(contact[i].phone_number, searched, matched, i);
                counter += temp;
            }
            printf("\nBerhasil menemukan %d hasil yang sesuai.\n", counter);
            break;
        case 3:
            for(int i = 0; i < LIMIT; i++)
            {
                temp = searchFunc(contact[i].organization, searched, matched, i);
                counter += temp;
            }
            printf("\nBerhasil menemukan %d hasil yang sesuai.\n", counter);
            break;
        case 4:
            for(int i = 0; i < LIMIT; i++)
            {
                temp = searchFunc(contact[i].tags, searched, matched, i);
                counter += temp;
            }
            printf("\nBerhasil menemukan %d hasil yang sesuai.\n", counter);
            break;
        default:
            invalidInput();
            break;
        }
        break;
    case 6:
        cout << endl << "Data sudah tersimpan." << endl << "Terima kasih telah menggunakan program ini." << endl;
        end_program = 1;
        break;
    default:
        invalidInput();
        break;
    }
}

int main()                      //Driver Code
{
    ifstream readData("Phonebook Save.txt");

    while(!end_program)
    {
        readFile(readData);
        mainMenu();

        while (cin.fail())
            ignoreLine();
    }

    ofstream writeData("Phonebook Save.txt");

    for(int i = 0; i < LIMIT; i++)
        writeFile(i, writeData);

    writeData.close();
    readData.close();

    return 0;
}
