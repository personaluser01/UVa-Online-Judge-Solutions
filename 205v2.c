/*
 * 205. Getting There
 * TOPIC: dp, dijkstra
 * status:
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x20
#define M 0x40
#define A 26
#define oo (1<<29)
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define tol 1e-12
#define DAY (24*60)
#define Q (1<<20)
#define enc(p,t) ((p)|((t)<<5))
typedef unsigned int state;

typedef struct cell {
	struct cell *son[A];
	int idx;
} cell;

cell pool[N*A],*ptr = pool;
char buff[0x400],name[N][0x20],T[DAY+1][0x10];
int m,n,adj[N][M],deg[N],cnt,pos[Q],inq[Q],yes;
state heap[Q<<1];
unsigned int p[Q];

cell *init() {
	cell *x = ptr++;
	int i;
	for ( x->idx = -1, i = 0; i < A; x->son[i++] = NULL );
	return x;
}

int push( cell *root, char *s ) {
	cell *x,*y;
	char *p = s;
	for ( x = root; x && *s; x=x->son[*s++-'a'] )
		if ( !x->son[*s-'a'] )
			x->son[*s-'a'] = init();
	if ( x->idx >= 0 ) return x->idx;
	deg[n] = 0, strcpy(name[n],p), name[n][0] = toupper(name[n][0]);
	return x->idx = n++;
}

int find( cell *root, char *s ) {
	cell *x,*y;
	char *p = s;
	for ( x = root; x && *s; x=x->son[*s++-'a'] )
		if ( !x->son[*s-'a'] ) return -1;
	if ( *s ) return -1;
	if ( x->idx >= 0 ) return x->idx;
	return -1;
}

typedef struct {
	int x,y,price,
		st,duration;
	char leave[0x10],arrive[0x10], pr[0x10];
} edge;

edge e[M];

typedef struct { int t,cost; } distance;

int cmp_by_time( const distance *a, const distance *b ) {
	if ( a->t == b->t ) 
		return a->cost-b->cost;
	return a->t-b->t;
}

int cmp_by_cost( const distance *a, const distance *b ) {
	if ( a->cost == b->cost ) 
		return a->t-b->t;
	return a->cost-b->cost;
}

typedef int (*func)( const distance*, const distance* );
func cmp[] = {cmp_by_time,cmp_by_cost};

distance d[Q];

void heap_push( state x, const int tt ) {
	int i,j;
	if ( inq[x] != yes )
		pos[heap[cnt]=x] = cnt, ++cnt, inq[x] = yes;
	for ( j = pos[x]; j && cmp[tt](d+heap[i=(j-1)>>1],d+heap[j]) > 0; bubble, j = i );
}

state pop( const int tt ) {
	int i,j;
	state x=*heap;
	if ( cnt+=(pos[x]=-1) )
		pos[*heap=heap[cnt]] = 0;
	for ( inq[x]=0, j=0; (i=j,j<<=1,++j)<cnt; bubble ) {
		if ( j<cnt-1 && cmp[tt](d+heap[j+1],d+heap[j]) < 0 ) ++j;
		if ( cmp[tt](d+heap[i],d+heap[j]) <= 0 ) break ;
	}
	return x;
}

void reg( state *b, state u, int dst, int tt ) {
	if ( (u&31UL) != dst ) return ;
	if ( *b == -1 || cmp[tt](d+*b,d+u) > 0 )
		*b = u;
}

state dijkstra( int src, int dst, const int tt ) {
	int x,y,i,j,k,l,t,o,curtime,ncurtime;
	state u,v,best=-1;
	distance ad;

	for ( ++yes, cnt = 0, i = 0; i < deg[src]; ++i ) {
		k=adj[src][i], u = enc(src,e[k].st);
		d[u].cost = d[u].t = 0, heap_push(u,tt), p[u] = -1;
	}
	for (;cnt;)
		for(u=pop(tt),x=(u&31UL),reg(&best,u,dst,tt), curtime=(u>>5),i=0;i<deg[x]&&x!=dst&&d[u].cost<=100000;++i) {
			y=e[k=adj[x][i]].y, t=e[k].st, o=curtime%DAY;
			if ( o <= t ) 
				ad.t = d[u].t+(t-o)+e[k].duration, ncurtime = curtime+(t-o)+e[k].duration;
			else 
				l = o-t, ad.t = d[u].t+(DAY-l)+e[k].duration, ncurtime = curtime+(DAY-l)+e[k].duration;
			ad.cost = d[u].cost+e[k].price, v = enc(y,ncurtime);
			if ( ncurtime >= 11*DAY || ad.cost >= 100000 ) continue ;
			if ( inq[v] != yes ) d[v].t = d[v].cost = +oo;
			if ( cmp[tt](&ad,d+v) < 0 )
				d[v] = ad, heap_push(v,tt), p[v] = (k|(u<<6));
		}
	return best;
}

void dump( state u ) {
	int i = (p[u]&63UL);
	state v = (p[u]>>6);
	char tmp[0x10];
	if ( p[u] == -1 ) return ;
	dump(v);
	sprintf(tmp,"$%.2lf",e[i].price/100.00+tol);
	printf("%-20s%-23s%-8s%-8s%7s\n",name[e[i].x],name[e[i].y],T[e[i].st],T[(e[i].st+e[i].duration)%DAY],tmp);
}

int main() {
	int i,j,k,l,t,travelid,p0,p1,sh,sm,th,tm,ts=0,cs,days,rem;
	char tmp[0x200],aa[0x20],bb[0x20],tmps[0x20],tmpt[0x20],SH[0x20],TH[0x20],price[0x20];
	state u;
	cell *root;
#ifndef ONLINE_JUDGE
	freopen("205.in","r",stdin);
#endif
	for ( i = 0; i <= 23; ++i )
		for ( j = 0; j <= 59; ++j ) 
			sprintf(T[k=i*60+j],"%d:%02d%c",i%12,j,i>=12?'P':'A');
	for (;fgets(buff,sizeof buff,stdin) && 2==sscanf(buff,"%s %d",tmp,&travelid);) {
		if ( ++ts > 1 ) puts("\n");
		for ( n=0, m=0, ptr=pool, root=init(); fgets(buff,sizeof buff,stdin) &&\
			5==sscanf(buff,"%s %s %s %s %s",aa,bb,SH,TH,price); adj[i][deg[i]++] = m++ ) {
			sscanf(SH,"%d:%d%s",&sh,&sm,tmps);
			sscanf(TH,"%d:%d%s",&th,&tm,tmpt);
			sscanf(price,"%d.%d",&p0,&p1);
			for ( i=0; aa[i]; aa[i]=tolower(aa[i]), ++i );
			for ( i=0; bb[i]; bb[i]=tolower(bb[i]), ++i );
			e[m].x = i = push(root,aa), e[m].y = j = push(root,bb);
			if ( toupper(0[tmps]) == 'A' && sh == 12 ) sh = 0;
			if ( toupper(0[tmpt]) == 'A' && th == 12 ) th = 0;
			e[m].st = sh*60+sm+(toupper(0[tmps])=='A'?0:DAY/2);
			k = th*60+tm+(toupper(0[tmpt])=='A'?0:DAY/2);
			e[m].duration = k>=e[m].st?k-e[m].st:DAY-e[m].st+k;
			e[m].price = p0*100+p1;
			strcpy(e[m].leave,SH);
			strcpy(e[m].arrive,TH);
			e[m].pr[0]='$',strcpy(e[m].pr+1,price);
		}
		printf("Requests and optimal routes for travel %d\n------------------------------------------\n\n",travelid);
		for ( cs = 0; fgets(buff,sizeof buff,stdin) && 3==sscanf(buff,"%s %s %s",aa,bb,tmp); ) {
			if ( ++cs > 1 ) putchar('\n');
			for ( i=0; aa[i]; aa[i]=tolower(aa[i]), ++i );
			for ( i=0; bb[i]; bb[i]=tolower(bb[i]), ++i );
			i = find(root,aa), j = find(root,bb);
			0[aa] = toupper(0[aa]), 0[bb] = toupper(0[bb]);
			if ( 0 == strcmp(aa,bb) ) {
				printf("You are already in %s.\n",aa);
				continue ;
			}
			if ( i == -1 || j == -1 ) {
				printf("There is no route from %s to %s.\n",aa,bb);
				continue ;
			}
			for ( 0[tmp] = toupper(0[tmp]), k = 1; tmp[k]; tmp[k] = tolower(tmp[k]), ++k );
			switch ( tolower(0[tmp]) ) {
					case 'c': u = dijkstra(i,j,1); break ;
					case 't': u = dijkstra(i,j,0); break ;
					default: assert(0);
			}
			if ( i == j ) {
				printf("You are already in %s.\n",name[i]);
				continue ;
			}
			if ( u == -1 ) {
				printf("There is no route from %s to %s.\n",name[i],name[j]);
				continue ;
			}
		  printf("%-4s: %-17s%6s: %-17s%12s: %s\n","From",aa,"To",bb,"Optimize",tmp);
			puts("==================================================================");
			puts("From                To                     Leave   Arrive     Cost");
			puts("==================================================================");
			dump(u), puts("                                           -----------------------");
			days = d[u].t/DAY, rem = d[u].t%DAY;
			if ( days == 1 )
				sprintf(tmp,"1 day %d:%02d",rem/60,rem%60);
			else if ( days >= 2 )
				sprintf(tmp,"%d days %d:%02d",days,rem/60,rem%60);
			else sprintf(tmp,"%d:%02d",rem/60,rem%60);
			printf("%57s",tmp), sprintf(tmp,"$%.2lf",d[u].cost/100.00+tol),
			printf("%9s\n",tmp);
		}
	}
	return 0;
}


