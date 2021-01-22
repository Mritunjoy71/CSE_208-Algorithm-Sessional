package Datastructure;

public class MinHeap implements Heap{
    private static final int initialLength = 16;
    private Node data[];
    private int heapLength;

    public MinHeap(){
        data = new Node[initialLength];
        heapLength = 0;
    }

    @Override
    public void insert(Node ob){
        if(heapLength == data.length) doubleSize();

        data[heapLength] = ob;
        heapLength++;
        if(heapLength == 1) return;

        int i = heapLength - 1;
        int p = parent(i);
        while (data[p].compareTo(data[i]) == 1){
            Node t = data[p];
            data[p] = data[i];
            data[i] = t;

            i = p;
            p = parent(i);
        }
    }

    @Override
    public Node extractMin(){
        if(heapLength == 0) return null;
        Node t  = data[0];
        data[0] = data[heapLength - 1];
        heapLength--;
        heapify(0);
        return t;
    }

    public void print(){
        for (int i = 0; i < heapLength; i++) {
            System.out.println(data[i].str + ":" + data[i].freq);
        }
    }

    @Override
    public int getLength() {
        return heapLength;
    }

    private void doubleSize(){
        Node[] tmp = new Node[data.length * 2];
        for (int i = 0; i < data.length; i++){
            tmp[i] = data[i];
        }
        data = tmp;
    }

    private void heapify(int i){
        int l = left(i);
        int r = right(i);

        int smallest = i;
        if(l < heapLength && data[l].compareTo(data[smallest]) == -1){
            smallest = l;
        }
        if(r < heapLength && data[r].compareTo(data[smallest]) == -1){
            smallest = r;
        }
        if(smallest == i) return;
        Node t = data[i];
        data[i] = data[smallest];
        data[smallest] = t;
        heapify(smallest);
    }

    private int left(int i){
        return 2 * i;
    }

    private int right(int i ){
        return 2 * i + 1;
    }

    private int parent(int i){
        return i / 2;
    }
}