
CC := gcc
CXX := g++
AR := ar
CFLAGS := -Wall
# Initialize
INCLUDE := 
LIBRARY :=
LDFLAGS := 

THIRD_PARTY := ./3rdparty
GTEST_LIB_NAME := gtest
GTEST_STATIC_LIB := lib$(GTEST_LIB_NAME).a
GTEST_DIR := $(THIRD_PARTY)/gtest
GTEST_INC_DIR := $(GTEST_DIR)/include
GTEST_SRC_DIR := $(GTEST_DIR)/src
INCLUDE += -I$(GTEST_INC_DIR) -I$(GTEST_DIR)

FOO_NAME := foo
BAR_NAME := bar
TEST_NAME:= test

INC_DIR := ./include
SRC_DIR := ./src
FOO_SRC_DIR := $(SRC_DIR)/$(FOO_NAME)
BAR_SRC_DIR := $(SRC_DIR)/$(BAR_NAME)
TEST_SRC_DIR:= $(SRC_DIR)/$(TEST_NAME)

LIB_DIR := ./lib
OBJ_DIR := ./obj
FOO_OBJ_DIR := $(OBJ_DIR)/$(FOO_NAME)
BAR_OBJ_DIR := $(OBJ_DIR)/$(BAR_NAME)
TEST_OBJ_DIR:= $(OBJ_DIR)/$(TEST_NAME)
BIN_DIR := ./bin
TEST_BIN_DIR:= $(BIN_DIR)/$(TEST_NAME)

BUILD_DIRS := \
	$(LIB_DIR) \
	$(OBJ_DIR) \
	$(BIN_DIR) \
	$(FOO_OBJ_DIR)\
	$(BAR_OBJ_DIR)\
	$(TEST_OBJ_DIR)\
	$(TEST_BIN_DIR)

# unit test names
TEST_NAMES := \
	foo_test bar_test
TEST_BIN := $(foreach test,$(TEST_NAMES),$(TEST_BIN_DIR)/$(test).bin)

# OBJECTS for our foobar project
OBJ := $(FOO_NAME)/foo.o $(BAR_NAME)/bar.o
# OBJECTS for test programs
OBJS := $(addprefix $(OBJ_DIR)/, $(OBJ))

INCLUDE += -I$(INC_DIR)
LIBRARY += -L$(LIB_DIR)

CFLAGS += $(INCLUDE)
LDFLAGS += $(LIBRARY) 

LDFLAGS += -pthread

DEPS := $(wildcard $(INC_DIR)/*.h)

all: dirs 3rdparty test

test: $(TEST_BIN)

$(TEST_BIN_DIR)/%.bin: $(TEST_OBJ_DIR)/%.o $(OBJS) $(LIB_DIR)/$(GTEST_STATIC_LIB)
	@echo "CXX\t $@"
	@$(CXX) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(DEPS)
	@echo "CXX\t $@"
	@$(CXX) $(CFLAGS) -c $< -o $@

3rdparty: $(LIB_DIR)/$(GTEST_STATIC_LIB)

$(LIB_DIR)/$(GTEST_STATIC_LIB): $(OBJ_DIR)/gtest-all.o
	@echo "AR\t $@"
	@$(AR) -r $@ $^

$(OBJ_DIR)/gtest-all.o: $(GTEST_SRC_DIR)/gtest-all.cc
	@echo "CXX\t $@"
	@$(CXX) $(CFLAGS) -isystem -pthread -c $(GTEST_SRC_DIR)/gtest-all.cc -o $@

.PHONY: dirs clean 3rdparty

dirs:
	@mkdir -p $(BUILD_DIRS)

clean:
	@rm -rf $(BUILD_DIRS)
