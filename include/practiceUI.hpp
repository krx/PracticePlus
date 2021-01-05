#pragma once

#include "main.hpp"

void increaseNJS();
void decreaseNJS();
void resetNJS();

void increaseOffset();
void decreaseOffset();
void resetOffset();

void updateNJSText();
void updateOffsetText();

class PracticeMenuUI {
public:
    PracticeMenuUI() {};
    ~PracticeMenuUI() { this->destroyUI(); }

    void createUI();
    void destroyUI();

private:
    void createNJSUI(UnityEngine::GameObject*, UnityEngine::Transform*);
    void createOffsetUI(UnityEngine::GameObject*, UnityEngine::Transform*);
    void updateSpeedSlider();

    bool created = false;
    int oldDifficulty;
    std::string oldLvlID;
};
