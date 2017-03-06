/*
 * 1064. Network
 * TOPIC:
 * status:
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 8, M = 0x400, oo = (1<<29), Q = 4*N;
	int m,n,cs,ans,mask;
	int []sz = new int[N], mess = new int[M], left = new int[M], right = new int[M], c = new int[N];
	Scanner scan = new Scanner(System.in);
	public static void main( String []args ) throws Exception { new Main().go(); }
	class Packet {
		int id,i,j;
		Packet( int id, int i, int j ) { this.id = id; this.i = i; this.j = j; }
		Packet merge( Packet other ) { return new Packet(this.id,this.i,other.j); }
	}
	int f() {
		int i,j,k,head,tail,cnt,cursize = 0,w = -1,cur_block,I,J;
		int []last = new int[N];
		List<Packet> a = new ArrayList<Packet>();
		Iterator<Packet> ii,jj,it;
		Packet t=null,p=null,xx=null,yy=null,zz=null;
		boolean up,ok,flag;
		//for ( int l = 0; l < n; ++l, w = Math.max(w,cursize) ) {
			//i = c[l];
			cur_block = 0;
			for ( int ll = 0; ll < m; w = Math.max(w,cursize), ++ll ) {
				//if ( mess[ll] != i ) continue ;
				i = mess[ll];
				if ( i == c[cur_block] && last[i]+1 == left[ll] ) {
					last[i] = right[ll];
					for ( ok = false, it = a.iterator(); it.hasNext() && !ok; ) {
						p = it.next();
						if ( p.id == i ) {
							if ( p.i == last[i]+1 ) {
								t = p;
								ok = true;
							}
						}
					}
					if ( ok ) {
						a.remove(t); cursize -= (t.j-t.i+1); last[i] = t.j;
						if ( last[i] == sz[i] ) {
							++cur_block;
							for ( flag = true; flag; ) {
								for ( flag = false, it = a.iterator(); it.hasNext() && !flag; ) {
									p = it.next();
									if ( p.id != c[cur_block] ) continue ;
									if ( p.i == 1 && p.j == sz[p.id] ) {
										t = p; flag = true ;
									}
								}
								if ( flag ) { a.remove(t); cursize -= (t.j-t.i+1);  ++cur_block; }
							}
						}
					}
					continue ;
				}
				it = a.iterator(); p = null; t = null;
				for ( flag = false; it.hasNext()&&!flag;) {
					p = it.next();
					if ( p.id != i ) continue ;
					if ( p.j+1 == left[ll] ) {
						t = p.merge(new Packet(i,left[ll],right[ll]));
						flag = true;
					}
					else if ( right[ll]+1 == p.i ) {
						t = new Packet(i,left[ll],right[ll]).merge(p);
						flag = true;
					}
				}
				if ( flag ) { 
					a.remove(p); a.add(t);
					cursize -= (p.j-p.i+1);
					cursize += (t.j-t.i+1);
					for (up = true; up;) {
						for ( up = false, ii = a.iterator(); ii.hasNext() && !up; ) {
							Packet ia = ii.next();
							for ( jj = a.iterator(); jj.hasNext() && !up; ) {
								Packet ja = jj.next();
								if ( ia.j+1 == ja.i ) {
									up = true;
									xx = ia; yy = ja;
									break ;
								}	
							}
						}	
						if ( up ) {
							a.remove(xx); a.remove(yy);
							cursize -= (xx.j-xx.i+1);
							cursize -= (yy.j-yy.i+1);
							a.add(zz=xx.merge(yy));
							cursize+=(zz.j-zz.i+1);
						}
					}
				}
				else { a.add(zz=new Packet(i,left[ll],right[ll])); cursize+=(zz.j-zz.i+1); }
				for ( flag = true; flag; ) {
					for ( flag = false, it = a.iterator(); it.hasNext() && !flag; ) {
						p = it.next();
						if ( p.id!=c[cur_block] ) continue ;
						if ( p.i == 1 && p.j == sz[p.id] ) {
							t = p; flag = true ;
						}
					}
					if ( flag ) { a.remove(t); cursize -= (t.j-t.i+1); ++cur_block; }
				}
			}
		//}
		return w;
	}
	int L( int k ) { return ((k) & ((~(k))+1)); }
	int B( int k ) { return (1<<k); }
	int who( int u ) { return which[L(u)]; }
	int []which = new int[1<<N];
	void rec( int k ) {
		int i,u;
		if ( k == n ) {
			for ( i = 0; i < n; ++i )
				System.out.print(c[i]+" ");
			u = f();
			System.out.println(": "+u);
			ans = Math.min(ans,u);
			return ;
		}
		for(u=((~mask)&((1<<n)-1));u>0&&(i=who(u))>=0;mask|=B(i),c[k]=i,rec(k+1),mask&=~B(i),u&=~L(u));
	}
	int g() {
		ans = +oo; mask = 0; rec(0);
		return ans;
	}
	void go() throws Exception {
		int i,j,k;
		for ( i = 0; i < N; which[B(i)] = i, ++i );
		while ( true ) {
			n = scan.nextInt();
			m = scan.nextInt();
			if ( m == 0 && n == 0 ) break ;
			for ( i = 0; i < n; ++i )
				sz[i] = scan.nextInt();
			for ( i = 0; i < m; ++i ) {
				mess[i] = scan.nextInt()-1;
				left[i] = scan.nextInt();
				right[i] = scan.nextInt();
			}
			System.out.println("Case "+(++cs)+": "+g()+"\n");
		}
	}
};

