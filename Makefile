OBJS = BankTester.o Login.o Register.o BankMenu.o Date.o LinkedList.o Admin.o
CC = g++

BankOut: $(OBJS)
	g++ -o BankOut $(OBJS)
	rm -f $(OBJS)

Login.o: 
	g++ -c CPPFiles/Login.cpp

Register.o:
	g++ -c CPPFiles/Register.cpp
	
BankMenu.o:
	g++ -c CPPFiles/BankMenu.cpp

Date.o:
	g++ -c CPPFiles/Date.cpp

LinkedList.o:
	g++ -c CPPFiles/LinkedList.cpp
	
Admin.o:
	g++ -c CPPFiles/Admin.cpp
	
BankTester.o: 
	$(CC) -c BankTester.cpp
	
clean:
	rm -f core BankOut $(OBJS)