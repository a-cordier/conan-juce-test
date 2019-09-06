#pragma once

#include <juce.h>

class hello: public Component {
public:
    hello();
    ~hello();

    void paint (Graphics&) override;
    void resized() override;
};


