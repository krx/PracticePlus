#include "main.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/utils.h"
#include "custom-ui/shared/customui.hpp"

#include <cmath>
#include <sstream>
#include <string>
#include <iomanip>

void GetNJS();
void GetOffset();
void IncreaseNJS();
void DecreaseNJS();
void ResetNJS();
void IncreaseOffset();
void DecreaseOffset();
void ResetOffset();
void UpdateNJSText();
void UpdateOffsetText();

using namespace il2cpp_utils;

CustomButton NJSIncrease;
CustomButton NJSDecrease;
CustomButton NJSReset;

CustomButton OffsetIncrease;
CustomButton OffsetDecrease;
CustomButton OffsetReset;

std::string oldsongname;
int olddiff;

void NJSUI(UnityEngine::GameObject* button, UnityEngine::Transform* parent) {
    NJSIncrease.parent = button;
    NJSIncrease.parentTransform = parent;
    NJSIncrease.text = ">";
    NJSIncrease.scale = {0.2f, 0.75f, 1.0f};
    NJSIncrease.onPress = IncreaseNJS;
    NJSIncrease.sizeDelta = {-27.0f, -50.0f, 0.0f};
    NJSIncrease.fontSize = 5;
    NJSIncrease.create();

    NJSDecrease.parent = button;
    NJSDecrease.parentTransform = parent;
    NJSDecrease.text = "<";
    NJSDecrease.scale = {0.2f, 0.75f, 1.0f};
    NJSDecrease.onPress = DecreaseNJS;
    NJSDecrease.sizeDelta = {-47.0f, -50.0f, 0.0f};
    NJSDecrease.fontSize = 5;
    NJSDecrease.create();

    NJSReset.parent = button;
    NJSReset.parentTransform = parent;
    NJSReset.text = "";
    NJSReset.scale = {0.35f, 0.75f, 1.0f};
    NJSReset.onPress = ResetNJS;
    NJSReset.sizeDelta = {-37.0f, -50.0f, 0.0f};
    NJSReset.create();
    UpdateNJSText();
}

void OffsetUI(UnityEngine::GameObject* button, UnityEngine::Transform* parent){
    Vector2 OffsetTextPos = {69.0f, -1.0f};

    OffsetIncrease.parent = button;
    OffsetIncrease.parentTransform = parent;
    OffsetIncrease.text = ">";
    OffsetIncrease.scale = {0.2f, 0.75f, 1.0f};
    OffsetIncrease.onPress = IncreaseOffset;
    OffsetIncrease.sizeDelta = {51.0f, -50.0f, 0.0f};
    OffsetIncrease.fontSize = 5;
    OffsetIncrease.create();

    OffsetDecrease.parent = button;
    OffsetDecrease.parentTransform = parent;
    OffsetDecrease.text = "<";
    OffsetDecrease.scale = {0.2f, 0.75f, 1.0f};
    OffsetDecrease.onPress = DecreaseOffset;
    OffsetDecrease.sizeDelta = {25.0f, -50.0f, 0.0f};
    OffsetDecrease.fontSize = 5;
    OffsetDecrease.create();

    OffsetReset.parent = button;
    OffsetReset.parentTransform = parent;
    OffsetReset.text = "";
    OffsetReset.scale = {0.515f, 0.75f, 1.0f};
    OffsetReset.onPress = ResetOffset;
    OffsetReset.sizeDelta = {38.0f, -50.0f, 0.0f};
    OffsetReset.create();
    UpdateOffsetText();
}

void CreatePracticeMenuUI(Il2CppObject* self, int diff){
    getLogger().info("Creating practice UI!");
    UnityEngine::GameObject *text_obj = UnityEngine::GameObject::Find(createcsstr("SongNameText"));
    HMUI::CurvedTextMeshPro *song_text = text_obj->GetComponentInChildren<HMUI::CurvedTextMeshPro*>();
    Il2CppString* songName = song_text->get_text();
    std::string songNamestr = to_utf8(csstrtostr(songName));

    if(songNamestr != oldsongname || diff != olddiff) {
        GetNJS();
        GetOffset();
        olddiff = diff;
        oldsongname = songNamestr;
    }

    UnityEngine::GameObject *playButton = UnityEngine::GameObject::Find(createcsstr("PracticeViewController/PlayButton"));
    UnityEngine::GameObject *slider = UnityEngine::GameObject::Find(createcsstr("SongStart"));
    UnityEngine::Transform* parent = slider->get_transform()->get_parent();

    NJSUI(playButton, parent);
    OffsetUI(playButton, parent);
}

void GetNJS(){
    customNjs = defaultNjs;
}

void GetOffset(){
    customOffset = defaultOffset;
}

void UpdateNJSText() {
    NJSReset.setText("NJS : " + std::to_string((int)customNjs));
}

void UpdateOffsetText() {
    std::stringstream ss;
    ss << "Offset : " << std::fixed << std::setprecision(1) << customOffset;
    OffsetReset.setText(ss.str());
}

void ResetNJS(){
    customNjs = defaultNjs;
    UpdateNJSText();
}

void IncreaseNJS(){
    if(customNjs < 99){
        customNjs++;
        UpdateNJSText();
    }
}

void DecreaseNJS(){
    if(customNjs > -99){
        customNjs--;
        UpdateNJSText();
    }
}

void ResetOffset(){
    customOffset = defaultOffset;
    UpdateOffsetText();
}

void IncreaseOffset(){
    if(customOffset < 9.9f){
        customOffset += 0.1f;
        UpdateOffsetText();
    }
}

void DecreaseOffset(){
    if(customOffset > -9.9f){
        customOffset -= 0.1f;
        UpdateOffsetText();
    }
}

void DestroyPracticeUI() {
    OffsetIncrease.destroy();
    OffsetDecrease.destroy();
    OffsetReset.destroy();

    NJSIncrease.destroy();
    NJSDecrease.destroy();
    NJSReset.destroy();
}
