/*
 * 12704. Little Masters
 * status: Accepted
 * TOPIC: trigonometry, math, neat
 */
import java.io.*;
import java.util.*;
import java.lang.Math.*;

class Main {
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		int i,j,k,l,ts,n;
		double x,y,r,d,phi,tol = 1e-9;
		String s;
		StringTokenizer st;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
		while ( ts-- > 0 ) {
			st = new StringTokenizer(br.readLine());
			x = Double.parseDouble(st.nextToken());
			y = Double.parseDouble(st.nextToken());
			r = Double.parseDouble(st.nextToken());
			d = Math.sqrt(x*x+y*y);
			System.out.printf("%.2f %.2f\n",tol+Math.sqrt(x*x+y*y+r*r-2*r*d),tol+Math.sqrt(x*x+y*y+r*r+2*r*d));
		}
	}
};

