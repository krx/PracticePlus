#include "../include/main.hpp"
#include "../extern/beatsaber-hook/shared/customui/customui.hpp"
#include "../extern/beatsaber-hook/shared/utils/utils.h"
#include <string>

using namespace il2cpp_utils;

CustomUI::TextObject NJSText;

float customNjs = 0;

std::string oldsongname;
int olddiff;

Il2CppObject* increaseBtn;
Il2CppObject* decreaseBtn;
Il2CppObject* resetNjsBtn;

Vector2 textPos = {9.0f, 0.0f};
Vector3 increaseBtnPos = {-23.0f, 5.75f, 0.0f};
Vector3 decreaseBtnPos = {-47.0f, 5.75f, 0.0f};
Vector3 resetBtnPos = {-14.0f, 5.75f, 0.0f};
Vector3 scale ={0.3f, 0.4f, 1.0f};

void GetNJS(Il2CppObject* sldv){
    Il2CppObject* beatmapDiff = *GetFieldValue(sldv, "_selectedDifficultyBeatmap");
    customNjs = *RunMethod<float>(beatmapDiff, "get_noteJumpMovementSpeed");
    log(INFO, "NJS: %s", std::to_string((int)customNjs).c_str());
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
    GetNJS(sldv);
    RunMethod(NJSText.textMesh, "set_text", createcsstr("NJS: " + std::to_string((int)customNjs)));
}

void CreateUIObjects(Il2CppObject* self){
    Il2CppObject* songNameUGUI = *GetFieldValue(self, "_songNameText");
    Il2CppString* songName = *RunMethod<Il2CppString*>(songNameUGUI, "get_text");
    std::string songNamestr = to_utf8(csstrtostr(songName));
    Il2CppObject* selectedDifficultyBeatmap = *GetFieldValue(sldv, "_selectedDifficultyBeatmap");
    int diff = *RunMethod<int>(selectedDifficultyBeatmap, "get_difficultyRank");
    // Bit scuff but it works so fuck it
    if(songNamestr != oldsongname || diff != olddiff){ GetNJS(sldv); olddiff = diff; oldsongname = songNamestr;}
    //Il2CppObject* backBtn = *GetFieldValue(smsvc, "_dismissButton");
    //if(backBtn == nullptr) log(INFO, "Failed to get _dismissButton");
    Il2CppObject* slider = *GetFieldValue(self, "_songStartSlider");
    if(slider == nullptr) log(INFO, "Failed to get _songStartSlider");
    Il2CppObject* playButton = *GetFieldValue(self, "_playButton");
    if(playButton == nullptr) log(INFO, "Failed to get _playButton");
    Il2CppObject* go = *RunMethod(slider, "get_transform");
    Il2CppObject* parent = *RunMethod(go, "get_parent");
    if(parent == nullptr) log(INFO, "Failed to get parent");
    increaseBtn = *RunMethod("UnityEngine", "Object", "Instantiate", playButton);
    Il2CppObject* increaseBtnTransform = *RunMethod(increaseBtn, "get_transform");
    if(increaseBtn == nullptr) log(INFO, "Failed to instantiate _playButton as increaseBtn");
    decreaseBtn = *RunMethod("UnityEngine", "Object", "Instantiate", playButton);
    Il2CppObject* decreaseBtnTransform = *RunMethod(decreaseBtn, "get_transform");
    if(decreaseBtn == nullptr) log(INFO, "Failed to instantiate _playButton as decreaseBtn");
    resetNjsBtn = *RunMethod("UnityEngine", "Object", "Instantiate", playButton);
    Il2CppObject* resetTransform = *RunMethod(resetNjsBtn, "get_transform");
    Il2CppObject* onResetClick = *GetPropertyValue(resetNjsBtn, "onClick");
    Il2CppObject* onDecreaseClick = *GetPropertyValue(decreaseBtn, "onClick");
    Il2CppObject* onIncreaseClick = *GetPropertyValue(increaseBtn, "onClick");
    auto reset = MakeAction(il2cpp_functions::class_get_type(GetClassFromName("UnityEngine.Events", "UnityAction")), (Il2CppObject*)nullptr, resetNjs);
    auto increase = MakeAction(il2cpp_functions::class_get_type(GetClassFromName("UnityEngine.Events", "UnityAction")), (Il2CppObject*)nullptr, increaseNJS);
    auto decrease = MakeAction(il2cpp_functions::class_get_type(GetClassFromName("UnityEngine.Events", "UnityAction")), (Il2CppObject*)nullptr, decreaseNJS);
    RunMethod(onResetClick, "AddListener", reset);
    RunMethod(onIncreaseClick, "AddListener", increase);
    RunMethod(onDecreaseClick, "AddListener", decrease);
    RunMethod(resetTransform, "SetParent", parent);
    RunMethod(increaseBtnTransform, "SetParent", parent);
    RunMethod(decreaseBtnTransform, "SetParent", parent);
    RunMethod(resetTransform, "set_localScale", scale);
    RunMethod(decreaseBtnTransform, "set_localScale", scale);
    RunMethod(increaseBtnTransform, "set_localScale", scale);
    RunMethod(resetTransform, "set_localPosition", resetBtnPos);
    RunMethod(increaseBtnTransform, "set_localPosition", increaseBtnPos);
    RunMethod(decreaseBtnTransform, "set_localPosition", decreaseBtnPos);
    Il2CppObject* resetBtnGO = *RunMethod(resetNjsBtn, "get_gameObject");
    Il2CppObject* resetTMP = *RunMethod(resetBtnGO, "GetComponentInChildren", GetSystemType("TMPro", "TextMeshProUGUI"));
    RunMethod(resetTMP, "set_text", createcsstr("Reset"));
    Il2CppObject* increaseBtnGO = *RunMethod(increaseBtn, "get_gameObject");
    Il2CppObject* increaseBtnTMP = *RunMethod(increaseBtnGO, "GetComponentInChildren", GetSystemType("TMPro", "TextMeshProUGUI"));
    RunMethod(increaseBtnTMP, "set_text", createcsstr(">"));
    Il2CppObject* decreaseBtnGO = *RunMethod(decreaseBtn, "get_gameObject");
    Il2CppObject* decreaseBtnTMP = *RunMethod(decreaseBtnGO, "GetComponentInChildren", GetSystemType("TMPro", "TextMeshProUGUI"));
    RunMethod(decreaseBtnTMP, "set_text", createcsstr("<"));
    RunMethod(resetTMP, "set_fontSize", 10.0f);
    RunMethod(increaseBtnTMP, "set_fontSize", 10.0f);
    RunMethod(decreaseBtnTMP, "set_fontSize", 10.0f);
    NJSText.anchoredPosition = textPos;
    NJSText.fontSize = 6.0f;
    NJSText.parentTransform = parent;
    std::string njsstr = std::to_string((int)customNjs);
    NJSText.text = "NJS: " + njsstr;
    NJSText.create();
}

void Destroy(){
    Il2CppObject* resetGO = *RunMethod(resetNjsBtn, "get_gameObject");
    Il2CppObject* increaseBtnGO = *RunMethod(increaseBtn, "get_gameObject");
    Il2CppObject* decreaseBtnGO = *RunMethod(decreaseBtn, "get_gameObject");
    RunMethod(GetClassFromName("UnityEngine", "Object"), "Destroy", resetGO);
    RunMethod(GetClassFromName("UnityEngine", "Object"), "Destroy", increaseBtnGO);
    RunMethod(GetClassFromName("UnityEngine", "Object"), "Destroy", decreaseBtnGO);
    NJSText.destroy();
}
