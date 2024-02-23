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
    pmap p = malloc(sizeof(struct pmap_struct)) ; size_t i ;
    p->x = x ; 
    p->y = y ;
    p->s = x * y * 3 * sizeof(uint8_t) ;
    p->pxls = malloc(p->s) ;
    return p ;
}

void desc_pmap(pmap p) { printf("pmap at loc %p of size x=%zu by y=%zu", p, p->x, p->y) ; return ; } // no \n
void free_pmap(pmap p) { free(p->pxls) ; free(p) ; return ; }

void pmap_to_ppm(pmap p) // if you want to decide the file name, add a char * argument
{
    FILE *f = fopen("imag.ppm", "w") ;
    fprintf(f, "P6\n%zu %zu\n255\n", p->x, p->y) ;
    fwrite(p->pxls, 1, p->s, f)) ;
    fclose(f) ;
}

// set color c at pixel x,y to value v
void set_colr(pmap p, size_t x, size_t y, size_t c, uint8_t v)
{
    p->pxls[3 * (y * p->x + x) + c] = v ;
    return ;
}

uint8_t get_colr(pmap p, size_t x, size_t y, size_t c)
{
    return p->pxls[3 * (y * p->x + x) + c] ;
}
