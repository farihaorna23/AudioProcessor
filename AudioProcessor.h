#ifndef AUDIOPROCESSOR_H 
#define AUDIOPROCESSOR_H 
#include <vector>       //vector
#include <stdexcept>    //throw exception
#include <iostream>
#include <cmath>

class AudioProcessor
{
    public:
    std::vector<short> Compress(const std::vector<short> & audio, short threshold, float rate);
    std::vector<short> CutOutSilence(const std::vector<short> & audio, short level, int silenceLength);
    std::vector<short> StretchTwice(const std::vector<short> & audio);
    std::vector<short> Normalize(const std::vector<short> & audio, short normalizeTarget);

};


#endif