#include "../include/main.hpp"
#include "../extern/beatsaber-hook/shared/customui/customui.hpp"
#include "../extern/beatsaber-hook/shared/utils/utils.h"
#include <string>

using namespace il2cpp_utils;

CustomUI::TextObject NJSText;
CustomUI::TextObject OffsetText;

float customNjs = 0;
float customOffset = 0;

std::string oldsongname;
int olddiff;

Il2CppObject* increaseNjsBtn;
Il2CppObject* decreaseNjsBtn;
Il2CppObject* resetNjsBtn;
Il2CppObject* increaseNjsBtnGO;
Il2CppObject* decreaseNjsBtnGO;
Il2CppObject* resetNjsBtnGO;

Il2CppObject* increaseOffsetBtn;
Il2CppObject* decreaseOffsetBtn;
Il2CppObject* resetOffsetBtn;
Il2CppObject* increaseOffsetBtnGO;
Il2CppObject* decreaseOffsetBtnGO;
Il2CppObject* resetOffsetBtnGO;

Vector2 njsTextPos = {9.0f, -1.0f};
Vector3 increaseNjsBtnPos = {-27.0f, 5.75f, 0.0f};
Vector3 decreaseNjsBtnPos = {-47.0f, 5.75f, 0.0f};
Vector3 resetNjsBtnPos = {-18.0f, 5.75f, 0.0f};
Vector3 scale ={0.3f, 0.3f, 1.0f};

Vector2 offsetTextPos = {70.0f, -1.0f};
Vector3 increaseOffsetBtnPos = {38.0f, 5.75f, 0.0f};
Vector3 decreaseOffsetBtnPos = {12.0f, 5.75f, 0.0f};
Vector3 resetOffsetBtnPos = {47.0f, 5.75f, 0.0f};

void GetNJS(){
    Il2CppObject* beatmapDiff = *GetFieldValue(sldv, "_selectedDifficultyBeatmap");
    customNjs = *RunMethod<float>(beatmapDiff, "get_noteJumpMovementSpeed");
    log(INFO, "NJS: %s", std::to_string((int)customNjs).c_str());
}

void GetOffset(){
    Il2CppObject* beatmapDiff = *GetFieldValue(sldv, "_selectedDifficultyBeatmap");
    customOffset = *RunMethod<float>(beatmapDiff, "get_noteJumpStartBeatOffset");
    log(INFO, "Offset: %s", std::to_string(customOffset).c_str());
}

void increaseNJS(){
    if(customNjs < 99){
        customNjs++;
        RunMethod(NJSText.textMesh, "set_text", createcsstr("NJS: " + std::to_string((int)customNjs)));
    }
}

void decreaseNJS(){
    if(customNjs > -99){
        customNjs--;
        RunMethod(NJSText.textMesh, "set_text", createcsstr("NJS: " + std::to_string((int)customNjs)));
    }
}

void resetNjs(){
    GetNJS();
    RunMethod(NJSText.textMesh, "set_text", createcsstr("NJS: " + std::to_string((int)customNjs)));
}

void increaseOffset(){
    if(customOffset < 5.0f){
        customOffset += 0.1f;
        RunMethod(OffsetText.textMesh, "set_text", createcsstr("Offset: " + std::to_string(customOffset).substr(0, 4)));
    }
}

void decreaseOffset(){
    if(customOffset > -5.0f){
        customOffset -= 0.1f;
        RunMethod(OffsetText.textMesh, "set_text", createcsstr("Offset: " + std::to_string(customOffset).substr(0, 4)));
    }
}

void resetOffset(){
    GetOffset();
    RunMethod(OffsetText.textMesh, "set_text", createcsstr("Offset: " + std::to_string(customOffset).substr(0, 4)));
}

void CreateNJSUI(Il2CppObject* pvc, Il2CppObject* parent, Il2CppObject* playButton){
    // Increase Button
    increaseNjsBtn = *RunMethod("UnityEngine", "Object", "Instantiate", playButton);
    Il2CppObject* increaseBtnTransform = *RunMethod(increaseNjsBtn, "get_transform");
    RunMethod(increaseBtnTransform, "SetParent", parent);
    RunMethod(increaseBtnTransform, "set_localPosition", increaseNjsBtnPos);
    RunMethod(increaseBtnTransform, "set_localScale", scale);
    increaseNjsBtnGO = *RunMethod(increaseNjsBtn, "get_gameObject");
    Il2CppObject* increaseBtnTMP = *RunMethod(increaseNjsBtnGO, "GetComponentInChildren", GetSystemType("TMPro", "TextMeshProUGUI"));
    RunMethod(increaseBtnTMP, "set_text", createcsstr(">"));
    RunMethod(increaseBtnTMP, "set_fontSize", 10.0f);
    Il2CppObject* onIncreaseClick = *GetPropertyValue(increaseNjsBtn, "onClick");
    auto increase = MakeAction(il2cpp_functions::class_get_type(GetClassFromName("UnityEngine.Events", "UnityAction")), (Il2CppObject*)nullptr, increaseNJS);
    RunMethod(onIncreaseClick, "AddListener", increase);
    // Decrease Button
    decreaseNjsBtn = *RunMethod("UnityEngine", "Object", "Instantiate", playButton);
    Il2CppObject* decreaseBtnTransform = *RunMethod(decreaseNjsBtn, "get_transform");
    RunMethod(decreaseBtnTransform, "SetParent", parent);
    RunMethod(decreaseBtnTransform, "set_localPosition", decreaseNjsBtnPos);
    RunMethod(decreaseBtnTransform, "set_localScale", scale);
    decreaseNjsBtnGO = *RunMethod(decreaseNjsBtn, "get_gameObject");
    Il2CppObject* decreaseBtnTMP = *RunMethod(decreaseNjsBtnGO, "GetComponentInChildren", GetSystemType("TMPro", "TextMeshProUGUI"));
    RunMethod(decreaseBtnTMP, "set_text", createcsstr("<"));
    RunMethod(decreaseBtnTMP, "set_fontSize", 10.0f);
    Il2CppObject* onDecreaseClick = *GetPropertyValue(decreaseNjsBtn, "onClick");
    auto decrease = MakeAction(il2cpp_functions::class_get_type(GetClassFromName("UnityEngine.Events", "UnityAction")), (Il2CppObject*)nullptr, decreaseNJS);
    RunMethod(onDecreaseClick, "AddListener", decrease);
    // Reset Button
    resetNjsBtn = *RunMethod("UnityEngine", "Object", "Instantiate", playButton);
    Il2CppObject* resetTransform = *RunMethod(resetNjsBtn, "get_transform");
    RunMethod(resetTransform, "SetParent", parent);
    RunMethod(resetTransform, "set_localPosition", resetNjsBtnPos);
    RunMethod(resetTransform, "set_localScale", scale);
    resetNjsBtnGO = *RunMethod(resetNjsBtn, "get_gameObject");
    Il2CppObject* resetTMP = *RunMethod(resetNjsBtnGO, "GetComponentInChildren", GetSystemType("TMPro", "TextMeshProUGUI"));
    RunMethod(resetTMP, "set_text", createcsstr("Reset"));
    RunMethod(resetTMP, "set_fontSize", 10.0f);
    Il2CppObject* onResetClick = *GetPropertyValue(resetNjsBtn, "onClick");
    auto reset = MakeAction(il2cpp_functions::class_get_type(GetClassFromName("UnityEngine.Events", "UnityAction")), (Il2CppObject*)nullptr, resetNjs);
    RunMethod(onResetClick, "AddListener", reset);
    // NJS Text
    NJSText.anchoredPosition = njsTextPos;
    NJSText.fontSize = 4.5f;
    NJSText.parentTransform = parent;
    NJSText.text = "NJS: " + std::to_string((int)customNjs);
    NJSText.create();
}

void CreateOffsetUI(Il2CppObject* pvc, Il2CppObject* parent, Il2CppObject* playButton){
    // Increase Button
    increaseOffsetBtn = *RunMethod("UnityEngine", "Object", "Instantiate", playButton);
    Il2CppObject* increaseOffsetBtnTransform = *RunMethod(increaseOffsetBtn, "get_transform");
    RunMethod(increaseOffsetBtnTransform, "SetParent", parent);
    RunMethod(increaseOffsetBtnTransform, "set_localPosition", increaseOffsetBtnPos);
    RunMethod(increaseOffsetBtnTransform, "set_localScale", scale);
    increaseOffsetBtnGO = *RunMethod(increaseOffsetBtn, "get_gameObject");
    Il2CppObject* increaseBtnTMP = *RunMethod(increaseOffsetBtnGO, "GetComponentInChildren", GetSystemType("TMPro", "TextMeshProUGUI"));
    RunMethod(increaseBtnTMP, "set_text", createcsstr(">"));
    RunMethod(increaseBtnTMP, "set_fontSize", 10.0f);
    Il2CppObject* onIncreaseClick = *GetPropertyValue(increaseOffsetBtn, "onClick");
    auto increase = MakeAction(il2cpp_functions::class_get_type(GetClassFromName("UnityEngine.Events", "UnityAction")), (Il2CppObject*)nullptr, increaseOffset);
    RunMethod(onIncreaseClick, "AddListener", increase);
    // Decrease Button
    decreaseOffsetBtn = *RunMethod("UnityEngine", "Object", "Instantiate", playButton);
    Il2CppObject* decreaseOffsetBtnTransform = *RunMethod(decreaseOffsetBtn, "get_transform");
    RunMethod(decreaseOffsetBtnTransform, "SetParent", parent);
    RunMethod(decreaseOffsetBtnTransform, "set_localPosition", decreaseOffsetBtnPos);
    RunMethod(decreaseOffsetBtnTransform, "set_localScale", scale);
    decreaseOffsetBtnGO = *RunMethod(decreaseOffsetBtn, "get_gameObject");
    Il2CppObject* decreaseBtnTMP = *RunMethod(decreaseOffsetBtnGO, "GetComponentInChildren", GetSystemType("TMPro", "TextMeshProUGUI"));
    RunMethod(decreaseBtnTMP, "set_text", createcsstr("<"));
    RunMethod(decreaseBtnTMP, "set_fontSize", 10.0f);
    Il2CppObject* onDecreaseClick = *GetPropertyValue(decreaseOffsetBtn, "onClick");
    auto decrease = MakeAction(il2cpp_functions::class_get_type(GetClassFromName("UnityEngine.Events", "UnityAction")), (Il2CppObject*)nullptr, decreaseOffset);
    RunMethod(onDecreaseClick, "AddListener", decrease);
    // Reset Button
    resetOffsetBtn = *RunMethod("UnityEngine", "Object", "Instantiate", playButton);
    Il2CppObject* resetOffsetBtnTransform = *RunMethod(resetOffsetBtn, "get_transform");
    RunMethod(resetOffsetBtnTransform, "SetParent", parent);
    RunMethod(resetOffsetBtnTransform, "set_localPosition", resetOffsetBtnPos);
    RunMethod(resetOffsetBtnTransform, "set_localScale", scale);
    resetOffsetBtnGO = *RunMethod(resetOffsetBtn, "get_gameObject");
    Il2CppObject* resetBtnTMP = *RunMethod(resetOffsetBtnGO, "GetComponentInChildren", GetSystemType("TMPro", "TextMeshProUGUI"));
    RunMethod(resetBtnTMP, "set_text", createcsstr("Reset"));
    RunMethod(resetBtnTMP, "set_fontSize", 10.0f);
    Il2CppObject* onResetClick = *GetPropertyValue(resetOffsetBtn, "onClick");
    auto reset = MakeAction(il2cpp_functions::class_get_type(GetClassFromName("UnityEngine.Events", "UnityAction")), (Il2CppObject*)nullptr, resetOffset);
    RunMethod(onResetClick, "AddListener", reset);
    // Offset Text
    OffsetText.anchoredPosition = offsetTextPos;
    OffsetText.fontSize = 4.5f;
    OffsetText.parentTransform = parent;
    OffsetText.text = "Offset: " + std::to_string(customOffset).substr(0, 4);
    OffsetText.create();
}

void CreateUIObjects(Il2CppObject* self){
    Il2CppObject* songNameUGUI = *GetFieldValue(self, "_songNameText");
    Il2CppString* songName = *RunMethod<Il2CppString*>(songNameUGUI, "get_text");
    std::string songNamestr = to_utf8(csstrtostr(songName));
    Il2CppObject* selectedDifficultyBeatmap = *GetFieldValue(sldv, "_selectedDifficultyBeatmap");
    int diff = *RunMethod<int>(selectedDifficultyBeatmap, "get_difficultyRank");
    // Bit scuff but it works so fuck it
    if(songNamestr != oldsongname || diff != olddiff){ GetNJS(); GetOffset(); olddiff = diff; oldsongname = songNamestr;}
    Il2CppObject* slider = *GetFieldValue(self, "_songStartSlider");
    if(slider == nullptr) log(INFO, "Failed to get _songStartSlider");
    Il2CppObject* playButton = *GetFieldValue(self, "_playButton");
    if(playButton == nullptr) log(INFO, "Failed to get _playButton");
    Il2CppObject* go = *RunMethod(slider, "get_transform");
    Il2CppObject* parent = *RunMethod(go, "get_parent");
    if(parent == nullptr) log(INFO, "Failed to get parent");
    CreateNJSUI(self, parent, playButton);
    CreateOffsetUI(self, parent, playButton);
}

void Destroy(){
    RunMethod(GetClassFromName("UnityEngine", "Object"), "Destroy", resetNjsBtnGO);
    RunMethod(GetClassFromName("UnityEngine", "Object"), "Destroy", increaseNjsBtnGO);
    RunMethod(GetClassFromName("UnityEngine", "Object"), "Destroy", decreaseNjsBtnGO);
    NJSText.destroy();
    RunMethod(GetClassFromName("UnityEngine", "Object"), "Destroy", resetOffsetBtnGO);
    RunMethod(GetClassFromName("UnityEngine", "Object"), "Destroy", increaseOffsetBtnGO);
    RunMethod(GetClassFromName("UnityEngine", "Object"), "Destroy", decreaseOffsetBtnGO);
    OffsetText.destroy();
}
