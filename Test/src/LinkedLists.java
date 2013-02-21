
class Node {
	
	public Node next;
	public int value;
	
	public Node(int value) {
		this.value = value;
		this.next = null;
	}
	
	public static Node createFromArray(int[] array) {
		
		if(array.length == 0)
			return null;
		Node head = new Node(array[0]);
		Node tail = head;
		for(int i = 1; i < array.length; i++) {
			tail.next = new Node(array[i]);
			tail = tail.next;
		}
		return head;
	}
	
	public static Node findLastElem(Node node, int n) {
		
		Node start = node, end = node;
		int i = 0;
		
		while(i < n-1 && end != null) {
			end = end.next;
			i++;
		}
		
		if(end == null)
			return null;
		
		while(end.next != null) {
			start = start.next;
			end = end.next;
		}
		
		return start;
	}
	
	public static Node findLastElemRec(Node node, int n, int count[]) {
		
		if(node.next == null) {
			count[0] = 1;
			return null;
		} else {
			Node ret = findLastElemRec(node.next, n, count);
			count[0]++;
			if(count[0] == n)
				return node;
			else
				return ret;
		}
	}
	
	public static void removeDuplicates(Node node) {
		int val;
		Node prev;
		while(node != null) {
			val = node.value;
			prev = node;
			
			while(prev.next != null) {
				if(prev.next.value == val)
					prev.next = prev.next.next;
				else
					prev = prev.next;
			}
			node = node.next;
		}
	}
	
	public static void removeNode(Node node) {
		node.value = node.next.value;
		node.next= node.next.next;
	}
	
	public static void printList(Node node) {
		while(node != null) {
			System.out.print(node.value+" ");
			node = node.next;
		}
		System.out.println();
	}
}


public class LinkedLists {

	public static void testFindLastElem() {
		int[] array = {8,7,6,5,4,3,2,1};
		Node list = Node.createFromArray(array);
		System.out.println("Test 1: findLastElem");
		System.out.println(Node.findLastElem(list, 3).value);
		System.out.println(Node.findLastElem(list, 8) == null);
	}
	
	public static void testFindLastElemRec() {
		int[] array = {8,7,6,5,4,3,2,1};
		Node list = Node.createFromArray(array);
		System.out.println("Test 1': findLastElemRec");
		int[] count = new int[1];
		System.out.println(Node.findLastElemRec(list, 3, count).value);
		System.out.println(Node.findLastElemRec(list, 8, count) == null);
	}
	
	public static void testRemoveDuplicates() {
		int[] array = {1,1,1,1,2,2,1,3,4,1,2,1,5,7,9};
		Node list = Node.createFromArray(array);
		Node.removeDuplicates(list);
		System.out.println("Test 2: removeDuplicates");
		Node.printList(list);
	}
	
	public static void testRemoveNode() {
		int[] array = {1,2,3,4,5,6};
		Node list = Node.createFromArray(array);
		System.out.println(list.next.next.next.value);
		Node.removeNode(list.next.next.next);
		System.out.println("Test 3: removeNode");
		Node.printList(list);
	}
	
	public static void main(String[] args) {
		testFindLastElem();
		testFindLastElemRec();
		testRemoveDuplicates();
		testRemoveNode();
	}

}
