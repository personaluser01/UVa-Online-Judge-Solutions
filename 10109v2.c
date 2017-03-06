/*
 *  * `Solving Systems of Linear Equations'
 *   */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tol 1e-7
#ifdef _MSC_VER
typedef __int64 i64;
typedef unsigned __int64 u64;
#else
typedef long long i64;
typedef unsigned long long u64;
#endif
#define N 0x200

i64 Abs( i64 x )
{ return x < 0 ? -x : x; }

i64 gcd( i64 x, i64 y ) {
		   if ( x < 0 || y < 0 )
				         return gcd(Abs(x),Abs(y));
		      return !y ? x : gcd(y, x % y);
}

typedef struct {
		   i64 p,q;
}frac;

void reduce( frac *z ) {
		   i64 g = gcd(z->p,z->q);
		      z->p /= g, z->q /= g;
			     /*assert( g > 0 );*/
			     if ( z->p == 0 ) {
						       z->q = 1;
							         return ;   
									    }
				    if ( z->p < 0 && z->q < 0 )
							       z->p *= -1, z->q *= -1;
					   else if ( z->p > 0 && z->q < 0 )
							         z->p *= -1, z->q *= -1;
}

int n,m,ts,cs,id[N];
frac a[N][N],x[N];

int get_frac( frac *z ) {
		   char s[0x100],sign = 1,i = 0;
		      if ( EOF == scanf("%s",s) )
					        return 0;
			     if ( s[i] == '-' )
						       ++i, sign = -1;   
				    z->p = 0, z->q = 1;
					   while ( isdigit(s[i]) )   
							         z->p = 10*z->p + s[i++]-'0';
					      if ( s[i] == '/' ) {
								        if ( s[++i] == '-' )
												         sign *= -1;
										      else --i;   
											        for ( z->q = 0; isdigit(s[++i]); )
															         z->q = 10*z->q + s[i]-'0';
													   }
						     z->p *= sign;
							    reduce(z);
								   return 1;
}

int cmp( frac *a, frac *b ) {
		   double A = ((double)a->p)/a->q,
				           B = ((double)b->p)/b->q;
		      if ( fabs(A-B) < tol )
					        return 0;
			     return A < B ? -1 : 1;
}

int get_pivot( int k, int *row, int *col ) {
		   int i,j;
		      frac w,ww;

			     w.p = 0LL, w.q = 1LL;
				    for ( i = k; i < m; ++i )
							      for ( j = k; j < n; ++j ) {
										           ww = a[i][j];
												            ww.p = Abs(ww.p), ww.q = Abs(ww.q);
															         if ( cmp(&ww,&w) > 0 ) {
																			             w = ww, *row = i, *col = j;
																						             return 1;
																									          }
																	       }
					   return 0;
}

void swap_rows( int r1,int r2 ) {
		   int j;
		      frac tmp;

			     for ( j = 0; j <= n; ++j )
						       tmp = a[r1][j], a[r1][j] = a[r2][j], a[r2][j] = tmp;
}

void swap_cols( int c1, int c2 ) {
		   int i,k;
		      frac tmp;

			     for ( i = 0; i < m; ++i )
						       tmp = a[i][c1], a[i][c1] = a[i][c2], a[i][c2] = tmp;
				    k = id[c1], id[c1] = id[c2], id[c2] = k;
}

void add( frac *z, frac *x, frac *y ) {
		   i64 a = x->p,
			         b = x->q,
					       p = y->p,
						         q = y->q,
								       g = gcd(b,q),
									         qq = q/g,
											       bb = b/g,
												         u = a*qq + p*bb,
														       v = qq*bb*g;
		      g = gcd(u,v);
			     z->p = u/g, z->q = v/g;
				    reduce(z);
}

void negate( frac *x ) {
		   x->p *= -1;
}

void sub( frac *z, frac *x, frac *y ) {
		   negate(y), add(z,x,y), negate(y);
}

void mult( frac *z, frac *x, frac *y ) {
		   i64 g1 = gcd(x->p,y->q),
			         g2 = gcd(x->q,y->p),
					       aa = x->p/g1,
						         bb = x->q/g2,
								       pp = y->p/g2,
									         qq = y->q/g1,
											       u = aa*pp,
												         v = bb*qq,
														       g = gcd(u,v);
		      z->p = u/g, z->q = v/g;
			     reduce(z);
}

void rev( frac *z ) {
		   i64 t;
		      t = z->p, z->p = z->q, z->q = t;
}

void ddiv( frac *z, frac *x, frac *y ) {
		   rev(y), mult(z,x,y), rev(y);
}

frac *mmult( frac *x, frac *y ) {
		   frac *z = (frac *)malloc(sizeof *z);

		      i64 g1 = gcd(x->p,y->q),
				        g2 = gcd(x->q,y->p),
						      aa = x->p/g1,
							        bb = x->q/g2,
									      pp = y->p/g2,
										        qq = y->q/g1,
												      u = aa*pp,
													        v = bb*qq,
															      g = gcd(u,v);
			     z->p = u/g, z->q = v/g;
				    reduce(z);
					   return z;
}

int main() {
		   int i,j,k,
			         row,col;
		      frac cf,s;
#ifndef ONLINE_JUDGE
			     freopen("input.txt","r",stdin);
#endif
				    while ( 1 == scanf("%d",&ts) && ts != 0 ) {
							      if ( ++cs > 1 ) putchar('\n');
								        scanf("%d %d",&n,&m);
										      for ( i = 0; i < m; ++i )
													           for ( j = 0; j <= n; ++j )
																	               assert( get_frac(&a[i][id[j] = j]) );

											        printf("Solution for Matrix System # %d\n",ts);

													      
													      if ( m <= n ) {
																           for ( k = 0; k < m; ++k ) {
																				               if ( !get_pivot(k,&row,&col) ) {
																									                  for ( i = k; i < m; ++i )
																															                    if ( Abs(a[i][n].p) != 0 ) {
																																						                     puts("No Solution.");
																																											                      goto next;
																																																                    }
																													                 printf("Infinitely many solutions containing %d arbitrary constants.\n",n-k);
																																	                goto next;
																																					            }
																							               swap_rows(k,row),swap_cols(k,col);
																										               assert( a[k][k].p != 0 );
																													               for ( i = k+1; i < m; ++i )
																																		                  if ( Abs(a[i][k].p) ) {
																																								                    ddiv(&cf,&a[i][k],&a[k][k]);
																																													                  for ( j = k; j <= n; ++j )
																																																			                       sub(&a[i][j],&a[i][j],mmult(&cf,&a[k][j]));
																																																	                    assert( a[i][k].p == 0 );
																																																						               }
																																            }
																		            if ( m < n ) {
																							            printf("Infinitely many solutions containing %d arbitrary constants.\n",n-m);
																										            goto next;
																													         }
																					         assert( m == n );
sol:
																							          ddiv(&x[id[n-1]],&a[n-1][n],&a[n-1][n-1]);
																									           for ( i = n-2; i >= 0; --i ) {
																													               s.p = 0, s.q = 1;
																																               for ( j = i+1; j < n; ++j )
																																					                  add(&s,&s,mmult(&a[i][j],&x[id[j]]));
																																			               s.p *= -1;
																																						               add(&s,&a[i][n],&s);
																																									               assert( Abs(a[i][i].p) );
																																												               ddiv(&x[id[i]],&s,&a[i][i]);
																																															            }
																											            for ( i = 0; i < n; ++i ) {
																																            reduce(&x[i]);
																																			            if ( x[i].q != 1 ) {
																																								               if ( x[i].p == 0 )
																																													                     printf("x[%d] = %lld\n",i+1,0);
																																											                  else
																																																	                    printf("x[%d] = %lld/%lld\n",i+1,x[i].p,x[i].q);
																																															              }
																																						            else printf("x[%d] = %lld\n",i+1,x[i].p);
																																									         }
																														         goto next;
																																       }
														        else {
																		         for ( k = 0; k < n; ++k ) {
																						             if ( !get_pivot(k,&row,&col) ) {
																											                for ( i = k; i < m; ++i )
																																	                  if ( a[i][n].p != 0 ) {
																																							                       puts("No Solution.");
																																												                        goto next;
																																																		                  }
																															               printf("Infinitely many solutions containing %d arbitrary constants.\n",n-k);
																																		                  goto next;
																																						              }
																									             swap_rows(k,row),swap_cols(k,col);
																												             assert( a[k][k].p != 0 );
																															             for ( i = k+1; i < m; ++i )
																																				                if ( Abs(a[i][k].p) ) {
																																										                  ddiv(&cf,&a[i][k],&a[k][k]);
																																														                    for ( j = k; j <= n; ++j )
																																																					                     sub(&a[i][j],&a[i][j],mmult(&cf,&a[k][j]));
																																																			                  assert( a[i][k].p == 0 );
																																																							                 }
																																		          }
																				          for( i = k; i < m; ++i )
																								              if ( a[i][n].p != 0 ) {
																													                 puts("No Solution.");
																																	                goto next;
																																					            }
																						           goto sol;
																								         }
next:;
	    }
					   return 0;
} 
