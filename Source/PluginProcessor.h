/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

//==============================================================================
/**
*/
#pragma once
#include <JuceHeader.h>
#include "Moorer.h"

class ObliqueReverbAudioProcessor  : public AudioProcessor,
                public AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    ObliqueReverbAudioProcessor();
    ~ObliqueReverbAudioProcessor() {};

    //==============================================================================
    void prepareToPlay (double, int) override;
    void releaseResources() override;
    void processBlock (juce::AudioSampleBuffer&, juce::MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override     { return true; }

    //==============================================================================
    const juce::String getName() const override;
    bool acceptsMidi() const override    { return false; }
    bool producesMidi() const override   { return false; }
    double getTailLengthSeconds() const override { return 0; }

    //==============================================================================
    int getNumPrograms() override                                { return 0; }
    int getCurrentProgram() override                             { return 0; }
    void setCurrentProgram (int) override                        {}
    const juce::String getProgramName (int) override             { return {}; }
    void changeProgramName (int, const juce::String&) override   {}
    void processBlockBypassed (AudioSampleBuffer& buffer, MidiBuffer&
                               midiMessages) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    /*float getParameter(int index) override;
    void setParameter(int index, float newValue) override;*/
    void parameterChanged(const String &parameterId, float newValue) override;
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    
    AudioProcessorValueTreeState& getValueTreeState();
    
    enum Parameters{
        MasterBypass = 0,
        Mix,
        Decay,
        LPF,
        NumParams
    };
    
    bool NeedsUIUpdate(){return UIUpdateFlag;};
    void ClearUIUpdateFlag(){UIUpdateFlag = false;};
    void RaiseUIUpdateFlag(){UIUpdateFlag = true;};
    
    static String paramBypass;
    static String paramMix;
    static String paramDecay;
    static String paramLPF;
    static String numParams;
    static String paramOblique;
    static String paramConcrete;
    static String paramObliqueConcrete;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ObliqueReverbAudioProcessor)
    
    float UserParams[NumParams];
    
    Moorer mRevLeft;
    Moorer mRevRight;

    
    bool UIUpdateFlag;
    
    AudioProcessorValueTreeState rTree;
};
