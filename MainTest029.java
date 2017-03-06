/*
 * QUESTION: What is the output of the following program?
 * TOPIC: exceptions
 * OUTPUT: ``Catch'' and then IllegalStateException
 * OPTION: Compilation Error
 * EXPLANATION: 
 * IllegalStateException is not handled, nor main is declared to throw any Exception -- but this is OK, because IllegalStateException is
 * a subclass of RuntimeException, i.e. unchecked exception
 */
import java.io.*;

public class MainTest029 {
	public static void main( String [] args ) {
		try {
			throw new ArrayIndexOutOfBoundsException();
		}
		catch ( IndexOutOfBoundsException e ) {
			System.out.println("Catch");
		}
		finally {
			throw new IllegalStateException();
		}
	}
}

