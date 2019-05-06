Compile your application using gcc with the name mysh.
The commands are case sensitive.
COMMAND DESCRIPTION
help              Displays all the commands
quit              Exits / terminates the shell with “Bye!”
set               VAR STRING Assigns a value to shell memory
print             VAR Prints the STRING assigned to VAR


The command set VAR STRING first checks to see if VAR already exists. If it does exist,
STRING overwrites the previous value assigned to VAR. If VAR does not exist, then a new entry is
added to the shell memory where the variable name is VAR and the contents of the variable is
STRING. For example: set x 10 creates a new variable x and assigns to it the string 10.
Another example: set name Bob creates a new variable called name with string value Bob.
Another example: set x Mary, replaced the value 10 with Mary.
The command print VAR first checks to see if VAR exists. If it does not exist, then is displays
the error “Variable does not exist”. If VAR does exist, then is just prints the STRING. For
example: print x from the above example will display Mary.
