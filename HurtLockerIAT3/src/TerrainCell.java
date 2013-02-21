import javafx.animation.FillTransition;
import javafx.animation.TranslateTransition;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.util.Duration;

public class TerrainCell {

	private static final double boxOuterSize = 50;
	private static final double boxInnerSize = 48;
	private static final double boxCornerRadius = 20;
	private static final double waitTime = 400;
	
	private Rectangle cell;
	private boolean bomb;
	
	public TerrainCell(int x, int y) {
		this.cell = getRectangle(x,y, false);
		this.bomb = false;
	}
	
	public TerrainCell(int x, int y, boolean bomb) {
		this.cell = getRectangle(x,y,bomb);
		this.bomb = bomb;
	}

	public Rectangle getCell() {
		return cell;
	}

	public void setCell(Rectangle cell) {
		this.cell = cell;
	}

	public boolean hasBomb() {
		return bomb;
	}

	public void setBomb(boolean bomb) {
		this.bomb = bomb;
		if(bomb) {
			
			FillTransition transition = new FillTransition(Duration.millis(waitTime), cell);
//			cell.setFill(Color.RED);
			transition.setToValue(Color.RED);
			transition.play();
		}
		else {
			
			FillTransition transition = new FillTransition(Duration.millis(waitTime), cell);
//			cell.setFill(Color.BURLYWOOD);
			transition.setToValue(Color.BURLYWOOD);
			transition.play();
		}
	}
	
	private Rectangle getRectangle(int x, int y, boolean bomb) {
		Rectangle r = new Rectangle();
		if(bomb)
			r.setFill(Color.RED);
		else
			r.setFill(Color.BURLYWOOD);
		r.setX(x * boxOuterSize);
		r.setY(y * boxOuterSize);
		r.setWidth(boxInnerSize);
		r.setHeight(boxInnerSize);
		r.setArcHeight(boxCornerRadius);
		r.setArcWidth(boxCornerRadius);
		r.setSmooth(true);
		return r;
	}
}
