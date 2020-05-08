#include <dlfcn.h>
#include "../extern/beatsaber-hook/shared/utils/utils.h"
#include "../extern/beatsaber-hook/shared/utils/logging.hpp"
#include "../extern/beatsaber-hook/shared/utils/typedefs.h"
#include "../extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp"

using namespace il2cpp_utils;

extern float customNjs;
extern Il2CppObject* sldv;
void CreateUIObjects(Il2CppObject* self);
void Destroy();

extern "C" void load();
