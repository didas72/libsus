CC?=gcc
C_FLAGS?=-O2 -Wall -Wextra -Wpedantic -Werror

DIR_BUILD=build
DIR_SRC=src
DIR_INCLUDE=include

LIB_NAME=libsus.a
PREFIX?=/usr/local

SRCS=$(shell find $(DIR_SRC) -type f -name '*.c')
OBJS=$(patsubst $(DIR_SRC)/%.c,$(DIR_BUILD)/obj/%.o,$(SRCS))
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

$(TARGET): $(OBJS)
	ar rcs $@ $^

$(DIR_BUILD)/obj/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(@D)
	$(CC) $(C_FLAGS) -I$(DIR_INCLUDE) -c $< -o $@

clean:
	-rm -r $(DIR_BUILD)
