/*--------------------------------------------------------------------------------------------------------------------
| Simple_Menu.cpp: Allows for the building and navigation of menus via OLED screen or in the Serial Monitor. Can
| easily be modified for other display media
|
| Created by:     Cameron Jupp
| Date Started:   December 14, 2022
--------------------------------------------------------------------------------------------------------------------*/

#include "Simple_Menu.h"

// -------------------------------------------------------------------------------------------------------------------- //
// ----------------------------------------------------- OLED  -------------------------------------------------------- //
// -------------------------------------------------------------------------------------------------------------------- //

// This section can be moved to the Simple_Menu.h file to make the display object accessible from your main()
#include <Wire.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



// -------------------------------------------------------------------------------------------------------------------- //
// -------------------------- / ___/  / /     / __  /  / _ /    / _\      / /     / ____/ ----------------------------- //
// ------------------------- / /_//  / /__   / /_/ /  / _  \   / /_\\    / /__    \__ \  ------------------------------ //
// ------------------------ /____/  /____/  /_____/  /_____/  /_/   \\  /____/  /_____/ ------------------------------- //
// -------------------------------------------------------------------------------------------------------------------- //

 // Feel free to add your own global variables, but declaring global menu objects in your main() is recommended


// -------------------------------------------------------------------------------------------------------------------- //
// --------------------------- / ___/  / /     /  \      / ____/  / ____/  / ___/  / ____/ ---------------------------- //
// -------------------------- / /__   / /__   / /_\\     \__ \    \__ \   / __/    \__ \  ----------------------------- //
// ------------------------- /____/  /____/  /_/   \\  /_____/  /_____/  /____/  /_____/ ------------------------------ //
// -------------------------------------------------------------------------------------------------------------------- //


/*---------------------------------------------------------------------------------------------------------------------
| menuNode::config: Configures the node with its name, type (ACT or SUB), and a function pointer if applicable.
| This function is almost identical to the menuFrame::addNode function that calls it.
|        -------------------------------------------------------------------------------------------------------
| Arguments:
| - char * namePtr: The string pointer to the name of the node (will be displayed)
|
| - char type: the type of node; either a SUB node that directs to a menu, or an ACT node that links a function
|
| - void (*functPtr) (void): the pointer to the function to be activated, can be left as NULL if not an ACT node
|        -------------------------------------------------------------------------------------------------------
| Returns: nothing
|
|        -------------------------------------------------------------------------------------------------------
| Notes/Future Changes:
| - 
|        -------------------------------------------------------------------------------------------------------
| Created by: Cameron Jupp
| Date:       December 14,2022
| Edited:     {Date}  
----------------------------------------------------------------------------------------------------------------------*/
void menuNode::config(char * namePtr, char type, void (*functPtr) (void))
{
    this->nodeType = type;

    this->setName(namePtr);    

    this->choose = functPtr;
}

/*---------------------------------------------------------------------------------------------------------------------
| menuNode::setName: Sets the name of the node. This is included as a separate function to allow users to dynamically
| change the name of nodes if they desire. 
|        -------------------------------------------------------------------------------------------------------
| Arguments:
| - char * namePtr: the string pointer to the name of the node
|        -------------------------------------------------------------------------------------------------------
| Returns: nothing
|
|        -------------------------------------------------------------------------------------------------------
| Notes/Future Changes:
| - 
|        -------------------------------------------------------------------------------------------------------
| Created by: Cameron Jupp
| Date:       December 14,2022
| Edited:     {Date}  
----------------------------------------------------------------------------------------------------------------------*/
void menuNode::setName(char * namePtr)
{
    strcpy(this->name, namePtr);
}

/*---------------------------------------------------------------------------------------------------------------------
| menuNode::link: Links the node to the menu it will open
|        -------------------------------------------------------------------------------------------------------
| Arguments:
| - char menuNum: the index of the menu that the node links to
|        -------------------------------------------------------------------------------------------------------
| Returns: nothing
|
|        -------------------------------------------------------------------------------------------------------
| Notes/Future Changes:
| - 
|        -------------------------------------------------------------------------------------------------------
| Created by: Cameron Jupp
| Date:       December 14,2022
| Edited:     {Date}  
----------------------------------------------------------------------------------------------------------------------*/
void menuNode::link(char menuNum)
{
    // Set the menu number within the node object
    this->menuCall = menuNum;
}

// -------------------------------------------------------------------------------------------------------------------- //
// -------------------------------------------------- MENU CLASS ------------------------------------------------------ //
// -------------------------------------------------------------------------------------------------------------------- //

/*---------------------------------------------------------------------------------------------------------------------
| menu::addNode: Configures the next node in the current menu array. Sets the name, node type, and function (if wanted).
| Increments the node count afterwards. This function is almost identical to the menuFrame version.
|        -------------------------------------------------------------------------------------------------------
| Arguments:
| - char * nodeName: The string pointer to the name of the node (will be displayed)
|
| - char nodeType: the type of node; either a SUB node that directs to a menu, or an ACT node that links a function
|
| - void (*functPtr) (void): the pointer to the function to be activated, can be left as NULL if not an ACT node
|        -------------------------------------------------------------------------------------------------------
| Returns: nothing
|
|        -------------------------------------------------------------------------------------------------------
| Notes/Future Changes:
| - 
|        -------------------------------------------------------------------------------------------------------
| Created by: Cameron Jupp
| Date:       {Date}
| Edited:     {Date}  
----------------------------------------------------------------------------------------------------------------------*/
void menu::addNode(char * nodeName, char nodeType, void (*functPtr) (void))
{
    node[nodeCount].config(nodeName, nodeType, functPtr);

    nodeCount++;
}

/*---------------------------------------------------------------------------------------------------------------------
| menu::setName: Sets/changes the name of the menu 
|        -------------------------------------------------------------------------------------------------------
| Arguments:
| - char * namePtr: the string pointer to the name of the menu
|        -------------------------------------------------------------------------------------------------------
| Returns: nothing
|
|        -------------------------------------------------------------------------------------------------------
| Notes/Future Changes:
| - 
|        -------------------------------------------------------------------------------------------------------
| Created by: Cameron Jupp
| Date:       December 14,2022
| Edited:     {Date}  
----------------------------------------------------------------------------------------------------------------------*/
void menu::setName(char * namePtr)
{
    // Take the name and input it into the class name array
    strcpy(this->name, namePtr);
}

/*---------------------------------------------------------------------------------------------------------------------
| menu::build: Builds the menu onto whatever display is being used. Lists the name of the menu first, then all nodes
| within the menu. The current node index is passed in to add a special character or feature to the currently selected
| menu node. This function should be edited for different display mediums to be used.
|        -------------------------------------------------------------------------------------------------------
| Arguments:
| - char nodeIndex: The node index to allow the menu to distinguish to the user which node is currently selected
|        -------------------------------------------------------------------------------------------------------
| Returns: nothing
|
|        -------------------------------------------------------------------------------------------------------
| Notes/Future Changes:
|
| - Add a definition in the h file that turns on or off the Serial display of the menu
|
|        -------------------------------------------------------------------------------------------------------
| Created by: Cameron Jupp
| Date:       December 14,2022
| Edited:     {Date}  
----------------------------------------------------------------------------------------------------------------------*/
void menu::build(char nodeIndex)
{
    // Clear the display
    display.clearDisplay();
    display.setTextColor(WHITE); // Draw white text
    display.setCursor(0, 0);     // Start at top-left corner

    // Use larger text font for menu name
    display.setTextSize(2);      // Normal 1:1 pixel scale
    // Menu title front decorator
    display.write("-");
    // Display menu name
    display.write(this->name);
    // Menu title back decorator and newline
    display.write("-\n");

    // Set text to smallest size for menu nodes
    display.setTextSize(1);      // Normal 1:1 pixel scale

    // For every node
    for(int i = 0; i < MAX_NODES; i++)
    {   
        // If the menu is configured (nodeType is not 0)
        if(this->node[i].nodeType)
        {
        
        // If on the currently selected node, display a special indicator
        if(i == nodeIndex)
        {
            display.write("-> ");
            
            //Serial.print("->");
        }

        // Otherwise space out the same amount of characters to keep nodes aligned
        else
        {
            display.write("   ");
            
            //Serial.print("  ");
        }
        
        // Display menu name to OLED
        display.write(this->node[i].name);
        display.write("\n");
        
        //Serial.println(this->node[i].name);
        }
    }

    // Send display buffer
    display.display();
}

// -------------------------------------------------------------------------------------------------------------------- //
// ------------------------------------------------ MENUFRAME CLASS --------------------------------------------------- //
// -------------------------------------------------------------------------------------------------------------------- //

/*---------------------------------------------------------------------------------------------------------------------
| menFrame::build: Takes the current menu index and builds the menu onto whatever display you are using
|        -------------------------------------------------------------------------------------------------------
| Arguments:
| - N/A
|        -------------------------------------------------------------------------------------------------------
| Returns: nothing
|
|        -------------------------------------------------------------------------------------------------------
| Notes/Future Changes:
| - 
|        -------------------------------------------------------------------------------------------------------
| Created by: Cameron Jupp
| Date:       December 14,2022
| Edited:     {Date}  
----------------------------------------------------------------------------------------------------------------------*/
void menuFrame::build()
{
    // Calls the build function from the menu object currently indexed. It is displayed at the menu object level to allow
    // the user to call it from dynamically within the menu if desired. 
    menuList[currentMenu].build(this->nodeIndex);
}

/*---------------------------------------------------------------------------------------------------------------------
| menuFrame::addMenu: Initializes a menu object within the array inside the menuFrame object. You can manually set the
| index for the menu 
|        -------------------------------------------------------------------------------------------------------
| Arguments:
| - char * menuName: The string pointer for the menus name
|
| - char index: The index for the menu within the menuFrame array
|        -------------------------------------------------------------------------------------------------------
| Returns: nothing
|
|        -------------------------------------------------------------------------------------------------------
| Notes/Future Changes:
| - 
|        -------------------------------------------------------------------------------------------------------
| Created by: Cameron Jupp
| Date:       December 14,2022
| Edited:     {Date}  
----------------------------------------------------------------------------------------------------------------------*/
void menuFrame::addMenu (char * menuName, char index)
{
    // Ensure that the index is valid within the specified number of menus allowed
    if(index >= 0 && index <= MAX_MENUS)
    {
        // Configure the name of the menu
        menuList[index].setName(menuName);

        // Set the menu configuration index so that any nodes added afterwards are automatically associated with this men
        configIndex = index;
    }

}

/*---------------------------------------------------------------------------------------------------------------------
| menuFrame::addNode: Adds a node to the most recently declared menu
|        -------------------------------------------------------------------------------------------------------
| Arguments:
| - char * nodeName: The string pointer to the name of the node (will be displayed)
|
| - char nodeType: the type of node; either a SUB node that directs to a menu, or an ACT node that links a function
|
| - void (*functPtr) (void): the pointer to the function to be activated, can be left as NULL if not an ACT node
|
|        -------------------------------------------------------------------------------------------------------
| Returns: nothing
|
|        -------------------------------------------------------------------------------------------------------
| Notes/Future Changes:
| - 
|        -------------------------------------------------------------------------------------------------------
| Created by: Cameron Jupp
| Date:       December 14,2022
| Edited:     {Date}  
----------------------------------------------------------------------------------------------------------------------*/
void menuFrame::addNode(char * nodeName, char nodeType, void (*functPtr) (void))
{
    // The menuFrame addNode function simply calls the menu::addNode function and passes down the arguments.
    // This was done to allow the user to still be able to dynamically add nodes from the menu level if need be
    this->menuList[configIndex].addNode(nodeName, nodeType, functPtr);

    // Updates the node link index so that when calling the linkNode function it automatically uses the last made node.
    // This is done for usability and simplicity
    this->nodeLinkIndex = this->menuList[configIndex].nodeCount - 1;
}

/*---------------------------------------------------------------------------------------------------------------------
| menuFrame::linkNode: Links a node to the menu it leads to, and also links that same menu back to the node that
| triggers it
|        -------------------------------------------------------------------------------------------------------
| Arguments:
| - char menuNum: the index of the menu you want to link to the node. This is also used as an index in the menFrame
| object to link that menu back to the node
|        -------------------------------------------------------------------------------------------------------
| Returns: nothing
|
|        -------------------------------------------------------------------------------------------------------
| Notes/Future Changes:
| - 
|        -------------------------------------------------------------------------------------------------------
| Created by: Cameron Jupp
| Date:       December 14,2022
| Edited:     {Date}  
----------------------------------------------------------------------------------------------------------------------*/
void menuFrame::linkNode(char menuNum)
{
    // Add the menu a node directs to
    this->menuList[configIndex].node[nodeLinkIndex].link(menuNum);

    // Create a back reference to the parent node of a menu
    this->menuList[menuNum].backLink[MENU] = this->configIndex;
    this->menuList[menuNum].backLink[NODE] = this->nodeLinkIndex;
}

/*---------------------------------------------------------------------------------------------------------------------
| menuFrame::up: Decrements the node index (decrementing moves it up the menu) 
|        -------------------------------------------------------------------------------------------------------
| Arguments:
| - 
|        -------------------------------------------------------------------------------------------------------
| Returns: nothing
|
|        -------------------------------------------------------------------------------------------------------
| Notes/Future Changes:
| - 
|        -------------------------------------------------------------------------------------------------------
| Created by: Cameron Jupp
| Date:       December 14,2022
| Edited:     {Date}  
----------------------------------------------------------------------------------------------------------------------*/
void menuFrame::up()
{
    // If the index is greater than zero, decrement it (top choice is zero)
    if(nodeIndex)
    {
        this->nodeIndex--;
    }
}

/*---------------------------------------------------------------------------------------------------------------------
| menuFrame::down: Increments the node index (incrementing moves it down the menu) 
|        -------------------------------------------------------------------------------------------------------
| Arguments:
| - N/A
|        -------------------------------------------------------------------------------------------------------
| Returns: nothing
|
|        -------------------------------------------------------------------------------------------------------
| Notes/Future Changes:
| - 
|        -------------------------------------------------------------------------------------------------------
| Created by: Cameron Jupp
| Date:       December 14,2022
| Edited:     {Date}  
----------------------------------------------------------------------------------------------------------------------*/
void menuFrame::down()
{
    // If the index is less than the menu size, then increment the index (last option is largest value)
    if(nodeIndex < menuList[currentMenu].nodeCount - 1)
    {    
        this->nodeIndex++;
    }
}

/*---------------------------------------------------------------------------------------------------------------------
| menuFrame::choose: Triggers the action associated with the current menu node. This action can be to open another
| menu, or to trigger a linked function via function pointer.
|        -------------------------------------------------------------------------------------------------------
| Arguments:
| - N/A
|        -------------------------------------------------------------------------------------------------------
| Returns: nothing
|
|        -------------------------------------------------------------------------------------------------------
| Notes/Future Changes:
| - 
|        -------------------------------------------------------------------------------------------------------
| Created by: Cameron Jupp
| Date:       December 14, 2022
| Edited:     {Date}  
----------------------------------------------------------------------------------------------------------------------*/
void menuFrame::choose()
{
    // Depending on if the node triggers another menu, or a function:
    switch(this->menuList[currentMenu].node[nodeIndex].nodeType)
    {
        // Changes the current menu index and resets the node index to start at the top of the new menu
        case SUB_NODE:
        // Change the active menu to that of the node's linked menu number
        this->currentMenu = this->menuList[currentMenu].node[nodeIndex].menuCall;
        // Reset the choice index to zero
        this->nodeIndex = 0;
        break;

        // Triggers the function pointer associated with the menu node
        case ACT_NODE:
        // Activate the linked function for the node
        this->menuList[currentMenu].node[nodeIndex].choose();
        break;
    }
}

/*---------------------------------------------------------------------------------------------------------------------
| menuFrame::back: Returns to the previous menu if there is one. Also resets the node index to the node that triggered
| the current menu.
|        -------------------------------------------------------------------------------------------------------
| Arguments:
| - N/A
|        -------------------------------------------------------------------------------------------------------
| Returns: nothing
|
|        -------------------------------------------------------------------------------------------------------
| Notes/Future Changes:
| - 
|        -------------------------------------------------------------------------------------------------------
| Created by: Cameron Jupp
| Date:       December 14, 2022
| Edited:     {Date}  
----------------------------------------------------------------------------------------------------------------------*/
void menuFrame::back()
{
    //Changes the current menu to the one linked in the current menu class
    this->nodeIndex = this->menuList[currentMenu].backLink[NODE];

    //Changes the current node to the one linked in the current menu class
    this->currentMenu = this->menuList[currentMenu].backLink[MENU];
}

// -------------------------------------------------------------------------------------------------------------------- //
// -------------------  / ___/  / / //  / \  / /  / ___/ /__  __/  /_  _/  / __  /  / \  / /  / ____/ ----------------- //
// ------------------  / __/   / /_//  / /\\/ /  / /__     / /      / /   / /_/ /  / /\\/ /   \__ \ ------------------- //
// -----------------  /_/     /____/  /_/  \_/  /____/    /_/     /___/  /_____/  /_/  \_/  /_____/ ------------------- //
// -------------------------------------------------------------------------------------------------------------------- //

/*---------------------------------------------------------------------------------------------------------------------
| oledSystemInit; This function initializes all of the OLED specific components and then clears the display.
| If using a different kind of display, this function should be replaced with whatever initializations are needed
| for that system
|        -------------------------------------------------------------------------------------------------------
| Arguments:
| - N/A
|        -------------------------------------------------------------------------------------------------------
| Returns: nothing
|
|        -------------------------------------------------------------------------------------------------------
| Notes/Future Changes:
| - 
|        -------------------------------------------------------------------------------------------------------
| Created by: Cameron Jupp
| Date:       December 16, 2022
| Edited:     {Date}  
----------------------------------------------------------------------------------------------------------------------*/
void oledSystemInit()
{
// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
{ 
  Serial.println(F("SSD1306 allocation failed"));
  for(;;); // Don't proceed, loop forever
}

  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  display.clearDisplay();
}