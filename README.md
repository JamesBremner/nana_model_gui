# nana_model_gui
An essential model-gui application using nana library

A GUI class makes adding to and maintaining a GUI application so much easier. 
It keeps all the widget code separate from the code that implements the application model.

The construction code is split into three steps which is very helpful when maintaining the code for a complex GUI containing dozens of widgets. 
 * Step 1 constructs the widgets, specifying only the parent widget. This is done in the GUI class initializer list.
 * Step 2 moves the widgets to their locations in the parent widget. This ts done in a move method called from the GUI class constructor, which is important because the move method can also be called from a resize handler. 
 * Step 3 specifies remaining details such as captions. This is done in the GUI class constructor.

The application model in this code is merely a stub to show how the GUI and the model interact.
 
