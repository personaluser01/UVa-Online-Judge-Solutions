/*
 * 12894. Perfect Flag
 * TOPIC: geometry
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final double tol = 1e-9;
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception { new Main().go(); };
	void go() throws Exception {
		int i,j,k,ts = scan.nextInt();
		double []x = new double[2], y = new double[2];
		double L,W,cx,cy,r;
		for ( ;ts-->0; ) {
			for ( i = 0; i <= 1; ++i ) {
				x[i] = scan.nextDouble();
				y[i] = scan.nextDouble();
			};
			cx = scan.nextDouble();
			cy = scan.nextDouble();
			r = scan.nextDouble();
			L = x[1]-x[0]; W = y[1]-y[0];
			if ( Math.abs(6*L-10*W)>tol || Math.abs(cy-(y[0]+y[1])/2)>tol || Math.abs(cx-x[0]-9*L/20)>tol || Math.abs(L-5*r)>tol )
				System.out.println("NO");
			else 
				System.out.println("YES");
		};
	};
};

