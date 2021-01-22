package Datastructure;

/**
 * Created by Muktadir on 3/17/2016.
 */
public interface Heap{
    void insert(Node ob);
    Node extractMin();
    void print();
    int getLength();
}
