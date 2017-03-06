/*
 * KEYWORDS: minimum diameter spanning tree, r-b tree, balanced bst, pareto optimality
 * AUTHOR: Serikzhan Kazi
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#define tol 1e-9
enum { L, R };
enum { Red, Black };
#define color(x) ((x)->c)
#define flip(x) ((x)->c^=1)
#define set_color(x,C) ((x)->c=(C))
#define which(x) ((x)->p->son[L]==x?L:R)
#define N 0x400
#define oo 0xfffffffful
#define INF (DBL_MAX-0x400)
#define pi (2*acos(0.00))

int are_adj[N][N],weight[N][N];
typedef struct { double a,b; int idx; } tpair;
double Pi;

int cmp( tpair *p, tpair *q ) {
	if ( fabs(p->a-q->a) < tol ) {
		if ( fabs(p->b-q->b) < tol )
			return 0;
		if ( p->b > q->b )
			return -1;
		return 1;
	}
	if ( p->a < q->a )
		return -1;
	return 1;
}

typedef struct cell {
	struct cell *son[2],*p;
	tpair e;
	char c;
	int freq;
} cell;

cell *NIL;

typedef struct {
	cell *root;
	size_t cnt;
} tree;

cell *init( cell *p ) {
	cell *x = (cell *)malloc(sizeof *x);
	if ( !x ) assert( 0 );
	set_color(x,Red), x->p = p, x->son[L] = x->son[R] = NIL, x->freq = 1;
	return x;
}

tree *init_rb() {
	tree *t = (tree *)malloc(sizeof *t);
	if ( !t ) assert( 0 );
	t->root = NIL, t->cnt = 0;
	return t;
}

void rotate( tree *t, cell *x, const int i ) {
	cell *y;
	assert( x != NIL );
	assert( (y = x->son[i^1]) != NIL );
	if ( (x->son[i^1] = y->son[i]) != NIL )
		y->son[i]->p = x;
	if ( (y->p = x->p) == NIL )
		t->root = y;
	else x->p->son[which(x)] = y;
	x->p = y, y->son[i] = x;
}

void push( tree *t, tpair e ) {
	cell **hold,*x,*y,*g,*w;
	int i;

	for ( x = *(hold = &t->root), y = NIL; ; ) {
		if ( x == NIL ) {
			x = *hold = init(y), x->e = e, ++t->cnt;
			break ;
		}
		if ( (i = cmp(&x->e,&e)) == 0 ) {
           ++x->freq, ++t->cnt;
           return ;
        }
		i = (i<0?R:L);
		y = *hold, hold = &x->son[i], x = x->son[i];
	}
	while ( x != t->root && color(x->p) == Red ) {
        assert( x != NIL && color(x) == Red );
		g = x->p->p, i = which(x->p), y = g->son[i^1];
		if ( color(y) == Red ) {
			flip(x->p), flip(y), flip(g), x = g;
			continue ;
		}
		if ( which(x) == (i^1) )
			x = x->p, rotate(t,x,i);
		flip(x->p), flip(g), rotate(t,g,i^1);
	}
	set_color(t->root,Black);
}

void fixup( tree *t, cell *x ) {
	cell *y;
	int i;
	while ( x != t->root && color(x) == Black ) {
		i = which(x), y = x->p->son[i^1];
		if ( color(y) == Red ) {
			flip(x->p), flip(y), rotate(t,x->p,i);
			continue ;
		}
		if ( color(y->son[i]) == Black && color(y->son[i^1]) == Black ) {
			flip(y), x = x->p;
			continue ;
		}
		if ( color(y->son[i]) == Red && color(y->son[i^1]) == Black ) {
			flip(y->son[i]), flip(y), rotate(t,y,i^1);
			continue ;
		}
		flip(y->son[i^1]), set_color(y,color(x->p)), set_color(x->p,Black);
	   	rotate(t,x->p,i), x = t->root;
	}
	set_color(x,Black);
}

void erase( tree *t, cell *z ) {
	cell *x,*y;
	assert( z && z != NIL );
	assert( t->cnt >= z->freq );
	t->cnt -= z->freq;
	if ( (y=z->son[R]!=NIL?z->son[R]:z) != z ) {
		for ( ;y->son[L] != NIL; y = y->son[L] );
		assert( y != NIL );
		z->e = y->e, z->freq = y->freq;
	}
	(x=y->son[R]==NIL?y->son[L]:y->son[R]);
	(x->p=y->p)==NIL?(t->root=x):(y->p->son[which(y)]=x);
	if ( color(y) == Black ) fixup(t,x);
}

cell *pred( tree *t, cell *x ) {
	cell *y;
	if ( (y = x->son[L]) == NIL )
       for ( y = x->p; y != NIL && which(x) == L; x = y, y = y->p );
    else
       for ( ;y->son[R] != NIL; y = y->son[R] );
    return y;
}

cell *succ( tree *t, cell *x ) {
     cell *y;
     if ( (y = x->son[R]) == NIL )
        for ( y = x->p; y != NIL && which(x) == R; x = y, y = y->p );
     else
        for ( ;y->son[L] != NIL; y = y->son[L] );
     return y;
}

cell *find( tree *t, tpair e ) {
   cell *x;
   int i;
   for ( x = t->root; x != NIL && (i = cmp(&x->e,&e)); x = x->son[i<0?R:L] );
   return x;
}

int dominates( tpair *p, tpair *q ) {
    if ( p->a >= q->a && p->b > q->b )
       return 1;
    if ( p->a > q->a && p->b >= q->b )
       return 1;
    return 0;
}

double min( double x, double y ) { return x<y?x:y; }
double max( double x, double y ) { return x<y?y:x; }

int adj[N][N],deg[N],n,m,uu,vv,r[2][N*N];
unsigned int d[N][N];
double tau,min_w;
tree *T;
tpair to_delete[1 << 20],*ptr;

#define G( u, v, z, e ) (((e) + (double)d[v][z] - (double)d[u][z])/(2.00*(e)))

void update( tree *t, tpair h ) {
  cell *x,*y;
  x = find(T,h);
  if ( (y = pred(T,x)) != NIL && dominates(&y->e,&x->e) ) {
    erase(t,x);
    return ;
  }
  if ( (y = succ(T,x)) != NIL && dominates(&y->e,&x->e) ) {
    erase(t,x);
    return ;
  }
  for ( x = find(T,h), ptr = to_delete, y = pred(T,x); y != NIL && dominates(&x->e,&y->e); *++ptr = y->e, y = pred(T,y) );
  for ( ;ptr > to_delete; erase(T,find(T,*ptr--)) );
  for ( x = find(T,h), ptr = to_delete, y = succ(T,x); y != NIL && dominates(&x->e,&y->e); *++ptr = y->e, y = succ(T,y) );
  for ( ;ptr > to_delete; erase(T,find(T,*ptr--)) );
}

typedef struct {
  double t;
  int z;
} coord;

int cmp01( const void *a, const void *b ) {
  coord *x = (coord *)a,
        *y = (coord *)b;
  if ( fabs(x->t-y->t) < tol ) {
     if ( x->z == y->z )
        return 0;
	 if ( x->z < y->z )
		return -1;
	 return 1;
  }
  assert( fabs(x->t-y->t) >= tol );
  if ( x->t < y->t )
     return -1;
  if ( x->t > y->t )
     return 1;
}

double find_t( int u, int v, double *LV ) {
    int i,j,k,z,zz,o[N],*qtr,K;
    coord pr[N];
    cell *x;
    double A,B,t,s,tt,ss,e=weight[u][v],alpha=Pi-2*atan(e),t_star,level,TAN,SIN,CO,SI;
   	/* double phi=3*atan(e)-Pi, */
   	double phi=atan(e),prev_t,
		   M = cos(alpha/2) + sin(alpha/2)*tan(phi);
    tpair h;
	NIL = (cell *)malloc(sizeof *NIL), NIL->p = NIL->son[L] = NIL->son[R] = NIL, set_color(NIL,Black);
	TAN = tan(alpha), SIN = sin(alpha), CO = cos(phi), SI = sin(phi);
	for ( T = init_rb(), z = 0; z < n; ++z ) {
      t = G(u,v,z,e);
      s = t*e+d[u][z];
	  tt = t*sin(phi+alpha)/sin(alpha) - s*cos(phi+alpha)/sin(alpha);
	  ss = -t*sin(phi)/sin(alpha) + s*cos(phi)/sin(alpha);
      /*A = t-s/TAN, B = s/SIN;
      tt = A*CO - B*SI;
      ss = A*SI + B*CO;
	  */
      h.a = tt, h.b = ss, h.idx = z, push(T,h), update(T,h);
    }
    for ( x = T->root; x != NIL && x->son[L] != NIL; x = x->son[L] );
    assert( x != NIL );
    for ( qtr = o, k = T->cnt; k > 0; *++qtr = x->e.idx, k -= x->freq, x = succ(T,x) );
    assert( k == 0 );
    for ( K = 0; qtr > o; pr[K].t = G(u,v,*qtr,e), pr[K++].z = *qtr-- );
    qsort( pr, K, sizeof *pr, cmp01 );
    for ( i = 0; i < K; ++i ) {
      z = pr[i].z, t = pr[i].t;
      if ( i == 0 ) {
		tt = 0;
        level = min(tt*e+d[u][z],(1-tt)*e+d[v][z]);
		t_star = tt, prev_t = t;
        continue ;
      }
	  assert( prev_t <= t );
      zz = pr[i-1].z;
      tt = (((double)d[v][zz]-(double)d[u][z])+e)/(2.00*e);
	  tt = min(tt,1), tt = max(tt,0);
      if ( min(tt*e+d[u][z],(1-tt)*e+d[v][z]) < level ) {
        level = min(tt*e+d[u][z],(1-tt)*e+d[v][z]);
        t_star = tt;
      }
	  prev_t = t;
    }
	tt = 1, z = pr[--i].z;
    if ( min(tt*e+d[u][z],(1-tt)*e+d[v][z]) < level ) {
        level = min(tt*e+d[u][z],(1-tt)*e+d[v][z]);
        t_star = tt;
    }
	*LV = level;
    return t_star;
}

void abs_centre() {
     int i,j,k,l;
     double t,w,e,LV;
     for ( min_w = +INF, k = 0; k < m; ++k ) {
         i = r[0][k], j = r[1][k];
         t = find_t(i,j,&LV), e = weight[i][j];
         assert( 0 <= t && t <= 1 );
         for ( w = -INF, l = 0; l < n; ++l )
             w = max(w,min(t*e+d[i][l],(1-t)*e+d[j][l]));
		 // assert( fabs(w-LV) < tol );
         if ( w < min_w ) {
            min_w = w;
            uu = i, vv = j, tau = t;
         }
     }
}

double get_ans() {
  double w = -INF,e = weight[uu][vv];
  int i,j,k;
  for ( i = 0; i < n; ++i )
      for ( j = i+1; j < n; ++j ) {
          w = max(w,min(tau*e+d[uu][i],(1-tau)*e+d[vv][i])+min(tau*e+d[uu][j],(1-tau)*e+d[vv][j]));
          w = max(w,min(tau*e+d[uu][j],(1-tau)*e+d[vv][j])+min(tau*e+d[uu][i],(1-tau)*e+d[vv][i]));
	  }
  return w;
}

int main() {
	int i,j,k,l,cs = 0,ts,ii,num_edges;
	tpair tt;
	cell *x,*y;
	for ( Pi = pi, scanf("%d",&ts); ts--;) {
		memset(are_adj,0,sizeof are_adj);
		memset(deg,0,sizeof deg);
		for ( scanf("%d %d",&n,&num_edges); num_edges-- && 3 == scanf("%d %d %d",&i,&j,&k); ) {
			are_adj[i][j] = are_adj[j][i] = 1;
			weight[i][j] = weight[j][i] = k;
		}
		/*
		for ( scanf("%d",&n), memset(deg,0,sizeof deg), k = 0, ii = 0; ii < n; ++ii ) {
            assert( 2 == scanf("%d %d",&i,&l) );
			for ( --i; l-- && 1 == scanf("%d",&j); ++k ) {
				--j, are_adj[i][j] = are_adj[j][i] = 1;
			}
        }
		*/
		for ( m = 0, i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j )
				if ( are_adj[i][j] ) {
					r[0][m] = i, r[1][m++] = j;
					adj[i][deg[i]++] = j, adj[j][deg[j]++] = i;
				}
        memset(d,0xff,sizeof d);
        for ( i = 0; i < n; ++i )
			for ( k = 0; k < deg[i]; d[i][adj[i][k]] = weight[i][adj[i][k]], ++k );
        for ( i = 0; i < n; d[i][i] = 0, ++i );
        for ( k = 0; k < n; ++k )
            for ( i = 0; i < n; ++i )
                for ( j = 0; j < n; ++j )
                    if ( d[i][k] < +oo && d[k][j] < +oo && d[i][j] > d[i][k]+d[k][j] )
                       d[i][j] = d[i][k]+d[k][j];
        for ( i = 0; i < n; ++i )
            for ( j = 0; j < n; ++j ) {
                if ( d[i][j] == +oo )
                   printf("These %d %d\n",i,j);
                assert( d[i][j] < +oo );
            }
		if ( n == 1 ) {
			puts("0");
			continue ;
		}
        abs_centre();
        /*printf("%d %d %.4lf %.4lf\n",uu,vv,tau,min_w);*/
        printf("%.lf\n",get_ans()+tol);
    }
	return 0;
}

