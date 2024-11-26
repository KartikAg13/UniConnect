CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lstdc++fs

all: uniconnect

uniconnect: main.o User.o Node.o AVLTree.o File.o Graph.o Chat.o
	$(CXX) $(CXXFLAGS) -o uniconnect main.o User.o Node.o AVLTree.o File.o Graph.o Chat.o $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

User.o: User.cpp User.h
	$(CXX) $(CXXFLAGS) -c User.cpp

Node.o: Node.cpp Node.h
	$(CXX) $(CXXFLAGS) -c Node.cpp

AVLTree.o: AVLTree.cpp AVLTree.h
	$(CXX) $(CXXFLAGS) -c AVLTree.cpp

File.o: File.cpp File.h
	$(CXX) $(CXXFLAGS) -c File.cpp

Graph.o: Graph.cpp Graph.h
	$(CXX) $(CXXFLAGS) -c Graph.cpp -o Graph.o

Chat.o: Chat.cpp Chat.h
	$(CXX) $(CXXFLAGS) -c Chat.cpp

clean:
	rm -f *.o uniconnect
