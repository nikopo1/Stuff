
public class Pair<T1, T2> {

	private T1 val1;
	private T2 val2;

	public Pair(T1 t1, T2 t2) {
		this.val1 = t1;
		this.val2 = t2;
	}

	public T1 getVal1() {
		return val1;
	}

	public void setVal1(T1 val1) {
		this.val1 = val1;
	}

	public T2 getVal2() {
		return val2;
	}

	public void setVal2(T2 val2) {
		this.val2 = val2;
	}

	@Override
	public boolean equals(Object o) {

		if(!(o instanceof Pair<?,?>))
			return false;
		else {
			Pair<Integer,Integer> c = (Pair<Integer,Integer>)o;
			return (val1 == c.getVal1()) && (val2 == c.getVal2());
		}
	}
	
	@Override
	public String toString() {
		return "("+val1+","+val2+")";
	}
}
