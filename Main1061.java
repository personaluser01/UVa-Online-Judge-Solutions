/*
 * 1061. Consanguine Calculations
 * TOPIC: real life, blood types, brute force
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	final int O = 0, A = 1, B = 2, Rhm = 0, Rhp = 1;
	Scanner scan = new Scanner(System.in);
	String []t = new String[3];
	Pattern pbt = Pattern.compile("([A,B,O]+)([+-])");
	String [][]g = new String[3][3],r = new String[2][2];
	class BloodType implements Comparable<BloodType> {
		int []u,v;
		BloodType() { u = new int[2]; v = new int[2]; };
		BloodType( int i, int j, int k, int l ) { u=new int[2];v=new int[2];u[0]=i;v[0]=j;u[1]=k;v[1]=l; };
		public String toString() { return g[u[0]][u[1]]+r[v[0]][v[1]]; };
		public int compareTo( BloodType other ) {
			return this.toString().compareTo(other.toString());
		};
		public Set<BloodType> generate( BloodType other ) {
			Set<BloodType> s = new TreeSet<BloodType>();
			for ( int i = 0; i < 2; ++i )
				for ( int j = 0; j < 2; ++j )
					for ( int k = 0; k < 2; ++k )
						for ( int t = 0; t < 2; ++t ) {
							BloodType b = new BloodType();
							b.u[0] = u[i]; b.u[1] = other.u[k];
							b.v[0] = v[i]; b.v[1] = other.v[t];
							s.add(b);
						}
			return s;
		};
	};
	public static void main( String [] args ) throws Exception { new Main().go(); };

	String toStr( Set<BloodType> S ) {
		int k = 0;
		StringBuilder sb = new StringBuilder();
		if ( S.isEmpty() ) { sb.append("IMPOSSIBLE"); return sb.toString(); };
		if ( S.size() > 1 ) sb.append("{"); 
		k = 0;
		for ( BloodType b: S ) {
			if ( ++k > 1 ) sb.append(", ");
			sb.append(b);
		}
		if ( S.size() > 1 ) sb.append("}");
		return sb.toString();
	};

	void go() throws Exception {
		int i,j,k,cs = 0,l,e;
		int []m = new int[2];
		String []orig = new String[3];
		BloodType [][]p = new BloodType[2][0x40];
		g[O][O] = "O"; g[O][A] = "A"; g[O][B] = "B";
		g[A][O] = "A"; g[A][A] = "A"; g[A][B] = "AB";
		g[B][O] = "B"; g[B][A] = "AB"; g[B][B] = "B";
		r[Rhm][Rhm] = "-"; r[Rhm][Rhp] = "+";
		r[Rhp][Rhm] = "+"; r[Rhp][Rhp] = "+";
		while ( scan.hasNext() && !(t[0]=scan.next()).equals("E") ) {
			for ( i = 1; i < 3; t[i++] = scan.next() );
			for ( i = 0; i < 3; ++i ) orig[i] = t[i];
			System.out.print("Case "+(++cs)+":");
			if ( t[0].equals("?") ) {
				String tmp = t[0]; t[0] = t[1]; t[1] = tmp;
			}
			assert !t[0].equals("?");
			if ( t[1].equals("?") ) {
				for ( m[e = 0] = 0, i = O; i <= B; ++i )
					for ( j = Rhm; j <= Rhp; ++j ) 
						for ( k = O; k <= B; ++k )
							for ( l = Rhm; l <= Rhp; ++l ) {
								BloodType d = new BloodType(i,j,k,l);
								if ( d.toString().equals(t[e]) )
									p[e][m[e]++] = d;
							}
				Set<BloodType> s,S = new TreeSet<BloodType>();
				boolean ok;
				for ( i = O; i <= B; ++i )
					for ( j = Rhm; j <= Rhp; ++j )
						for ( k = O; k <= B; ++k )
							for ( l = Rhm; l <= Rhp; ++l ) {
								BloodType d = new BloodType(i,j,k,l);
								ok = false; 
								for ( int z = 0; z < m[0] && !ok; ++z ) {
									s = p[0][z].generate(d);
									for ( BloodType b: s ) 
										if ( b.toString().equals(t[2]) ) {
											S.add(d);
											ok = true ;
											break ;
										}
								}
							}
				if ( orig[0].equals("?") ) 
					System.out.println(" "+toStr(S)+" "+orig[1]+" "+orig[2]);
				else 
					System.out.println(" "+orig[0]+" "+toStr(S)+" "+orig[2]);
			}
			else {
				assert t[2].equals("?");
				for ( e = 0; e <= 1; ++e ) 
				for ( m[e] = 0, i = O; i <= B; ++i )
					for ( j = Rhm; j <= Rhp; ++j ) 
						for ( k = O; k <= B; ++k )
							for ( l = Rhm; l <= Rhp; ++l ) {
								BloodType d = new BloodType();
								d.u[0] = i; d.u[1] = k;
								d.v[0] = j; d.v[1] = l;
								if ( d.toString().equals(t[e]) )
									p[e][m[e]++] = d;
							}
				Set<BloodType> s,S = new TreeSet<BloodType>();
				for ( i = 0; i < m[0]; ++i )
					for ( j = 0; j < m[1]; ++j ) {
						s = p[0][i].generate(p[1][j]);
						for ( BloodType b: s ) 
							S.add(b);
					}
				System.out.println(" "+orig[0]+" "+orig[1]+" "+toStr(S));
			}
		};
	};
};

