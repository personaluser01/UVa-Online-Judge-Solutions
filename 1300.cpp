/*
 * 1300. Parallel Expectations
 * TOPIC: dp, Bayes Theorem, very tricky, good DP problem, probability, expectations
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <map>
#include <cmath>
using namespace std;
typedef long long i64;
#define MAXVAR 0x10
#include <vector>
enum { MOV = 0, ADD = 1, SUB = 2 };
#define MAXS BIT(SH*MAXP)
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define SH 7
#define MAXLEN BIT(SH)
#define MAXP 2
#define enc(x,y) ((x)|((y)<<SH))
#define oo 0xfffffffful
typedef unsigned int state;
typedef int var;
#define MAXC 0x80
#define Q (BIT(MAXP*SH))

long double tp[Q],prob[Q];
map<string,var> str2var;
int L[MAXP], len[MAXP], command[MAXP][MAXLEN],n, seen[Q], yes, visited[Q];
long double F[MAXLEN*MAXP];
long double const _log2 = log(2.00), tol = 1e-9;
state FINAL_STATE, INITIAL_STATE = 0;
long double average_of[MAXC+MAXVAR][Q];
var dst[MAXP][MAXLEN], src[MAXP][MAXLEN], R[MAXP][2], constant[MAXC];
string name[MAXC+MAXVAR];

int get_step( state s, int t ) { return (s>>(SH*t))&MASK(SH); }

state get_prev( state s, int t ) {
	// assert( t < MAXP );
	int k = get_step(s,t)-1;
	if ( k < 0 ) return +oo;
	state ps = ((~(MASK(SH)<<(t*SH)))&s)|(k<<(SH*t));
	// assert( get_step(ps,t) == k );
	return ps;
}

long double get_tp( state s ) {
	int k[] = {s&MASK(SH), s>>SH};
	if ( s == FINAL_STATE )
		return tp[s] = 0.00;
	if ( k[0] < L[0] && k[1] < L[1] )
		return tp[s] = 0.5;
	assert( k[0] == L[0] || k[1] == L[1] );
	return tp[s] = 1.00;
}

var find_var( string s ) {
	if ( str2var.find(s) != str2var.end() )
		return str2var[s];
	name[n] = s;
	return str2var[s] = n++;
}

long double calc_prob( state s ) {
	if ( visited[s] == yes )
		return prob[s];
	visited[s] = yes;
	int k[2] = {s&MASK(SH),s>>SH}, m = k[0]+k[1];
	if ( s == FINAL_STATE ) 
		return prob[s] = 1.00;
	if ( s == INITIAL_STATE )
		return prob[s] = 1.00;
	prob[s] = 0;
	for ( int t = 0; t < MAXP; ++t ) {
		state ps = get_prev(s,t);
		if ( ps < +oo )
			prob[s] += get_tp(ps)*calc_prob(ps);
	}
	return prob[s];
}

void init() {
	n = 0, str2var.clear(), ++yes;
}

void display_state( state s ) {
	printf("%llu %u\n",s&MASK(SH),s>>SH);
}

void calc_state( state s ) {
	if ( seen[s] == yes )
		return ;
	seen[s] = yes;
	if ( s == INITIAL_STATE ) {
		for ( var x = MAXC; x < n; ++x )
			average_of[x][s] = 0.00;
		return ;
	}
	long double sum = 0.00;
	for ( int k,t = 0; t < MAXP; ++t ) {
		state ps;
		if ( (ps = get_prev(s,t)) == +oo ) continue ;
		calc_state(ps);
		long double ps2s = get_tp(ps);
		k = get_step(s,t);
		// assert( get_step(ps,t) == k-1 );
		var dest = dst[t][k], source = src[t][k];
		long double pi = min((long double)1.00,ps2s*(calc_prob(ps)/calc_prob(s)));
		//assert( 0 <= pi && pi <= 1.00 );
		switch ( command[t][k] ) {
			case MOV: average_of[dest][s] += average_of[source][ps]*ps2s;
					  break ;
			case ADD: average_of[dest][s] += (average_of[dest][ps]+average_of[source][ps])*ps2s;
					  break ;
			case SUB: average_of[dest][s] += (average_of[dest][ps]-average_of[source][ps])*ps2s;
					  break ;
		}
		for ( var x = MAXC; x < n; ++x )
			if ( x != dest ) 
				//average_of[x][s] += average_of[x][ps]*pi;
				average_of[x][s] += average_of[x][ps]*ps2s;
		sum += pi;
	}
	// assert( fabs(sum-1.00) < tol );
}

char buff[0x400],*ptr;

int is_empty_line( char *s ) {
	while ( *s && *s != '\n' )
		if ( *s++ != ' ') return 0;
	return 1;
}

void read_program( int t ) {
	char x[0x20], y[0x20], z[0x20], op[0x20], ass[0x20], ch, *qtr;
	var i,j,k;
	for ( L[t] = len[t] = 0; ptr = fgets(buff,sizeof buff,stdin); L[t] = len[t] ) {
		if ( 0 == strncmp(ptr,"END",3) ) break ;
		if ( is_empty_line(ptr) ) continue ;
		while ( *ptr == ' ' ) ++ptr;
		for ( qtr = x, *qtr++ = *ptr; isalnum(*++ptr); *qtr++ = *ptr );
		*qtr = '\0';
		while ( *ptr == ' ' ) ++ptr;
		++ptr, ++ptr;
		while ( *ptr == ' ' ) ++ptr;
		for ( qtr = y, *qtr++ = *ptr; isalnum(*++ptr); *qtr++ = *ptr );
		*qtr = '\0';
		while ( *ptr == ' ' ) ++ptr;
		0[op] = *ptr++, op[1] = '\0';
		while ( *ptr == ' ' ) ++ptr;
		for ( qtr = z, *qtr++ = *ptr; *++ptr && *ptr != '\n' && isalnum(*ptr); *qtr++ = *ptr );
		*qtr = '\0';
		// printf("%s := %s %s %s\n",x,y,op,z);

		// assert( 0 == strcmp(":=",ass) );
		// assert( 0[op] == '+' || 0[op] == '-' );
		for ( int l = 0; x[l]; ++l )
			if ( isupper(x[l]) ) x[l] = tolower(x[l]);
		for ( int l = 0; y[l]; ++l )
			if ( isupper(y[l]) ) y[l] = tolower(y[l]);
		for ( int l = 0; z[l]; ++l )
			if ( isupper(z[l]) ) z[l] = tolower(z[l]);
		i = isdigit(0[x])?constant[atol(x)]:find_var(string(x));
		j = isdigit(0[y])?constant[atoi(y)]:find_var(string(y));
		k = isdigit(0[z])?constant[atoi(z)]:find_var(string(z));
		command[t][++len[t]] = MOV, dst[t][len[t]] = R[t][0], src[t][len[t]] = j;
		command[t][++len[t]] = MOV, dst[t][len[t]] = R[t][1], src[t][len[t]] = k;
		command[t][++len[t]] = 0[op]=='-'?SUB:ADD, dst[t][len[t]] = R[t][0], src[t][len[t]] = R[t][1];
		command[t][++len[t]] = MOV, dst[t][len[t]] = i, src[t][len[t]] = R[t][0];
	}
}

string rgstr[MAXP][2] = {"R1@1", "R2@1", "R1@2", "R2@2"};

int main() {
	int i,j,k,t,ts,id[0x400];
	state s;
#ifndef ONLINE_JUDGE
	freopen("p1300.in","r",stdin);
#endif
	for ( k = 1; k < MAXLEN*MAXP; F[k] = F[k-1]+log(k), ++k );
	for ( scanf("%d\n",&ts); ts--; ) {
		for ( init(), i = 0; i < MAXC; constant[i++] = n++ );
		for ( t = 0; t < MAXP; ++t ) 
			for ( i = 0; i < 2; ++i )
				R[t][i] = find_var(rgstr[t][i]);
		for ( t = 0; t < MAXP; read_program(t++) );
		FINAL_STATE = enc(L[0],L[1]);
		for ( i = 0; i <= L[0]; ++i )
			for ( j = 0; j <= L[1]; ++j )
				for ( s = enc(i,j), k = 0; k < n; ++k )
					if ( k < MAXC ) 
						average_of[k][s] = k*calc_prob(s);
					else average_of[k][s] = 0.00;
		calc_state(FINAL_STATE);
		for ( i = MAXC+2*MAXP; i < n; ++i ) id[i] = i;
		for ( j = 1; j; )
			for ( j = 0, i = MAXC+2*MAXP; i < n-1; ++i )
				if ( strcmp(name[id[i]].c_str(),name[id[i+1]].c_str()) > 0 ) 
					swap(id[i],id[i+1]), ++j;
		for ( i = MAXC+2*MAXP; i < n; ++i )
			printf("%.4Lf\n",average_of[id[i]][FINAL_STATE]);
		putchar('\n');
	}
	return 0;
}

