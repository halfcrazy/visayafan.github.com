/*
  g++ -g -Wall -o VirtualInheritence VirtualInheritence.cc -fpermissive
  http://blog.csdn.net/haoel/article/details/3081385
*/
#include <iostream>
#include <vector>
using namespace std;

class B
{
public:
     int ib;
     char cb;
public:
     B():ib(0),cb('B') {}

     virtual void f() { cout << "B::f()" << endl;}
     virtual void Bf() { cout << "B::Bf()" << endl;}
};
class B1 :  virtual public B
{
public:
     int ib1;
     char cb1;
public:
     B1():ib1(11),cb1('1') {}

     virtual void f() { cout << "B1::f()" << endl;}
     virtual void f1() { cout << "B1::f1()" << endl;}
     virtual void Bf1() { cout << "B1::Bf1()" << endl;}

};
class B2:  virtual public B
{
public:
     int ib2;
     char cb2;
public:
     B2():ib2(12),cb2('2') {}

     virtual void f() { cout << "B2::f()" << endl;}
     virtual void f2() { cout << "B2::f2()" << endl;}
     virtual void Bf2() { cout << "B2::Bf2()" << endl;}

};

class D : public B1, public B2
{
public:
     int id;
     char cd;
public:
     D():id(100),cd('D') {}

     virtual void f() { cout << "D::f()" << endl;}
     virtual void f1() { cout << "D::f1()" << endl;}
     virtual void f2() { cout << "D::f2()" << endl;}
     virtual void Df() { cout << "D::Df()" << endl;}

};
int main(int argc, char *argv[])
{
     typedef void(*Fun)(void);
     int** pVtab = NULL;
     Fun pFun = NULL;

     D d;
     pVtab = (int**)&d;
     cout << "[0] D::B1::_vptr->" << endl;
     pFun = (Fun)pVtab[0][0];
     cout << "     [0] ";    pFun();
     pFun = (Fun)pVtab[0][1];
     cout << "     [1] ";    pFun();
     pFun = (Fun)pVtab[0][2];
     cout << "     [2] ";    pFun();
     pFun = (Fun)pVtab[0][3];
     cout << "     [3] ";    pFun();
     pFun = (Fun)pVtab[0][4];
     cout << "     [4] ";    pFun();
     pFun = (Fun)pVtab[0][5];
     cout << "     [5] 0x" << pFun << endl;

     cout << "[1] B1::ib1 = " << (int)pVtab[1] << endl;
     cout << "[2] B1::cb1 = " << (char)pVtab[2] << endl;

     cout << "[3] D::B2::_vptr->" << endl;
     pFun = (Fun)pVtab[3][0];
     cout << "     [0] ";    pFun();
     pFun = (Fun)pVtab[3][1];
     cout << "     [1] ";    pFun();
     pFun = (Fun)pVtab[3][2];
     cout << "     [2] ";    pFun();
     pFun = (Fun)pVtab[3][3];
     cout << "     [3] 0x" << pFun << endl;

     cout << "[4] B2::ib2 = " << (int)pVtab[4] << endl;
     cout << "[5] B2::cb2 = " << (char)pVtab[5] << endl;

     cout << "[6] B::ib = " << (int)pVtab[6] << endl;
     cout << "[7] B::cb = " << (char)pVtab[7] << endl;

     cout << "[8] D::B2::_vptr->" << endl;
     pFun = (Fun)pVtab[8][0];
     cout << "     [0] ";    pFun();
     pFun = (Fun)pVtab[8][1];
     cout << "     [1] ";    pFun();
     pFun = (Fun)pVtab[8][2];
     cout << "     [2] 0x" << pFun << endl;
     return 0;
}


/*
[0] D::B1::_vptr->
     [0] D::f()
     [1] D::f1()
     [2] B1::Bf1()
     [3] D::f2()
     [4] D::Df()
     [5] 0x1
[1] B1::ib1 = 11
[2] B1::cb1 = 1
[3] D::B2::_vptr->
     [0] D::f()
     [1] D::f2()
     [2] B2::Bf2()
     [3] 0x0
[4] B2::ib2 = 12
[5] B2::cb2 = 2
[6] B::ib = 100
[7] B::cb = D
[8] D::B2::_vptr->
     [0] D::f()
     [1] B::Bf()
     [2] 0x1
 */