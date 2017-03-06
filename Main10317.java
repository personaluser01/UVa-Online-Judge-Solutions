/*
 * 10317. Equating Equations
 * TOPIC: 
 * status: WA 
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	Pattern p = Pattern.compile("(\\d+)");

	char []op;
	int m,n,pluses;
	int []x,z = new int[0x400], sum = new int[1<<21];

	static int []who = new int[1<<17];
	static int L( int k ) { return k & (~(k)+1); }
	static int BIT( int k ) { return (1<<k); }
	static char[]R = new char[0x200];
	static int MASK( int k ) { return BIT(k)-1; }
	static int []bts = new int[1<<21];

	public static void main( String ... args ) throws Exception {
		int i;
		for ( i = 0; i < 17; who[BIT(i)] = i, ++i );
		for ( i = 0; i < (1<<21); ++i )
			//bts[i] = bts[i>>1]+((i&1)==0?0:1);
			bts[i] = Integer.bitCount(i);
		R[R['+']='-']='+';
		new Main().go();
	}

	boolean oddEvenTest() {
		int parity = 0,i;
		for ( i = 0; i < n; ++i ) 
			parity += (Math.abs(x[i])%2);
		return (parity%2) == 0;
	}

	boolean f( int k, int s, int used ) throws Exception {
		int i,u;
		if ( k == n ) {
			if ( s == 0 ) {
				for ( bw.write(z[0]+""), i = 1; i < m; bw.write(" "+op[i]+" "), bw.write(z[i++]+"") );
				bw.write(" = ");
				for ( bw.write(z[i++]+""); i < n; bw.write(" "+R[op[i]]+" "), bw.write(z[i++]+"") );
				bw.write("\n");
				return true ;
			}
			return false ;
		}
		if ( s > sum[(~used)&MASK(n)] ) return false ;
		if ( s < -sum[(~used)&MASK(n)] ) return false ;
		for ( u = (~used)&MASK(n); u > 0; u &= ~L(u) ) {
			z[k] = x[i = who[L(u)]];
			if ( f(k+1,s+(op[k]=='+'?z[k]:-z[k]),used|BIT(i)) )
				return true ;
		}
		return false ;
	}

	boolean g() throws Exception {
		int u,v,i,s = 0,P = 0, M = 0,k,l;
		int []pl = new int[pluses], mn = new int[n-pluses];
		for ( u = 0; u < (1<<n); ++u ) 
			if ( bts[u] == pluses ) {
				s = P = M = 0;
				for ( i = 0; i < n; ++i )
					if ( ((u>>i)&1) == 1 ) {
						s += x[i];
						pl[P++] = x[i];
					}
					else {
						s -= x[i];
						mn[M++] = x[i];
					}
				if ( s == 0 ) {
					k = l = 0;
					for ( i = 0; i < m; ++i )
						if ( op[i] == '+' ) {
							if ( i == 0 ) {
								bw.write(pl[k++]+"");
								continue ;
							}
							bw.write(" + ");
							bw.write(pl[k++]+"");
						}
						else {
							if ( i == 0 ) v=1/0;
							bw.write(" - ");
							bw.write(mn[l++]+"");
						}
					assert op[i] == '-';
					bw.write(" = ");
					for (;i < n; ++i ) {
						if ( op[i] == '+' ) {
							if ( i == m ) v = 1/0;
							bw.write(" - ");
							bw.write(pl[k++]+"");
						}
						else {
							if ( i == m ) {
								bw.write(mn[l++]+"");
								continue ;
							}
							bw.write(" + ");
							bw.write(mn[l++]+"");
						}
					}
					bw.write("\n");
					return true ;
				}
			}

		return false ;
	}

	void go() throws Exception {

		Pattern oper = Pattern.compile("([-+=])");

		String s;
		StringTokenizer st;
		int i,j,k;

		Map<Integer,List<Character>> operations;
		List<Integer> numbers;
		boolean seen;

		for (;(s=br.readLine())!=null;) {
			Matcher mtch = oper.matcher(s);
			operations = new HashMap<Integer,List<Character>>();
			numbers = new ArrayList<Integer>();
			for ( i = 0; i < 2; operations.put(i++,new ArrayList<Character>()) );
			seen = false;
			for (k=0;mtch.find();) {
				switch ( mtch.group(1) ) {
					case "=": ++k; seen = true; break ;
					case "-": operations.get(k).add('-'); break;
					default: operations.get(k).add('+'); break;
				}
			}

			for ( mtch = p.matcher(s); mtch.find(); numbers.add(Integer.parseInt(mtch.group(1))) );

			op = new char[operations.get(0).size()+operations.get(1).size()+2];
			m = operations.get(0).size()+1;
			i = 0; op[i++] = '+';
			for ( Character c: operations.get(0) )
				op[i++] = c;
			op[i++] = '-';
			for ( Character c: operations.get(1) ) {
				op[i] = R[(int)op[i]];
				++i;
			}
			n = numbers.size();
			boolean allLessThan100 = true;
			if ( !seen || n==0 || operations.get(0).size()+operations.get(1).size()+2 != n ) {
				bw.write("no solution\n");
				continue ;
			}
			for ( pluses = 0, i = 0; i < n; ++i )
				if ( op[i] == '+' )
					++pluses;
			assert op.length == n;
			x = new int[numbers.size()];
			i = 0;
			for ( int a: numbers ) 
				if ( (x[i++] = a) >= 100 )
					allLessThan100 = false ;
			if ( n >= 17 || !allLessThan100 || !oddEvenTest() || !g() ) 
				bw.write("no solution\n");
		}
		bw.flush();
	}
};


