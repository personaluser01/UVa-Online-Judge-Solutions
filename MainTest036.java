/*
 * QUESTION: The output of the following code is ...
 * TOPIC: wrapper classes
 * OUTPUT: primitive long
 * OPTION: var-args
 * OPTION: Wrapper Integer
 * OPTION: Wrapper Long
 * EXPLANATION: There are four overloaded functions f, and the compiler always tries to apply the most specific of them,
 * where widening is preferred to Boxing/unboxing, which is in turn preferred over var-args;
 */

public class MainTest036 {
	public static void main( String [] args ) { new MainTest036().f(1); }
	void f( int ... x ) { System.out.println("var-args"); }
	void f( Integer x ) { System.out.println("Wrapper Integer"); }
	void f( Long x ) { System.out.println("Wrapper Long"); }
	void f( long x ) { System.out.println("primitive long"); }
}

