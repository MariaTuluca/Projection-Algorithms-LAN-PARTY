#include<stdio.h>
#include<stdlib.h>

void f4(int aPatra){

    aPatra++;

    printf("sunt in f4\n");
    printf("valoarea %d, adresa %p\n",  aPatra, &aPatra);

    printf("val f4 %d adresa %p\n", aPatra, &aPatra);
}


void f3(int aTreia){

    aTreia++;

    printf("sunt in f3\n");
    printf("valoarea %d, adresa %p\n",  aTreia, &aTreia);

    f4(aTreia);

    printf("val f3 %d adresa %p\n", aTreia, &aTreia);
}

void f2(int *aDoua){

    (*aDoua)++;

    printf("sunt in f2\n");
    printf("valoarea %d, adresa %p\n", *aDoua, aDoua);

    f3(*aDoua);

    printf("val f2 %d adresa %p\n", *aDoua, &(*aDoua));
}

void f1(int *prima){

    (*prima)++;

    printf("sunt in f1\n");
    printf("valoarea %d, adresa %p\n", *prima, prima);

    f2(&(*prima));

    printf("val f1 %d adresa %p\n", *prima, &(*prima));
}

int main(){

    int val = 0;
    val++;

    printf("sunt in main\n");
    printf("valoarea %d, adresa %p\n", val, &val);

    f1(&val);

    printf("val main %d adresa %p", val, &val);
}