/*
 * 11070. The Good Old Times
 * TOPIC: parsing, javascript
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;

class Main{
	final double tol = 1e-9;
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		String s;
		double x;
		while ( scan.hasNext() ) {
			s = scan.next();
			ScriptEngineManager sem = new ScriptEngineManager();
			ScriptEngine se = sem.getEngineByName("JavaScript");
			Number g = (Number)se.eval(s);
			System.out.printf("%.3f\n",g.doubleValue());
		}
	}
}

