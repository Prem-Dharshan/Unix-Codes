#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

void *factorial(void *arg);
void *exponent(void *arg);

typedef struct {
    int base;
    int exp;
} t_args;

int fact = 1;
int power;

int main() {

    pthread_t t1, t2;

    int n;

    printf("Enter the n for factorial: ");
    scanf("%d", &n);

    t_args args;
    printf("Enter the base to calculate power: ");
    scanf("%d", &args.base);
    printf("Enter the exp to calculate power: ");
    scanf("%d", &args.exp);

    int t1_ret = pthread_create(&t1, NULL, factorial, (void *) &n);
    int t2_ret = pthread_create(&t2, NULL, exponent, (void *) &args);

    if (t1_ret != 0 || t2_ret != 0) {
        perror("Threads not created\n");
        exit(0);
    }

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("The factorial of %d is %d.\n", n, fact);
    printf("%d ^ %d = %d.\n", args.base, args.exp, power);

    return 0;
}

void *factorial(void *arg) {
    int *num = (int *)arg;
    int n = *num;
    while (n) {
        fact *= n;
        n--;
    }
    pthread_exit(0);
}


void *exponent(void *arg) {
    t_args *args = (t_args*)arg;
    t_args obj = *args;
    power = pow(obj.base, obj.exp);
    pthread_exit(0);
}