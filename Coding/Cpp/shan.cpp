semaphore mutex=1;
semaphore s1=s2=s3=s4=s5=s6=0;

ProcessA(){
    P(mutex);                   // 获得输入设备
    输入a;
    V(mutex);
    V(s1);
    P(s2);
    x=a+b;
    P(s3);
    P(s6);
    打印x,y,z;
}

ProcessB(){
    P(s1);
    P(mutex);
    输入b;
    V(mutex);
    V(s4);
    V(s2);
    y=a*b;
    V(s5);
    V(s3);
}

ProcessC(){
    P(s4);
    P(mutex);
    输入c;
    V(mutex);
    P(s5);
    z=y+c-a;
    V(s6);
}


semaphore S=0;
A(){
    ....;
    V(S);
}
B(){
    P(S);
    ....;
}
