package tree;

public class Node {
	int value;
	Node left;
	Node right;
	Node parent;
	public Node(int value) {
		this.value = value;
	}
	
	public void print() {
		if(left != null)
			left.print();
		System.out.print(value + " ");
		if(right != null)
			right.print();
	}
	
	@Override 
	public String toString() {
		return Integer.toString(value);
	}
}
