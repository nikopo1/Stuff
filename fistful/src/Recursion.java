import java.util.ArrayList;
import java.util.Arrays;


public class Recursion {

	private static int counter = 0;
	
	// 8.3
	public static void getAllSubsets(int current, ArrayList<Integer> acc, 
			ArrayList<Integer> set, ArrayList<ArrayList<Integer>> result) {

		if( current >= set.size() )
			return;

		counter++;
		ArrayList<Integer> setwith = new ArrayList<Integer>(acc);
		setwith.add(set.get(current));
		result.add(setwith);
		getAllSubsets(current + 1, acc, set, result);
		getAllSubsets(current + 1, setwith, set, result);
	}

	public static void testGetAllSubsets() {
		int n = 8;
		ArrayList<Integer> set = new ArrayList<Integer>();
		for(int i = 0; i < n; ++i)
			set.add(i);

		ArrayList<ArrayList<Integer>> result = new ArrayList<ArrayList<Integer>>();
		getAllSubsets(0, new ArrayList<Integer>(), set, result);
		for(ArrayList<Integer> list : result)
			System.out.println(list);
		System.out.println(counter);
	}

	// 8.4
	public static void getAllPermutations(String str, ArrayList<Integer> result) {
		
		if( result.size() == str.length() ) {
			String s = new String();
			for(int i = 0; i < result.size(); i++)
				s += str.charAt(result.get(i));
			System.out.println(s);
		}
		
		for(int i = 0; i < str.length(); i++)
			if( !result.contains(i) ) {
				result.add(i);
				getAllPermutations(str, result);
				result.remove(result.size() - 1);
			}
	}

	public static void testGetAllPermutations() {
		getAllPermutations("abcd", new ArrayList<Integer>());
	}

	// Decodificare un set de cifre in a->1, b->2, ... , z->26
	public static int countDecode(int n, int last, int[] input) {

		if( last > 26 )
			return 0;
		if( n == input.length )
			return 1;
		if( n == 0)
			return countDecode( n + 1, input[n], input);

		int with = last * 10 + input[n];
		int wout = input[n];

		return countDecode( n + 1, wout, input ) + countDecode( n + 1, with, input );
	}

	public static void testCountDecode() {
		int[] array = { 1, 1, 2, 2, 3 };
		System.out.println(countDecode(0,0,array));
	}

	// 8.7
	public static int splitChange(int sum, int nom) {
		int nextnom = 0;
		switch( nom ) {
			case 25:
				nextnom = 10;
				break;
			case 10:
				nextnom = 5;
				break;
			case 5:
				nextnom = 1;
				break;
			case 1:
				return 1;
		}
		
		int total = 0;
		int noCoins = sum / nom;
		for(int i = 0; i <= noCoins; i++)
			total += splitChange(sum - i * nom, nextnom);
		return total;
	}

	public static void testSplitChange() {
		System.out.println(splitChange(20 , 25));
	}

	// 8.8
	public static boolean nonAttacking(int[] queens, int row, int column) {
		boolean test = true;
		for(int i = 0; i < column; i++) {
			// Verificare acelasi rand, oblic paralel cu a doua diag, oblic paralel cu prima diag
			if( queens[i] == row || i + queens[i] == row + column || column - i == row - queens[i]) {
				test = false;
				break;
			}
		}
		return test;
	}

	public static void doBKT(int[] queens, int current) {
		for(int i = 0; i < 8; i++) {
			queens[current] = i;
			if(nonAttacking(queens, i, current)) {
				if( current == 7 ) {
					for(int j = 0; j < 8; j++)
						System.out.print(queens[j] + " ");
					System.out.println();
				}
				else
					doBKT(queens, current + 1);
			}
		}
	}

	public static void testDoBKT() {
		doBKT(new int[8], 0);
	}

	public static void swap(int a, int b) {
		System.out.println("Before: a = "+a+" , b = "+b);
		a = a + b - (b = a);
		System.out.println("After:  a = "+a+" , b = "+b);
	}

	// 19.7
	public static void maximumSequenceSum(int[] array) {
		int maxsum = 0, sum = 0;
		int startnew = 0, start = 0, end = -1;
		
		for(int i = 0; i < array.length; i++) {
			if( sum < 0) {
				sum = 0;
				startnew = i;
			}
			sum += array[i];
			if( sum > maxsum ) {
				start = startnew;
				end = i;
				maxsum = sum;
			}
		}
		System.out.println("MaxSum = " + maxsum + " - [" + start + "," + end + "]");
	}

	public static void testMaximumSequenceSum() {
		int[] array = { 2, -8, 3, -2, 4, -10 };
		int[] array2 = { -2, -8, -3, -2, -4, -10 };
		maximumSequenceSum(array);
		maximumSequenceSum(array2);
	}

	// Given an array of integers.
	// Find two disjoint contiguous sub-arrays such that the absolute difference
	// between the sum of two sub-array is maximum.
	// * The sub-arrays should not overlap.
	public static int maximumAbsoluteDifference(int[] array) {
		int pos_s = 0, neg_s = 0;
		int i, best = 0;
		int[] max = new int[array.length];
		int max_s = 0;
		int[] min = new int[array.length];
		int min_s = 0;

		for(i = 0; i < array.length; i++) {
			if(pos_s < 0)
				pos_s = 0;
			if(neg_s > 0)
				neg_s = 0;
			pos_s += array[i];
			neg_s += array[array.length-1 - i];
			if(pos_s > max_s)
				max_s = pos_s;
			if(neg_s < min_s)
				min_s = neg_s;
			max[i] = max_s;
			min[array.length-1 - i] = min_s;
		}

		for(i = 0; i < array.length - 1; i++) {
			if(max[i] - min[i+1] > best)
				best = max[i] - min[i+1];
//			System.out.print("max[" + i + "]=" + max[i] + ", min[" + (i+1) + "]=" + min[i+1]);
//			System.out.println(" best=" + best);
		}

		max_s = 0;
		min_s = 0;
		pos_s = 0;
		neg_s = 0;
		for(i = 0; i < array.length; i++) {
			if(pos_s < 0)
				pos_s = 0;
			if(neg_s > 0)
				neg_s = 0;
			neg_s += array[i];
			pos_s += array[array.length-1 - i];
			if(pos_s > max_s)
				max_s = pos_s;
			if(neg_s < min_s)
				min_s = neg_s;
			min[i] = min_s;
			max[array.length-1 -i] = max_s;
		}

		for(i = 0; i < array.length -1; i++) {
			if(max[i+1] - min[i] > best)
				best = max[i+1] - min[i];
//			System.out.print("max[" + (i+1) + "]=" + max[i+1] + ", min[" + i + "]=" + min[i]);
//			System.out.println(" best=" + best);
		}

		return best;
	}

	public static void testMaximumAbsoluteDifference() {
		int[] array = {2, -1, -2, 1, -4, 2, 8};
		System.out.println(maximumAbsoluteDifference(array));
	}

	public static void main(String[] args) {
		testMaximumSequenceSum();
		testMaximumAbsoluteDifference();
	}
}
