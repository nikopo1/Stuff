package interview;

public class Primes {

	public static int getPrime(int index, int max) {
		
		boolean[] prime = new boolean[max];
		
		for(int i = 0; i < max; i++)
			prime[i] = true;
		
		for(int i = 2; i < Math.sqrt(max); i++) {
			if(prime[i]) {
				int square_i = i * i;
				for(int j = square_i; j < max; j += i)
					prime[j] = false;
			}
		}
		
		int count = 0;
		for(int i = 2; i < max; i++)
			if(prime[i]) {
				count++;
				if(count == index)
					return i;
			}
		return -1;
	}
	
	public static void main(String[] args) {
		
		System.out.println("Prime number 1 is " + getPrime(1, 1000000));
		System.out.println("Prime number 6 is " + getPrime(6, 1000000));
		System.out.println("Prime number 10001 is " + getPrime(10001, 1000000));
		
	}
	
}
