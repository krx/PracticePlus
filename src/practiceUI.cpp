#include "practiceUI.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/utils.h"

#include "HMUI/PercentSlider.hpp"

#include <cmath>
#include <sstream>
#include <string>
#include <iomanip>

#define SPEED_MIN  0.25
#define SPEED_MAX  3.0
#define SPEED_STEP 0.05

CustomButton NJSIncrease;
CustomButton NJSDecrease;
CustomButton NJSReset;

CustomButton OffsetIncrease;
CustomButton OffsetDecrease;
CustomButton OffsetReset;

void PracticeMenuUI::createNJSUI(UnityEngine::GameObject* button, UnityEngine::Transform* parent) {
    NJSIncrease.parent = button;
    NJSIncrease.parentTransform = parent;
    NJSIncrease.text = ">";
    NJSIncrease.scale = {0.2f, 0.75f, 1.0f};
    NJSIncrease.onPress = increaseNJS;
    NJSIncrease.sizeDelta = {-27.0f, -50.0f, 0.0f};
    NJSIncrease.fontSize = 5;
    NJSIncrease.create();

    NJSDecrease.parent = button;
    NJSDecrease.parentTransform = parent;
    NJSDecrease.text = "<";
    NJSDecrease.scale = {0.2f, 0.75f, 1.0f};
    NJSDecrease.onPress = decreaseNJS;
    NJSDecrease.sizeDelta = {-53.0f, -50.0f, 0.0f};
    NJSDecrease.fontSize = 5;
    NJSDecrease.create();

    NJSReset.parent = button;
    NJSReset.parentTransform = parent;
    NJSReset.text = "";
    NJSReset.scale = {0.515f, 0.75f, 1.0f};
    NJSReset.onPress = resetNJS;
    NJSReset.sizeDelta = {-40.0f, -50.0f, 0.0f};
    NJSReset.create();

    updateNJSText();
}

void PracticeMenuUI::createOffsetUI(UnityEngine::GameObject* button, UnityEngine::Transform* parent) {
    Vector2 OffsetTextPos = {69.0f, -1.0f};

    OffsetIncrease.parent = button;
    OffsetIncrease.parentTransform = parent;
    OffsetIncrease.text = ">";
    OffsetIncrease.scale = {0.2f, 0.75f, 1.0f};
    OffsetIncrease.onPress = increaseOffset;
    OffsetIncrease.sizeDelta = {51.0f, -50.0f, 0.0f};
    OffsetIncrease.fontSize = 5;
    OffsetIncrease.create();

    OffsetDecrease.parent = button;
    OffsetDecrease.parentTransform = parent;
    OffsetDecrease.text = "<";
    OffsetDecrease.scale = {0.2f, 0.75f, 1.0f};
    OffsetDecrease.onPress = decreaseOffset;
    OffsetDecrease.sizeDelta = {25.0f, -50.0f, 0.0f};
    OffsetDecrease.fontSize = 5;
    OffsetDecrease.create();

    OffsetReset.parent = button;
    OffsetReset.parentTransform = parent;
    OffsetReset.text = "";
    OffsetReset.scale = {0.515f, 0.75f, 1.0f};
    OffsetReset.onPress = resetOffset;
    OffsetReset.sizeDelta = {38.0f, -50.0f, 0.0f};
    OffsetReset.create();

    updateOffsetText();
}

/**
 * Expands the range of song speeds than can be selected from 50%-200% to 25%-300%
 */
void PracticeMenuUI::updateSpeedSlider() {
    if (!this->created) {
        getLogger().info("Updating speed slider range");
        UnityEngine::GameObject *slider_obj = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("PracticePanel/Speed/RangeValuesTextSlider"));
        HMUI::PercentSlider *slider = slider_obj->GetComponentInChildren<HMUI::PercentSlider*>();
        slider->set_minValue(SPEED_MIN);
        slider->set_maxValue(SPEED_MAX);
        slider->set_numberOfSteps(1 + (int)((SPEED_MAX - SPEED_MIN) / SPEED_STEP));
        slider->SetNormalizedValue(slider->NormalizeValue(1.0));
    }
}

void PracticeMenuUI::createUI() {
    if (this->created) {
        this->destroyUI();
    }

    getLogger().info("Creating practice UI");

    // Reset NJS/offset states if the map changed
    if (STATE.levelID != this->oldLvlID || STATE.difficulty != this->oldDifficulty) {
        STATE.customNjs = STATE.defaultNjs;
        STATE.customOffset = STATE.defaultOffset;
        this->oldDifficulty = STATE.difficulty;
        this->oldLvlID = STATE.levelID;
    }

    UnityEngine::GameObject *playButton = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("PracticeViewController/PlayButton"));
    UnityEngine::GameObject *slider = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("SongStart"));
    UnityEngine::Transform* parent = slider->get_transform()->get_parent();

    this->createNJSUI(playButton, parent);
    this->createOffsetUI(playButton, parent);
    this->updateSpeedSlider();
    this->created = true;
}

void PracticeMenuUI::destroyUI() {
    getLogger().info("Destroying practice UI");

    OffsetIncrease.destroy();
    OffsetDecrease.destroy();
    OffsetReset.destroy();

    NJSIncrease.destroy();
    NJSDecrease.destroy();
    NJSReset.destroy();
}

void updateNJSText() {
    std::stringstream ss;
    ss << "NJS : ";
    if (std::fmod(STATE.customNjs, 1) == 0.0) {
        ss << (int) STATE.customNjs;
    } else {
        ss << std::fixed << std::setprecision(1) << STATE.customNjs;
    }
    NJSReset.setText(ss.str());
}

void updateOffsetText() {
    std::stringstream ss;
    ss << "Offset : " << std::fixed << std::setprecision(1) << STATE.customOffset;
    OffsetReset.setText(ss.str());
}

void increaseNJS(){
    if(STATE.customNjs < 99){
        STATE.customNjs++;
        updateNJSText();
    }
}

void decreaseNJS(){
    if(STATE.customNjs > 1){
        STATE.customNjs--;
        updateNJSText();
    }
}

void resetNJS(){
    STATE.customNjs = STATE.defaultNjs;
    updateNJSText();
}

void increaseOffset(){
    if(STATE.customOffset < 9.9f){
        STATE.customOffset += 0.1f;
        updateOffsetText();
    }
}

void decreaseOffset(){
    if(STATE.customOffset > -9.9f){
        STATE.customOffset -= 0.1f;
        updateOffsetText();
    }
}

void resetOffset(){
    STATE.customOffset = STATE.defaultOffset;
    updateOffsetText();
}
