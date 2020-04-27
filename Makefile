COMPILER ?= g++
LINKER ?= g++
COMPILE_FLAGS = -c -g -std=c++11
LINKER_FLAGS =
BUILD_DIR = build
TARGET ?= Network
SRC_DIRS = src
OBJ_DIR = build/obj
INCLUDES = -Iheaders
DEFINES =
BUILD_EXT = cpp
ARGS ?=

OBJ=$(foreach dir, $(SRC_DIRS), $(patsubst $(dir)/%.${BUILD_EXT}, $(OBJ_DIR)/%.o, $(wildcard $(dir)/*.${BUILD_EXT})))
SRC_FILES=$(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.${BUILD_EXT}))

.PHONY: all clean
all: ${TARGET}

${TARGET}: ${OBJ}
	@mkdir -p ${BUILD_DIR}
	${LINKER} $^ -o ${BUILD_DIR}/$@ ${LINKER_FLAGS}

define make_obj 
$(OBJ_DIR)/$(notdir $(1:%.${BUILD_EXT}=%.o)): $1
endef

$(foreach d, $(SRC_FILES), $(eval $(call make_obj,$d)))

%.o:
	@mkdir -p $(OBJ_DIR)
	$(COMPILER) $(INCLUDES) $(DEFINES) $(COMPILE_FLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(OBJ_DIR)

run: ${TARGET}
	${BUILD_DIR}/$^