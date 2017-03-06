/*
 * 403. Postscript
 * TOPIC: ad hoc, text formatting, enums, java language techniques, oop principles, overriding
 * status: Accepted
 */

/**
 * Created by sj on 12/01/17.
 */

import java.io.*;
import java.util.*;
import java.util.regex.Pattern;

public class Main {

    private final static int N = 60, WIDTH = 6;

    enum Letters {
        A {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,".***..");
                myFill(g,row+1,col,col+WIDTH,"*...*.");
                myFill(g,row+2,col,col+WIDTH,"*****.");
                myFill(g,row+3,col,col+WIDTH,"*...*.");
                myFill(g,row+4,col,col+WIDTH,"*...*.");
            }
        },
        B {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"****..");
                myFill(g,row+1,col,col+WIDTH,"*...*.");
                myFill(g,row+2,col,col+WIDTH,"****..");
                myFill(g,row+3,col,col+WIDTH,"*...*.");
                myFill(g,row+4,col,col+WIDTH,"****..");
            }
        },
        C {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,".****.");
                myFill(g,row+1,col,col+WIDTH,"*...*.");
                myFill(g,row+2,col,col+WIDTH,"*.....");
                myFill(g,row+3,col,col+WIDTH,"*.....");
                myFill(g,row+4,col,col+WIDTH,".****.");
            }
        },
        D {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"****..");
                myFill(g,row+1,col,col+WIDTH,"*...*.");
                myFill(g,row+2,col,col+WIDTH,"*...*.");
                myFill(g,row+3,col,col+WIDTH,"*...*.");
                myFill(g,row+4,col,col+WIDTH,"****..");
            }
        },
        E {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"*****.");
                myFill(g,row+1,col,col+WIDTH,"*.....");
                myFill(g,row+2,col,col+WIDTH,"***...");
                myFill(g,row+3,col,col+WIDTH,"*.....");
                myFill(g,row+4,col,col+WIDTH,"*****.");
            }
        },
        F {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"*****.");
                myFill(g,row+1,col,col+WIDTH,"*.....");
                myFill(g,row+2,col,col+WIDTH,"***...");
                myFill(g,row+3,col,col+WIDTH,"*.....");
                myFill(g,row+4,col,col+WIDTH,"*.....");
            }
        },
        G {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,".****.");
                myFill(g,row+1,col,col+WIDTH,"*.....");
                myFill(g,row+2,col,col+WIDTH,"*..**.");
                myFill(g,row+3,col,col+WIDTH,"*...*.");
                myFill(g,row+4,col,col+WIDTH,".***..");
            }
        },
        H {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"*...*.");
                myFill(g,row+1,col,col+WIDTH,"*...*.");
                myFill(g,row+2,col,col+WIDTH,"*****.");
                myFill(g,row+3,col,col+WIDTH,"*...*.");
                myFill(g,row+4,col,col+WIDTH,"*...*.");
            }
        },
        I {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"*****.");
                myFill(g,row+1,col,col+WIDTH,"..*...");
                myFill(g,row+2,col,col+WIDTH,"..*...");
                myFill(g,row+3,col,col+WIDTH,"..*...");
                myFill(g,row+4,col,col+WIDTH,"*****.");
            }
        },
        J {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"..***.");
                myFill(g,row+1,col,col+WIDTH,"...*..");
                myFill(g,row+2,col,col+WIDTH,"...*..");
                myFill(g,row+3,col,col+WIDTH,"*..*..");
                myFill(g,row+4,col,col+WIDTH,".**...");
            }
        },
        K {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"*...*.");
                myFill(g,row+1,col,col+WIDTH,"*..*..");
                myFill(g,row+2,col,col+WIDTH,"***...");
                myFill(g,row+3,col,col+WIDTH,"*..*..");
                myFill(g,row+4,col,col+WIDTH,"*...*.");
            }
        },
        L {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"*.....");
                myFill(g,row+1,col,col+WIDTH,"*.....");
                myFill(g,row+2,col,col+WIDTH,"*.....");
                myFill(g,row+3,col,col+WIDTH,"*.....");
                myFill(g,row+4,col,col+WIDTH,"*****.");
            }
        },
        M {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"*...*.");
                myFill(g,row+1,col,col+WIDTH,"**.**.");
                myFill(g,row+2,col,col+WIDTH,"*.*.*.");
                myFill(g,row+3,col,col+WIDTH,"*...*.");
                myFill(g,row+4,col,col+WIDTH,"*...*.");
            }
        },
        N {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"*...*.");
                myFill(g,row+1,col,col+WIDTH,"**..*.");
                myFill(g,row+2,col,col+WIDTH,"*.*.*.");
                myFill(g,row+3,col,col+WIDTH,"*..**.");
                myFill(g,row+4,col,col+WIDTH,"*...*.");
            }
        },
        O {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,".***..");
                myFill(g,row+1,col,col+WIDTH,"*...*.");
                myFill(g,row+2,col,col+WIDTH,"*...*.");
                myFill(g,row+3,col,col+WIDTH,"*...*.");
                myFill(g,row+4,col,col+WIDTH,".***..");
            }
        },
        P {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"****..");
                myFill(g,row+1,col,col+WIDTH,"*...*.");
                myFill(g,row+2,col,col+WIDTH,"****..");
                myFill(g,row+3,col,col+WIDTH,"*.....");
                myFill(g,row+4,col,col+WIDTH,"*.....");
            }
        },
        Q {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,".***..");
                myFill(g,row+1,col,col+WIDTH,"*...*.");
                myFill(g,row+2,col,col+WIDTH,"*...*.");
                myFill(g,row+3,col,col+WIDTH,"*..**.");
                myFill(g,row+4,col,col+WIDTH,".****.");
            }
        },
        R {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"****..");
                myFill(g,row+1,col,col+WIDTH,"*...*.");
                myFill(g,row+2,col,col+WIDTH,"****..");
                myFill(g,row+3,col,col+WIDTH,"*..*..");
                myFill(g,row+4,col,col+WIDTH,"*...*.");
            }
        },
        S {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,".****.");
                myFill(g,row+1,col,col+WIDTH,"*.....");
                myFill(g,row+2,col,col+WIDTH,".***..");
                myFill(g,row+3,col,col+WIDTH,"....*.");
                myFill(g,row+4,col,col+WIDTH,"****..");
            }
        },
        T {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"*****.");
                myFill(g,row+1,col,col+WIDTH,"*.*.*.");
                myFill(g,row+2,col,col+WIDTH,"..*...");
                myFill(g,row+3,col,col+WIDTH,"..*...");
                myFill(g,row+4,col,col+WIDTH,".***..");
            }
        },
        U {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"*...*.");
                myFill(g,row+1,col,col+WIDTH,"*...*.");
                myFill(g,row+2,col,col+WIDTH,"*...*.");
                myFill(g,row+3,col,col+WIDTH,"*...*.");
                myFill(g,row+4,col,col+WIDTH,".***..");
            }
        },
        V {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"*...*.");
                myFill(g,row+1,col,col+WIDTH,"*...*.");
                myFill(g,row+2,col,col+WIDTH,".*.*..");
                myFill(g,row+3,col,col+WIDTH,".*.*..");
                myFill(g,row+4,col,col+WIDTH,"..*...");
            }
        },
        W {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"*...*.");
                myFill(g,row+1,col,col+WIDTH,"*...*.");
                myFill(g,row+2,col,col+WIDTH,"*.*.*.");
                myFill(g,row+3,col,col+WIDTH,"**.**.");
                myFill(g,row+4,col,col+WIDTH,"*...*.");
            }
        },
        X {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"*...*.");
                myFill(g,row+1,col,col+WIDTH,".*.*..");
                myFill(g,row+2,col,col+WIDTH,"..*...");
                myFill(g,row+3,col,col+WIDTH,".*.*..");
                myFill(g,row+4,col,col+WIDTH,"*...*.");
            }
        },
        Y {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"*...*.");
                myFill(g,row+1,col,col+WIDTH,".*.*..");
                myFill(g,row+2,col,col+WIDTH,"..*...");
                myFill(g,row+3,col,col+WIDTH,"..*...");
                myFill(g,row+4,col,col+WIDTH,"..*...");
            }

        },
        Z {
            public void print( int row, int col, char [][]g ) {
                myFill(g,row,col,col+WIDTH,"*****.");
                myFill(g,row+1,col,col+WIDTH,"...*..");
                myFill(g,row+2,col,col+WIDTH,"..*...");
                myFill(g,row+3,col,col+WIDTH,".*....");
                myFill(g,row+4,col,col+WIDTH,"*****.");
            }
        };
        abstract public void print( int row, int col, char [][]g ) ;
        private static void myFill( char [][]g, int row, int from, int to, String s ) {
            char []x = s.toCharArray();
            if ( row >= g.length ) return ;
            int j,k = 0;
            if ( from < 0 ) { k += -from; j = 0; }
            else { k = 0; j = from; }
            for ( ;j < to && j < g[row].length && k < x.length; ++k, ++j )
                g[row][j]=x[k]=='.'?g[row][j]:x[k];
        }
        private static void myFill( char [][]g, int row, int from, int to, char ... x ) {
            if ( row < 0 || row >= g.length ) return ;
            int j,k = 0;
            if ( from < 0 ) { k += -from; j = 0; }
            else { k = 0; j = from; }
            for ( ;j < to && j < g[row].length && k < x.length; ++k, ++j)
                g[row][j]=x[k]==' '?g[row][j]:x[k];
        }
    }

    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    char [][]g = new char[N][N];

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/403/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/403/src/out02.txt")));
        new Main().go();
    }

    static Letters []x = new Letters[Letters.values().length];
    static {
        for ( int i = 0; i < Letters.values().length; ++i ) {
            x[i] = Letters.values()[i];
            assert x[i].ordinal() == i;
        }
    }

    void place( String font, int row, int col, String str ) {
        int k = 0;
        boolean c1 = font.equals("C1");
        for ( char ch: str.toCharArray() ) {
            if ( c1 ) {
                Letters.myFill(g,row,col+k,col+k+1,ch);
                ++k;
            }
            else {
                if ( ch == ' ' ) {
                    k += WIDTH;
                    continue ;
                }
                assert 'A' <= ch && ch <= 'Z';
                x[ch-'A'].print(row,col+k,g);
                k += WIDTH;
            }
        }
    }

    void leftJustify( String font, int row, String str ) {
        place(font,row,0,str);
    }

    void rightJustify( String font, int row, String str ) {
        int k = N-1;
        boolean c1 = font.equals("C1");
        for ( int i = str.length()-1; i >= 0; --i ) {
            char ch = str.charAt(i);
            if ( c1 ) {
                Letters.myFill(g,row,k,k+1,ch);
                --k;
            }
            else {
                if ( ch == ' ' ) {
                    k -= WIDTH;
                    continue ;
                }
                x[ch-'A'].print(row,k-WIDTH+1,g);
                k -= WIDTH;
            }
        }
    }

    void center( String font, int row, String str ) {
        if (  font.equals("C1") )
            place(font,row,N/2-str.length()/2,str);
        else place(font,row,N/2-str.length()*WIDTH/2,str);
    }

    private static String f( String s ) {
        int n = s.length(),i = 0;
        while ( i < n && s.charAt(i) == ' ' ) ++i;
        return s.substring(i+1,n-1);
    }

    void go() throws Exception {
        int i,j,k,row,col;
        for ( String s; (s=br.readLine())!=null; ) {
            for ( i = 0; i < N; ++i )
                for ( j = 0; j < N; g[i][j++] = '.' );
            for (;s != null && !s.equals(".EOP"); s = br.readLine() ) {
                Scanner scan = new Scanner(s);
                String comm = scan.next(), font = scan.next();
                row = scan.nextInt()-1;
                switch (comm) {
                    case ".P":
                        col = scan.nextInt()-1;
                        scan.useDelimiter("\\z");
                        place(font, row, col, f(scan.next()));
                        break;
                    case ".L":
                        scan.useDelimiter("\\z");
                        leftJustify(font, row, f(scan.next()));
                        break;
                    case ".R":
                        scan.useDelimiter("\\z");
                        rightJustify(font, row, f(scan.next()));
                        break;
                    case ".C":
                        scan.useDelimiter("\\z");
                        center(font, row, f(scan.next()));
                        break;
                    default:
                        assert false;
                }
            }
            if ( s == null ) break ;
            for ( i = 0; i < N; ++i, bw.write("\n") )
                for ( j = 0; j < N; bw.write(g[i][j++]) ) ;
            bw.write("\n");
            bw.write(new String(new char[N]).replace('\0','-')+"\n");
            bw.write("\n");
        }
        bw.flush();
    }
}

