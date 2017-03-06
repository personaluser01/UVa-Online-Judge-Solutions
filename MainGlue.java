import java.io.*;
import java.util.*;

class Main {
	public static void main( String [] args ) throws Exception { new Main().go(); };
	void go() throws Exception {
		for ( int i = 3; i <= 50; ++i ) {
			StringBuilder sb = new StringBuilder();
			Formatter fmt = new Formatter(sb);
			fmt.format("asteroids%1$02d.ans",i);
			Runtime r = java.lang.Runtime.getRuntime();
			String command = "cat "+sb+" >> 1710.out";
			// Process p = new ProcessBuilder("/bin/sh","-c",command).start();
			System.out.println(command);
		}
	};
};

