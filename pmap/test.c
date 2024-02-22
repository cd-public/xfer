#include <stdio.h>
#include <stdlib.h>
#include "pmap.h"

int main() 
{
    pmap p = new_pmap(255, 255) ;
    desc_pmap(p) ; putchar('\n') ;
    size_t i, j ;
    for ( i = 0 ; i < 255 ; i++ )
    {
        for ( j = 0 ; j < 255 ; j++ )
        {
            if ( j > i ) 
            { 
                set_colr(p, i, j, 2, j) ;
                set_colr(p, i, j, 1, i) ;
                set_colr(p, i, j, 0, 255 - i) ;

            } else {
                set_colr(p, i, j, 2, i) ;
                set_colr(p, i, j, 1, j) ;
                set_colr(p, i, j, 0, i) ;
            }
        }
    }
    pmap_to_ppm(p) ;
    free_pmap(p) ;
    return 0 ;
}
