# SDLViewer Extension
Implemented by Carolina Nobre and Oscar Mejia


This Views Extension allows you to interact with the SDLViewer using your keyboard and mouse. The following events are supported:

+ Mouse left/right click  
+ Mouse movement events  
+ Keyboard events  

You can implement any functionality you need when any of these events is triggered, like update nodes in a Graph or Mesh, change forces or constraints in a simulation, rotate or zoom the viewer, alter the time of the simulation, just to list a few.

Integrating this extension with your project is very easy. It only takes 3 steps:


## 1) Create a struct that extends Viewer::Listener.

Viewer::Listener has 5 virtual member function that you have to implement.

================IMAGE

**handle_keyboard_event**: Called every time a keyboard key is pressed. c is the pressed key.  
**handle_mouse_left_click_event**: Called when the left button of the mouse is clicked.  
**handle_mouse_right_click_event**: Called when the right button of the mouse is clicked.  
**handle_node_selection_event**: Called when a node is clicked.  
**handle_mouse_move_event**: Called when the mouse moves over the viewer.  
**handle**: Low level handle event call for every mouse and keyboard event including all the above. The above methods are convenient abstractions of SDL_event objects.  



Note: In this example, a constructor that takes a reference to a Graph was added as a convenience and quick and easy way to interact with the graph when the “callback methods” are called. In your implementation, you can create any number of constructors that take any object types you may need.


## 2) Create an instance of EventListener and add it as a callback to viewer.

Use smart pointers to wrap your EventListener object and add it to the viewer using the add_listener methods..

================IMAGE


## 3) Implement your custom logic in the callback methods.

In the following example you can see how easy is to change the position of all nodes in a Graph in “x” direction by adding 0.05 to the initial values when the key “z” is pressed.

You can implement far more complex interactions, but this illustrates how easy and clean is to add interactivity to your simulations.

You can create and add many EventListener that encapsulate different logic for each supported event or create one that does it all, your choice.


================IMAGE
