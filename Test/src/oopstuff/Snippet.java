package oopstuff;
class Human {
	private int money;
	Human(int money) {
		this.money = money;
	}
	
	void showMeTheMoney(Human otherGuy) {
		System.out.println(otherGuy.money);
	}
}

public class Snippet {
	public static void main(String[] args) {
		Human gigi = new Human(100);
		Human vasile = new Human(200);
		gigi.showMeTheMoney(vasile);
	}
}