import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import javafx.animation.TranslateTransition;
import javafx.scene.Group;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.util.Duration;


public class Arena {

	private Group  root;
	private int width;
	private int height;
	private int totalBombs;
	
	private static final boolean time = true;
	private static final long waitTime = 200;
	
	private TerrainCell[][] arena;
	private Robot robot;
	
	public Arena(Group root, int width, int height) {
		this.root = root;
		this.width = width;
		this.height = height;
		this.arena = new TerrainCell[height][width];
		this.robot = new Robot(0, 0);
		for(int i = 0; i < this.height; i++)
			for(int j = 0; j < this.width; j++) {
				arena[i][j] = new TerrainCell(j,i);
				root.getChildren().add(arena[i][j].getCell());
			}
		
		root.getChildren().add(robot.getRobot());
	}
	
	public int getTotalBombs() {
		return totalBombs;
	}
	
	public void setRandomBombs(int totalBombs) {
		this.totalBombs = totalBombs;
		Random rand = new Random(System.currentTimeMillis());
		int current = 0;
		while(current < totalBombs) {
			int x = rand.nextInt(width);
			int y = rand.nextInt(height);
			
			if(arena[y][x].hasBomb() || robot.isAt(x,y))
				continue;
			
			arena[y][x].setBomb(true);
			current++;
		}
	}
	
	public boolean isTicking(int x, int y) {
		
		if(x > 0 && arena[y][x-1].hasBomb())
			return true;
		if(y > 0 && arena[y-1][x].hasBomb())
			return true;
		if(x < width-1 && arena[y][x+1].hasBomb())
			return true;
		if(y < height-1 && arena[y+1][x].hasBomb())
			return true;
		
		return false;
	}
	
	public List<Pair<Integer,Integer>> getNeighbours() {
		List<Pair<Integer,Integer>> result = new ArrayList<Pair<Integer,Integer>>();
		
		int x = robot.getX();
		int y = robot.getY();
		
		if(x > 0)
			result.add(new Pair<Integer,Integer>(x-1, y));
		if(x < width-1)
			result.add(new Pair<Integer,Integer>(x+1, y));
		if(y > 0)
			result.add(new Pair<Integer,Integer>(x, y-1));
		if(y < height-1)
			result.add(new Pair<Integer,Integer>(x, y+1));
		
		return result;
	}
	
	
	public boolean move(int x, int y) {
		
		if(Math.abs(robot.getX() - x) + Math.abs(robot.getY() - y) > 1) {
			System.out.println("Mutare prea mare la ["+y+"]["+x+"]  (coordonate("+x+","+y+")");
			return false;
		}
		if(x < 0 || x >= width || y < 0 || y >= height) {
			System.out.println("Mutare in afara arenei la ["+y+"]["+x+"]  (coordonate("+x+","+y+")");
			return false;
		}
		if(arena[y][x].hasBomb()) {
			System.out.println("Robotul a murit lovit de bomba ("+y+","+x+")");
			return false;
		}
		robot.moveTo(x, y);
		return true;
	}
	
	public boolean moveAndDefuse(int x, int y) {
		boolean bomb, ret;

		bomb = arena[y][x].hasBomb();
		if(bomb)
			totalBombs--;

		arena[y][x].setBomb(false);
		
		ret = move(x,y);
		if(!ret)
			return false;
		return bomb;
	}
}
