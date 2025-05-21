.DEFAULT_GOAL := all
TARGET = wav2midi

MIDIFILE_LIB = midifile/lib/libmidifile.a
MIDIFILE_DIR = midifile

CC = g++
CFLAGS = -Wall -Wextra -std=c++17
LDFLAGS := -lsndfile -lfftw3 -Lmidifile/lib -lmidifile

# Source files
SRCS = $(wildcard *.cpp)

ifeq ($(OS),Windows_NT)
EXE = .exe
else
EXE =
endif

.PHONY: all clean
all: $(TARGET)$(EXE)

clean:
	$(RM) -f $(TARGET)$(EXE)
	$(MAKE) -C $(MIDIFILE_DIR) clean

$(MIDIFILE_LIB):
	$(MAKE) library -C $(MIDIFILE_DIR)

$(TARGET)$(EXE): $(SRCS) $(MIDIFILE_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
