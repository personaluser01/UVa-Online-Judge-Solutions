#include <stdio.h>
#include <stdlib.h>
unsigned r = 123456; int T = 20, a[65536], i, n;
int R(unsigned m) { r = r * 1812433253 + 1; return (r >> 4) % m; }
int C(const void *p, const void *q) { return (*(int *)q - *(int *)p); }
int main() {
		  for(printf("%d\n",T);T--;) {
				      for(printf("%d\n",n=1+R(50000)),i=n;i--;)a[i]=R(2000000)-1000000;
					      qsort(a,n,sizeof(a[0]),&C);
						      while(n--)printf("%s%d.%.3d%c",(a[n]<0)?"-":"",abs(a[n]/1000),abs(a[n])%1000,n?' ':'\n');
							    }
		    return 0;
}
