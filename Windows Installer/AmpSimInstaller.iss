[Setup]
AppName="GAE AmpSim"
AppVersion=0.1.0
DefaultDirName="C:\Program Files"
DefaultGroupName="GAE AmpSim"
OutputBaseFilename=GAEAmpSim-windows

[Files]

Source: "C:\Users\gregl\OneDrive\Desktop\AmpSim\*"; DestDir: "C:\Program Files\AmpSim"; Flags: recursesubdirs createallsubdirs
Source: "D:\code\juce\AmpSim\AmpSim\Builds\VisualStudio2022\x64\Debug\VST3\AmpSim.vst3"; DestDir: "C:\Program Files\Common Files\VST3";
; NOTE: Don't use "Flags: ignoreversion" on any shared system files
