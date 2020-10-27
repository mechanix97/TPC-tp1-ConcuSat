

SRC = $(wildcard src/*)
OBJECTS = $(foreach file, $(SRC), out/$(basename $(notdir $(file))).o)

CC = g++
CFLAGS = -Wall

all: out $(OBJECTS)
	@echo Building...
	@$(CC) -o concusat $(OBJECTS) -lm
	@echo Done

out:
	@mkdir -p $@

out/%.o: src/%.cpp
	@echo CC $<
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf out
