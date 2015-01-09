###############################################################################################
# This makefile demonstrates the creation of a simple makefile				      #
# Team	 : Veda                                                                               #
# Version: 1.0										      #################################################################################################	
# The makefiles creation consists of creating the targets and the rules for achieving the
# targets. The syntax of creating the targets and rules are as follows
# <target-name>: <dependencie_list>
#	<rules for creating the target> 

# for displaying messages "echo" is used.
# if we don't want to display the background running process of the makefile, we need to simply# add "@" before them. 


# target name = app
app: gif.o ui.o
	gcc -o app ui.o gifhandler.o
	@echo "Application Created Succeisfully"

gif.o: gifhandler.c
	gcc -c gifhandler.c

ui.o:  ui.c
	gcc -c ui.c
	
















