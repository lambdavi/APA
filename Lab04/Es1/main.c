#include <stdio.h>
int gcd(int a, int b){
    if(a==b) return a;
    if(b > a){
        int t;
        t=a;
        a=b;
        b=t;
    }
    if (a % 2 == 0) {
        if (b % 2 == 0)
            return 2 * gcd(a / 2, b / 2);
        else
            return gcd(a / 2, b);
    }
    else if(b%2==0) return gcd(a,b/2);
    else return gcd((a-b)/2, b);
}
int main() {
    int a, b, MCD;
    printf("Inserisci a e b: ");
    scanf("%d %d", &a, &b);
    MCD = gcd(a, b);
    printf("L'MCD e': %d", MCD);
}
