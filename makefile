ifeq ($(origin CC),default)
CC=gcc
endif
C_FLAGS?=-O2 -Wall -Wextra -Wpedantic -Werror

DIR_BUILD=build
DIR_SRC=src
DIR_INCLUDE=include
DIR_TEST=test

LIB_NAME=libsus.a
PREFIX?=/usr/local

SRCS=$(shell find $(DIR_SRC) -type f -name '*.c')
OBJS=$(patsubst $(DIR_SRC)/%.c,$(DIR_BUILD)/obj/%.o,$(SRCS))
TEST_SRCS=$(wildcard $(DIR_TEST)/*.c)
TEST_ELFS=$(patsubst $(DIR_TEST)/%.c,$(DIR_BUILD)/test/%.elf,$(TEST_SRCS))
TARGET=$(DIR_BUILD)/$(LIB_NAME)

.PHONY: all build rebuild clean install uninstall reinstall

all: build
build: $(TARGET)
rebuild: clean build
reinstall: uninstall rebuild install

install: $(TARGET)
	mkdir -p $(PREFIX)/lib
	cp $(TARGET) $(PREFIX)/lib/
	mkdir -p $(PREFIX)/include/sus
	cp $(DIR_INCLUDE)/*.h $(PREFIX)/include/sus/

uninstall:
	rm -f $(PREFIX)/lib/$(LIB_NAME)
	rm -rf $(PREFIX)/include/sus

test: $(TEST_ELFS)
	@-for elf in $(TEST_ELFS) ; do \
		echo "=== Running $$elf ===" ; \
		./$$elf ; \
	done

$(TARGET): $(OBJS)
	ar rcs $@ $^

$(DIR_BUILD)/obj/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	$(CC) $(C_FLAGS) -D_SUS_IMPLEMENTATION_ -I$(DIR_INCLUDE) -c $< -o $@

$(DIR_BUILD)/test/%.elf: $(DIR_TEST)/%.c $(DIR_TEST)/unity/unity.c $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(C_FLAGS) -DSUS_TARGET_VERSION=10000 -I$(DIR_INCLUDE) $^ -o $@

clean:
	-rm -r $(DIR_BUILD)
