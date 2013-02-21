import javafx.animation.TranslateTransition;
import javafx.scene.shape.Circle;
import javafx.util.Duration;


public class MovementTransition implements Runnable {

	private static final double boxOuterSize = 50;
	private static final double boxInnerSize = 48;
	private static final double robotSphereRadius = 10;
	private static final double waitTime = 750;
	
	private Circle robot;
	private int x, y;
	
	public MovementTransition(Circle r, int x, int y) {
		this.robot = r;
		this.x = x;
		this.y = y;
	}
	
	@Override
	public void run() {
		TranslateTransition transition = new TranslateTransition(Duration.millis(waitTime), robot);
		transition.setByX(x * boxOuterSize + boxInnerSize/2);
		transition.setByY(y * boxOuterSize + boxInnerSize/2);
		transition.play();
		System.out.println("Movement...");
	}

}
