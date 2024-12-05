# Makefile generated by MakefileGenerator.cs
# *DO NOT EDIT*

UNREALROOTPATH = /home/alex/Downloads/UE/Linux_Unreal_Engine_5.4.4
GAMEPROJECTFILE =/home/alex/Repos/TowerDefenseUE/TowerDefense/TowerDefense.uproject

TARGETS = \
	UnrealEditor-Linux-DebugGame  \
	UnrealEditor-Linux-Shipping  \
	UnrealEditor \
	UnrealGame-Linux-DebugGame  \
	UnrealGame-Linux-Shipping  \
	UnrealGame \
	TowerDefense-Linux-DebugGame  \
	TowerDefense-Linux-Shipping  \
	TowerDefense \
	TowerDefenseEditor-Linux-DebugGame  \
	TowerDefenseEditor-Linux-Shipping  \
	TowerDefenseEditor\
	configure

BUILD = bash "$(UNREALROOTPATH)/Engine/Build/BatchFiles/Linux/Build.sh"
PROJECTBUILD = "$(UNREALROOTPATH)/Engine/Binaries/ThirdParty/DotNet/6.0.302/linux/dotnet" "$(UNREALROOTPATH)/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.dll"

all: StandardSet

RequiredTools: CrashReportClient-Linux-Shipping CrashReportClientEditor-Linux-Shipping ShaderCompileWorker UnrealLightmass EpicWebHelper-Linux-Shipping

StandardSet: RequiredTools UnrealFrontend TowerDefenseEditor UnrealInsights

DebugSet: RequiredTools UnrealFrontend-Linux-Debug TowerDefenseEditor-Linux-Debug


UnrealEditor-Linux-DebugGame:
	 $(BUILD) UnrealEditor Linux DebugGame  $(ARGS)

UnrealEditor-Linux-Shipping:
	 $(BUILD) UnrealEditor Linux Shipping  $(ARGS)

UnrealEditor:
	 $(BUILD) UnrealEditor Linux Development  $(ARGS)

UnrealGame-Linux-DebugGame:
	 $(BUILD) UnrealGame Linux DebugGame  $(ARGS)

UnrealGame-Linux-Shipping:
	 $(BUILD) UnrealGame Linux Shipping  $(ARGS)

UnrealGame:
	 $(BUILD) UnrealGame Linux Development  $(ARGS)

TowerDefense-Linux-DebugGame:
	 $(PROJECTBUILD) TowerDefense Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

TowerDefense-Linux-Shipping:
	 $(PROJECTBUILD) TowerDefense Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

TowerDefense:
	 $(PROJECTBUILD) TowerDefense Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

TowerDefenseEditor-Linux-DebugGame:
	 $(PROJECTBUILD) TowerDefenseEditor Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

TowerDefenseEditor-Linux-Shipping:
	 $(PROJECTBUILD) TowerDefenseEditor Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

TowerDefenseEditor:
	 $(PROJECTBUILD) TowerDefenseEditor Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

configure:
	xbuild /property:Configuration=Development /verbosity:quiet /nologo "$(UNREALROOTPATH)/Engine/Source/Programs/UnrealBuildTool/UnrealBuildTool.csproj"
	$(PROJECTBUILD) -projectfiles -project="\"$(GAMEPROJECTFILE)\"" -game -engine 

.PHONY: $(TARGETS)