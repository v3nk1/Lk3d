#handlers.o:	$(PWD)/handlers/deleteHand.c $(PWD)/handlers/insrtHand.c $(PWD)/handlers/printHand.c $(PWD)/handlers/sortHand.c
#		cc -c $(PWD)/handlers/deleteHand.c $(PWD)/handlers/insrtHand.c $(PWD)/handlers/printHand.c $(PWD)/handlers/sortHand.c #-o $(PWD)/handlers/handlers.o
#modules.o:	$(PWD)/modules/delmodule.c $(PWD)/modules/dispmodule.c $(PWD)/modules/insrtmodule.c $(PWD)/modules/sortmodule.c
#		cc -c $(PWD)/modules/delmodule.c $(PWD)/modules/dispmodule.c $(PWD)/modules/insrtmodule.c $(PWD)/modules/sortmodule.c #-o $(PWD)/modules/modules.o


#app: 		error.h menu.c menuHandler.c headers.h $(PWD)/handlers/*.o $(PWD)/modules/*.o test.c
#		cc menu.c menuHandler.c headers.h $(PWD)/handlers/*.o $(PWD)/modules/*.o test.c -o app

app:	test.c $(PWD)/headers/*.h $(PWD)/menu/*.c $(PWD)/handlers/*.c $(PWD)/modules/*.c $(PWD)/backup/*.c
	cc -g test.c $(PWD)/menu/*.c $(PWD)/handlers/*.c $(PWD)/modules/*.c $(PWD)/backup/*.c -o app

