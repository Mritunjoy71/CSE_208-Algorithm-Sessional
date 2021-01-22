package Datastructure;

public class Node implements Comparable{
    public String str;
    public int freq;

    public Node left;
    public Node right;

    public Node(String str, int freq){
        this.str = str;
        this.freq = freq;
        this.left = null;
        this.right = null;
    }

    public int compareTo(Object ob){
        Node n = (Node) ob;
        if(n.freq == freq) return 0;
        if(n.freq > freq ) return -1;
        else return 1;
    }
}
