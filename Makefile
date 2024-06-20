CC := clang++

CFLAGS := -I/opt/homebrew/include 
CFLAGS += -I./header
CFLAGS += -Wall 
CFLAGS += -std=c++20

LFLAGS := -L/opt/homebrew/lib 
CFLAGS += -I./lib
LFLAGS += -lsdl2 
LFLAGS += -lsdl2_image 
LFLAGS += -lsdl2_ttf

OBJ := main.o
OBJ += lib/bst.o
OBJ += lib/util.o
OBJ += lib/res.o

TARGET := bst



.PHONY: release clean



release: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)
%.o : %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
clean:
	rm -rf $(TARGET)
	rm -rf $(OBJ)

