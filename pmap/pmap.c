#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "pmap.h"

struct pmap_struct 
{
    size_t x ;
    size_t y ;
    size_t s ;
    uint8_t *pxls ;
} ;

pmap new_pmap(size_t x, size_t y) 
{
    pmap p = (pmap)malloc(sizeof(struct pmap_struct)) ; size_t i ;
    if ( NULL == p ) { (void)fprintf(stderr, "pmap.c: new_pmap: struct malloc failed. exiting...\n") ; exit(1) ; }
    p->x = x ; 
    p->y = y ;
    p->s = x * y * 3 * sizeof(uint8_t) ;
    p->pxls = (uint8_t *)malloc(p->s) ;
    if ( NULL == p ) { (void)fprintf(stderr, "pmap.c: new_pmap: internal malloc failed. exiting...\n") ; exit(1) ; }
    for ( i = 0 ; i < p->s ; i++ ) { p->pxls[i] = 0 ; }
    return p ;
}

void desc_pmap(pmap p) { printf("pmap at loc %p of size x=%zu by y=%zu", p, p->x, p->y) ; return ; } // no \n
void free_pmap(pmap p) { free(p->pxls) ; free(p) ; return ; }

void pmap_to_ppm(pmap p) // if you want to decide the file name, add a char * argument
{
    FILE *f = fopen("imag.ppm", "w") ;
    if (NULL == f) { (void)fprintf(stderr, "pmap.c: pmap_to_ppm: fopen failed. exiting...\n") ; exit(1) ; }
    (void)fprintf(f, "P6\n%zu %zu\n255\n", p->x, p->y) ;
    if (p->s != fwrite(p->pxls, 1, p->s, f)) { (void)fprintf(stderr, "pmap.c: pmap_to_ppm: fwrite failed. exiting...\n") ; exit(1) ; }
    if (fclose(f)) { (void)fprintf(stderr, "pmap.c: pmap_to_ppm: fclose failed. exiting...\n") ; exit(1) ; }
}

// set color c at pixel x,y to value v
void set_colr(pmap p, size_t x, size_t y, size_t c, uint8_t v)
{
    if (x >= p->x || y >= p->y) { (void)fprintf(stderr, "pmap.c: set_pixl: out of bounds. exiting...\n") ; exit(1) ; }
    p->pxls[3 * (y * p->x + x) + c] = v ;
    return ;
}

uint8_t get_colr(pmap p, size_t x, size_t y, size_t c)
{
    if (x >= p->x || y >= p->y) { (void)fprintf(stderr, "pmap.c: get_pixl: out of bounds. exiting...\n") ; exit(1) ; }
    return p->pxls[3 * (y * p->x + x) + c] ;
}
