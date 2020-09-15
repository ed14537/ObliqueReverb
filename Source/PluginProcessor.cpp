/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
String ObliqueReverbAudioProcessor::paramMix ("Mix");
String ObliqueReverbAudioProcessor::paramDecay ("Decay");
String ObliqueReverbAudioProcessor::paramLPF ("Filter Cutoff");
String ObliqueReverbAudioProcessor::paramBypass ("Master Bypass");
String ObliqueReverbAudioProcessor::paramOblique ("Oblique");
String ObliqueReverbAudioProcessor::paramConcrete ("Concrete");
String ObliqueReverbAudioProcessor::paramObliqueConcrete
 ("ObliqueConcrete");

ObliqueReverbAudioProcessor::ObliqueReverbAudioProcessor() : rTree (*this, nullptr, "Reverb", createParameterLayout())
{
    UserParams[MasterBypass] = 0.0f;
    UserParams[Mix] = 50.0f;
    UserParams[Decay] = 3.0f;
    UserParams[LPF] = 3800.0f;
    
    
    UIUpdateFlag = true;
        
    rTree.addParameterListener(paramMix, this);
    rTree.addParameterListener(paramDecay, this);
    rTree.addParameterListener(paramLPF, this);
    rTree.addParameterListener(paramBypass, this);
    rTree.addParameterListener(paramOblique, this);
    rTree.addParameterListener(paramConcrete, this);
    rTree.addParameterListener(paramObliqueConcrete, this);

}

AudioProcessorValueTreeState::ParameterLayout ObliqueReverbAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<RangedAudioParameter>> params;
    
    auto mixParam = std::make_unique<AudioParameterFloat>(paramMix, TRANS("Mix"), NormalisableRange<float> (0.0f, 100.0f, 0.5f), 50.0f, "", AudioProcessorParameter::genericParameter, [](float v, int) {return String (v, 1);}, [](const String& t) {return t.dropLastCharacters(3).getFloatValue(); });
    auto decayParam = std::make_unique<AudioParameterFloat>
        (paramDecay, TRANS("Decay"), NormalisableRange<float>
        (1.0f, 12.0f, 0.1f), 3.0f, "Ms",
        AudioProcessorParameter::genericParameter,
        [](float v, int) {return String(v, 1) + "Ms";}, []
        (const String& t) {return t.dropLastCharacters(3)
        .getFloatValue();});
    auto filterParam = std::make_unique<AudioParameterFloat>
        (paramLPF, TRANS("LPF"), NormalisableRange<float>
        (0.0f, 20000.0f, 40.0f), 3800.0f, "Hz",
        AudioProcessorParameter::genericParameter,
        [](float v, int) { return String (v, 1) + "Hz"; },
        [](const String& t) { return
        t.dropLastCharacters(3).getFloatValue(); });
    auto bypassParam = std::make_unique<AudioParameterFloat>
        (paramBypass, TRANS("Bypass"), NormalisableRange<float>
        (0.0f, 1.0f, 1.0f), 0.0f, "",
        AudioProcessorParameter::genericParameter, [](float v, int) {
        return String (v, 1); },
        [](const String& t) { return t.dropLastCharacters
        (3).getFloatValue(); });
    auto obliqueParam = std::make_unique<AudioParameterFloat>
        (paramOblique, TRANS("Oblique"),
        NormalisableRange<float>(0.0f, 1.0f, 1.0f), 0.0f);
    auto concreteParam = std::make_unique<AudioParameterFloat>
        (paramConcrete, TRANS("Concrete"),
        NormalisableRange<float>(0.0f, 1.0f, 1.0f), 0.0f);
    auto obliqueConcreteParam =  std::make_unique<AudioParameterFloat>
        (paramObliqueConcrete, TRANS("Oblique Concrete"),
        NormalisableRange<float>(0.0f, 20.0f), 1.0f);
    
    params.push_back(std::move(mixParam));
    params.push_back(std::move(decayParam));
    params.push_back(std::move(filterParam));
    params.push_back(std::move(bypassParam));
    params.push_back(std::move(obliqueParam));
    params.push_back(std::move(concreteParam));
    params.push_back(std::move(obliqueConcreteParam));
    
    
    
    return { params.begin(), params.end() };
}
    
void ObliqueReverbAudioProcessor::parameterChanged(const String &parameterId, float
                                       newValue)
{
    if (parameterId == paramMix)
    {
        UserParams[Mix] = newValue;
    }
    else if (parameterId == paramDecay)
    {
        UserParams[Decay] = newValue;
        mRevLeft.setDecayFactor(UserParams[Decay]);
        mRevRight.setDecayFactor(UserParams[Decay]);
    }
    else if (parameterId == paramLPF)
    {
        UserParams[LPF] = newValue;
        mRevLeft.setLPFreq(UserParams[LPF]);
        mRevRight.setLPFreq(UserParams[LPF]);
    }
    else if (parameterId == paramBypass)
    {
        UserParams[MasterBypass] = newValue;
        mRevLeft.setBypass((bool)UserParams[MasterBypass]);
        mRevRight.setBypass((bool)UserParams[MasterBypass]);
    }
}

void ObliqueReverbAudioProcessor::releaseResources()
{
    
}
    
AudioProcessorValueTreeState& ObliqueReverbAudioProcessor::getValueTreeState()
{
    return rTree;
}
    
void ObliqueReverbAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{

}
        
void ObliqueReverbAudioProcessor::processBlock
                (juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
            //if UI has bypass value then dont do any processing
            if(UserParams[MasterBypass])
                return;
                           
            int numSamples = buffer.getNumSamples(); //THIS IS NUM SAMPLES PER CHANNEL
            float mix = *rTree.getRawParameterValue("Mix")/100;
                   
            // This is the place where you'd normally do the guts of your plugin's
            // audio processing...
            float* channelDataLeft = buffer.getWritePointer(0);  //buffer.getSampleData(0);
            float* channelDataRight = buffer.getWritePointer(1);

            float outL=0.0f, outR=0.0f;
                   
            for(int i = 0; i < numSamples; i+=2){
                float in = channelDataLeft[i], in_1 = channelDataRight[i+1];
                       
                       
            //here we have to create a mixing matrix as proposed by Jot
            //  [ +1    +1 ]
            //  [ +1    -1 ]
            //  [ +1    +1 ]
            //  [ +1    -1 ]
            //  [ +1    +1 ]
            //  [ +1    -1 ]
            //
            //and access each of the component parts and its output seperately
                       
            //CIRCUIT IS : ERS > APF1 > PARRALLEL COMBS 1-6 > SUMMING COMBS > LATE REFLECTION DELAY
            float erSummedLeft=0.0f, erSummedRight = 0.0f;
            erSummedLeft = mRevLeft.getEROutput(in);
            erSummedRight = mRevRight.getEROutput(in_1);
                
            float c1_l=0.0f, c2_l=0.0f, c3_l=0.0f, c4_l=0.0f, c5_l=0.0f, c6_l=0.0f, c1_r=0.0f, c2_r=0.0f, c3_r=0.0f, c4_r=0.0f, c5_r=0.0f, c6_r=0.0f;
            float erScaledLeft=erSummedLeft;
            float erScaledRight=erSummedRight;
                       
            float outAllPassL, outAllPassR = 0.0f;
            outAllPassL = mRevLeft.getAllpassOutput(erScaledLeft,0);
            outAllPassR = mRevRight.getAllpassOutput(erScaledRight,0);
                       
            c1_l = mRevLeft.getCombOutput(outAllPassL*0.70f,0);
            c1_r = mRevRight.getCombOutput(outAllPassR*0.70f,0);

            c2_l = mRevLeft.getCombOutput(outAllPassL*0.70f,1);
            c2_r = mRevRight.getCombOutput(outAllPassR*-0.70f,1);

            c3_l = mRevLeft.getCombOutput(outAllPassL*0.70f,2);
            c3_r = mRevRight.getCombOutput(outAllPassR*0.70f,2);
                
            c4_l = mRevLeft.getCombOutput(outAllPassL*0.70f,3);
            c4_r = mRevRight.getCombOutput(outAllPassR*-0.70f,3);

            c5_l = mRevLeft.getCombOutput(outAllPassL*0.70f,4);
            c5_r = mRevRight.getCombOutput(outAllPassR*0.70f,4);
                       
            c6_l = mRevLeft.getCombOutput(outAllPassL*0.70f,5);
            c6_r = mRevRight.getCombOutput(outAllPassR*-0.70f,5);

            //apply summing of individual comb ouputs
            float outMatrixL=0.0f, outMatrixR=0.0f,outCombL=0.0f, outCombR=0.0f;
            outCombL = ((c1_l * 0.30f) - (c2_l * 0.30f) + (c3_l * 0.30f) - (c4_l * 0.30f) + (c5_l * 0.30f) - (c6_l * 0.30f));
            outCombR = ((c1_r * 0.30f) - (c2_r * 0.30f) + (c3_r * 0.30f) - (c4_r * 0.30f) + (c5_r * 0.30f) - (c6_r * 0.30f));
                       
            float lr_ShiftLeft = 0.0f, lr_ShiftRight = 0.0f;
                   
            //Late Reflections generated delay to provide a slight delay in
            //the return of the late reflections reverberant tail
            lr_ShiftLeft = mRevLeft.getLR(outCombL);
            lr_ShiftRight = mRevRight.getLR(outCombR);
                   
            //add the ERs and late reverberation tail
            outMatrixL = (erSummedLeft*0.50f) + lr_ShiftLeft;
            outMatrixR = (erSummedRight*0.50f) + lr_ShiftRight;
                       
            //Scale outputs of left/right with the mix wet/dry ratio
            outL = mix * outMatrixL + (1.0f - mix) * in;
            outR = mix * outMatrixR + (1.0f - mix) * in_1;
                       
            channelDataLeft[i] = outL;
                       
            //MONO-IN, Stereo Out
            if(getTotalNumInputChannels() == 1 && getTotalNumOutputChannels()
               == 2)
            {
                channelDataRight[i+1] = channelDataLeft[i]; //copy mono
            }
                       
                       //Stereo In , Stereo Out
            if(getTotalNumInputChannels() == 2 && getTotalNumOutputChannels()
               == 2)
            {
                channelDataRight[i+1] = outR;
            }

                
            }
                   
            // In case we have more outputs than inputs, we'll clear any output
            // channels that didn't contain input data, (because these aren't
            // guaranteed to be empty - they may contain garbage).
            for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
            {
                buffer.clear (i, 0, buffer.getNumSamples());
            }
        
}
    
void ObliqueReverbAudioProcessor::processBlockBypassed (AudioSampleBuffer& buffer,
                                                MidiBuffer& midiMessages)
{
        int numSamples = buffer.getNumSamples(); //THIS IS NUM SAMPLES PER CHANNEL

        for(int channel = 0; channel < getTotalNumInputChannels(); channel++){
            float* channelData = buffer.getWritePointer(channel);
            for(int i = 0; i < numSamples; i++){
                //float in = channelData[i], out = 0.0f;
                //out = in;
                channelData[i] = channelData[i];
                
            }
        }
       
        return;
}

AudioProcessorEditor* ObliqueReverbAudioProcessor::createEditor()
{
    return new ObliqueReverbAudioProcessorEditor (*this);
}
    
void ObliqueReverbAudioProcessor::getStateInformation (MemoryBlock& destData)
{
        // You should use this method to store your parameters in the memory block.
        // You could do that either as raw data, or use the XML or ValueTree classes
        // as intermediaries to make it easy to save and load complex data.
        MemoryOutputStream stream(destData, false);
        rTree.state.writeToStream (stream);
}

void ObliqueReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
        // You should use this method to restore your parameters from this memory block,
        // whose contents will have been created by the getStateInformation() call.
        ValueTree tree = ValueTree::readFromData (data, sizeInBytes);
        if (tree.isValid()) {
            rTree.state = tree;
        }
        UIUpdateFlag = true; //Request UI update
}
        
const juce::String ObliqueReverbAudioProcessor::getName() const { return "Oblique Concrete Reverb"; }

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ObliqueReverbAudioProcessor();
}
