/*
 * 1593. Alignment of Code
 * TOPIC: replaceFirst, Java built-in libraries and methods, excellent interview question
 * status: Accepted
 */

/**
 * Created by sj on 30/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/179/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/179/src/out02.txt")));
        new Main().go();
    }

    String [][]s = new String[0x400][];
    int []start = new int[0x200];
    int m,n;


    void go() throws Exception {
        int i,j,k;
        for ( String buff; (buff = br.readLine()) != null; s[m++] = buff.replaceFirst("^\\s+","").split("\\s+") );
        for ( n = 0, i = 0; i < m; ++i )
            n = Math.max(n,s[i].length);
        for ( start[0] = 0, j = 1; j < n; ++j )
            for (start[j] = 0,  i = 0; i < m; ++i )
                if ( j-1 < s[i].length )
                    start[j] = Math.max(start[j],start[j-1]+s[i][j-1].length()+1);
        for ( i = 0; i < m; ++i, bw.write("\n") )
            for ( k = 0, j = 0; j < s[i].length; bw.write(s[i][j]), k += s[i][j++].length() )
                for ( ;k < start[j]; ++k, bw.write(" ") );
        bw.flush();
    }
}

