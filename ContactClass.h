#include <string>
using namespace std;
class Contact                       //Class Contact untuk kontak, termasuk method untuk manipulasi datanya
{
    public:
        string name, phone_number, organization, tags;

        void displayData(int i);                         //Daffa
        void addData();                                  //Gilbert
        void editContact();                              //Gilbert
        void deleteData();                               //Giga

};
