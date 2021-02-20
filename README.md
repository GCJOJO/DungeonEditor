# DungeonEditor
 A Simple Project
 
 # https://gcjojo.github.io/DungeonEditor/

# Setup

-First download the project or open it with Github Desktop\
![download-source-img](https://github.com/GCJOJO/DungeonEditor/blob/master/docs/Ressources/IMG/download-source.PNG)

# Launch game from Standalone.bat
  -First you will need to change "F:\UnrealEngine\Engine\Binaries\Win64\UE4Editor.exe" in Standalone.bat by you UE4Editor.exe location\
  -Then you will need to change "D:\DungeonEditor\DungeonEditor.uproject" in Standalone.bat by the .uproject file location\
  -Now you can launch the game via this simple file !

If you want to build the project, you will have in the "BatchFiles\" directory .bat files to build the game but you will need to replace "F:/UnrealEngine/Engine/Build/BatchFiles/RunUAT.bat" by "{You Engine Location}/Engine/Build/BatchFiles/RunUAT.bat"\
"D:/DungeonEditor/DungeonEditor.uproject" by "{You Project Loaction}/DungeonEditor.uproject"\
"F:\UnrealEngine\Engine\Binaries\Win64\UE4Editor-Cmd.exe" by "{You Engine Location}\Engine\Binaries\Win64\UE4Editor-Cmd.exe"\
-archivedirectory="{Where you want to archive the build}"


You can edit the .bat files to change how the engine will build the game
