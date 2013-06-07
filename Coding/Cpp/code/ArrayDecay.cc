// Message-ID: <84vc631ljm.fsf@gmail.com>
#include <iostream>
using namespace std;

template <typename T, int U>
void pass_by_value(const T px[U]){
     cout<<sizeof(px)<<endl;
}

template <typename T, int U>
void pass_by_reference(const T (&px)[U]){
     cout<<sizeof(px)<<endl;
}
int main(int argc, char *argv[])
{
     int x[100]={1,2,3};
     cout<<x<<endl;
     cout<<&x<<endl;
     cout<<sizeof(x)<<endl;     // 400
     pass_by_value<int,100>(x);     // 4
     pass_by_reference<int,100>(x); // 400
     return 0;
}
