#define MyAppName "GameNet Manager"
#define MyAppVersion "1.0.0"
#define MyAppPublisher "Mohsen Hatami"
#define MyAppExeName "GameNet-Manager.exe"

[Setup]
AppId={{081f42c6-e77d-4e8a-9230-3cb903fc259b}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}

DefaultDirName={autopf}\{#MyAppName}
DefaultGroupName={#MyAppName}

OutputDir=output
OutputBaseFilename=GameNet-Manager-Setup

Compression=lzma
SolidCompression=yes

ArchitecturesAllowed=x64
ArchitecturesInstallIn64BitMode=x64

[Files]
Source: "..\release\*"; DestDir: "{app}"; \
    Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; \
    Filename: "{app}\{#MyAppExeName}"

[Run]
Filename: "{app}\{#MyAppExeName}"; \
    Description: "Launch {#MyAppName}"; \
    Flags: nowait postinstall skipifsilent