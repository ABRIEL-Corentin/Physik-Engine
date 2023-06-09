##
## EPITECH PROJECT, 2023
## B-PSU-400-LYN-4-1-ftrace-adam.balfet
## File description:
## Makefile
##

SRC_PATH = src
BUILD_PATH = ./obj
COMPILER = g++
FILE_TYPE = .cpp
SECTION_NAME = PHYSIK ENGINE
DEBUG ?= 0

SRC =\
	${SRC_PATH}/main.cpp\
	${SRC_PATH}/core.cpp\
	${SRC_PATH}/window.cpp\
	${SRC_PATH}/time.cpp\
	${SRC_PATH}/scene.cpp\
	${SRC_PATH}/grid.cpp\
	${SRC_PATH}/shapes/ashape.cpp\
	${SRC_PATH}/shapes/circle.cpp\
	${SRC_PATH}/shapes/rectangle.cpp\
	${SRC_PATH}/shapes/polygon.cpp\
	${SRC_PATH}/error_handling/check_and_get_args.cpp\

INCLUDE =\
	-I./include/\

INDEX = ${words ${shell a="${2}" ; echo $${a/${1}*/${1}} }}
SRC_COUNT = ${shell echo ${SRC} | wc -w}
OBJ = ${SRC:${SRC_PATH}/%${FILE_TYPE}=${BUILD_PATH}/%.o}
DEBUG_FLAGS = -g3
OBJ_FLAGS = -O3 -W -Wall -Wextra -Werror -std=c++20 ${INCLUDE}
BIN_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system ./imgui.so
BIN_NAME = physik-engine

all: ${BIN_NAME}

${BUILD_PATH}/%.o: ${SRC_PATH}/%${FILE_TYPE}
	@mkdir -p ${dir $@}
ifeq (${DEBUG}, 1)
	@echo "[DEBUG] [${SECTION_NAME}] [${call INDEX, "$<", ${SRC}}/${SRC_COUNT}] $<"
	@${COMPILER} -MD ${OBJ_FLAGS} ${DEBUG_FLAGS} -c $< -o $@
else
	@echo "[${SECTION_NAME}] [${call INDEX, "$<", ${SRC}}/${SRC_COUNT}] $<"
	@${COMPILER} -MD ${OBJ_FLAGS} -c $< -o $@
endif

${BIN_NAME}: ${OBJ}
ifeq (${DEBUG}, 1)
	@echo -n "[DEBUG] "
endif
	@echo "[${SECTION_NAME}] final build: ${BIN_NAME}"
	@${COMPILER} -o ${BIN_NAME} ${OBJ} ${BIN_FLAGS}

clean:
ifeq (${DEBUG}, 1)
	@echo -n "[DEBUG] "
endif
	@echo "[${SECTION_NAME}] remove: ${BUILD_PATH}"
	@rm -rf ${BUILD_PATH}

fclean: clean
ifeq (${DEBUG}, 1)
	@echo -n "[DEBUG] "
endif
	@echo "[${SECTION_NAME}] remove: ${BIN_NAME}"
	@rm -rf ${BIN_NAME}

fclena: fclean
	@echo "---------écris mieux stp--------------"

re: fclean all

-include ${OBJ:%.o=%.d}

.PHONY: all clean fclean re
