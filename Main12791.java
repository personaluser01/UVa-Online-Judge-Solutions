/*
 * 12791. Lap
 * TOPIC: ad hoc
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	double a,b;
	Scanner scan = new Scanner(System.in);
	public static void main( String[] args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		while ( scan.hasNext() ) {
			a = scan.nextDouble();
			b = scan.nextDouble();
			System.out.printf("%d\n",(int)Math.ceil(((double)b)/(b-a)));
		}
	}
};

