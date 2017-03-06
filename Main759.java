/*
 * 759. The Return of the Roman Empire
 * TOPIC: roman numerals
 * status: Accepted
 */

/**
 * Created by sj on 31/01/17.
 */

import java.io.*;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static Map<Character,Integer> m = new HashMap<>();
    boolean ok;

    static {
        m.put('I',1);
        m.put('V',5);
        m.put('X',10);
        m.put('L',50);
        m.put('C',100);
        m.put('D',500);
        m.put('M',1000);
    }

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/759/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/759/src/out02.txt")));
        new Main().go();
    }

    String []pats = {"IIII","XXXX", "CCCC", "MMMM", "III[^I]+I", "XXX[^X]+X", "CCC[^C]+C","MMM[^M]+M","V[^V]+V","L[^L]+L","D[^D]+D"};

    void checkViolation( String s ) {
        ok = true ;
        for ( Character ch: s.toCharArray() )
            if ( !m.containsKey(ch) ) {
                ok = false ;
                return ;
            }
            /*
        for ( String t: pats ) {
            Pattern p = Pattern.compile(t);
            Matcher matcher = p.matcher(s);
            if ( matcher.find() ) {
                ok = false ;
                return ;
            }
        }
        */
    }

    int convert( char []c ) {
        int res = 0, n = c.length, i,j,k,sentinel = (1<<29);
        for ( j = 0; j < n; ++j ) {
            for ( k = j; j+1 < n && m.get(c[j+1]) < m.get(c[j]); ++j );
            for ( i = k; i < j; res += m.get(c[i++]) );
            if ( j+1 < n ) {
                if ( sentinel < m.get(c[k]) ) { ok = false; return res; }
                sentinel = m.get(c[j]);
                res -= m.get(c[j]);
                res += m.get(c[++j]);
            }
            else res += m.get(c[j]);
        }
        return res ;
    }

    void int2roman( int n, StringBuilder sb ) {
        if ( n == 0 ) return ;
        if ( n >= 3000 ) {
            sb.append("MMM");
            int2roman(n-3000,sb);
        }
        else if ( n >= 2000 ) {
            sb.append("MM");
            int2roman(n-2000,sb);
        }
        else if ( n >= 1000 ) {
            sb.append("M");
            int2roman(n-1000,sb);
        }
        else {
            if ( n >= 900 ) {
                sb.append("CM");
                int2roman(n-900,sb);
            }
            else if ( n >= 800 ) {
                sb.append("DCCC");
                int2roman(n-800,sb);
            }
            else if ( n >= 700 ) {
                sb.append("DCC");
                int2roman(n-700,sb);
            }
            else if ( n >= 600 ) {
                sb.append("DC");
                int2roman(n-600,sb);
            }
            else if ( n >= 500 ) {
                sb.append("D");
                int2roman(n-500,sb);
            }
            else if ( n >= 400 ) {
                sb.append("CD");
                int2roman(n-400,sb);
            }
            else if ( n >= 300 ) {
                sb.append("CCC");
                int2roman(n-300,sb);
            }
            else if ( n >= 200 ) {
                sb.append("CC");
                int2roman(n-200,sb);
            }
            else if ( n >= 100 ) {
                sb.append("C");
                int2roman(n-100,sb);
            }
            else {
                if ( n >= 90 ) {
                    sb.append("XC");
                    int2roman(n-90,sb);
                }
                else if ( n >= 80 ) {
                    sb.append("LXXX");
                    int2roman(n-80,sb);
                }
                else if ( n >= 70 ) {
                    sb.append("LXX");
                    int2roman(n-70,sb);
                }
                else if ( n >= 60 ) {
                    sb.append("LX");
                    int2roman(n-60,sb);
                }
                else if ( n >= 50 ) {
                    sb.append("L");
                    int2roman(n-50,sb);
                }
                else if ( n >= 40 ) {
                    sb.append("XL");
                    int2roman(n-40,sb);
                }
                else if ( n >= 30 ) {
                    sb.append("XXX");
                    int2roman(n-30,sb);
                }
                else if ( n >= 20 ) {
                    sb.append("XX");
                    int2roman(n-20,sb);
                }
                else if ( n >= 10 ) {
                    sb.append("X");
                    int2roman(n-10,sb);
                }
                else {
                    if ( n >= 9 ) {
                        sb.append("IX");
                        int2roman(n-9,sb);
                    }
                    else if ( n >= 8 ) {
                        sb.append("VIII");
                        int2roman(n-8,sb);
                    }
                    else if ( n >= 7 ) {
                        sb.append("VII");
                        int2roman(n-7,sb);
                    }
                    else if ( n >= 6 ) {
                        sb.append("VI");
                        int2roman(n-6,sb);
                    }
                    else if ( n >= 5 ) {
                        sb.append("V");
                        int2roman(n-5,sb);
                    }
                    else if ( n >= 4 ) {
                        sb.append("IV");
                        int2roman(n-4,sb);
                    }
                    else if ( n >= 3 ) {
                        sb.append("III");
                        int2roman(n-3,sb);
                    }
                    else if ( n >= 2 ) {
                        sb.append("II");
                        int2roman(n-2,sb);
                    }
                    else if ( n == 1 ) {
                        sb.append("I");
                        int2roman(n-1,sb);
                    }
                }
            }
        }
    }

    Map<String,Integer> h = new HashMap<>();

    void go() throws Exception {
        int res = 0;
        for ( int k = 1; k <= 3999; ++k ) {
            StringBuilder sb = new StringBuilder();
            int2roman(k,sb);
            if ( k == 89 ) {
                sb = sb;
            }
            h.put(sb.toString(),k);
        }
        for ( String s; (s = br.readLine()) != null; ) {
            checkViolation(s);
            if ( ok ) {
                if ( !h.containsKey(s) ) ok = false ;
                else res = h.get(s);
            }
            if ( !ok )
                bw.write("This is not a valid number\n");
            else bw.write(res+"\n");
        }
        bw.flush();
    }
}
