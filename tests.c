#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define P 761
#define Q 547


static int get_gcd(int num1, int num2)
{
    return num2 ? get_gcd (num2, num1 % num2) : num1;
}

static int are_coprime(int num1, int num2)
{
    return get_gcd(num1, num2) == 1;
}

static int generate_random_num(int min, int max)
{
    int rand_num = rand() % (max - min + 1) + min;
    printf("\nrand: %d\n", rand_num);
    return rand_num;
}

int gcd (int a, int b) 
{
	return b ? gcd (b, a % b) : a;
}

int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i <= sqrt(num); ++i) {
        if (num % i == 0) return 0;
    }
    return 1;
}

static int generate_e(int phi)
{
    int e; 

    do
    {
        e = generate_random_num(1, phi - 1);
    }
    while(!are_coprime(phi, e));

    return e;
}

static int generate_d(int phi, int e)
{   
    for(int i = 0; i < phi; ++i)
    {
        if(((e * i) % phi) == 1) return i;
    }
}

int gcdExtended(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    
    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1);
    
    *x = y1 - (b/a) * x1;
    *y = x1;
    
    return gcd;
}

int modInverse(int e, int phi) {
    int x, y;
    int gcd = gcdExtended(e, phi, &x, &y);
    
    if (gcd != 1) {
        // Невозможно вычислить обратное значение
        return -1;
    } else {
        int result = (x % phi + phi) % phi;
        return result;
    }
}


int main(void)
{
    int e;
    int phi;

    srand(time(NULL));
    //printf("gcd: %d", gcd(9787, 9839));
    //printf("\n%d\n", is_prime(1522123123));
    phi = (P - 1) * (Q - 1);
    e = generate_e(phi);
    printf("e: %d", e);
    printf("\nd: %d\n", modInverse(e, phi));

    return 0;
}