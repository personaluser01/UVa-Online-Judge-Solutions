/*
 * 848. fmt
 * TOPIC: simulation, hard
 * status: Accepted
 */
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LEN 72
#define N (ch = getchar())
#define OUT(i,j) (tmp=buff[(j)],buff[(j)]='\0',puts(buff+(i)),buff[(j)]=tmp)
#define no_spaces_so_far (i>j)
enum { WORD, SPACE, NEWLINE, END_OF_FILE };
#include <vector>
using namespace std;

char buff[LEN+8],ch;

typedef struct {
	char *w;
	int len;
	char tp;
} word;

vector<word> v;

word *next_word() {
	char a[0x400];
	int i,j,k;
	word *r = (word *)malloc(sizeof *r);

	if ( ch == EOF ) {
		r->w=NULL, r->tp = END_OF_FILE;
		return r;
	}
	if ( ch == '\n' ) {
		r->w = (char *)malloc(2*sizeof *(r->w));
		r->w[0] = ch, r->w[1] = '\0', r->len = 1, r->tp = NEWLINE, N;
		return r;
	}
	if ( ch == ' ' ) {
		for ( k = 0, a[k++] = ch; N == a[k-1]; a[k++] = ch );
		r->w = (char *)malloc((k+1)*sizeof *(r->w));
		for ( i = 0; i < k; ++i )
			r->w[i] = a[i];
		r->w[i] = '\0', r->len = k, r->tp = SPACE;
		return r;
	}
	for(k=0,a[k++]=ch;N != ' ' && ch != EOF && ch != '\n';a[k++]=ch);
	r->w = (char *)malloc((k+1)*sizeof *(r->w));
	for ( i = 0; i < k; ++i )
		r->w[i] = a[i];
	r->w[i] = '\0', r->len = k, r->tp = WORD;
	return r;
}

int main() {
	int i,j,k,l,t,st;
	word r;
	N;
	do { v.push_back(r=*next_word()); } while ( r.tp!=END_OF_FILE );
	for ( t = 0, st = 0, j = -1, i = 0; i < (int)v.size(); ) {
		r = v[i];
		if ( r.tp == WORD ) {
			if ( t+r.len <= LEN ) {
				t += r.len;
				if ( st > j )
					st = j = i++;
				else j = i++;
				continue ;
			}
			assert( t+r.len > LEN );
			for ( l = st; l <= j; ++l )
				printf("%s",v[l].w);
			putchar('\n');
			t = r.len, st = j = i++;
			continue ;
		}
		if ( r.tp == SPACE ) {
			if ( !i || i > 0 && v[i-1].tp == NEWLINE ) {
				for ( l = 0; l < LEN && l < r.len; ++l )
					putchar(' ');
				t += l, ++i;
				continue ;
			}
			if ( t+r.len <= LEN ) {
				t += r.len, ++i;
				continue ;
			}
			assert( t+r.len > LEN );
			for ( l = st; l <= j; ++l )
				printf("%s",v[l].w);
			putchar('\n');
			t = 0, st = 0, j = -1, ++i;
			continue ;
		}
		if ( r.tp == NEWLINE ) {
			if ( t+r.len > LEN ) {
				for ( l = st; l <= j; ++l )
					printf("%s",v[l].w);
				putchar('\n');
				t = 0, st = 0, j = -1, ++i;
				continue ;
			}
			if ( !(st>j || !t || (i+1<(int)v.size()&&(v[i+1].tp==SPACE||v[i+1].tp==NEWLINE))) ) {
				v[i].w[0] = ' ', v[i].tp = SPACE;
				continue ;
			}
			for ( l = st; l <= j; ++l )
				printf("%s",v[l].w);
			printf("%s",r.w);
			t = 0, 0, st = 0, j = -1, ++i;
			continue ;
		}
		for ( l = st; l <= j; ++l )
			printf("%s",v[l].w);
		putchar('\n');
		break ;
	}
    return 0;
}

