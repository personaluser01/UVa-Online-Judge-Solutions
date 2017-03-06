/*
 * 1200. A DP Problem
 * TOPIC: regex, parsing, solving equations, neat
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	final double tol = 1e-11;
	Pattern x = Pattern.compile("([-+]\\d+)x");
	Pattern sx = Pattern.compile("([-+]x)");
	Pattern a = Pattern.compile("([-+]\\d+)");
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String s;
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		int i,j,k,ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
		int []coeff = new int[2], fr = new int[2];
		for ( ;ts-- > 0; ) {
			s = br.readLine();
			String []t = s.split("=");
			for ( i = 0; i <= 1; ++i )
				t[i] = '+'+t[i]+'+';
			Matcher []X = {x.matcher(t[0]),x.matcher(t[1])}, A = {a.matcher(t[0]),a.matcher(t[1])}, S = {sx.matcher(t[0]),sx.matcher(t[1])};
			for ( i = 0; i <= 1; ++i ) {
				for ( coeff[i] = 0; X[i].find(); coeff[i] += Integer.parseInt(X[i].group(1)) );
				for ( fr[i] = -coeff[i]; A[i].find(); fr[i] += Integer.parseInt(A[i].group(1)) );
				for ( ;S[i].find(); coeff[i] += S[i].group(1).charAt(0)=='-'?-1:1 );
				//System.out.println(coeff[i]+"x"+fr[i]);
			}
			if ( coeff[0] == coeff[1] && fr[0] == fr[1] )
				System.out.println("IDENTITY");
			else if ( coeff[0] == coeff[1] && fr[0] != fr[1] )
				System.out.println("IMPOSSIBLE");
			else System.out.println((int)(Math.floor((fr[1]-fr[0]+0.00)/(coeff[0]-coeff[1]))));
		}
	}
};

