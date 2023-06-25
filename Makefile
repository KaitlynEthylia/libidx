BUILD=build
ARCHIVE=$(BUILD)/libidx.a
SRC=src
INC=include

CC=clang
INCFLAGS=-I$(INC)
DEPFLAGS=-MP -MD
CFLAGS=-Wall -Werror -O2 $(INCFLAGS) $(DEPFLAGS)

SRCS=$(wildcard $(SRC)/*.c)

OBJS=$(patsubst $(SRC)%.c,$(BUILD)%.o,$(SRCS))
DEPS=$(patsubst $(SRC)%.c,$(BUILD)%.d,$(SRCS))

all: $(ARCHIVE)

$(ARCHIVE): $(BUILD) $(OBJS)
	ar rcs $@ $(OBJS)

$(BUILD):
	mkdir $(BUILD)

$(BUILD)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)
