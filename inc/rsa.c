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

// memory leak here
uint64_t *getPrimes(uint64_t seed){
	uint64_t *ret = (uint64_t *)malloc(2 * sizeof(uint64_t));
	srand(seed);
	ret[0] = getPrime(), ret[1] = getPrime();
	return ret;
}

// write tests along the way, this could be main
// frees memory
uint64_t getter_test()
{
    uint64_t *ps, i = 5;
	while (i--) 
	{
		ps = getPrimes(RAND_SEED + i);
		printf("%lu,%lu\n",ps[0],ps[1]);
		free(ps);
	}
	return 0;
}

//I'm recursing
uint64_t gcd(uint64_t a, uint64_t b)
{
	return ((!a) ? b : gcd(b%a,a));
}

uint64_t lcm(uint64_t a, uint64_t b)
{
	return (a*b)/gcd(a,b);
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

// get d s.t. d * e = 1 mod lamb (d is the PRIVATE KEY EXPONENT)
// I essentially have no idea how to test this because I don't know math
uint64_t priv_key_exp(uint64_t e, uint64_t l)
{	
	int i = l + 1;
	for ( ; i % e ; i += l ) { }
	return i;
}

// Just return the private key, we'll slice it up if we need to
// memory leak here
uint64_t *make_key(uint64_t seed)
{
	srand(seed);
	uint64_t p = getPrime(), q = getPrime(), n, l, e, d, *ret = (uint64_t *)malloc(3 * sizeof(uint64_t));
	ret[0] = p * q, l = lcm(p-1,q-1);
	ret[1] = coprime(l);
	ret[2] = priv_key_exp(ret[1], l);
	return ret;
}


// fixes memory leaks
uint64_t priv_test() //main()
{
	uint64_t *ret = make_key(RAND_SEED);
	printf("priv=[%lu,%lu,%lu]\n",ret[0],ret[1],ret[2]);	
	free(ret);
	return 0;
}

// I can't be bothered to keep track of array lengths
// We'll stuff ciphertexts inside these structs
struct lenarr_struct {
    uint64_t len, *arr;
};
  
typedef struct lenarr_struct *lenarr;

// memory leak here
lenarr new_lenarr(uint64_t l, uint64_t *a)
{
	lenarr la = (lenarr)malloc(sizeof(lenarr)); // watch for memory leaks
	la->len = l;
	la->arr = a;
	return la;
}

// so we
// put 4 characters (32 bits) into the low bits of a uint64_t
// return an array of uint64_t
// we'll hash uint64_t's independently

// memory leak here
lenarr str_to_arr(char* s)
{
	int l = strlen(s), i;
	uint64_t *ret = (uint64_t *)malloc((l / 4) + 1 * sizeof(uint64_t));
    uint32_t *arr = s;
    for ( i = 0 ; i <= (l / 4) ; i++ )
    {
		ret[i] = arr[i];
    }
	//printf("s2a: l = %d, i = %d, ret[0] = %lu, arr[0] = %u, str[0] = %c\n", l, i, ret[0], arr[0], s[0]);
    return new_lenarr(i, ret);
}


// memory leak here
char *arr_to_str(lenarr la)
{
	int l = la->len, i;
	char *str = (char *)malloc(l * 4 * sizeof(char));
    uint32_t *arr = str;
    for ( i = 0 ; i < l ; i++)
    {
		arr[i] = (int32_t)la->arr[i];
    }
	// eliminate leading zeros
	for ( ; !str ; str++ ) { }
    return str;
}

// fixes memory leaks
uint64_t string_conversion_test() //main()
{
	char buf[8] = "hi";
	printf("buf[1] = %d\n", (int)buf[1]);
	printf("before: \"%s\"\n", buf);
	lenarr la = str_to_arr(buf);
	printf("lenarr length = %lu\nlenarr arr[1] = %lu\n", la->len, la->arr[1]);
	char *str = arr_to_str(la);
	printf("after:  \"%s\"\n", str);
	free(la->arr);
	free(la);
	free(str);
	return 0;	
}

// modular exponentiation by squares
// this is why we can cannot load array elements more than half full
// realistically probably all the key parts should be in 32's - I'll think on that.
uint64_t exp_fast(uint64_t x, uint64_t p, uint64_t m)
{
	uint64_t temp;
	x = x % m;
	if ( !p )
	{
		return 1;
	}
	if ( p == 1 )
	{
		return x;
	}
	temp = exp_fast((x * x) % m, p / 2, m); 
	return (p % 2) ? (x * temp) % m : temp % m ;
}

uint64_t exp_test()
{
	for (uint64_t i = 2 ; i <= 100 ; i++ )
	{
		printf("%lu ^ %lu = %lu \n", i, i, exp_fast(i, i, 0 - 1));
	}
	return 0;
}

// lets do this in place
// looking at this theres no way its right but, alas
void encrypt(lenarr x, uint64_t p, uint64_t m)
{
	for ( int i = 0 ; i < x->len ; i++ )
	{
		x->arr[i] = exp_fast(x->arr[i], p, m);
	}
	return;
}

// forked from string test
uint64_t main()//rsa_test() //main()
{
	char buf[8] = "hi";
	uint64_t *key = make_key(RAND_SEED), n, e, d;
	n = key[0], e = key[1], d = key[2]; // I hope
	printf("n=%lu,e=%lu,d=%lu\n", n, e, d);
	printf("buf[1] = %d\n", (int)buf[1]);
	printf("before: \"%s\"\n", buf);
	lenarr la = str_to_arr(buf);
	printf("cipher src len = %lu\n", la->len);
	printf("cipher src arr[0] = %lu\n", la->arr[0]);
	encrypt(la, e, n);
	printf("cipher enc arr[0] = %lu\n", la->arr[0]);
	encrypt(la, d, n);
	printf("cipher dec arr[0] = %lu\n", la->arr[0]);
	char *str = arr_to_str(la);
	printf("after:  \"%s\"\n", str);
	free(la->arr);
	free(la);
	free(str);
	return 0;
}
