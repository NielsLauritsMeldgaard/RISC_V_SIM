// A NEW CHANGE

#include <stdio.h>
#include "../inc/utils.h"
#include <stdbool.h>

bool is_prime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

void print_prime(int num) {
    if (is_prime(num)) {
        printf("%d is prime\n", num);
    } else {
        printf("%d is not prime\n", num);
    }
}

void secret_message() {
    int ascii_values[] = {65, 108, 98, 101, 114, 116, 32, 101, 114, 32, 103, 114, 105, 109};
    int length = sizeof(ascii_values) / sizeof(ascii_values[0]);

    printf("Secret Message: ");
    for (int i = 0; i < length; i++) {
        printf("%c", ascii_values[i]);
    }
    printf("\n");
}

int main() {
    print_prime(NUM);
    secret_message();
    while(1);
    return 0;
}
