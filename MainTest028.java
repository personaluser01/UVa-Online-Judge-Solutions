/*
 * QUESTION: What is the output of the following program?
 * TOPIC: exceptions
 * OUTPUT: ``Catch'' and then ``Wait! What about me?!!!''
 * OPTION: Catch 
 * OPTION: Compilation Error
 * EXPLANATION: 
 * finally block ALWAYS executes
 */
public class MainTest028 {
	public static void main( String [] args ) throws Exception {
		try {
			throw new ArrayIndexOutOfBoundsException();
		}
		catch ( IndexOutOfBoundsException e ) {
			System.out.println("Catch");
			return ;
		}
		finally {
			System.out.println("Wait! What about me?!!!");
		}
	}
}

