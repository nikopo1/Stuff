import javafx.animation.AnimationTimer;
import javafx.animation.KeyValue;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.event.EventType;
import javafx.geometry.Insets;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.layout.HBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;
import javafx.util.Duration;

public class Test extends Application {

	private static final double boxOuterSize = 50;
	private static final double boxInnerSize = 48;
	private static final double boxCornerRadius = 20;

	private Stage applicationStage;
	private Scene applicationScene;

	private static double   sceneWidth  = 1024;
	private static double   sceneHeight = 800;
	private static HBox     container = new HBox();
	private static Group    root = new Group();
	private Rectangle[] rectangles = new Rectangle[10];
	private AnimationTimer[] animationtimers = new AnimationTimer[10];
	
	private int i;

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

		for(i=0; i<10; i++) {
			Rectangle r = new Rectangle();
			r.setFill(Color.BLUE);
			r.setX(i * boxOuterSize);
			r.setY(0);
			r.setWidth(boxInnerSize);
			r.setHeight(boxInnerSize);
			r.setArcHeight(boxCornerRadius);
			r.setArcWidth(boxCornerRadius);
			r.setSmooth(true);
			rectangles[i] = r;
			root.getChildren().add(rectangles[i]);
			
			KeyValue keyValue = new KeyValue(r.fillProperty(), Color.RED);
			Duration duration = Duration.millis(2000);
			
			animationtimers[i] = new AnimationTimer() {
				final int index = i;
				@Override
				public void handle(long arg0) {
					rectangles[index].setFill(Color.RED);
				}
			};
		}
		
        
        //one can add a specific action when the keyframe is reached
        EventHandler onFinished = new EventHandler<ActionEvent>() {
            public void handle(ActionEvent t) {
                 
            }
        };
 
  KeyFrame keyFrame = new KeyFrame(duration, onFinished , keyValueX, keyValueY);
 
        //add the keyframe to the timeline
        timeline.getKeyFrames().add(keyFrame);
 
        timeline.play();
        timer.start();

		container.getChildren().add(root);
		Button startButton = new Button("Start");
		startButton.setOnMouseClicked(new EventHandler<Event>() {
			@Override
			public void handle(Event arg0) {
				for(int i=0; i<10; i++) {
					animationtimers[i].start();
//					try {
//						Thread.sleep(500);
//					} catch (InterruptedException e) {
//						// TODO Auto-generated catch block
//						e.printStackTrace();
//					}
				}
			}
		});
		container.getChildren().add(startButton);
		

		applicationStage.show();
	}

	public static void main(String[] args) {
		launch(args);
	}
}