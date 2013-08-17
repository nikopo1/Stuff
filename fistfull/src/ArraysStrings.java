
public class ArraysStrings {

	// Utils
	public static void printMatrix(int[][] m) {
		for(int i = 0; i < m.length; i++) {
			for(int j = 0; j < m[i].length; j++)
				System.out.print(m[i][j] + " ");
			System.out.println();
		}
	}

	// Problems
	// 1.1
	public static boolean hasUniqueCharacters(String s) {

		byte[] b = new byte[32];
		char[] array = s.toCharArray();

		for(int i = 0; i < array.length; i++) {
			char c = array[i];
			int bytepos = c/8;
			int offset = c - bytepos * 8;
			byte mask = (byte) (1 << offset);
			if((b[bytepos] & mask) != 0)
				return false;
			else
				b[bytepos] |= mask;
		}
		return true;
	}
	
	public static void testHasUniqueCharacters() {
		String s = "abcd1ef?gabgfsred";
		String v = "abababababa";
		System.out.println(hasUniqueCharacters(s));
		System.out.println(hasUniqueCharacters(v));
	}
	
	// 1.2
	public static String reverseString(String s) {
		char[] array = s.toCharArray();
		char aux;
		int middle = array.length / 2;
		for(int i = 0; i < middle; i++) {
			aux = array[i];
			array[i] = array[array.length-1 - i];
			array[array.length-1 - i] = aux;
		}
		return String.valueOf(array);
	}
	
	public static void testReverseString() {
		String s = "abcd1ef?gabgfsred";
		String v = "abababababa";
		System.out.println(reverseString(s));
		System.out.println(reverseString(v));
	}
	
	// 1.3
	public static String removeAllDuplicates(String s) {
		char[] str = s.toCharArray();
		int last = 1;
		for(int i = 1; i < str.length; i++) {
			int j;
			for(j = 0; j < last; j++)
				if(str[i] == str[j])
					break;
			if(j == last) {
				str[last] = str[i];
				++last;
			}
		}

		str[last] = 0;
		return String.valueOf(str);
	}
	
	public static void testRemoveAllDuplicates() {
		String s = "abcd1ef?gabgfsred";
		String v = "abababababa";
		System.out.println(removeAllDuplicates(s));
		System.out.println(removeAllDuplicates(v));
	}

	// 1.6
	public static void turnImage(int[][] m) {

		int i, j, aux;
		int len = m.length - 1;
		int middle = m.length/2;
		for(i = 0; i <= middle; i++) {
			for(j = 0; j < len - 2*i; j++) {
				aux = m[i][i+j];
				m[i][i+j] = m[i+j][len-i];
				m[i+j][len-i] = m[len-i][len-i-j];
				m[len-i][len-i-j] = m[len-i-j][i];
				m[len-i-j][i] = aux;
			}
		}
	}

	public static void testTurnImage() {
		int[][] image = new int[10][10];
		int  p = 0;
		for(int i = 0; i < image.length; i++)
			for(int j = 0; j < image[i].length; j++)
				image[i][j] = p++;
		printMatrix(image);
		System.out.println();
		turnImage(image);
		printMatrix(image);
	}	
	
	// 1.7
	public static void clearWithZeros(int[][] matrix) {
		int m = matrix.length;
		int n = matrix[0].length;
		
		boolean[] rows = new boolean[m];
		boolean[] columns = new boolean[n];
		// find zeros
		for(int i = 0; i < m; i++)
			for(int j = 0; j < n; j++)
				if(matrix[i][j] == 0) {
					rows[i] = true;
					columns[j] = true;
				}
		// set columns and rows with zeros
		for(int i = 0; i < m; i++)
			for(int j = 0; j < n; j++)
				if(rows[i] || columns[j])
					matrix[i][j] = 0;
	}
	
	public static void testClearWithZeros() {
		int[][] matrix = { {3,4,0,1}, {0,1,1,2},{5,6,3,5} };
		printMatrix(matrix);
		clearWithZeros(matrix);
		System.out.println();
		printMatrix(matrix);
	}

	
	public static void main(String[] args) {
		testClearWithZeros();
	}
}
