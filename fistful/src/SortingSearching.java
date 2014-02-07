import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

import com.sun.xml.internal.bind.v2.runtime.unmarshaller.XsiNilLoader.Array;


public class SortingSearching {
	
	// 9.1
	public static void merge(int[] a, int na, int[] b, int nb) {
		int i = na - 1;
		int j = nb - 1;
		int k = na + nb - 1;
		
		while(i >= 0 && j >= 0) {
			if(a[i] < b[j])
				a[k--] = b[j--];
			else
				a[k--] = a[i--];
		}
		
		while(j >= 0) {
			a[k--] = b[j--];
		}
	}
	
	public static void testMerge() {
		int maxsize = 100;
		int step = 10;
		int[] a, b;
		int na, nb;
		
		for(int size = step; size < maxsize; size += step) {
			
			a = new int[maxsize];
			na = size;
			b = new int[maxsize - size];
			nb = maxsize - size;
			
			System.out.println("Testing with a[" + na + "] and b[" + nb + "]");
			
			for(int i = 0; i < na; i++)
				a[i] = (int)(Math.random() * 1000.0);
			for(int i = na; i < a.length; i++)
				a[i] = 10000;
			Arrays.sort(a);
			
			for(int i = 0; i < nb; i++)
				b[i] = (int)(Math.random() * 1000.0);
			Arrays.sort(b);
			
			merge(a, na, b, nb);
			
			for(int i = 0; i < a.length - 1; i++)
				if(a[i] > a[i+1])
					System.out.println("Arrays not merged properly!");
			
			for(int i = 0; i < a.length; i++) {
				System.out.print(a[i] + " ");
			}
			System.out.println();
			System.out.println();
		}
		
	}
	
	// 9.2
	public static void sortAnagrams(String[] a) {
		
		class AnagramComparator implements Comparator<String> {
			@Override
			public int compare(String o1, String o2) {
				char[] s1, s2;
				s1 = o1.toCharArray();
				s2 = o2.toCharArray();
				
				Arrays.sort(s1);
				Arrays.sort(s2);
				
				return (new String(s1)).compareTo(new String(s2));
			}
		}
		
		Arrays.sort(a, new AnagramComparator());
	}
	
	public static void testSortAnagrams() {
		ArrayList<String> strings = new ArrayList<String>();
		strings.add("car");
		strings.add("acr");
		strings.add("arbadacarba");
		strings.add("cbr");
		strings.add("abracadabra");
		strings.add("rac");
		strings.add("nigel");
		
		String[] strs = new String[strings.size()];
		strs = strings.toArray(strs);
		
		sortAnagrams(strs);
		
		for(String s: strs)
			System.out.println(s);
	}
	
	// 9.5
	public static int findSparseStringIndex(String[] strs, String s, int lower, int upper) {
		int mid, mid_lower, mid_upper;
		
		System.out.println(lower + " " + upper);
		
		if(lower > upper)
			return -1;
		
		mid = (upper - lower) / 2;
		mid_lower = mid_upper = mid;
		
		while(strs[mid_lower].equals("") && mid_lower >= lower)
			mid_lower--;
		
		if(strs[mid_lower].equals("")) {
			while(strs[mid_upper].equals("") && mid_upper <= upper)
				mid_upper++;
			if(strs[mid_upper].equals(""))
				return -1;
			mid = mid_upper;
		} else {
			mid = mid_lower;
		}
		
		int cmp = strs[mid].compareTo(s);
		if(cmp == 0)
			return mid;
		else if(cmp < 0)
			return findSparseStringIndex(strs, s, mid_upper + 1, upper);
		else
			return findSparseStringIndex(strs, s, lower, mid_lower - 1);
	}
	
	public static void testFindSparseStringIndex() {
		String[] strings1 = {"at", "", "", "", "ball", "", "", "car", "", "", "dad", "", ""};
		String[] strings2 = {"at", "", "", "", "ball", "car", "", "", "dad", "", ""};
		
		System.out.println("Search for \"ball\": "
				+ findSparseStringIndex(strings1, "ball", 0, strings1.length - 1));
		System.out.println("Search for \"ballcar\": "
				+ findSparseStringIndex(strings2, "ballcar", 0, strings2.length - 1));
	}
	
	// 9.6
	public static boolean findSortedMatrix(int[][] matrix, int elem, int n, int m) {
		int row = 0;
		int col = n - 1;
		while(row < m && col >= 0) {
			if(matrix[row][col] == elem)
				return true;
			else if(matrix[row][col] > elem)
				col--;
			else
				row++;
		}
		return false;
	}
	
	public static void testFindSortedMatrix() {
		int[][] m = {
				{-10, -5, -2, -1},
				{-9, -4, 0, 6},
				{-7, -3, 1, 8},
				{4, 9, 11, 12}
				};
		for(int i = 0; i < 16; i++)
			if(findSortedMatrix(m, m[i % 4][i / 4], 4, 4) == false) {
				System.out.println("findSortedMatrix failed to find");
				System.out.println("Test failed!");
				return;
			}
		System.out.println("Test successful!");
	}
	
	public static void main(String[] args) {
		//testMerge();
		//testSortAnagrams();
		//testFindSortedMatrix();
		testFindSparseStringIndex();
	}

}
