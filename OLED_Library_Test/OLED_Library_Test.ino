#include <Simple_Menu.h>

#include <Arduino.h>
menuFrame mainMenu;

void setup() 
{

Serial.begin(115200);

oledSystemInit();

  //Main menu
  mainMenu.addMenu("Menu 1", 0);
  mainMenu.addNode("Menu 1 Node 1", SUB_NODE, NULL);
  mainMenu.linkNode(1);
  
  mainMenu.addNode("Menu 1 Node 2", SUB_NODE, NULL);
  mainMenu.linkNode(2);


  mainMenu.addNode("Menu 1 Node 3", SUB_NODE, NULL);
  mainMenu.linkNode(3);


  //Submenu 1
  mainMenu.addMenu("SubM 1", 1);
  mainMenu.addNode("SubM1 Node 1", ACT_NODE, &testFunct);
  mainMenu.addNode("SubM1 Node 2", ACT_NODE, &testFunct);
  mainMenu.addNode("SubM1 Node 3", ACT_NODE, &testFunct);
  mainMenu.addNode("SubM1 Node 4", ACT_NODE, &testFunct);

  //Submenu 2
  mainMenu.addMenu("SubM 2", 2);
  mainMenu.addNode("SubM2 Node 1", ACT_NODE, &testFunct);
  mainMenu.addNode("SubM2 Node 2", ACT_NODE, &testFunct);
  mainMenu.addNode("SubM2 Node 3", ACT_NODE, &testFunct);
  mainMenu.addNode("SubM2 Node 4", ACT_NODE, &testFunct);
  mainMenu.addNode("SubM2 Node 5", ACT_NODE, &testFunct);

  //Submenu 3
  mainMenu.addMenu("SubM 3", 3);
  mainMenu.addNode("SubM3 Node 1", ACT_NODE, &testFunct);
  mainMenu.addNode("SubM3 Node 2", ACT_NODE, &testFunct);
  mainMenu.addNode("SubM3 Node 3", ACT_NODE, &testFunct);
  mainMenu.addNode("SubM3 Node 4", ACT_NODE, &testFunct);
  mainMenu.addNode("SubM3 Node 5", ACT_NODE, &testFunct);
  mainMenu.addNode("SubM3 Node 6", ACT_NODE, &testFunct);


  
}

void loop() 
{
  mainMenu.build();

  if(Serial.available())
  {
    switch(Serial.read())
    {
      case 'u':
        mainMenu.up();
      break;
        
      case 'd':
        mainMenu.down();
      break;
  
      case 'c':
        mainMenu.choose();
      break;
  
      case 'b':
      //Need to backlink nodes to menus with another variable "linkedNode"
        mainMenu.back();
      break;
  
      default:
        
      break;
    }
  }
  
  delay(100);
  
}

void testFunct()
{
  Serial.println("Function successfully called");
}
