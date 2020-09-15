/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "OtherLookAndFeel.h"

//==============================================================================
/**
*/
class ObliqueReverbAudioProcessorEditor  : public AudioProcessorEditor,
private Button::Listener, private ComboBox::Listener
{
public:
    ObliqueReverbAudioProcessorEditor (ObliqueReverbAudioProcessor&);
    ~ObliqueReverbAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void addSelectionsToComboBox();

    
    void addTextToOblique() {
        obliqueTexts.add("Simulate infinity");
        obliqueTexts.add("Negative Space as foreground");
        obliqueTexts.add("Remove specifics and convert to ambiguities");
        obliqueTexts.add("Humanize something free of error");
        obliqueTexts.add("Randomize something free of error");
        obliqueTexts.add("Go to an extreme before moving back to a more comfortable space");
        obliqueTexts.add("Make the distance reveal the details.");
        obliqueTexts.add("Flatten your perception");
        obliqueTexts.add("Emphasize differences");
        obliqueTexts.add("Remove ambiguities and convert to specifics");
        obliqueTexts.add("Make repetition a form of change");
        obliqueTexts.add("Find difficulty in what should be a simple task");
        obliqueTexts.add("All of it but less");
        obliqueTexts.add("Do the bare minimum");
        obliqueTexts.add("Make audible your mistakes");
        obliqueTexts.add("Make your room");
        obliqueTexts.add("Remove the most important thing");
    }
    
    void addTextToConcrete() {
        
        concreteLabels.add("What does reverb do?");
        concreteTexts.add("Reverb is a spatial effect which confers a perceived sense that a sound exists within a 'space', like a room or a hall. It can be used to provide a sense of depth to mixes, or even to completely transform the initial sound-source into something else, depending on the source sound as well as how the reverb is set up by the producer.");
        
        concreteLabels.add("Long Reverb and when to use it");
        concreteTexts.add("Increasing the decay dial of reverbs will increase the size of the perceived space the sound is in, and also make the reverb tail longer. Long reverbs are useful if you have a track or part of a track that is sparse and requires something to 'glue' the elements together. As a general rule of thumb though, longer reverbs are easy to overuse, particularly if your arrangement is quite busy or the tempo (bpm) of your track is fast. This is because they have a gentle slope on their decay, which can get in the way of other elements in your tracks, particularly elements with sharp transient (Transients are the short burst of energy that you hear at the start of any sound. The loudest of transients are things like drum hits - check the sound wave of a kick or snare and look at the vertical change in sound wave over time). Long reverb is best used to fill the sonic gaps in tracks with sparser arrangements, lower tempos or both. Generally it is recommended to use a lower mix percentage with longer reverbs (or, if you are using the reverb on a send track, reducing the gain of the send), particularly if your arrangement is busy. This is only a rule of thumb though; anything is permitted in sound design provided the results sound good to you. Try and implement some long reverbs on a busy arrangement versus a sparser one.");
        
        concreteLabels.add("Short Reverb and when to use it");
        concreteTexts.add("Decreasing the decay dial of reverbs will decrease the size of the perceived space the sound is in, and make the reverb tail shorter. In general, shorter reverbs are preferred for busier tracks (tracks with lots of elements) or tracks at higher tempos (bpms) if some spatial shaping is required, as shorter reverbs are less likely to interrupt the other elements of your track because they have an abrupt decay slope. Because of this, you are generally able to push the mix percentage (or, if you are using the reverb on a send track, increasing the gain of the send) higher than you would with a longer reverb tail. You are likely to use short reverbs more often when mixing if you write music with a lot of elements. Try and implement some short reverbs on a busy arrangement and compare it to using a longer reverb. Which sounds better? Conversely, do the same on a track with a sparser arrangement.");
        
        concreteLabels.add("Filtering the reverb tail");
        concreteTexts.add("This reverb comes with a dedicated low-pass filter. Filters are used on reverbs to shape their presence in the mix and also how the reverb interacts with the element it is acting upon. On sharp sounds, like vocal consonants and clicking percussion, reverb can amplify the sibilant frequencies and introduce an unwanted ringing or slapping sound that floats over the mix. Rolling off some highs on your favorite reverb plug-in prevents this from happening while preserving the overall reverb feel. Low-pass filters are also handy for introducing a sense of mix depth; a bright reverb will sound up-front, whereas a darker verb seems to come from further back in the mix. This comes down to the way we perceive sound in real-life scenarios outside of a DAW. Things that are further away from us sound quieter, but they also sound more muted as the reflections are diffused and absorbed by things and people in the surrounding environment.");
        
        concreteLabels.add("Tailoring the Mix");
        concreteTexts.add("The mix dial dictates the proportion of dry (non-reverb) to wet (reverb) signal that the reverb allows through its output. In most cases, you would want to use a low percentage mix for your drums (5%-25%), a mid percentage mix for your chords and leads (i.e. the lead components of your track) (15%-40%), a high percentage mix for your pads (25%-45%), and a super high percentage mix for your background elements (30%-70%). One exception to this is the use of reverb on a send, where in nearly all situations you should use 100% mix to ensure that you are not duplicating any dry output signal from the actual sound source (see the Reverb as a send effect lesson for more info). Try out the above proportions on their respective element in your track, then compare it against other proportions. In most cases, these will feel right for you, but bear in mind it is fine to go outside of these ranges; how the end product sounds always trumps theoretical suggestions.");
        
        concreteLabels.add("Automating the Mix");
        concreteTexts.add("Mix automation (that is, changing the mix dial over time), is an essential component to reverb usage; it allows you to match the reverb settings to the context and intensity of the music. Automating the mix proportion to increase over time can create a 'swell' effect that can be used to add excitments to key moments in your track. Converseley, subtle automation to reduce the mix proportion on a reverb-heavy element in your track can provide your track with extra clarity in busier sections, and also provide extra contrast between different sections of your track. Try automating the mix from low to high on an element in your track as you transition from one section to another. Also try reducing the mix of a reverb-heavy element as your track introduces more elements.");
        
        concreteLabels.add("Automating the filter");
        concreteTexts.add("In this reverb, you have control over a low-pass filter; that is, a parameter which allows you to control the frequency spectrum of the reverb tail specifically. As a general rule of thumb, you will find that setting this to a high value will make the reverb feel 'brighter' (have a higher density of high frequencies), which makes the sound seem more up front or present in the mix. Conversely, setting this to a low value will make the reverb tail feel 'darker' (have a low density of high frequencies), and will make the sound seem further away, and thus quieter. As a result, you can use this paramater to simulate the placement of elements of your track in a 3d space. Automating it will change the perceived closeness of the sound and can be used to bring elements of your track either further forward or back in a mix. Try this on an element that you want to introduce in a subtle way, where it initially appears in the background but gradually becomes a key element as your track goes on.");
        
        concreteLabels.add("Automating the decay?");
        concreteTexts.add("Decay is a time-based effect, dictating the time it takes for the reverb reflections to fade away. Automating the decay of an element with reverb is uncommon in non-electronic styles, where it is the job of the producer / mixing engineer to create a sense of the recording being in a certain space. Changing this too much undermines this and can create a confusing experience for the listener. In electronic music however, there are fewer considerations and as a result, it is within the remit of the producer to make creative decisions about how to change the decay of an element over time. Although it is rare, decay automation can be used to tighten transitions between sections of your track; try reducing the decay of an element with a long tail as the track introduces more parts, or the inverse. Automating the decay can also be used for sound-design. Within electronic music, the producer has total control over texture and spatial manipulation, so this can be used creatively and a sound design tool, particularly for more textural / ambient elements such as pads and found-sound ambience.");
        
        concreteLabels.add("Using bypasses");
        concreteTexts.add("The bypass parameter has several creative uses. Firstly, it can be activated on sections where the element the reverb is attached to isn't playing, to ensure that none of the residual decay of the reverb bleeds over if not desired. The second is to suddenly introduce / take away reverb from an element, which can be useful when you have an element such as a chord sequence where you don't want the reverb decay of each chord to bleed into the next one. Automating the bypass off and on for each chord in the sequence can fix this issue.");
        
        concreteLabels.add("Reverb as a send effect");
        concreteTexts.add("When adding reverb as a send (if you don't know what a send is, refer to your DAW's manual), always ensure that you set the mix of your reverb to 100%. Otherwise, you will have some of the dry signal outputting through the send as well as the through the original track. Only change the mix parameter from 100% if you are inserting it onto the sound signal's effect chain directly.");
        
        concreteLabels.add("Advanced: reverb on multiple sends");
        concreteTexts.add("Send an element of your track (such as a lead) into two separate, but complementary reverbs on individual sends, and pan the sends hard left and right. The center will stay clear for the original element and the sides will provide the space. Listen to the before and after of a vocal with a stereo verb and the three channel setup described here.");
        
        concreteLabels.add("Advanced: panning a reverb send");
        concreteTexts.add("Leave the sound in the center, but automate its reverb bus to pan back and forth to create the impression of movement. This can make for a unique special effect in sparse mixes where small details are noticeable.");
        
        //
        
        concreteLabels.add("Beyond this reverb plugin: pre-delay");
        concreteTexts.add("Pre-delay refers to the amount of time between the original dry sound, and the audible onset of early reflections and reverb tail. Carefull adjusting the pre-delay parameter makes a huge difference in the 'clarity' of a mix. A longer pre-delay is used to make a clear distinction between the original sound and its reverb, and generall has the effect of making the sound appear closer to the listener in a physical space. Pre-delay can also be used rhythmically - setting the pre-delay of a reverb to be in time with the rhythmic meter of your track will make your track feel more rhythmically 'tight'.");
        
        concreteLabels.add("Beyond this reverb plugin: diffusion");
        concreteTexts.add("Diffusion, also known as shape, represents the complexity of the room the reverb takes place in. More complex rooms mean more surfaces to bounce off of and thus more diffusion. Diffusion also controls the density of the amount of reverbs, allowing you to create a more washy effect or have many distinct echoes.");
        
        concreteLabels.add("Beyond this reverb plugin: other filters");
        concreteTexts.add("When using reverb as a send, you have control over the reverb sound isolated from the sound signal which comes through it. This allows you to control the frequencies output by the reverb; for example, using a high pass filter to cut out the low frequencies can assist with making your low-end elements kick through your mix more. The interactions between reverb and filters are multidudinous and complex, but generally speaking you use them in conjunction to control the interactions of the different elements of your mix or to provide extra 'movement' and textural metamorphosis to a sound.");
        
        concreteLabels.add("Reverb as sound design");
        concreteTexts.add("Reverb can be used to fundamentally alter the sonic charateristics of a sound when used heavily and particularly in conjunction with other effects. For example, you could turn a shot vocal snippet into a background pad or atmospheric ambience by adding an extremely long decay tail to it, and using a combination of the inbuilt filter or other filter effects to generate a sense of the sound morphing over time. Morphing elements are pleasing to the ear and can provide important contrast in music that is repetitive by nature.");
        
        ///
        
        concreteLabels.add("Beyond this reverb: panning / mono");
        concreteTexts.add("Just as we pan individual sounds to enhance the stereo image of a mix, we can add some interest to the left-right space by panning reverb returns. There are many combinations, but here are a few that works quite well: 1. To more clearly reinforce the spatial location of a sound, pan its reverb to the same (or a similar) position. For some hard-panned sounds, it can be confusing if its reverb goes off in a different direction. 2. Leave the sound in the center, but automate its reverb bus to pan back and forth to create the impression of movement. This can make for a unique special effect in sparse mixes where small details are noticeable. 3. Mono-ing your reverb send or channel might sound a little counter-intuitive, and although usage is rare, narrow or even mono-ed reverbs have their place in production, particularly on drums. Kick drums in particular benefit from mono-ed reverb - reverb should almost always be avoided on low-end elements (because they muddy the mix and cause other issues such as phasing), but a mono-ed reverb on a kick can lead to interesting results.");
        
        concreteLabels.add("Beyond this reverb: reverb types");
        concreteTexts.add("Not all reverbs are designed in the same way (obviously). Some focus on simulating a real space such as a room or a hall, while others use synthetic reverb types (such as plate and spring reverb).");
        
        concreteLabels.add("Beyond this reverb: avoid too many types");
        concreteTexts.add("If you are using lots of reverb and different styles / plugins each time around, you'll end up with a stange mix that's unsure of exactly what it's trying to be. To restore the focus, you may want to limit the amount and types of spaces your mix exists in. The shouldn't have to ask themselves 'Where am I?' but should instead immediately think 'I'm comfortable here.' ");
        

    }

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ObliqueReverbAudioProcessor& processor;
    void buttonStateChanged(Button*) override;
    void buttonClicked(Button*) override;
    void comboBoxChanged(ComboBox*) override;
    int currentItemIndex = 1;
    juce::Array<String> obliqueTexts;
    juce::Array<String> concreteTexts;
    juce::Array<String> concreteLabels;
    
    juce::Random rand;
    int maxNum;
    
    juce::Font textFont {"Arial", 17, Font::plain};
    juce::Font labelFont {"Arial", 14, Font::plain};
    
    static String concreteToolTip;
    static String obliqueToolTip;
    static String lessonsToolTip;
    static String nextToolTip;
    static String previousToolTip;
    static String mixToolTip;
    static String decayToolTip;
    static String lpfToolTip;
    static String bypassToolTip;
    static String textToolTip;
    TooltipWindow tooltipWindow {this, 1000};
    
    OtherLookAndFeelSlider otherLookAndFeelSlider;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ObliqueReverbAudioProcessorEditor)
    
    //Reverb Parameters
    juce::Slider mMixSlider {Slider::RotaryHorizontalVerticalDrag,
        Slider::TextBoxBelow};
    juce::Slider mDecaySlider {Slider::RotaryHorizontalVerticalDrag,
        Slider::TextBoxBelow};
    juce::Slider mLPFSlider {Slider::RotaryHorizontalVerticalDrag,
        Slider::TextBoxBelow};
    juce::ToggleButton mBypass;
    juce::ComboBox obliqueConcreteChoices;
    juce::TextButton oblique;
    juce::TextButton concrete;
    juce::Label text;
    ArrowButton next {"next", 0.0, juce::Colours::white};
    ArrowButton previous {"previous", 0.5, juce::Colours::white};
    juce::Label mixLabel;
    juce::Label decayLabel;
    juce::Label lpfLabel;
    
    
    AudioProcessorValueTreeState::SliderAttachment mMixAttachment {
        processor.getValueTreeState(),
        ObliqueReverbAudioProcessor::paramMix, mMixSlider};
    AudioProcessorValueTreeState::SliderAttachment mDecayAttachment {
        processor.getValueTreeState(), ObliqueReverbAudioProcessor::paramDecay,
        mDecaySlider};
    AudioProcessorValueTreeState::SliderAttachment mLPFAttachment {
        processor.getValueTreeState(), ObliqueReverbAudioProcessor::paramLPF,
        mLPFSlider};
    AudioProcessorValueTreeState::ButtonAttachment mBypassAttachment {
        processor.getValueTreeState(), ObliqueReverbAudioProcessor::paramBypass,
        mBypass};
    AudioProcessorValueTreeState::ButtonAttachment
    mObliqueAttachment { processor.getValueTreeState(), "oblique", oblique };
    AudioProcessorValueTreeState::ButtonAttachment mConcreteAttachment
    { processor.getValueTreeState(), "concrete", concrete };
    AudioProcessorValueTreeState::ComboBoxAttachment mObConcreteAttachment { processor.getValueTreeState(), "obliqueConcrete", obliqueConcreteChoices};
};
