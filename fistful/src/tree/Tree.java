package tree;

import java.util.ArrayList;
import java.util.LinkedList;

public class Tree {
	
	// 4.1
	public static int minTreeHeight(Node node) {
		
		if(node == null)
			return 0;
		return 1 + Math.min(minTreeHeight(node.left), minTreeHeight(node.right));
	}
	
	public static int maxTreeHeight(Node node) {
		
		if(node == null)
			return 0;
		return 1 + Math.max(maxTreeHeight(node.left), maxTreeHeight(node.right));
	}
	
	public static boolean isBalanced(Node root) {
		
		return maxTreeHeight(root) - minTreeHeight(root) < 2;
	}
	
	public static void testIsBalanced(int n) {
		int[] array;
		
		for(int i = 0; i < n; i++) {
			array = new int[i+1];
			for(int j = 0; j <= i; j++) {
				array[j] = j;
			}
			Node tree = createBTreeFromArray(array, 0, array.length - 1);
			System.out.println("Testing isBalanced");
			tree.print();
			System.out.println(isBalanced(tree));
		}
	}

	// 4.3
	public static Node createBTreeFromArray(int[] array, int start, int end) {
		if(start > end)
			return null;
		int middle = (start + end) / 2;
		System.out.println("Tree: start="+start+" end="+end+" middle="+middle);
		Node current = new Node(array[middle]);
		current.left = createBTreeFromArray(array, start, middle - 1);
		current.right = createBTreeFromArray(array, middle + 1, end);
		return current;
	}
	
	public static void testCreateBTreeFromArray(int n) {
		int[] array;
		
		for(int i = 0; i < n; i++) {
			array = new int[i+1];
			for(int j = 0; j <= i; j++) {
				array[j] = j;
			}
			Node tree = createBTreeFromArray(array, 0, array.length - 1);
			tree.print();
			System.out.println();
		}
	}
	
	// 4.4
	public static void createLists(Node node, int level, ArrayList<LinkedList<Node>> lists) {
		if(node == null)
			return;
		if(lists.size() < level + 1)
			lists.add(new LinkedList<Node>());
		lists.get(level).add(node);
		createLists(node.left, level + 1, lists);
		createLists(node.right, level + 1, lists);
	}
	
	public static ArrayList<LinkedList<Node>> createListsFromBTree(Node root) {
		ArrayList<LinkedList<Node>> result = new ArrayList<LinkedList<Node>>();
		createLists(root, 0, result);
		return result;
	}
	
	public static void testCreateListsFromBTree(int n) {
		int[] array = new int[n];
		for(int i = 0; i < n; i++)
			array[i] = i;
		Node root = createBTreeFromArray(array, 0, n-1);
		ArrayList<LinkedList<Node>> lists = createListsFromBTree(root);
		for(LinkedList<Node> list : lists)
			System.out.println(list);
		System.out.println();
	}
	
	// 4.5 - nu va functiona cautarea in sus (nu e implementata completarea referintelor parent in noduri
	public static Node findNext(Node node) {
		
		Node next = node;
		if(node.right != null) { // go right, then go leftmost
			next = node.right;
			while(next.left != null)
				next = next.left;
		} else {
			next = node.parent;
			while(next != null) { // go upward until next.parent == next.parent.left
				if(next.value > node.value)
					break;
				next = next.parent;
			}
		}
		return next;
	}

	public static void testFindNext() {
		int n = 15;
		int[] array = new int[n];
		for(int i = 0; i < n; i++)
			array[i] = i;
		
		Node root = createBTreeFromArray(array, 0, array.length - 1);
		root.print();
		ArrayList<LinkedList<Node>> lists = createListsFromBTree(root);
		Node node = lists.get(1).get(0);
		Node result = findNext(node);
		System.out.println();
		System.out.println(result);
	}
	
	// 4.6
	public static boolean hasDescendent(Node n1, Node n2) {
		if(n1 == null)
			return false;
		if(n1 == n2)
			return true;
		return hasDescendent(n1.left, n2) || hasDescendent(n1.right, n2);
	}
	
	public static Node findFirstCommonAncestor(Node root, Node n1, Node n2) {
		if(root == null)
			return null;
		if(hasDescendent(root.left, n1) && hasDescendent(root.left, n2))
			return findFirstCommonAncestor(root.left, n1, n2);
		if(hasDescendent(root.right, n1) && hasDescendent(root.right, n2))
			return findFirstCommonAncestor(root.right, n1, n2);
		return root;
	}
	
	public static void testFindFirstCommonAncestor() {
		int n = 15;
		int[] array = new int[n];
		for(int i = 0; i < n; i++)
			array[i] = i;
		
		Node root = createBTreeFromArray(array, 0, array.length - 1);
		ArrayList<LinkedList<Node>> lists = createListsFromBTree(root);
		for(LinkedList<Node> list : lists)
			System.out.println(list);
		
		Node n1 = lists.get(3).get(0);
		Node n2 = lists.get(2).get(0);
		
		System.out.println(findFirstCommonAncestor(root, n1, n2));
	}
	
	// 4.7
	public static boolean sameTree(Node n1, Node n2) {
		if(n1 == null && n2 == null)
			return true;
		if(n1 == null || n2 == null)
			return false;
		System.out.println("n1="+n1+" n2="+n2);
		return(n1.value == n2.value && 
				sameTree(n1.left, n2.left) && 
				sameTree(n1.right, n2.right));
	}
	
	public static boolean isSubTree(Node n1, Node n2) {
		
		if(n1 == null || n2 == null)
			return false;
		return sameTree(n1,n2) || 
				isSubTree(n1.left, n2) || 
				isSubTree(n1.right, n2);
	}
	
	public static void testIsSubTree() {
		int n1 = 10, n2 = 4;
		int[] array1 = new int[n1];
		int[] array2 = new int[n2];
		Node root1, root2;
		
		for(int i = 0; i < n1; i++)
			array1[i] = i;
		for(int i = 0; i < n2; i++)
			array2[i] = i;
		
		root1 = createBTreeFromArray(array1, 0, n1 - 1);
		ArrayList<LinkedList<Node>> lists1 = createListsFromBTree(root1);
		for(LinkedList<Node> list : lists1)
			System.out.println(list);
		
		root2 = createBTreeFromArray(array2, 0, n2 - 1);
		ArrayList<LinkedList<Node>> lists2 = createListsFromBTree(root2);
		for(LinkedList<Node> list : lists2)
			System.out.println(list);
		
//		root1.print();
//		System.out.println();
//		root2.print();
		
		System.out.println(isSubTree(root1, root2));			
	}
	
	// 4.8
	public static void findSums(Node node, ArrayList<Integer> path, int partial, int total) {
		
		if(node == null)
			return;
		
		path.add(node.value);
		partial += node.value;
		
		if(partial == total)
			System.out.println(path);
		
		findSums(node.left, path, partial, total);
		findSums(node.right, path, partial, total);
		
		path.remove(path.size() - 1);
	}
	
	public static void findAllPaths(Node node, int total) {
		if(node == null)
			return;
		
		findSums(node, new ArrayList<Integer>(), 0, total);
		findAllPaths(node.left, total);
		findAllPaths(node.right, total);
	}
	
	public static void testFindAllPaths() {
		int n = 14;
		int[] array = new int[n];
		for(int i = 0; i < n; i++)
			array[i] = i % 3;
		
		Node root = createBTreeFromArray(array, 0, array.length - 1);
		ArrayList<LinkedList<Node>> lists = createListsFromBTree(root);
		for(LinkedList<Node> list : lists)
			System.out.println(list);
		System.out.println("Result:");
		findAllPaths(root, 5);
	}
	
	public static void main(String[] args) {
		//testCreateBTreeFromArray(10);
		//testCreateListsFromBTree(7);
		//testIsBalanced(10);
		//testFindNext();
		testFindFirstCommonAncestor();
		//testIsSubTree();
		//testFindAllPaths();
	}
}
