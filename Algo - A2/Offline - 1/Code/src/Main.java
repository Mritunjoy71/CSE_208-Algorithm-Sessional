import Datastructure.*;
import java.util.Scanner;

/**
 * Created by Muktadir on 3/17/2016.
 */
public class Main {

    public static void main(String[] args) {
        int n;
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();

        Heap heap = new MinHeap();
        for (int i = 0; i < n; i++) {
            String ch = sc.next();
            int f = sc.nextInt();

            heap.insert(new Node(ch, f));
        }
        Solver s  = new Solver(heap);
        s.buildTree();
        s.printCodes();
    }




}
