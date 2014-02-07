package interview;

import java.util.ArrayList;
import java.util.List;

public class SmallestRange {
	
	/**
	 * You have k lists of sorted integers. Find the smallest range that includes at least one number from each of the k lists.
	 *  
	 * For example,
	 * List 1: [4, 10, 15, 24, 26] 
	 * List 2: [0, 9, 12, 20]
	 * List 3: [5, 18, 22, 30]
	 * 
	 * The smallest range here would be [20, 24] as it contains 24 from list 1, 20 from list 2, and 22 from list 3.
	 */
	public static void getSmallestRange(int[][] sortedLists) {
		
		int[] indexes = new int[sortedLists.length];
		int range;
		int min_range = Integer.MAX_VALUE;
		int best_start = 0;
		int best_end = 0;
		int start = 0;
		int end = 0;
		
		do {

			for(int i = 0; i < sortedLists.length; i++) {
				int number = sortedLists[i][indexes[i]];
				if(sortedLists[start][indexes[start]] > number)
					start = i;
				if(sortedLists[end][indexes[end]] < number)
					end = i;
			}

			range = sortedLists[end][indexes[end]] - sortedLists[start][indexes[start]];
			
			if(range < min_range) {
				best_start = sortedLists[start][indexes[start]];
				best_end = sortedLists[end][indexes[end]];
				min_range = range;
			}
			
			indexes[start]++;
			
		} while(indexes[start] < sortedLists[start].length);
		
		System.out.println("Best range is " + min_range + " (" + best_start + ", " + best_end + ")");
		
	}
	
	public static void testGetSmallestRange() {
		int[][] list = {
				{4, 10, 15, 24, 26},
				{0, 9, 12, 20},
				{5, 18, 22, 30},
				{25}
		};
		
		getSmallestRange(list);
	}
	
	public static List<Integer> removeDuplicates(List<Integer> list) {
		List<Integer> result = new ArrayList<Integer>();
		
		for(Integer i : list) {
			result.add(i);
		}
		
		return result;
	}
	
	public static void main(String[] args) {
	}

}
