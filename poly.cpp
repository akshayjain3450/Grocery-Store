#include<iostream>
using namespace std;

class family
{
        string name;
};
class collegue
{
    string name;
};
class boss
{
    string name;
};
class person
{
    string name;
    public:
    void greet(family f)
    {
        cout<<"nameste!"<<endl;
    }
    void greet(collegue c)
    {
        cout<<"hi!"<<endl;
    }
    void greet(boss b)
    {
        cout<<"good morning!"<<endl;
    }
};
int main()
{
    person alice;
    family dad;
    collegue bob;
    boss harry;
    alice.greet(bob);
    alice.greet(dad);
    alice.greet(harry);
    return 0;
}