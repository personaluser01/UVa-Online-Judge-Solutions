/*
 * status: Accepted
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400

int n,cs,cnt[N],id[256],v[N];
char s[N],buff[N],*ptr;

int main() {
	int i,j,k;
	while ( ptr = fgets(buff,sizeof(buff),stdin) ) {
		if ( cs++ ) putchar('\n');
		memset(cnt,0,sizeof(cnt));
		for (;*ptr && *ptr != '\n'; ++cnt[*ptr++] );
		for ( n = 0, i = 0; i < 256; ++i )
			if ( cnt[i] && (v[n++] = i) );
		for (j=1;j;)
			for ( i = j = 0; i < n-1; ++i )
				if ( cnt[v[i]] > cnt[v[i+1]] || (cnt[v[i]] == cnt[v[i+1]] && v[i] < v[i+1]) )
					++j, k = v[i], v[i] = v[i+1], v[i+1] = k;
		for ( i = 0; i < n; ++i )
			printf("%d %d\n",v[i],cnt[v[i]]);
	}
	return 0;
}
