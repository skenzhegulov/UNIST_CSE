#include<iostream>

using namespace std;

class ClassA
{
public:
int* value;
ClassA(){
value= new int;
cout << "A: constructor is called\n";
}
~ClassA() {
cout << "A: destructor is called\n";
delete value;
}
void setValue(int x) {*value =x;};
};
class ClassB: public ClassA
{
public:
ClassB(){
cout << "B: constructor is called\n";
}
~ClassB() {
cout << "B: destructor is called\n";
}
};
int main(){
ClassB bObj1;
ClassB* bObj2 = &bObj1;
bObj1.setValue(50);
bObj2->setValue(70);
cout << *bObj1.value << endl;
cout << bObj1.value << endl;
cout << *bObj2->value << endl;
cout << *(*bObj2).value << endl;
return 0;
}
