CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

# Source files inside src/
SRC_FILES = $(SRC_DIR)/TCPSocket.cpp \
            $(SRC_DIR)/UDPSocket.cpp \
            $(SRC_DIR)/serverChannel.cpp \
            $(SRC_DIR)/clientChannel.cpp

# Object versions (inside obj/)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Test applications
SERVER_SRC = $(SRC_DIR)/server_test.cpp
CLIENT_SRC = $(SRC_DIR)/client_test.cpp

SERVER_OBJ = $(OBJ_DIR)/server_test.o
CLIENT_OBJ = $(OBJ_DIR)/client_test.o

SERVER_BIN = server_app
CLIENT_BIN = client_app

all: $(SERVER_BIN) $(CLIENT_BIN)

# Create obj directory if not exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile all channel/socket .cpp files into obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile server test file
$(SERVER_OBJ): $(SERVER_SRC) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SERVER_SRC) -o $(SERVER_OBJ)

# Compile client test file
$(CLIENT_OBJ): $(CLIENT_SRC) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(CLIENT_SRC) -o $(CLIENT_OBJ)

# Link server
$(SERVER_BIN): $(OBJ_FILES) $(SERVER_OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) $(SERVER_OBJ) -o $(SERVER_BIN)

# Link client
$(CLIENT_BIN): $(OBJ_FILES) $(CLIENT_OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) $(CLIENT_OBJ) -o $(CLIENT_BIN)

clean:
	rm -rf $(OBJ_DIR) $(SERVER_BIN) $(CLIENT_BIN)

.PHONY: all clean
