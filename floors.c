#include<stdio.h>
#include<string.h>
#include <assert.h>
#include<stdlib.h>

#define MIN(A,B) (((A)<(B))?(A):(B))
#define MAX(A,B) (((A)>(B))?(A):(B))

char el[128][128];
int access[128], fifo[128];
int elx[128], ely[128];
int f, e, a, b;

unsigned int Nsd(unsigned int a, unsigned int b)
{
  unsigned long int aa = MIN(a, b), bb = MAX(a, b);
  if (aa == 0) return bb;
  else return Nsd(aa, bb%aa);
}

int Stops(int el, int fl) /* stavi vytah el v patre fl ? */
{
  return ((fl >= ely[el]) && ((fl - ely[el])%elx[el] == 0));
}

int Connected(int e1, int e2) /* existuje patro, ve kterem stavi vytahy e1 a e2? */
{
  int nsd, period, max, diff, k1, k2, base, i;
  nsd = Nsd(elx[e1], elx[e2]);
  period = elx[e1]*elx[e2]/nsd;
  max = MAX(ely[e1], ely[e2]);
  diff = max - MIN(ely[e1], ely[e2]);
  if (diff%nsd) return 0;
  if ((f - max) >= period) return 1;
  k1 = (elx[e1] > elx[e2])?e1:e2;
  k2 = (elx[e1] > elx[e2])?e2:e1;
  base = elx[k1]*((max - ely[k1] + elx[k1] - 1)/elx[k1]) + ely[k1];
  for (i = 0; i < elx[k2]/nsd; ++i)
  {
    if (base + elx[k1]*i >= f) return 0;
    if (Stops(k2, base + elx[k1]*i)) return 1;
  }
printf("#######################\n");
  return 0; /* sem by se to nikdy nemelo dostat */
}

int GetElev(int fl) /* vrati index vytahu, ktery stavi v patre fl; pokud takovi vytah neexistuje, vrati -1 */
{
  int i;
  for (i = 0; i < e; ++i)
    if (Stops(i, fl)) return i;
  return -1;
}

void Generalize(void) /* zavedeni tranzitivity na prestup mezi vytahy */
{
  int i, j, k, first, last;
  memset(access, 0, sizeof(access));
  for (i = k = 0; i < e; ++i)
    if (access[i] == 0)
    {
      access[i] = ++k;
      fifo[first = 0] = i;
      last = 1;
      while (last > first)
      {
        for (j = 0; j < e; ++j)
          if ((access[j] == 0) && el[fifo[first]][j])
          {
            access[j] = k;
            fifo[last++] = j;
          }
        ++first;
      }
    }
}

int main(void)
{
  int n, i, j;
  scanf("%d", &n);
  while (n--)
  {
    memset(el, 0, sizeof(el));
    scanf("%d%d%d%d", &f, &e, &a, &b);
    for (i = 0; i < e; ++i)
    {
      scanf("%d%d", elx + i, ely + i);
      el[i][i] = 1;
      for (j = 0; j < i; ++j)
        if ((a != b) && Connected(i, j))
          el[i][j] = el[j][i] = 1;
    }
    if (a != b)
    {
      i = GetElev(a);
      j = GetElev(b);
      if (i != j) Generalize();
    }
    else i = j = 0;
    if ((i >= 0) && (j >= 0) && (access[i] == access[j]))
      printf("It is possible to move the furniture.\n");
    else
      printf("The furniture cannot be moved.\n");
  }
  return 0;
}
