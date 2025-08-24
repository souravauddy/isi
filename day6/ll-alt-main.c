#include "linked_lists.h"
#include <assert.h>

#define debug(x) printf("%s = %d\n", #x, x)

int main(int ac, char *av[])
{
    int n, i;
    DATA d;
    LIST l;

    if (ac < 2)
        ERR_MESG("Usage: linked-list n1 n2 n3 ...");

    n = ac-1;
    init_list(&l, n);

    for (i = 1; i <= n; i++) {
        d = atoi(av[i]);

        if (-1 == insert(&l, i-1, d))
            fprintf(stderr, "Inserting %d at index %d failed\n", d, i-1);
        else
            fprintf(stderr, "Inserted %d at index %d successfully\n", d, i-1);
        
        // dump_table(&l);
    }

    print_list(&l);

    free_list(&l);
    return 0;
}
