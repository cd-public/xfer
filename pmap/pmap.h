#ifndef pmap_H
#define pmap_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct pmap_struct *pmap ;

pmap new_pmap(size_t x, size_t y) ;
void desc_pmap(pmap c) ;
void free_pmap(pmap p) ;
void pmap_to_ppm(pmap p) ;
void set_colr(pmap p, size_t x, size_t y, size_t c, uint8_t v) ;
uint8_t get_colr(pmap p, size_t x, size_t y, size_t c) ;

#endif
