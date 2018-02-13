ArrayList<Node> nodes;
int sortType = 0;
int positionType = 4;

int NUM_NODE = 20;
int CELL_X_NUM = 5;
int CELL_Y_NUM = 4;

// import UDP library
char LED_HEADER = 'L';
char ID_PACKET_OFFSET = '0';
import hypermedia.net.*;
UDP udp;  // define the UDP object
int SRC_PORT = 4001;
String DST_HOST = "localhost";
int DST_PORT = 4000;

void settings() {
  //size(1200, 800);
  fullScreen();
}

void setup() {
  surface.setResizable(true); //for processing-3
  surface.setTitle("Visualizer");

  init_dynamicButton();
  nodes_init(NUM_NODE);

  udp = new UDP( this, SRC_PORT);
  udp.listen( true );
}

void draw() {
  int pastTime = millis();
  background(0);

  fill(255);
  textAlign(LEFT, TOP);
  textSize(height / 10);
  text("Visualizer", 5, 0);
  displaySortType(5, height / ceil(sqrt(nodes.size())) * 5 / 8);

  nodes_display();

  loop_dynamicButton();

  ////loop time and framerate drawing <===
  //int interval = millis() - pastTime;
  //println("one loop by millis() interval: " + interval + "ms frameRate: " + frameRate);
  ////===> loop time and framerate drawing
}

void keyPressed() {
  switch(key) {
  case 'p' :
    positionType++;
    if (positionType > 5) positionType = 0;
    break;  
  case 's' :
    sortType++;
    if (sortType > 2) sortType = 0;
    changeSortType();
    break;
  case 27:
    exit();
  default: 
    break;
  }
}

void mousePressed() {
  mouseClicked_dynamicButton();
}

void sendUdp(String _data, String _ip, int _port) {
  _data = _data+";\n"; //     // formats the message for Pd
  udp.send( _data, _ip, _port );
}

// udp connection receive
void receive( byte[] data, String ip, int port ) {
  String message = new String( data );
  println( "receive: \""+message+"\" from "+ip+" on port "+port );

  // assume "LIRRRGGGBBB"
  if (message.length() >= 11 && message.charAt(0) == LED_HEADER) { 
    int tmp_id = int(message.charAt(1) - ID_PACKET_OFFSET);
    int tmp_red = int(message.substring(2, 5));
    int tmp_green = int(message.substring(5, 8));
    int tmp_blue = int(message.substring(8, 11));
    String tmp_name = message.substring(11, message.length());

    println(tmp_id, tmp_red, tmp_green, tmp_blue);

    for (Node tempNode : nodes) {
      if (tempNode.nodeid == tmp_id) {
        tempNode.updateValue(tmp_red, tmp_green, tmp_blue, tmp_name);
      }
    }
  }
}
