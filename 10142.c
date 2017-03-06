/*
 * 10142. Australian Voting
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x20
#define M 0x400

int ts,n,m,vote[M][N],elim[N],yes,lst[N],len,dead;
char names[N][0x80],buff[1 << 16];

int read_contents() {
	int i,cnt=0,k;
	for(i=0;i<n&&1==sscanf(buff+cnt,"%d%n",vote[m]+i,&k);cnt+=k,--vote[m][i++]);
	if(i>=n)++m;
	return i>=n;
}

int Round() {
	int i,j,k,
		cnt[N] = {0}; 
	for ( i = 0; i < m; ++i ) {
		for ( j = 0; j < n; ++j )
			if ( elim[vote[i][j]] != yes ) {
				++cnt[vote[i][j]];
				goto nx;
			}
		assert( 0 );
		nx: ;
	}
	for ( i = 0; i < n; ++i )
		if ( elim[i] != yes && cnt[i]*2 > m )
			return i;
	for ( i = 0, k = (1<<29); i < n; ++i )
		if ( elim[i] != yes && cnt[i] < k )
			k = cnt[i];
	for ( len = 0, i = 0; i < n; ++i )
		if ( elim[i] != yes && cnt[i] == k )
			++dead, elim[lst[len++] = i] = yes;
	return -1;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d\n",&n) && ++yes; ) {
		for ( m = i = 0; i < n; fgets(names[i],sizeof(names[i]),stdin), ++i );
		for (;fgets(buff,sizeof(buff),stdin)&&read_contents(buff););
		for ( dead = 0;-1==(i=Round())&&dead<n;);
		if ( dead == n ) {
			for ( i = 0; i < len-1; ++i )
				printf("%s",names[lst[i]]);
			printf("%s",names[lst[i]]);
		}
		else 
			printf("%s",names[i]);
		if ( ts ) putchar('\n');
	}
	return 0;
}
