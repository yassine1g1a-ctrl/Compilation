# Compilateur et options
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

# Répertoires
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Création des dossiers si inexistants
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Fichiers sources
SRC = $(SRC_DIR)/automate.cpp $(SRC_DIR)/etats.cpp $(SRC_DIR)/lexer.cpp $(SRC_DIR)/symbole.cpp
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Exécutable principal
EXEC = $(BIN_DIR)/main
MAIN_OBJ = $(OBJ_DIR)/main.o

# Fichiers pour les tests
TEST_SRC = $(SRC_DIR)/tests.cpp
TEST_OBJ = $(OBJ_DIR)/tests.o
TEST_EXEC = $(BIN_DIR)/tests

# Compilation principale
all: $(EXEC)

$(EXEC): $(OBJ) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(MAIN_OBJ): $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilation et exécution des tests
tests: $(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJ) $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_OBJ): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJ) $(MAIN_OBJ) $(EXEC) $(TEST_OBJ) $(TEST_EXEC)

.PHONY: all clean tests