#include <iostream>
#include "GenericSet.h"

using namespace std;

int main()
{
    Set<int> s1;
    Bag<int> s2;
    try{
        for(int i=0;i<21;i++){
            s1.Insert(i/2);
            s2.Insert(i/2);
        }
    }
    catch(const char* ex){
        cout << ex << endl;
    }
    cout << "Set size=" << s1.GetSize() << endl;
    cout << s1 << endl;
    cout << "Bag size=" << s2.GetSize() << endl;
    cout << s2 << endl;

    try{
        for(int i=0;i<11;i++){
            s1.Delete(i);
        }
    }
    catch(const char* ex){
        cout << ex << endl;
    }

    try{
        for(int i=0;i<11;i++){
            s2.Delete(i);
        }
    }
    catch(const char* ex){
        cout << ex << endl;
    }

    cout << "Set size=" << s1.GetSize() << endl;
    cout << s1 << endl;
    cout << "Bag size=" << s2.GetSize() << endl;
    cout << s2 << endl;

}
