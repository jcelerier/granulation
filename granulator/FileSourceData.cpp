#include "FileSourceData.hpp"
#include <sndfile.hh>
#include <iostream>

namespace Granulation {
namespace Synthesis {

FileSourceData::FileSourceData() :
    SourceData(),
    m_channels{0},
    m_sampleRate{0},
    m_data{std::vector<float> ()}
{}

void FileSourceData::populate() {
    SF_INFO info;
    info.format = 0;
    SNDFILE* file = sf_open(m_filename.c_str(), SFM_READ, &info);
    if (file) {
        std::cout << info.format << std::endl;
        m_sampleRate = info.samplerate;
        m_channels = info.channels;
        m_data.resize(info.frames * info.channels);
        int16_t samples[info.channels];
        for (int i = 0; i < info.frames; ++i) {
            sf_readf_short(file, samples, 1);
            for (int j = 0; j < info.channels; ++j) {
                m_data[i * info.channels + j] = (float)samples[j] / 32768.f;
            }
        }

        std::cout << "sr: " << m_sampleRate << std::endl;
        sf_close(file);
    }
    else {
        std::cout << "Could not load file" << m_filename << sf_strerror(nullptr) << std::endl;
    }
}

float FileSourceData::data(int i) const {
    return m_data[i];
}

const unsigned int FileSourceData::size() const {
    return m_data.size();
}

int FileSourceData::sampleRate() const {
    return m_sampleRate;
}

void FileSourceData::setSource(std::string filename) {
    m_filename = filename;
    populate();
}

int FileSourceData::channels() const {
    return m_channels;
}

}
}
