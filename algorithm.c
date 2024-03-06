#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i <= sqrt(num); ++i) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int generate_prime() {
    int num;
    while (1) {
        num = rand() % 900 + 100;
        if (is_prime(num)) return num;
    }
}

int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mod_inverse(int a, int m) {
    for (int x = 1; x < m; ++x) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

void generate_keypair(int *public_key, int *private_key) {
    int p = generate_prime();
    int q = generate_prime();
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = rand() % (phi - 2) + 2;
    while (gcd(e, phi) != 1) {
        e = rand() % (phi - 2) + 2;
    }
    int d = mod_inverse(e, phi);
    public_key[0] = e;
    public_key[1] = n;
    private_key[0] = d;
    private_key[1] = n;
}

int encrypt(int message, int *public_key) {
    int e = public_key[0];
    int n = public_key[1];
    long long result = 1;
    for (int i = 0; i < e; ++i) {
        result = (result * message) % n;
    }
    return (int)result;
}

int decrypt(int encrypted_message, int *private_key) {
    int d = private_key[0];
    int n = private_key[1];
    long long result = 1;
    for (int i = 0; i < d; ++i) {
        result = (result * encrypted_message) % n;
    }
    return (int)result;
}

int main() {
    srand(time(NULL));
    int public_key[2], private_key[2];
    generate_keypair(public_key, private_key);
    char input_message[100];
    printf("Enter a message for encryption: ");
    fgets(input_message, sizeof(input_message), stdin);
    input_message[strcspn(input_message, "\n")] = '\0';
    int numeric_message[strlen(input_message)];
    for (int i = 0; i < strlen(input_message); ++i) {
        numeric_message[i] = (int)input_message[i];
    }
    int encrypted_message[strlen(input_message)];
    for (int i = 0; i < strlen(input_message); ++i) {
        encrypted_message[i] = encrypt(numeric_message[i], public_key);
    }

    printf("Encrypted message: ");
    for (int i = 0; i < strlen(input_message); ++i) {
        printf("%d ", encrypted_message[i]);
    }
    printf("\n");

    int decrypted_message[strlen(input_message)];
    for (int i = 0; i < strlen(input_message); ++i) {
        decrypted_message[i] = decrypt(encrypted_message[i], private_key);
    }

    printf("Decrypted message: ");
    for (int i = 0; i < strlen(input_message); ++i) {
        printf("%c", (char)decrypted_message[i]);
    }
    printf("\n");

    return 0;
}