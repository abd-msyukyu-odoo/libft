void quick_sort(int tab[], int s, int e)
{
    int     es = s;
    int     ee = s;
    int     sg = e;
    int     p = tab[s];
    int     tmp;

    while (ee < sg)
    {
        if (tab[ee] < p)
        {
            tmp = tab[ee];
            tab[ee] = tab[es];
            tab[es] = tmp;
            ++es;
            ++ee;
        }
        else if (tab[ee] == p)
            ++ee;
        else
        {
            --sg;
            tmp = tab[ee];
            tab[ee] = tab[sg];
            tab[sg] = tmp;
        }
    }
    if (s < es - 1)
        quick_sort(tab, s, es);
    if (sg < e - 1)
        quick_sort(tab, sg, e);
}

#include <stdio.h>
int     main(void)
{
    int d[] = {9,5,2,6,8,3,1,7,7};
    quick_sort(d, 0, 9);
    int i = -1;
    while (++i < 9)
    {
        printf("%d ", d[i]);
    }
    printf("\n");
    return (0);
}
