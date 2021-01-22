import Datastructure.Heap;
import Datastructure.Node;

public class Solver {
    private Heap heap;
    private Node root;

    public Solver(Heap h){
        this.heap = h;
    }

    public void buildTree(){
        while(heap.getLength() > 1){
            Node n1 = heap.extractMin();
            Node n2 = heap.extractMin();
            Node newNode = new Node(n1.str + n2.str, n1.freq + n2.freq);
            newNode.left = n1;
            newNode.right = n2;
            heap.insert(newNode);
        }
        root = heap.extractMin();
    }

    public void printTree(){

    }

    public void printCodes(){
        printCodes(root, "");
    }

    private void printCodes(Node r, String code){
        if(r.left == null && r.right == null){
            System.out.println(r.str + ":" + code);
            return;
        }
        if(r.left != null){
            printCodes(r.left, code + "0");
        }
        if(r.right != null){
            printCodes(r.right, code + "1");
        }
    }
}
