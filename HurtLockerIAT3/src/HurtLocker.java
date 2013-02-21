
import java.util.ArrayList;
import java.util.List;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.event.EventType;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

public class HurtLocker extends Application implements EventHandler {
	
	private static final long moveDuration = 500;
	
	private Stage applicationStage;
	private Scene applicationScene;

	private static double   sceneWidth  = 1024;
	private static double   sceneHeight = 800;
	private static HBox     container = new HBox();
	private static Group    root = new Group();
	private static GridPane score = new GridPane();
	private static Arena arena; 

	private static int mapWidth = 10;
	private static int mapHeight = 10;
	private static int totalBombs = 15;
	private static int totalActions = 0;
	private static int maxActions = 100;

	private static TextField initialNumberBombsText;
	private static TextField mapWidthText;
	private static TextField mapHeightText;
	private static TextField totalbombsText;
	private static TextField totalActionsText;
	private static TextField maxActionsText;

	@Override
	public void start(Stage mainStage) throws Exception {

		applicationStage = mainStage;
		container.setSpacing(10);
		container.setPadding(new Insets(10, 10, 10, 10));

		try {
			applicationScene = new Scene(container, sceneWidth, sceneHeight);
			applicationScene.addEventHandler(EventType.ROOT,(EventHandler<? super Event>)this);
			applicationScene.setFill(Color.WHITE);

		} catch (Exception exception) {
			System.out.println ("exception : "+exception.getMessage());
		}

		applicationStage.setTitle("HurtLockerRobot - Tema 3 IA");
		applicationStage.getIcons().add(new Image("icon.png"));
		applicationStage.setScene(applicationScene);

		arena = new Arena(root, mapWidth, mapHeight);
		arena.setRandomBombs(totalBombs);

		setScore();
		container.getChildren().add(root);
		container.getChildren().add(score);
		applicationStage.show();
	}

	public void setScore() {

		Label mapWidthLabel = new Label("Width ");
		mapWidthText = new TextField("10");
		score.add(mapWidthLabel, 0, 0);
		score.add(mapWidthText, 1, 0);

		Label mapHeightLabel = new Label("Height ");
		mapHeightText  = new TextField("10");
		score.add(mapHeightLabel, 0, 1);
		score.add(mapHeightText, 1, 1);

		Label initialNumberBombsLabel = new Label("Initial number of bombs ");
		initialNumberBombsText  = new TextField("15");
		score.add(initialNumberBombsLabel, 0, 2);
		score.add(initialNumberBombsText, 1, 2);

		Label totalbombsLabel = new Label("Bombs left ");
		totalbombsText  = new TextField("15");
		totalbombsText.setEditable(false);
		score.add(totalbombsLabel, 0, 3);
		score.add(totalbombsText, 1, 3);
		
		Label totalActionsLabel = new Label("Total actions ");
		totalActionsText = new TextField("0");
		totalActionsText.setEditable(false);
		score.add(totalActionsLabel, 0, 4);
		score.add(totalActionsText, 1, 4);
		
		Label maxActionsLabel = new Label("Maximum allowed actions ");
		maxActionsText = new TextField("100");
		score.add(maxActionsLabel, 0, 5);
		score.add(maxActionsText, 1, 5);

		Button startButton = new Button("Start");
		startButton.setOnMouseClicked(new EventHandler<Event>() {
			@Override
			public void handle(Event arg0) {
				totalActions = 0;
				totalBombs = Integer.parseInt(initialNumberBombsText.getText().toString());
				mapWidth = Integer.parseInt(mapWidthText.getText().toString());
				mapHeight = Integer.parseInt(mapHeightText.getText().toString());
				maxActions = Integer.parseInt(maxActionsText.getText().toString());
				arena = new Arena(root, mapWidth, mapHeight);
				arena.setRandomBombs(totalBombs);
				totalbombsText.setText(totalBombs+"");
				new DFSClass().start();
			}
		});
		score.add(startButton, 0, 6);
	}

	private static class DFSClass extends Thread {

		Pair<Integer,Integer> n;
		Pair<Integer,Integer> currentNode;
		boolean alive = true;
		
		public boolean explore(Pair<Integer,Integer> node, List<Pair<Integer,Integer>> visited) {
			//System.out.println("Exploring "+node);
			boolean finished = false;
			boolean ticking  = false;
			if(arena.getTotalBombs() == 0)
				return true;
			if(!alive || totalActions > maxActions)
				this.stop();

			List<Pair<Integer,Integer>> neighbours = arena.getNeighbours();

			for(int i=0; i<neighbours.size(); i++) {
				n = neighbours.get(i);
				
				if(!visited.contains(n)) {
					ticking = arena.isTicking(node.getVal1(), node.getVal2());
					if(ticking) { // daca se aude o bomba prin apropiere
						visited.add(n); // atunci adauga ca vizitat doar nodul prin care am trecut
						Platform.runLater(new Runnable() {
							@Override
							public void run() {
								boolean defused = arena.moveAndDefuse(n.getVal1(), n.getVal2());
								if(defused)
									totalbombsText.setText(arena.getTotalBombs()+"");
								totalActions+=2;
								totalActionsText.setText(totalActions+"");
							}
						});
					}
					else { // daca nu se aude nicio bomba, inseamna ca in niciuna din casutele alaturate nu se afla vreo
						// bomba, deci le putem considera vizitate
						visited.addAll(neighbours);
						Platform.runLater(new Runnable() {
							@Override
							public void run() {
								alive = arena.move(n.getVal1(), n.getVal2());
								totalActions++;
								totalActionsText.setText(totalActions+"");
							}
						});
					}
					
					try {
						Thread.sleep(moveDuration);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					
					finished = explore(n, visited);

					if(finished)
						return true;
					
					currentNode = node;
					// pentru a putea expanda si ceilalti vecini, trebuie sa se intoarca in nodul curent
					Platform.runLater(new Runnable() {
						Pair<Integer,Integer> returnNode = new Pair<Integer,Integer>(currentNode.getVal1(),currentNode.getVal2());
						@Override
						public void run() {
							arena.move(returnNode.getVal1(), returnNode.getVal2());
							totalActions++;
							totalActionsText.setText(totalActions+"");
						}
					});
					
					try {
						Thread.sleep(moveDuration);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}

			return false;
		}

		public void doDFS() {
			List<Pair<Integer,Integer>> visited = new ArrayList<Pair<Integer,Integer>>();
			Pair<Integer,Integer> start = new Pair<Integer,Integer>(0,0);
			visited.add(start);
			explore(start, visited);
		}

		@Override
		public void run() {
			doDFS();
		}
	}

	@Override
	public void handle(Event arg0) {
		// TODO Auto-generated method stub
	}

	public static void main(String[] args) {
		launch(args);
		System.out.println("This is the end, my faithfull friend, the end.");
	}
}
