#include "AudioProcessor.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>


std::vector<short> AudioProcessor::Compress(const std::vector<short> & audio, short threshold, float rate)
{
  
  if(audio.size()==0) ///*********
  {
    return {};
  }
  
  
  if( threshold<0 || rate<1 )
  {
    throw std::invalid_argument("Invalid Argument");
  }

    
  std::vector<short>vec;
  vec.reserve(audio.size());
    
  for(int i=0; i<audio.size(); i++)
  {
    short output=audio[i];
    if(audio[i]>threshold)
    {
      output= (short)std::round((audio[i]-threshold)/rate)+threshold; //13.3-->13   13.5-->14
    }
    
    else if(audio[i]<threshold*-1)
    {
      output= ((short)std::round((-1*audio[i]-threshold)/rate)+threshold)*-1;
    }

        //vec[i]= output;
    vec.push_back(output);
  }
  
    return vec;
} 

std::vector<short> AudioProcessor::CutOutSilence(const std::vector<short> & audio, short level, int silenceLength)
{
    
  if(audio.size()==0) ///*********
  {
    return {};
  }  
  
  
  if(level<0 || silenceLength<1)
  {
    throw std::invalid_argument("Invalid Argument");
  }

  
  std::vector<short>rhs;
  rhs.reserve(audio.size());
  
  std::vector<short>temp;
  temp.reserve(audio.size());
  
  for(int i=0; i<audio.size(); i++)
  {
    if (abs(audio[i])<=level)
    {
      temp.push_back(audio[i]);
    }
      
    else
    {
      if(temp.size()<silenceLength)
      {
        for(int i=0; i<temp.size(); i++)
        {
          rhs.push_back(temp[i]);
        }
      }
        
      temp.clear();
        
      rhs.push_back(audio[i]);
        
    }
  }

  if(temp.size()<silenceLength)
  {
    for(int i=0; i<temp.size(); i++)
    {
      rhs.push_back(temp[i]);
    }
  }
  
  return rhs;
} 

std::vector<short> AudioProcessor::StretchTwice(const std::vector<short> & audio)
{
  if(audio.size()==0) ///*********
  {
    return {};
  }

  if(audio.size()<2)
  {
    return audio;
  }
  
  std::vector<short>rhs;
  rhs.reserve(2*audio.size());
    
  if(audio.size()>0)
  {
    rhs.push_back(audio[0]);
  }
     
  for(int i=1; i<audio.size(); i++)
  {
    int avg=(short)std::round((audio[i-1]+audio[i])/2.0);
    rhs.push_back(avg);
    rhs.push_back(audio[i]);
  }
  
  return rhs;
} 

std::vector<short> AudioProcessor::Normalize(const std::vector<short> & audio, short normalizeTarget)
{
  
  if(audio.size()==0) ///*********
  {
    return {};
  }
  
  if(normalizeTarget<1)
  {
    throw std::invalid_argument("Invalid Argument");
  }

    
  std::vector<short>rhs;
  rhs.reserve(audio.size());
  
  short max=0;
    
  if(audio.size()>0)
  {
    max = abs(audio[0]);
  }
    
  for(int i=1; i<audio.size(); i++)
  {
    if(abs(audio[i])>max)
    {
      max=abs(audio[i]);
    }
  }

  float factor;

  if(max==0)
  {
    factor=1;
  }
  else
  {
    factor= (float)normalizeTarget/max;
  }
    
  for(int i=0; i<audio.size(); i++)
  {
    rhs.push_back(std::round(audio[i]*factor)); 
  }
  
  return rhs;
    
}
