#handlers.o:	$(PWD)/handlers/deleteHand.c $(PWD)/handlers/insrtHand.c $(PWD)/handlers/printHand.c $(PWD)/handlers/sortHand.c
#		cc -c $(PWD)/handlers/deleteHand.c $(PWD)/handlers/insrtHand.c $(PWD)/handlers/printHand.c $(PWD)/handlers/sortHand.c #-o $(PWD)/handlers/handlers.o
#modules.o:	$(PWD)/modules/delmodule.c $(PWD)/modules/dispmodule.c $(PWD)/modules/insrtmodule.c $(PWD)/modules/sortmodule.c
#		cc -c $(PWD)/modules/delmodule.c $(PWD)/modules/dispmodule.c $(PWD)/modules/insrtmodule.c $(PWD)/modules/sortmodule.c #-o $(PWD)/modules/modules.o


#app: 		error.h menu.c menuHandler.c headers.h $(PWD)/handlers/*.o $(PWD)/modules/*.o test.c
#		cc menu.c menuHandler.c headers.h $(PWD)/handlers/*.o $(PWD)/modules/*.o test.c -o app


# $(PWD) will cause problem since this directory contains (,) so when u just give $(PWD) it doesnt take care of these chars it directly prints as it is but to work this actutally we shud give \( and \)

app:	test.o ./headers/*.h ./menu/*.o ./handlers/*.o ./modules/*.o ./backup/*.o
	cc -g -v -m32 test.o ./menu/*.o ./handlers/*.o ./modules/*.o ./backup/*.o -o app
	clear
	echo "You can run app now"
