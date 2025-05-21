#include "wav2midi.hpp"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input.wav> <output.mid>" << std::endl;
        return 1;
    }

    processWavToMidi(argv[1], argv[2]);

    std::cout << "MIDI file generated: " << argv[2] << std::endl;
    return 0;
}

void processWavToMidi(const char *wavFile, const char *midiFile)
{
    // 打开 WAV 文件
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(wavFile, SFM_READ, &sfinfo);
    if (!sndfile)
    {
        std::cerr << "无法打开 WAV 文件: " << wavFile << std::endl;
        return;
    }

    // 读取音频数据
    std::vector<double> audioData(sfinfo.frames);
    sf_read_double(sndfile, audioData.data(), sfinfo.frames);
    sf_close(sndfile);

    // 进行 FFT 分析
    int fftSize = 1024;
    fftw_complex *fftOut = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * (fftSize / 2 + 1));
    fftw_plan plan = fftw_plan_dft_r2c_1d(fftSize, audioData.data(), fftOut, FFTW_ESTIMATE);

    fftw_execute(plan);
    fftw_destroy_plan(plan);

    // 分析频率并检测音符
    std::vector<int> midiNotes;
    for (int i = 0; i < fftSize / 2 + 1; ++i)
    {
        double magnitude = sqrt(fftOut[i][0] * fftOut[i][0] + fftOut[i][1] * fftOut[i][1]);
        if (magnitude > 0.1) // 阈值
        {
            double frequency = i * sfinfo.samplerate / fftSize;
            int midiNote = 69 + 12 * log2(frequency / 440.0); // 频率转 MIDI 音符
            midiNotes.push_back(midiNote);
        }
    }
    fftw_free(fftOut);

    // 创建 MIDI 文件
    smf::MidiFile midifile;
    midifile.addTrack(1);
    midifile.setTicksPerQuarterNote(120);

    int time = 0;
    for (int note : midiNotes)
    {
        std::vector<uint8_t> noteOn = {0x90, (uint8_t)note, 64}; // Note On
        midifile.addEvent(0, time, noteOn);
        time += 120;
        std::vector<uint8_t> noteOff = {0x80, (uint8_t)note, 64}; // Note Off
        midifile.addEvent(0, time, noteOff);
    }

    // 写入 MIDI 文件
    midifile.write(midiFile);
}
