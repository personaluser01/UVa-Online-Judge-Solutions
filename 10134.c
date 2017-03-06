/*
 * 10134. Autofish
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define FG (ptr = fgets(buff,sizeof(buff),stdin))

char buff[0x400],*ptr;
int bait_units,ax;

int empty( char *ptr ) {
	for ( ;*ptr && *ptr != '\n'; ++ptr )
		if ( *ptr == 'l'||*ptr == 'b'||*ptr == 'f' )
			return 0;
	return 1;
}

int main() {
	int i,j,k,ts,fs,t,curtime,cnt,last_success,baits;
	char instr[0x400];
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d\n",&ts), FG; ts--; ) {
		last_success = -1;
		for ( cnt=curtime=t=fs=ax=bait_units=baits=0; FG && !empty(ptr); ++curtime ) {
			sscanf(buff,"%s",instr);
			if ( instr[0] == 'f' && ++cnt ) {
				if ( baits <= 1 ) {
					/*--cnt;*/
					goto lunch;
				}
				if ( ++fs == 1 ) {
					success:
						baits -= 2, ++ax, cnt = 0;
						last_success = curtime;
						continue ;
				}
				assert( fs > 1 );
				assert( last_success != -1 );
				if ( curtime-last_success >= 7 && cnt >= 3 )
					goto success;
			}
			else if ( instr[0] == 'b' ) {
				if ( baits == 6 )
					goto lunch;
				++baits;
			}
			else {
				assert( instr[0] == 'l' );
				lunch:;
			}
		}
		printf("%d\n",ax);
		if ( ts ) putchar('\n');
	}
	return 0;
}
