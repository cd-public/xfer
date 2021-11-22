//RSA.c

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
//use stdint.h here to get uint64_t
#include <stdint.h>
#include <stdbool.h>
// Macros
#define PRIME_LEN 3
#define RAND_SEED 451


//Functions:

// I don't trust sqrt
uint64_t square_root(uint64_t n)
{
	uint64_t root = 0;
	while ((++root * root) <= n) { }
	return root;
}

// I like to print bools
char *btos(bool b)
{
	char *strs[2] = {"true", "false"};
	return strs[!b];
}

//returns 1 if it is prime, returns 0 if it is not
bool isPrime(uint64_t n)
{
    uint64_t r = square_root(n), d = 2;
    while ( n % d && d <= r ) { d++; }
    return d > r;
}

// write tests along the way, this could be main
uint64_t prime_test()
{
	for (uint64_t i = 2 ; i <= 100 ; i++ )
	{
		printf("%lu is prime: %s\n",	i, btos(isPrime(i)));
	}
	return 0;
}

//returns the number that happens to be prime
// INVARIANT: RUN ONLY AFTER SRAND
uint64_t getPrime(){
    uint64_t i = rand() % (16 << (PRIME_LEN * 3)); // 8 ~= 10
    while (!isPrime(++i)) { }
    return i;
}

uint64_t *getPrimes(uint64_t seed){
	uint64_t *ret = (uint64_t *)malloc(2 * sizeof(uint64_t));
	srand(seed);
	ret[0] = getPrime(), ret[1] = getPrime();
	return ret;
}

// write tests along the way, this could be main
uint64_t getter_test()
{
    uint64_t *ps = getPrimes(RAND_SEED), i = 5;
	while (i--) 
	{
		printf("%lu,%lu\n",ps[0],ps[1]);
		ps = getPrimes(ps[0]);
	}
	return 0;
}

//I'm recursing
uint64_t gcd(uint64_t a, uint64_t b)
{
	return ((!a) ? b : gcd(b%a,a));
}

// write tests along the way, this could be main
uint64_t gcd_test() // g4g rip
{
    uint64_t a = 10, b = 15;
    printf("GCD(%lu, %lu) = %lu\n", a, b, gcd(a, b));
    a = 35, b = 10;
    printf("GCD(%lu, %lu) = %lu\n", a, b, gcd(a, b));
    a = 31, b = 2;
    printf("GCD(%lu, %lu) = %lu\n", a, b, gcd(a, b));
    return 0;
}

uint64_t coprime(uint64_t x)
{
    uint64_t cand = 2;
    while (!(x % ++cand)) { }
    return cand;
}

uint64_t coprime_test()
{
	uint64_t a = 10, b = 15;
    printf("coprime(%lu, %lu) = %lu, %lu\n", a, b, coprime(a), coprime(b));
    a = 35, b = 10;
    printf("coprime(%lu, %lu) = %lu, %lu\n", a, b, coprime(a), coprime(b));
    a = 31, b = 2;
    printf("coprime(%lu, %lu) = %lu, %lu\n", a, b, coprime(a), coprime(b));
    return 0;
}

uint64_t main()
{
	return 0;
}

// so we
// put 4 characters (32 bits) into the low bits of a uint64_t
// return an array of uint64_t
// we'll hash uint64_t's independently
// need to decide how to handle length returns
uint64_t *string_to_int(char* s)
{
	int l = strlen(s) , i = 0;
	uint64_t *ret = (uint64_t *)malloc(l / 4 * sizeof(uint64_t));
    uint32_t *arr = (uint32_t *)s;
    while ( i++ < s / 4 )
    {
		ret[i] = (int64_t)arr[i];
    }
    return ret;
}

//Takes in an integer and returns a character array (string)
char *int_to_string(uint64_t *arr)
{
    static char word_array[10];
    uint64_t i = 0;
    while (integer > 0)
    {
        char letter = (char) integer % 256;
        printf("character:  %c\n", letter);
        word_array[i] = letter;
        integer = integer / 256;
        i++;
    }
    
    return word_array;
} 

//c = m^e mod n
uint64_t encrypt(uint64_t int_message, uint64_t coP, uint64_t n)
{
    uint64_t cipher; 
    double power;

    //power = pow((double)int_message, (double)coP);
    //cipher = fmod(power, (double)n);
    return cipher;
    
}


uint64_t decrypt(uint64_t cipher, uint64_t d, uint64_t n)
{
    uint64_t message;
    double power;

    //THIS POWER IS FUCKING IT ALL UP SOMEHOW
    //power = pow((double)cipher, (double)d);
    printf("Power1  %lf\n", power);

    //message = fmod(power, (double)n);
    return message;
}


uint64_t find_d(uint64_t coP, uint64_t totient)
{
    for (uint64_t i = 3; i <= totient; i++){
        if (coP * i % totient == 1){
            return i;
        }
    }
    return 0;
}


//Prints the final word after all the steps
void print_final(char* word)
{
    printf("###################\n");
    printf("PRINTING FINAL WORD:\n");
    for (uint64_t i = sizeof(word) / sizeof(char); i >= 0; i--){
            printf("%c", word[i]);
            word[i] = word[i];
        }
    printf("###################\n");
}



uint64_t old_main(){
    uint64_t p, q, n, totient, e, coP, k, d, c, m, greatest_common_div, cipher, int_word, decrypt_messsage;

    p = getPrime();
    q = 997;
    n = p * q;
    totient = (p - 1) * (q - 1);
    coP = coprime(totient);
    greatest_common_div = gcd(p-1, q-1);
    d = find_d(coP, totient);
    
    
    int_word = string_to_int("Paul");
    printf("int_word == %lu\n", int_word);


    cipher = encrypt(int_word, coP, n);
    printf("ENCRYPTED MESSAGE  ==  %lu\n", cipher);
    printf("\n");


    decrypt_messsage = decrypt(cipher, d, n);
    printf("DECRYPTED MESSAGE ==  %lu\n", decrypt_messsage);


    char* final = int_to_string(int_word);
    print_final(final);

}
