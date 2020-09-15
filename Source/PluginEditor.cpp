/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
String ObliqueReverbAudioProcessorEditor::concreteToolTip ("The concrete mode provides you with a series of lessons aimed to teach you the basics of reverb usage in a variety of production and mix settings.");

String ObliqueReverbAudioProcessorEditor::obliqueToolTip ("The oblique mode provides you with a series of prompts that are aimed to stimulate creativity in the sound design and mixing process. These will not provide direct instructions; only abstract concepts to use as brain food.");

String ObliqueReverbAudioProcessorEditor::lessonsToolTip ("This selection box allows you to choose which lesson you'd like to undertake. Note that this will only appear for the Concrete Mode. To change the Oblique prompt, use the next and previous arrows at the bottom right of the User Interface");

String ObliqueReverbAudioProcessorEditor::nextToolTip ("Loads the next prompt.");

String ObliqueReverbAudioProcessorEditor::previousToolTip ("Re-loads the previous prompt");

String ObliqueReverbAudioProcessorEditor::mixToolTip ("Indicates the proportion of the output which is dry (i.e. has no reverb) and the proportion which is wet (has the reverb). At 0%, only the dry signal is output, and at 100%, only the wet signal is output");

String ObliqueReverbAudioProcessorEditor::decayToolTip ("Sets the decay time of the reverb. Think of this as the length of the reverb tail, with larger values giving longer reverb tails.");

String ObliqueReverbAudioProcessorEditor::lpfToolTip ("The LPF setting simulates the 'brightness' of the reverb. Brightness is a term which refers to the density of high frequencies in a sound source, so think of this as a filter for the reverb tail, with lower values giving you a warmer tail with a lower density of high frequencies, and higher values giving you a bright, high-frequency-rich tail.");

String ObliqueReverbAudioProcessorEditor::bypassToolTip ("Ticking this bypasses the effect completely.");

String ObliqueReverbAudioProcessorEditor::textToolTip ("This section displays the lesson or prompt.");

ObliqueReverbAudioProcessorEditor::ObliqueReverbAudioProcessorEditor (ObliqueReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    setLookAndFeel(&otherLookAndFeelSlider);
    addAndMakeVisible(mMixSlider);
    mMixSlider.setTooltip(mixToolTip);
    addAndMakeVisible(mDecaySlider);
    mDecaySlider.setTooltip(decayToolTip);
    addAndMakeVisible(mLPFSlider);
    mLPFSlider.setTooltip(lpfToolTip);
    addAndMakeVisible(mBypass);
    mBypass.setTooltip(bypassToolTip);
    
    addAndMakeVisible(oblique);
    oblique.setName("Oblique");
    oblique.setComponentID("oblique");
    oblique.setButtonText("Oblique");
    oblique.setRadioGroupId(1);
    oblique.addListener(this);
    oblique.setTooltip(obliqueToolTip);
    
    addAndMakeVisible(concrete);
    concrete.setName("Concrete");
    concrete.setComponentID("concrete");
    concrete.setButtonText("Concrete");
    concrete.setRadioGroupId(1);
    concrete.addListener(this);
    concrete.setTooltip(concreteToolTip);
    
    addAndMakeVisible(obliqueConcreteChoices);
    obliqueConcreteChoices.setName("Oblique Concrete");
    obliqueConcreteChoices.setComponentID("obConcrete");
    obliqueConcreteChoices.setTextWhenNothingSelected("Lessons");
    obliqueConcreteChoices.setTooltip(lessonsToolTip);
    obliqueConcreteChoices.setSelectedItemIndex(currentItemIndex);
    obliqueConcreteChoices.addListener(this);
    
    next.setComponentID("next");
    next.addListener(this);
    next.setTooltip(nextToolTip);
    addAndMakeVisible(next);
    
    previous.setComponentID("previous");
    previous.addListener(this);
    previous.setTooltip(previousToolTip);
    addAndMakeVisible(previous);
    
    concrete.triggerClick();
    
    addAndMakeVisible(text);
    addAndMakeVisible(tooltipWindow);
    
    addTextToOblique();
    addTextToConcrete();
    int i = 1;
    
    for(String s : concreteLabels) {
        obliqueConcreteChoices.addItem(s, i);
        i++;
    }
    
    text.setName("lessons");
    text.setText(obliqueTexts.getReference(currentItemIndex), dontSendNotification);
    obliqueConcreteChoices.setSelectedId(currentItemIndex);
    
    setSize (500, 500);
}

ObliqueReverbAudioProcessorEditor::~ObliqueReverbAudioProcessorEditor()
{
    setLookAndFeel (nullptr);
}

void ObliqueReverbAudioProcessorEditor::addSelectionsToComboBox()
{
    
}

void ObliqueReverbAudioProcessorEditor::comboBoxChanged(ComboBox* c)
{
    text.setText(concreteTexts.getReference(c->getSelectedId()-1),
                 dontSendNotification);
}



void ObliqueReverbAudioProcessorEditor::buttonStateChanged(Button* b)
{
    
    
}

void ObliqueReverbAudioProcessorEditor::buttonClicked(Button* b)
{
    if(b == &next)
    {
        currentItemIndex++;
        if(concrete.getToggleState())
        {
            if(currentItemIndex >= obliqueConcreteChoices
            .getNumItems())
            {
                currentItemIndex = 1;
                obliqueConcreteChoices
                .setSelectedItemIndex(currentItemIndex);

            } else
            {
                obliqueConcreteChoices
                .setSelectedItemIndex(currentItemIndex);
            }
        } else
        {
            
            text.setText(obliqueTexts.getReference
                         (rand.nextInt(obliqueTexts.size()-1)),
                         dontSendNotification);
        }
    } else if(b == &previous) {
         currentItemIndex--;
        if(concrete.getToggleState())
        {
            if(currentItemIndex >= 0)
            {
                obliqueConcreteChoices
                .setSelectedItemIndex(currentItemIndex);
            } else
            {
                obliqueConcreteChoices
                .setSelectedItemIndex(obliqueConcreteChoices
                                        .getNumItems()-1);
                currentItemIndex = obliqueConcreteChoices
                .getNumItems()-1;
            }
        } else {
            if(currentItemIndex >= 0)
            {
                text.setText(obliqueTexts
                             .getReference(currentItemIndex),
                             dontSendNotification);
            } else
            {
                currentItemIndex = obliqueTexts.size() - 1;
                       
                text.setText(obliqueTexts
                             .getReference(currentItemIndex),
                             dontSendNotification);
            }
        }
    } else if (b == &oblique)
    {
        obliqueConcreteChoices.setEnabled(false);
        obliqueConcreteChoices.setVisible(false);
        text.setText(obliqueTexts.getReference(0),
                     dontSendNotification);
        oblique.setToggleState(true, dontSendNotification);
        concrete.setToggleState(false, dontSendNotification);
        concrete.setAlpha(0.5);
        oblique.setAlpha(1.0);
    } else if (b == &concrete)
    {
        obliqueConcreteChoices.setEnabled(true);
        obliqueConcreteChoices.setVisible(true);
        oblique.setToggleState(false, dontSendNotification);
        concrete.setToggleState(true, dontSendNotification);
        text.setText(concreteTexts
                     .getReference(obliqueConcreteChoices
                                   .getSelectedId()-1),
                     dontSendNotification);
        oblique.setAlpha(0.5);
        concrete.setAlpha(1.0);
    }
    
}

//==============================================================================
void ObliqueReverbAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::grey);

    g.setColour (Colours::white);
    g.setFont (17.0f);
    g.setFont(textFont);
       
    Rectangle<int> topBox (0,0, getWidth()-20, (getHeight()-10)/3);
    Rectangle<int> box (0, getHeight()/2, getWidth()-20,
                        getHeight()-10/3);
    Rectangle<int> bottomBox (0, getHeight()/3, getWidth()-20,
                              getHeight()-10/3);
    //topBox.setBounds(0, 0, getWidth()-20, getHeight()-10/2);
    //box.setBounds(0, getHeight()/2, getWidth()-20, getHeight()-10/2);
    box = box.withTop(10);
    topBox = topBox.withTop(160);
    text.setColour(Label::textColourId, juce::Colours::white);
    text.setFont(labelFont);
       
    const auto width = topBox.getWidth() / 4;
    g.drawFittedText(TRANS("Mix"), topBox.removeFromLeft (width),
                     Justification::centred, 1);
    g.drawFittedText (TRANS ("Decay"), topBox.removeFromLeft (width),
                      Justification::centred, 1);
    g.drawFittedText (TRANS ("Low-Pass"), topBox.removeFromLeft (width),
                      Justification::centred, 1);
    g.drawFittedText(TRANS ("Bypass"), topBox.removeFromLeft(width),
                     Justification::centred, 1);
}

void ObliqueReverbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    Rectangle<int> topBox (0,0, getWidth()-20, (getHeight()-10)/3);
    Rectangle<int> box (0, getHeight()/2, getWidth()-20,
                        getHeight()-10/3);
    Rectangle<int> bottomBox (0, getHeight()/3-150, getWidth()-20,
                              getHeight()-10/3);
    //topBox.setBounds(0, 0, getWidth()-20, getHeight()-10/2);
    //box.setBounds(0, getHeight()/2, getWidth()-20, getHeight()-10/2);
    box = box.withTop(20);
    topBox = topBox.withTop(20);

    const auto width = topBox.getWidth() / 4;
    mMixSlider.setBounds (topBox.removeFromLeft (width).reduced (10));
    mDecaySlider.setBounds (topBox.removeFromLeft (width).reduced
                            (10));
    mLPFSlider.setBounds (topBox.removeFromLeft (width).reduced (10));
    mBypass.setBounds (topBox.removeFromLeft(width-70).reduced (10));
    mBypass.setCentrePosition
    (topBox.removeFromLeft(width-100).getCentre());
    
    const auto midWidth = box.getWidth() / 3;
    obliqueConcreteChoices.setBounds(10, getHeight()/2-30,
                                     midWidth+50, 30);
    oblique.setBounds(midWidth*2 + 25,  getHeight()/2-30, 75, 30);
    concrete.setBounds(midWidth*2 + 100, getHeight()/2-30, 75, 30);
    
    //const auto bottomWidth2 = 100;
    
    previous.setBounds(getWidth()-100, getHeight()-40, 50, 30);
    next.setBounds(getWidth()-50, getHeight()-40, 50, 30);
    text.setBounds(bottomBox.reduced(10).removeFromBottom(250));
    text.toBack();
    next.setAlpha(0.5);
    text.setFont(textFont);
    previous.setAlpha(0.5);
    
}
