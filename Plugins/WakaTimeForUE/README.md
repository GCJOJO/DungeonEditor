# WakaTimeForUE

![plugin version](https://img.shields.io/badge/version-1.2.5-blue) ![Unreal Engine version](https://img.shields.io/badge/Unreal%20Engine%20version-4.26+-blue) ![Platform support](https://img.shields.io/badge/Platform_support-Windows-blue)

---

### Setting up the plugin
1. Download WakaTimeForUE.zip from the releases
2. Extract the plugin into your editor plugins folder (Commonly C:\Program Files\Epic Games\UE_4.xx\Engine\Plugins)  
   2.1. Your folder structure should be ...\Engine\Plugins\WakaTimeForUE\
   2.2. Within this folder resides WakaTimeForUE.uplugin and other files
3. Run the engine
4. If you already used WakaTime elsewhere, your api key gets loaded. If not, you get prompted by a window.

### Notice
This is my first ever project in C++, so it is definitely not perfect.  
If you have any suggestions how to improve it, or any bug reports, please, use the "Issues" tab.

### Troubleshooting
Q: **The plugin failed to build.**  
A: Branches other than `release` are development branches, so they might contain code that does not compile. If this happens on the `release` branch (or any version tag), make sure you have all dependencies required for building C++ code. You usually install all of them when installing Visual Studio and checking both C++ and .NET.

Q: **I have regenerated my api key, how do I change it in the editor?**  
A: There is a WakaTime icon in the main toolbar. When you click this icon, you can change the api key. Just remember to hit save!

Q: **Does this plugin work on both Unreal Engine 4 and 5?**  
A: Since the version 1.2.5, the main target version is Unreal Engine 5, however, the plugin should work on Unreal Engine 4.26+ as well.

Q: **The plugin says "Heartbeat successfully sent" but I don't see any data on the website.**  
A: You might be using an old version of the CLI, which doesn't support API keys in the `waka_[apiKey]` format.   
You may try to remove the `waka_` prefix to see if that works, but the recommended solution is to update the CLI.  
The latest CLI can be found [on this link](https://github.com/wakatime/wakatime-cli/releases/latest).  
The exe you need to replace is located in `C:\Users\[USER]\.wakatime\[wakatime].exe`.  


---
## Contributors
Thank you to all of you. You have been a huge help.

