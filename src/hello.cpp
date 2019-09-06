#include "hello.h"

hello::hello()
{
    setSize (600, 400);
}

hello::~hello()
{
}

void hello::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void hello::resized()
{

}