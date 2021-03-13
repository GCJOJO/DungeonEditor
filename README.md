# DungeonEditor
 A Simple Project
 
 # https://gcjojo.github.io/DungeonEditor/

# Setup

-First download the project or open it with Github Desktop\
![download-source-img](https://github.com/GCJOJO/DungeonEditor/blob/master/docs/Ressources/IMG/download-source.PNG)

Then download Unreal Engine 4 source and build it : [Tutorial on how to build Unreal Engine 4 from the source code](https://github.com/EpicGames/UnrealEngine#getting-up-and-running)\


Then right click the ```DungeonEditor.uproject``` file and select the ```Switch Unreal Engine Version``` option. A windows will open asking you to select the UE4 version. Select the Source Build version.

![switch-ue4-img](https://github.com/GCJOJO/DungeonEditor/blob/master/docs/Ressources/IMG/switch-ue4-version-and-gen-file.png)
![switch-windows-img](https://github.com/GCJOJO/DungeonEditor/blob/master/docs/Ressources/IMG/switc-ue4-version-windows.PNG)

After this right click the ```DungeonEditor.uproject``` file and select the ```Generate Visual Studio Project Files``` option if you use Visual Studio.

When it's finished double click ```DungeonEditor.sln``` and build the DungeonEditor project with the ```Development Editor``` configuration

![build-source-img](https://github.com/GCJOJO/DungeonEditor/blob/master/docs/Ressources/IMG/build-source.png)

Then launch the .uproject file and **create** !

# Launch game from Standalone.bat
  -First you will need to change "F:\UnrealEngine\Engine\Binaries\Win64\UE4Editor.exe" in Standalone.bat by you UE4Editor.exe location\
  -Then you will need to change "D:\DungeonEditor\DungeonEditor.uproject" in Standalone.bat by the .uproject file location\
  -Now you can launch the game via this simple file !

If you want to build the project, you will have in the ```BatchFiles\``` directory .bat files to build the game but you will need to replace ```F:/UnrealEngine/Engine/Build/BatchFiles/RunUAT.bat``` by ```{Your Engine Location}/Engine/Build/BatchFiles/RunUAT.bat```\
```D:/DungeonEditor/DungeonEditor.uproject``` by ```{Your Project Loaction}/DungeonEditor.uproject```\
```F:\UnrealEngine\Engine\Binaries\Win64\UE4Editor-Cmd.exe``` by ```{Your Engine Location}\Engine\Binaries\Win64\UE4Editor-Cmd.exe```\
```-archivedirectory="{Where you want to archive the build}"```


You can edit the .bat files to change how the engine will build the game
