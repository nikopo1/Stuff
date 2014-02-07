import java.util.ArrayList;
import java.util.Arrays;


public class Moderate {
	
	// 19.3
	public static int getNumFactorialTrailingZeros(int n) {
		int count = 0;
		for(int i = 5; n / i > 0; i *= 5)
			count += n / i;
		return count;
	}
	
	// 19.4
	public static int getMaximum(int a, int b) {
		int c = a - b;
		return a - ((c >> 31) & 0x1) * c;
	}
	
	public static void testGetMaximum() {
		System.out.println("max(-1, -2) = " + getMaximum(-1, -2));
		System.out.println("max( 1, 2) = " + getMaximum(1, 2));
		System.out.println("max(-1, 2) = " + getMaximum(-1, 2));
		System.out.println("max(1, -2) = " + getMaximum(1, -2));
	}
	// 19.6
	public static String getIntegerString(int n) {
		
		String[] numbers = {
				"Zero", "One", "Two", "Three", "Four", "Five",
				"Six", "Seven", "Eight", "Nine", "Ten",
				"Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
				"Sixteen", "Seventeen", "Eighteen", "Nineteen"
		};
		String[] tenths = {
				"Ten", "Twenty", "Thirty", "Fourty", "Fifty",
				"Sixty", "Seventy", "Eighty", "Ninety"
		};
		String[] thousands = {"", "Thousand", "Million"};
		
		if(n == 0)
			return numbers[n];
		
		String result = "";
		int k = 0;
		
		while(n > 0) {
			
			result = thousands[k++] + " " + result;
			int thousand = n % 1000;
			int under = n % 100;
			
			int hundred = thousand / 100;
			int tenth = (thousand % 100)/ 10;
			int unit = thousand % 10;
			
			if(under > 0 && under < 20)
				result = numbers[tenth] + " " + result;
			else if(under >= 20) {
				if(unit > 0)
					result = numbers[unit] + " " + result;
				if(tenth > 0)
					result = tenths[tenth - 1] + " " + result;
			}
			if(hundred > 0)
				result = numbers[hundred] + " Hundred and " + result;
			n = n / 1000;
		}
		
		return result;
	}
	
	public static void testGetIntegerString() {
		System.out.println(getIntegerString(0));
		System.out.println(getIntegerString(123943));
		System.out.println(getIntegerString(123943321));
	}
	
	// 19.11
	public static void findPairsWithSum(int[] array, int sum) {
		Arrays.sort(array);
		int i = 0;
		int j = array.length - 1;
		int c;
		
		while(i < j) {
			c = array[i] + array[j];
			if(c == sum) {
				System.out.println(array[i] + ", " + array[j]);
				if(i + 1 < j && array[i] == array[i + 1])
					i++;
				else if(j - 1 > i && array[j] == array[j - 1])
					j--;
				else {
					i++;
					j--;
				}
			} else if(c > sum) {
				j--;
			} else {
				i++;
			}
		}
	}
	
	public static void testFindPairsWithSum() {
		int a[] = { -3, -9, 10, 2, 1, 4, 2, 11};
		findPairsWithSum(a, 1);
		findPairsWithSum(a, 4);
	}
	
	public static void main(String[] args) {
		testGetMaximum();
		testGetIntegerString();
		testFindPairsWithSum();
	}
}
