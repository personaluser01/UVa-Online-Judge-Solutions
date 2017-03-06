/*
 * 12460. Careful Teacher
 * TOPIC: trie, bfs, easy
 * status: Accepted
 */

/**
 * Created by sj on 01/03/17.
 */

import java.io.*;
import java.util.*;

public class Main {

    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/12460/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/12460/src/out02.txt")));
        new Main().go();
    }

    class Node {
        Map<Character,Node> child = new HashMap<>();
        String t = null;
    }
    void push( Node root, String s ) {
        Node x;
        int i;
        for ( x = root, i = 0; i < s.length(); x = x.child.get(s.charAt(i++)) )
            if ( !x.child.containsKey(s.charAt(i)) )
                x.child.put(s.charAt(i),new Node());
        if ( x.t == null )
            x.t = new String(s);
    }

    String find( Node root, String s, int skipPos, char ch ) {
        Node x;
        int i;
        char t;
        for ( x = root, i = 0; i < s.length(); ++i ) {
            if ( i == skipPos ) t = ch;
            else t = s.charAt(i);
            if ( !x.child.containsKey(t) )
                return null;
            x = x.child.get(t);
        }
        return x.t;
    }

    Queue<String> q = new LinkedList<>();
    Set<String> seen = new HashSet<>();

    void go() throws Exception {
        Node root = new Node();
        String s,t,src,dst;
        char []arr = "abcdefghijklmnopqrstuvwxyz".toCharArray();
        int i;
        for ( ;!((s = scan.next()).equals("--"));  s = s, push(root,s) );
        while ( scan.hasNext() ) {
            src = scan.next();
            dst = scan.next();
            if ( (src = find(root,src,-1,'\0')) == null || (dst = find(root,dst,-1,'\0')) == null ) {
                bw.write("No\n");
                continue ;
            }
            for ( q.clear(), seen.clear(), seen.add(src), q.add(src); !q.isEmpty() && !seen.contains(dst); )
                for ( s = q.poll(), i = 0; i < s.length(); ++i )
                    for ( Character ch: arr )
                        if ( ch != s.charAt(i) )
                            if ( (t = find(root,s,i,ch)) != null )
                                if ( !seen.contains(t) ) {
                                    seen.add(t);
                                    q.add(t);
                                }
            bw.write(seen.contains(dst)?"Yes\n":"No\n");
        }
        bw.flush();
    }
}

