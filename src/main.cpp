#include "main.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/utils.h"
#include "custom-ui/shared/customui.hpp"


using namespace il2cpp_utils;
using namespace CustomUI;

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

Il2CppObject* sldv;
Il2CppObject* _spawnController;
float customNjs;
float customOffset;
float defaultNjs;
float defaultOffset;
int diff;
bool created = false;
bool inPracticeMode = false;

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
const Logger& getLogger() {
    static const Logger logger(modInfo);
    return logger;
}

void log(std::string str) {
    getLogger().info(str);
}


Il2CppObject* FindObjectsOfTypeAllFirstOrDefault(Il2CppReflectionType* Type) {
    Array<Il2CppObject*>* Objects = *RunMethod<Array<Il2CppObject*>*>(GetClassFromName("UnityEngine","Resources"), "FindObjectsOfTypeAll", Type);
    if(Objects)
        return Objects->values[0];
    else
        return nullptr;
}

MAKE_HOOK_OFFSETLESS(PauseMenuManager_ShowMenu, void, Il2CppObject* self) {
    PauseMenuManager_ShowMenu(self);
    _spawnController = FindObjectsOfTypeAllFirstOrDefault(GetSystemType("", "BeatmapObjectSpawnController"));
    if(!created && inPracticeMode){
        CreateInMapUI(self);
        created = true;
    }
}

MAKE_HOOK_OFFSETLESS(BOSMD_Init, void, Il2CppObject* self, int noteLinesCount, float startNoteJumpMovementSpeed, float startBPM, float noteJumpStartBeatOffset, float jumpOffsetY, Vector3 rightVec, Vector3 forwardVec){
    log("BOSMD_Init");
    BOSMD_Init(self, noteLinesCount, inPracticeMode ? customNjs : startNoteJumpMovementSpeed, startBPM, inPracticeMode ? customOffset : noteJumpStartBeatOffset, jumpOffsetY, rightVec, forwardVec);
}

MAKE_HOOK_OFFSETLESS(LevelSelectionFlowCoordinator_StartLevel, void,  Il2CppObject* self, Il2CppObject* beforeSceneSwitchCallback, bool practice){
    log("LSFC_StartLevel");
    inPracticeMode = practice;
    LevelSelectionFlowCoordinator_StartLevel(self, beforeSceneSwitchCallback, practice);
}

MAKE_HOOK_OFFSETLESS(PracticeViewController_DidActivate, void, Il2CppObject* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
    log("PVC_DidActivate");
    if(created) DestroyInMapUI();
    created = false;
    sldv = FindObjectsOfTypeAllFirstOrDefault(GetSystemType("", "StandardLevelDetailView"));
    Il2CppObject* diffBeatmap = *GetFieldValue(sldv, "_selectedDifficultyBeatmap");
    defaultOffset = *RunMethod<float>(diffBeatmap, "get_noteJumpStartBeatOffset");
    diff = *RunMethod<int>(diffBeatmap, "get_difficultyRank");
    PracticeViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
    defaultNjs = *RunMethod<float>(diffBeatmap, "get_noteJumpMovementSpeed");
    if(!firstActivation) DestroyPracticeUI();
    CreatePracticeMenuUI(self, diff);
}

extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;

    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
    getLogger().info("Modloader name: %s", Modloader::getInfo().name.c_str());
}

extern "C" void load() {
    il2cpp_functions::Init();
    // INSTALL_HOOK_OFFSETLESS(PauseMenuManager_ShowMenu, FindMethodUnsafe("", "PauseMenuManager", "ShowMenu", 0));
    INSTALL_HOOK_OFFSETLESS(PracticeViewController_DidActivate, FindMethodUnsafe("", "PracticeViewController", "DidActivate", 3));
    INSTALL_HOOK_OFFSETLESS(LevelSelectionFlowCoordinator_StartLevel, FindMethodUnsafe("", "SinglePlayerLevelSelectionFlowCoordinator", "StartLevel", 2));
    INSTALL_HOOK_OFFSETLESS(BOSMD_Init, FindMethodUnsafe("", "BeatmapObjectSpawnMovementData", "Init", 7));
}