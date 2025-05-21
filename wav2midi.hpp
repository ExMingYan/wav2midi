#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>
#include <fftw3.h>
#include <sndfile.h>
#include <cmath>
#include "midifile/include/MidiFile.h"

void processWavToMidi(const char *wavFile, const char *midiFile);
