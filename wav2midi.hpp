#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <cmath>
#include <fftw3.h>
#include <sndfile.h>
#include "midifile/include/MidiFile.h"

void processWavToMidi(const char *wavFile, const char *midiFile);
