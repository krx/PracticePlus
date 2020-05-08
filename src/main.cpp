#include "../include/main.hpp"

using namespace il2cpp_utils;

bool inPracticeMode = false;

Il2CppObject* smsvc;
Il2CppObject* sldv;


Il2CppObject* FindObjectsOfTypeAllFirstOrDefault(Il2CppReflectionType* Type)
{
    Array<Il2CppObject*>* Objects = *RunMethod<Array<Il2CppObject*>*>(GetClassFromName("UnityEngine","Resources"), "FindObjectsOfTypeAll", Type);
    if(Objects)
        return Objects->values[0];
    else
        return nullptr;
}

MAKE_HOOK_OFFSETLESS(BOSMD_Init, void, Il2CppObject* self, int noteLinesCount, float startNoteJumpMovementSpeed, float startBPM, float noteJumpStartBeatOffset, float jumpOffsetY, Vector3 centerPos, Vector3 rightVec, Vector3 forwardVec){
    BOSMD_Init(self, noteLinesCount, inPracticeMode ? customNjs : startNoteJumpMovementSpeed, startBPM, inPracticeMode ? customOffset : noteJumpStartBeatOffset, jumpOffsetY, centerPos, rightVec, forwardVec);
}

MAKE_HOOK_OFFSETLESS(LevelSelectionFlowCoordinator_StartLevel, void, Il2CppObject* self, Il2CppObject* difficultyBeatmap, Il2CppObject* beforeSceneSwitchCallback, bool practice) {
    inPracticeMode = practice;
    LevelSelectionFlowCoordinator_StartLevel(self, difficultyBeatmap, beforeSceneSwitchCallback, practice);
}

MAKE_HOOK_OFFSETLESS(PracticeViewController_DidActivate, void, Il2CppObject* self, bool firstActivation, int activationType){
    PracticeViewController_DidActivate(self, firstActivation, activationType);
    smsvc = FindObjectsOfTypeAllFirstOrDefault(GetSystemType("", "SoloModeSelectionViewController"));
    sldv = FindObjectsOfTypeAllFirstOrDefault(GetSystemType("", "StandardLevelDetailView"));
    //Il2CppObject* difficultyBeatmap = *GetFieldValue(sldv, "_selectedDifficultyBeatmap");
    //customNjs = *RunMethod<float>(difficultyBeatmap, "get_noteJumpMovementSpeed");
    if(!firstActivation) Destroy();
    CreateUIObjects(self);
}

extern "C" void load() {
    log(INFO, "Hello from il2cpp_init!");
    log(INFO, "Installing hooks...");
    INSTALL_HOOK_OFFSETLESS(PracticeViewController_DidActivate, FindMethodUnsafe("", "PracticeViewController", "DidActivate", 2));
    INSTALL_HOOK_OFFSETLESS(LevelSelectionFlowCoordinator_StartLevel, FindMethodUnsafe("", "LevelSelectionFlowCoordinator", "StartLevel", 3));
    INSTALL_HOOK_OFFSETLESS(BOSMD_Init, FindMethodUnsafe("", "BeatmapObjectSpawnMovementData", "Init", 8));
    log(INFO, "Installed all hooks!");
}
