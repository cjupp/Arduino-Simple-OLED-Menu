/*--------------------------------------------------------------------------------------------------------------------
| Simple_Menu.cpp: 
|
| Created by:     Cameron Jupp
| Date Started:   December 3, 2022
--------------------------------------------------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------------------------------------------------- |
| --------------------------------  / \  / /  / __  /  /__ __/  / ___/  / ____/ --------------------------------------- |
| -------------------------------  / /\\/ /  / /_/ /    / /    / __/    \__ \  ---------------------------------------- |
| ------------------------------  /_/  \_/  /_____/    /_/    /____/  /_____/ ----------------------------------------- |
| --------------------------------------------------------------------------------------------------------------------- |
| Last left off at:
|
| - Scrolling all the way down will place the cursor at the top
|
| - Limit characters for menu and nodes (concatenate in program)
|
|
| --------------------------------------------------------------------------------------------------------------------- */

#ifndef SIMPLE_MENU_H
#define SIMPLE_MENU_H

// -------------------------------------------------------------------------------------------------------------------- //
// --------------------------- /    \   / ___/  / ___/  /_  _/  / \  / /  / ___/  / ____/ ----------------------------- //
// -------------------------- / /_\ /  / __/   / __/     / /   / /\\/ /  / __/    \__ \  ------------------------------ //
// ------------------------- /_____/  /____/  /_/      /___/  /_/  \_/  /____/  /_____/ ------------------------------- //
// -------------------------------------------------------------------------------------------------------------------- //

#define MAX_CHAR        16
#define MAX_NODES       6
#define MAX_MENUS       10

#define SUB_NODE        1
#define ACT_NODE        2

#define MENU            0
#define NODE            1



// -------------------------------------------------------------------------------------------------------------------- //
// -------------------------- / ___/  / /     / __  /  / _ /    / _\      / /     / ____/ ----------------------------- //
// ------------------------- / /_//  / /__   / /_/ /  / _  \   / /_\\    / /__    \__ \  ------------------------------ //
// ------------------------ /____/  /____/  /_____/  /_____/  /_/   \\  /____/  /_____/ ------------------------------- //
// -------------------------------------------------------------------------------------------------------------------- //


// -------------------------------------------------------------------------------------------------------------------- //
// --------------------------- / ___/  / /     /  \      / ____/  / ____/  / ___/  / ____/ ---------------------------- //
// -------------------------- / /__   / /__   / /_\\     \__ \    \__ \   / __/    \__ \  ----------------------------- //
// ------------------------- /____/  /____/  /_/   \\  /_____/  /_____/  /____/  /_____/ ------------------------------ //
// -------------------------------------------------------------------------------------------------------------------- //

/*  ---------------------------------------------------------------------------------------------------------------------/ 
|  -------------------------------------------------- NODE CLASS -------------------------------------------------------/
| ---------------------------------------------------------------------------------------------------------------------/
| menuNode: A class for representing each option (node) within a menu. The class stores information such as
| the type of node, it's name, the index of a menu it might link to, and a function pointer. An ACT node triggers a function, while a SUB node links to
| another menu.
|        -------------------------------------------------------------------------------------------------------
| Notes/Future Changes:
| - 
|        -------------------------------------------------------------------------------------------------------
| Created by: Cameron Jupp
| Date:       December 14, 2022
| Edited:     {Date}  
|-----------------------------------------------------------------------------------------------------------------------/
|----------------------------------------------------------------------------------------------------------------------/
|--------------------------------------------------------------------------------------------------------------------*/
class menuNode
{
  public:

  // Name of the node
  char name[MAX_CHAR];

  // Tells if a node triggers an action or opens another menu. 0 if unconfigured
  char nodeType = 0;

  // Stores the menu that the node might call if it is configured as a submenu node
  char menuCall = 0;

  // The function pointer for the node if is configured as an action node
  void (*choose)(void);

  void config(char * namePtr, char type, void (*functPtr) (void));
  void setName(char * namePtr);
  void link(char menuNum);
  

};


/*  ---------------------------------------------------------------------------------------------------------------------/ 
|  -------------------------------------------------- NODE CLASS -------------------------------------------------------/
| ---------------------------------------------------------------------------------------------------------------------/
| menu: The menu class holds an array of node objects. It also has it's own name, a variable to keep track of how
| many nodes have been initialized, and a link to the node that triggers it (for navigating backwards)
|        -------------------------------------------------------------------------------------------------------
| Notes/Future Changes:
| - 
|        -------------------------------------------------------------------------------------------------------
| Created by: Cameron Jupp
| Date:       December 14, 2022
| Edited:     {Date}  
|-----------------------------------------------------------------------------------------------------------------------/
|----------------------------------------------------------------------------------------------------------------------/
|--------------------------------------------------------------------------------------------------------------------*/
class menu
{
  public:

  // The name of the menu
  char name[MAX_CHAR];

  // Array of node objects to populate menu
  menuNode node[MAX_NODES];
  
  // Keeps track of how many nodes are configured
  char nodeCount = 0;

  // Stores the parent node that links to the menu for when the "go back" action is called
  char backLink[2];

void addNode(char * nodeName, char nodeType, void (*functPtr) (void));
void setName(char * namePtr);
void build(char index);
void delNode();

};

/*  ---------------------------------------------------------------------------------------------------------------------/ 
|  -------------------------------------------------- NODE CLASS -------------------------------------------------------/
| ---------------------------------------------------------------------------------------------------------------------/
| menuFrame: The menu frame holds all of the menus and keeps track of user input and current menu/node. It also
| keeps track of the currently configured menu and node to make building a menu easier and more user friendly. This
| class is responsible for displaying the current state of the menus and triggering changes based on user input
|        -------------------------------------------------------------------------------------------------------
| Notes/Future Changes:
| - 
|        -------------------------------------------------------------------------------------------------------
| Created by: Cameron Jupp
| Date:       December 14, 2022
| Edited:     {Date}  
|-----------------------------------------------------------------------------------------------------------------------/
|----------------------------------------------------------------------------------------------------------------------/
|--------------------------------------------------------------------------------------------------------------------*/
// Holds all of the menus and keeps track of user input and indexing
// also builds/displays the menus
class menuFrame
{
  public:

  // Array to hold all of the menus
  menu menuList[MAX_MENUS];

  // Keeps track of the up/down position on the menu
  char nodeIndex = 0;
  
  // Keeps track of the current menu
  char currentMenu = 0;

  // During configuration, keeps track of the most recently created menu
  char configIndex = 0;

  // During configuration, keeps track of the node most recently created for linking purposes
  char nodeLinkIndex = 0;

  void build();
  void addMenu (char * menuName, char index);
  void addNode(char * nodeName, char nodeType, void (*functPtr) (void));
  void manAddNode(char * nodeName, char menuNum, char nodeType, void (*functPtr) (void));
  void delNode();
  void linkNode(char menuNum);
  void up();
  void down();
  void choose();
  void back();

};

// -------------------------------------------------------------------------------------------------------------------- //
// -------------------  / ___/  / / //  / \  / /  / ___/ /__  __/  /_  _/  / __  /  / \  / /  / ____/ ----------------- //
// ------------------  / __/   / /_//  / /\\/ /  / /__     / /      / /   / /_/ /  / /\\/ /   \__ \ ------------------- //
// -----------------  /_/     /____/  /_/  \_/  /____/    /_/     /___/  /_____/  /_/  \_/  /_____/ ------------------- //
// -------------------------------------------------------------------------------------------------------------------- //


#endif