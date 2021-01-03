# Builds a .zip file for loading with BMBF
& $PSScriptRoot/build.ps1

if ($?) {
    Compress-Archive -Path "./libs/arm64-v8a/libPracticePlus.so", "./libs/arm64-v8a/libbeatsaber-hook_0_8_4.so", "./libs/arm64-v8a/libcustom-ui_0_1_4.so", "./bmbfmod.json" -DestinationPath "./PracticePlus_v0.3.0.zip" -Update
}
