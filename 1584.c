/*
 * 1584. Circular Sequence
 * TOPIC: duval, chen-fox-lyndon
 * status: Accepted
 */
 #include <assert.h>
 #include <stdio.h>
 #include <ctype.h>
 #include <stdlib.h>
 #include <string.h>
 #define N 0x400
 #define enc(x,y) ((x)|((y)<<8))

 char s[N];
 int n;
 unsigned int *ptr,o[N];

 int CFL( char *a, int n, int shift ) {
   int i = 0, j = 1;
   if ( n <= 0 ) return 1;
   for ( ;j < n; )
     if ( a[i] == a[j] )
       ++i, ++j;
     else if ( a[i] < a[j] )
          i = 0, ++j;
     else {
       *ptr++ = enc(shift,shift+j-i-1);
       return CFL(a+j-i,n-j+i,j-i+shift);
     }
   *ptr++ = enc(shift,shift+j-i-1);
   return CFL(a+j-i,i,j-i+shift);
 }

 int main() {
   int i,j,k,ts;
   #ifndef ONLINE_JUDGE
   freopen("input.txt","r",stdin);
   #endif
   for ( scanf("%d",&ts); ts-- && 1 == scanf("%s",s); ) {
     for( n = strlen(s), i = n; i < n+n; ++i ) s[i] = s[i-n];
     for ( i = 0; i < n+n; ++i )
         s[i] = toupper(s[i]);
     ptr = o, CFL(s, n<<=1, 0);
     for ( i = 0; i < ptr-o; ++i ) {
       j = (o[i]&255), k = (o[i]>>8);
       if ( k-j+1 == (n>>1) ) {
         break ;
       }
     }
     for ( ;j <= k; putchar(s[j++]) );
     putchar('\n');
   }
   return 0;
 }
