Welcome to Remote text editor!

Run the binary file RemoteTxtEditor to start the application.
Application can work in two modes: client and server.
Enter 0 to work in server mode, or 1 to work in client mode.

Server mode.
Here is not much to do, it works on predefined settings. 
You can add text files to directory with the application
to let server use them.

Client mode.
Client application has main menu so user can enter some
code number to run some functionality. There is four cases
in main menu: 
	1 - Request text file. It allows you to request some portion
	of text of a file that stores on server. Here you should
	enter offset in a file from the beginning and a file name.
	As response you will get a text of a file or some error
	message;
	2 - Edit text. It allows you to change given from server the text.
	It has its own sub-menu with commands to edit the text:
		1 - Add line. Allows you to add new line at the end with a text
		you entered;
		2 - Remove line. Removes line by given number of a line;
		3 - Insert line. Inserts line by given number and text;
		4 - Edit line. Removes old line and insert new line by given
		position and new entered text;
		5 - Update changes. Sends request to server to update file
		with changes you have made;
		6 - See changes. Prints text with changes to see what you've done
		before you update it;
		0 - Back to main menu. Ends editing and returns to main menu;
	3 - Reconnect to server. You can reconnect to another server or restore
	a connection with current server by entering server's port and IP address;
	0 - Exit.
So what you have to do? For example, you run application and choose a client mode
by entering 1. If you've connected to server press 1 to request a text file. Here
you need enter offser, lets say, 0 (beginnig of the file) and file name file.txt.
Here we are! We got a text. Now press 2 to modify it. Lets insert some line, press 3,
enter position lets say 5, then enter text for line. Good. Now we press 5 to update it on server.
Yeah, we got message that update completed.
