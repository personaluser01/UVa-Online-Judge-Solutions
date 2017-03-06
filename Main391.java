/*
 * 391. Mark-up
 * status: Accepted
 * TOPIC: parsing, finite state automata, medium-decent
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    String s;
    int pos,n,markup_on,boldface,italics,prev_pos;
    boolean eat_all;

    public static void main( String [] args ) throws Exception { new Main().go(); }

    String nextToken() {
        String r = new String();
        char ch,t;
        boolean dot = false;

        assert r.length() == 0;
        if ( pos == n ) return r;

        if ( markup_on == 0 ) {
            while ( pos < n ) {
                ch = s.charAt(pos++);
                if ( ch == '\\' && pos < n && s.charAt(pos) == '*' ) {
                    ++pos; markup_on = 1;
                    return r;
                }
                r += ch;
            }
            return r;
        }

        assert markup_on == 1;
        assert pos < n;

        if ( s.charAt(pos) == '\\' ) {
            r += s.charAt(pos++);
            if ( pos == n ) return r;
            r += (t=s.charAt(pos++));
            while ( pos < n && t == 's' ) {
                if ( dot && s.charAt(pos) == '.' ) 
                    break ;
                if ( s.charAt(pos) == '.' ) {
                    dot = true;
                    r += s.charAt(pos++);
                    continue ;
                }
                if ( '0' <= s.charAt(pos) && s.charAt(pos) <= '9' ) {
                    r += s.charAt(pos++);
                    continue ;
                }
                break ;
            }
            return r;
        }
        while ( pos < n && s.charAt(pos) != '\\' ) r += s.charAt(pos++);
        return r;
    }

    void go() throws Exception {
        String e,r;
        boldface = 0; italics = 0; markup_on = 1; eat_all = false;
        while ( (s = br.readLine()) != null ) {
            n = s.length(); pos = 0;
            e = new String();
            while ( pos < n ) {
                r = nextToken();
                if ( r.length() == 0 ) { 
                    if ( markup_on == 1 ) eat_all = false; 
                    continue ;
                }
                if ( r.charAt(0) != '\\' || eat_all ) {
                    if ( markup_on == 1 )
                        eat_all = false;
                    e += r;
                    continue ;
                }

                if ( markup_on == 1 )
                    eat_all = false;

                assert markup_on == 1;

                if ( r.length() == 1 ) 
                    continue ;

                assert r.charAt(0) == '\\';
                assert r.length() >= 2;
                if ( r.charAt(1) == 'i' ) {
                    italics = italics^1;
                    continue ;
                }
                if ( r.charAt(1) == 'b' ) {
                    boldface = boldface^1;
                    continue ;
                }
                if ( r.charAt(1) == '*' ) {
                    markup_on = markup_on^1;
                    if ( markup_on == 0 ) 
                        eat_all = true;
                    continue ;
                }
                if ( r.charAt(1) == 's' ) 
                    continue ;
                e += r.substring(1);
            }
            System.out.println(e);
        }
    }

};

