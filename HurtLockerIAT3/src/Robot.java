import javafx.animation.Timeline;
import javafx.animation.TranslateTransition;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.util.Duration;


public class Robot {

	private static final double boxOuterSize = 50;
	private static final double boxInnerSize = 48;
	private static final double robotSphereRadius = 10;
	private static final double waitTime = 400;
	
	private int x;
	private int y;
	
	private Circle robot;

	public Robot(int x, int y) {
		this.x = x;
		this.y = y;
		robot = new Circle();
		robot.setRadius(robotSphereRadius);
		robot.setFill(Color.ROYALBLUE);
		robot.setCenterX(x * boxOuterSize + boxInnerSize/2);
		robot.setCenterY(y * boxOuterSize + boxInnerSize/2);
	}

	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}

	public void moveTo(int x, int y) {
		System.out.println("Transition from ("+this.x+","+this.y+") to ("+x+","+y+")");
		TranslateTransition transition = new TranslateTransition(Duration.millis(waitTime), robot);
		transition.setByX((x - this.x) * boxOuterSize);
		transition.setByY((y - this.y) * boxOuterSize);
		this.x = x;
		this.y = y;
		//robot.setCenterX(x * boxOuterSize + boxInnerSize/2);
		//robot.setCenterY(y * boxOuterSize + boxInnerSize/2);
		transition.play();
		
	}

	public Circle getRobot() {
		return robot;
	}
	
	public boolean isAt(int x, int y) {
		return (this.x == x) && (this.y == y);
	}
}
