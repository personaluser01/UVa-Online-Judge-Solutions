/*
 * 892. Finding Words
 * TOPIC: parsing, dfa, finite automaton
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	char ch = '\0';
	public static void main ( String [] args ) throws Exception { new Main().go(); }
	boolean isWhitespace( char ch ) { return ch==' '||ch=='\t'; }
	boolean isEndOfLine( char ch ) { return ch=='\n'; }
	char getchar() throws Exception { return (char)System.in.read(); }
	void putchar( char ch ) throws Exception { System.out.print(ch); }
	boolean q0() throws Exception {
		if ( ch == '\n' )
			putchar(ch);
		ch = getchar();
		if ( ch == '#' ) 
			return q3();
		if ( isWhitespace(ch) ) 
			return q1();
		if ( isEndOfLine(ch) ) 
			return q0();
		return q2();
	}
	boolean q1() throws Exception {
		do {
			putchar(ch);
		} while ( isWhitespace(ch = getchar()) );
		if ( isEndOfLine(ch) )
			return q0();
		return q2();
	}
	boolean q2() throws Exception {
		char []s = new char[80];
		char prev = '\0';
		int n = 0;
		do {
			prev = ch;
			if ( 'A'<=ch && ch<='Z' || 'a'<=ch && ch<='z' )
				s[n++] = ch;
		} while ( !isWhitespace(ch=getchar()) && !isEndOfLine(ch) );
		if ( prev == '-' && isEndOfLine(ch) ) {
			System.out.println("");
			while ( !isWhitespace(ch=getchar()) && !isEndOfLine(ch) ) 
				if ( 'A'<=ch && ch<='Z' || 'a'<=ch && ch<='z' )
					s[n++] = ch;
			System.out.println(new String(s,0,n));
		}
		else 
			System.out.print(new String(s,0,n));
		if ( isEndOfLine(ch) ) return q0();
		return q1();
	}
	boolean q3() throws Exception {
		if ( (ch=getchar()) == (char)-1 || isEndOfLine(ch) ) return true;
		if ( isWhitespace(ch) ) return q1();
		if ( isEndOfLine(ch) )  return q0();
		return q2();
	}
	void go() throws Exception { q0(); }
};

