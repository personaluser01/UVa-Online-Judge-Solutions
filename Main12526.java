/*
 * 12526. Cellphone Typing
 * TOPIC: ad hoc, trie, dp, recursion, tree
 * status: WA to do with precision in Java's output rounding
 */

/**
 * Created by sj on 17/02/17.
 */

import java.io.*;
import java.text.NumberFormat;
import java.util.*;

public class Main {
    double tol = 1e-9;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    int ID;

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/12526/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/12526/src/out02.txt")));
        new Main().go();
    }

    private class Node {
        Map<Character,Node> child = null ;
        boolean isTerminalNode = false ;
        int depth, numLeaves = 0, id;

        Node( int depth ) {
            this.id = ID++;
            this.depth = depth;
        }
    }

    void insert( Node root, char []word ) {
        int i,n = word.length;
        Node x;
        for ( x = root, i = 0; x != null && i < n; x = x.child.get(word[i++]) )
            if ( x.child == null || !x.child.containsKey(word[i]) ) {
                if ( x.child == null )
                    x.child = new HashMap<>();
                x.child.put(word[i],new Node(x.depth+1));
            }
        x.isTerminalNode = true ;
    }

    int calc( Node x ) {
        if ( x.child == null )
            return x.numLeaves = 1;
        x.numLeaves = x.isTerminalNode?1:0;
        for ( Map.Entry<Character,Node> entry: x.child.entrySet() )
            x.numLeaves += calc(entry.getValue());
        return x.numLeaves;
    }

    int f( Node x, int pressedSoFar ) {
        int acc = 0;
        if ( x.child == null || x.numLeaves <= 1 ) {
            acc = pressedSoFar;
            acc = acc;
            return acc;
        }
        if ( x.child.size() == 1 )
            for ( Map.Entry<Character,Node> entry: x.child.entrySet() ) {
                acc = (x.isTerminalNode?pressedSoFar:0)+f(entry.getValue(),pressedSoFar+(x.isTerminalNode?1:0));
                acc = acc;
                return acc;
            }
        if ( x.isTerminalNode ) ++acc;
        for ( Map.Entry<Character,Node> entry: x.child.entrySet() )
            acc += f(entry.getValue(),pressedSoFar+1);
        acc = acc;
        return acc;
    }

    void go() throws Exception {
        int i,n,ans,cs = 0;
        String lastWord = null;
        Node root;
        for ( String s; (s = br.readLine()) != null; ) {
            n = Integer.parseInt(s);
            ID = 0;
            root = new Node(0);
            for ( i = 0; i < n; insert(root,(lastWord = br.readLine()).toCharArray()), ++i );
            if ( root.child == null ) {
                bw.write("0.00\n");
                continue ;
            }
            calc(root);
            ans = 0;
            for ( Map.Entry<Character,Node> entry: root.child.entrySet() )
                ans += f(entry.getValue(),1);
            //bw.write(String.format("%.2f\n",((int)(100*((ans+0.00)/n)))/100.00));
            //bw.write(String.format("%.2f\n",ans/((double)n)));
            //bw.write(ans+"\n");
            NumberFormat nf = NumberFormat.getInstance();
            nf.setMinimumFractionDigits(2);
            nf.setMaximumFractionDigits(2);
            System.out.print(nf.format(ans/((double)n))+"\n");
        }
        //bw.flush();
    }

    private double g(double v) {
        v = (10000*(v+0.0005))/10000.00;
        int x = (int)(1000*v);
        if ( x%10 == 5 )
            return (x/10)/100.00;
        return v;
    }
}




