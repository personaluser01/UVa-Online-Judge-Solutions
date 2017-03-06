/*
 * 10217. Dinner with Arnie
 * TOPIC: probability, analysis of functions, recurrences
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.math.*;

class Main {
	final int N = 100100;
	final double tol = 1e-9;
	double []p = new double[N];
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer st;
	public static void main ( String [] args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		int n,i,j,k,l,t;
		String s;
		double best,w;
		while ( (s=br.readLine())!=null ) {
			st = new StringTokenizer(s);
			n = Integer.parseInt(st.nextToken());
			w = (1+Math.sqrt(1+4*n))/2.00;
			System.out.printf("%.2f %d\n",w+tol-1,(int)Math.floor(w-1)+1);
		}
	}
};

