//RSA.c

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
//use stdint.h here to get uint32_t
#include <stdint.h>
#include <stdbool.h>
// Macros
#define PRIME_LEN 3
#define RAND_SEED 451


//Functions:

// I don't trust sqrt
uint32_t square_root(uint32_t n)
{
	uint32_t root = 0;
	while (((root + 1) * (root + 1)) <= n)
	{
		root++;
	}
	return root;
}

// I like to pruint32_t bools
char *btos(bool b)
{
	if (b)
	{
		return "true";
	}
	return "false";
}

//returns 1 if it is prime, returns 0 if it is not
bool isPrime(uint32_t n)
{
    if (n == 1)
    {
        return 0;
    }
    uint32_t root = square_root(n);
    for (uint32_t d = 2; d <= root; d++)
    {
        if (n % d == 0)
        {
            return false;
        }
    }
    return true;
}

// write tests along the way, this could be main
uint32_t prime_test()
{
	for (uint32_t i = 2 ; i <= 100 ; i++ )
	{
		printf("%d is prime: %s\n",i, btos(isPrime(i)));
	}
	return 0;
}

//returns the number that happens to be prime
// INVARIANT: RUN ONLY AFTER SRAND
uint32_t getPrime(){
    uint32_t i = rand() % (16 << (PRIME_LEN * 3)); // 8 ~= 10
    while (isPrime(++i)) { }
    return i;
}

uint32_t *getPrimes(uint32_t seed){
	uint32_t *ret = (uint32_t *)malloc(2 * sizeof(uint32_t));
	ret[0], ret[1] = getPrime(), getPrime();
	return ret;
}

// write tests along the way, this could be main
uint32_t getter_test()
{
    uint32_t *ps = getPrimes(RAND_SEED);
	printf("%d,%d\n",ps[0],ps[1]);
	return 0;
}

//I'm recursing
uint32_t gcd(uint32_t a, uint32_t b)
{
	if (!a)
	{
		return b;
	}
	return gcd(b%a,a);
}

// write tests along the way, this could be main
uint32_t gcd_test() // g4g rip
{
    uint32_t a = 10, b = 15;
    printf("GCD(%d, %d) = %d\n", a, b, gcd(a, b));
    a = 35, b = 10;
    printf("GCD(%d, %d) = %d\n", a, b, gcd(a, b));
    a = 31, b = 2;
    printf("GCD(%d, %d) = %d\n", a, b, gcd(a, b));
    return 0;
}

uint32_t coprime(uint32_t x)
{
    uint32_t cand = 2;
    while (!(x % ++cand)) { }
    return cand;
}

uint32_t main()
{
	uint32_t a = 10, b = 15;
    printf("coprime(%d, %d) = %d, %d\n", a, b, coprime(a), coprime(b));
    a = 35, b = 10;
    printf("coprime(%d, %d) = %d, %d\n", a, b, coprime(a), coprime(b));
    a = 31, b = 2;
    printf("coprime(%d, %d) = %d, %d\n", a, b, coprime(a), coprime(b));
    return 0;
}

// This only works on strings of 4 or fewer characters
uint32_t string_to_int(char* s)
{
    uint32_t ret = 0, i = 0;
    while( s[i] )
    {
		end <<= 8;
        end += (uint32_t)s[i++];
    }
    return end;
}
