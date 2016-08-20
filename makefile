sSOURCES=$(wildcard ./src/*.cpp ./src/database/*.cpp ./src/parser/*.cpp ./src/utils/*.cpp ./src/bplustree/*.cpp)
HEADERS=$(wildcard  ./src/database/*.h ./src/parser/*.h ./src/bufmanager/*.h ./src/fileio/*.h ./src/utils/*.h ./src/bplustree/*.h)
sOBJECTS=$(sSOURCES:%.cpp=%.o)
TARGET=test

all: $(TARGET)
$(TARGET): $(sOBJECTS) $(HEADERS)
	@echo "Now Generating $(TARGET) ..."
	g++ $(sOBJECTS) -o $(TARGET)
%.o: %.cpp $(HEADERS)
	@echo "Now Compiling $< ..."
	g++ -g -I. -std=c++11 -c $< -o $@
clean:
	del *.o *.exe *.bak
explain:
	@echo "Headers: $(HEADERS)"
	@echo "User Sources: $(sSOURCES)"
	@echo "User Objects: $(sOBJECTS)"
	@echo "Target: $(TARGET)"
