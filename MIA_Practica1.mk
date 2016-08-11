##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=MIA_Practica1
ConfigurationName      :=Debug
WorkspacePath          := "/home/marvin/Documentos/MIA_Practica1"
ProjectPath            := "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Marvin Calderon
Date                   :=08/06/16
CodeLitePath           :="/home/marvin/.codelite"
LinkerName             :=gcc
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="MIA_Practica1.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := gcc
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/creacionDiscos.c$(ObjectSuffix) $(IntermediateDirectory)/limpiar.c$(ObjectSuffix) $(IntermediateDirectory)/getPathOnly.c$(ObjectSuffix) $(IntermediateDirectory)/getRandom.c$(ObjectSuffix) $(IntermediateDirectory)/vaciarNumeros.c$(ObjectSuffix) $(IntermediateDirectory)/removeSpaces.c$(ObjectSuffix) $(IntermediateDirectory)/vaciarArreglo.c$(ObjectSuffix) $(IntermediateDirectory)/escanearCrearDisco.c$(ObjectSuffix) $(IntermediateDirectory)/escanearRemoverDisco.c$(ObjectSuffix) \
	$(IntermediateDirectory)/removerDisco.c$(ObjectSuffix) $(IntermediateDirectory)/escanearCrearParticion.c$(ObjectSuffix) $(IntermediateDirectory)/crearParticion.c$(ObjectSuffix) $(IntermediateDirectory)/crearParticionPrimaria.c$(ObjectSuffix) $(IntermediateDirectory)/crearParticionLogica.c$(ObjectSuffix) $(IntermediateDirectory)/crearParticionExtendida.c$(ObjectSuffix) $(IntermediateDirectory)/escanearMontarParticion.c$(ObjectSuffix) $(IntermediateDirectory)/escanearDesmontarParticion.c$(ObjectSuffix) $(IntermediateDirectory)/analizar.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM "main.c"

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) "main.c"

$(IntermediateDirectory)/creacionDiscos.c$(ObjectSuffix): creacionDiscos.c $(IntermediateDirectory)/creacionDiscos.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1/creacionDiscos.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/creacionDiscos.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/creacionDiscos.c$(DependSuffix): creacionDiscos.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/creacionDiscos.c$(ObjectSuffix) -MF$(IntermediateDirectory)/creacionDiscos.c$(DependSuffix) -MM "creacionDiscos.c"

$(IntermediateDirectory)/creacionDiscos.c$(PreprocessSuffix): creacionDiscos.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/creacionDiscos.c$(PreprocessSuffix) "creacionDiscos.c"

$(IntermediateDirectory)/limpiar.c$(ObjectSuffix): limpiar.c $(IntermediateDirectory)/limpiar.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1/limpiar.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/limpiar.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/limpiar.c$(DependSuffix): limpiar.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/limpiar.c$(ObjectSuffix) -MF$(IntermediateDirectory)/limpiar.c$(DependSuffix) -MM "limpiar.c"

$(IntermediateDirectory)/limpiar.c$(PreprocessSuffix): limpiar.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/limpiar.c$(PreprocessSuffix) "limpiar.c"

$(IntermediateDirectory)/getPathOnly.c$(ObjectSuffix): getPathOnly.c $(IntermediateDirectory)/getPathOnly.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1/getPathOnly.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/getPathOnly.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/getPathOnly.c$(DependSuffix): getPathOnly.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/getPathOnly.c$(ObjectSuffix) -MF$(IntermediateDirectory)/getPathOnly.c$(DependSuffix) -MM "getPathOnly.c"

$(IntermediateDirectory)/getPathOnly.c$(PreprocessSuffix): getPathOnly.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/getPathOnly.c$(PreprocessSuffix) "getPathOnly.c"

$(IntermediateDirectory)/getRandom.c$(ObjectSuffix): getRandom.c $(IntermediateDirectory)/getRandom.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1/getRandom.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/getRandom.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/getRandom.c$(DependSuffix): getRandom.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/getRandom.c$(ObjectSuffix) -MF$(IntermediateDirectory)/getRandom.c$(DependSuffix) -MM "getRandom.c"

$(IntermediateDirectory)/getRandom.c$(PreprocessSuffix): getRandom.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/getRandom.c$(PreprocessSuffix) "getRandom.c"

$(IntermediateDirectory)/vaciarNumeros.c$(ObjectSuffix): vaciarNumeros.c $(IntermediateDirectory)/vaciarNumeros.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1/vaciarNumeros.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/vaciarNumeros.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/vaciarNumeros.c$(DependSuffix): vaciarNumeros.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/vaciarNumeros.c$(ObjectSuffix) -MF$(IntermediateDirectory)/vaciarNumeros.c$(DependSuffix) -MM "vaciarNumeros.c"

$(IntermediateDirectory)/vaciarNumeros.c$(PreprocessSuffix): vaciarNumeros.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/vaciarNumeros.c$(PreprocessSuffix) "vaciarNumeros.c"

$(IntermediateDirectory)/removeSpaces.c$(ObjectSuffix): removeSpaces.c $(IntermediateDirectory)/removeSpaces.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1/removeSpaces.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/removeSpaces.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/removeSpaces.c$(DependSuffix): removeSpaces.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/removeSpaces.c$(ObjectSuffix) -MF$(IntermediateDirectory)/removeSpaces.c$(DependSuffix) -MM "removeSpaces.c"

$(IntermediateDirectory)/removeSpaces.c$(PreprocessSuffix): removeSpaces.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/removeSpaces.c$(PreprocessSuffix) "removeSpaces.c"

$(IntermediateDirectory)/vaciarArreglo.c$(ObjectSuffix): vaciarArreglo.c $(IntermediateDirectory)/vaciarArreglo.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1/vaciarArreglo.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/vaciarArreglo.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/vaciarArreglo.c$(DependSuffix): vaciarArreglo.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/vaciarArreglo.c$(ObjectSuffix) -MF$(IntermediateDirectory)/vaciarArreglo.c$(DependSuffix) -MM "vaciarArreglo.c"

$(IntermediateDirectory)/vaciarArreglo.c$(PreprocessSuffix): vaciarArreglo.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/vaciarArreglo.c$(PreprocessSuffix) "vaciarArreglo.c"

$(IntermediateDirectory)/escanearCrearDisco.c$(ObjectSuffix): escanearCrearDisco.c $(IntermediateDirectory)/escanearCrearDisco.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1/escanearCrearDisco.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/escanearCrearDisco.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/escanearCrearDisco.c$(DependSuffix): escanearCrearDisco.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/escanearCrearDisco.c$(ObjectSuffix) -MF$(IntermediateDirectory)/escanearCrearDisco.c$(DependSuffix) -MM "escanearCrearDisco.c"

$(IntermediateDirectory)/escanearCrearDisco.c$(PreprocessSuffix): escanearCrearDisco.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/escanearCrearDisco.c$(PreprocessSuffix) "escanearCrearDisco.c"

$(IntermediateDirectory)/escanearRemoverDisco.c$(ObjectSuffix): escanearRemoverDisco.c $(IntermediateDirectory)/escanearRemoverDisco.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1/escanearRemoverDisco.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/escanearRemoverDisco.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/escanearRemoverDisco.c$(DependSuffix): escanearRemoverDisco.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/escanearRemoverDisco.c$(ObjectSuffix) -MF$(IntermediateDirectory)/escanearRemoverDisco.c$(DependSuffix) -MM "escanearRemoverDisco.c"

$(IntermediateDirectory)/escanearRemoverDisco.c$(PreprocessSuffix): escanearRemoverDisco.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/escanearRemoverDisco.c$(PreprocessSuffix) "escanearRemoverDisco.c"

$(IntermediateDirectory)/removerDisco.c$(ObjectSuffix): removerDisco.c $(IntermediateDirectory)/removerDisco.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1/removerDisco.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/removerDisco.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/removerDisco.c$(DependSuffix): removerDisco.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/removerDisco.c$(ObjectSuffix) -MF$(IntermediateDirectory)/removerDisco.c$(DependSuffix) -MM "removerDisco.c"

$(IntermediateDirectory)/removerDisco.c$(PreprocessSuffix): removerDisco.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/removerDisco.c$(PreprocessSuffix) "removerDisco.c"

$(IntermediateDirectory)/escanearCrearParticion.c$(ObjectSuffix): escanearCrearParticion.c $(IntermediateDirectory)/escanearCrearParticion.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1/escanearCrearParticion.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/escanearCrearParticion.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/escanearCrearParticion.c$(DependSuffix): escanearCrearParticion.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/escanearCrearParticion.c$(ObjectSuffix) -MF$(IntermediateDirectory)/escanearCrearParticion.c$(DependSuffix) -MM "escanearCrearParticion.c"

$(IntermediateDirectory)/escanearCrearParticion.c$(PreprocessSuffix): escanearCrearParticion.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/escanearCrearParticion.c$(PreprocessSuffix) "escanearCrearParticion.c"

$(IntermediateDirectory)/crearParticion.c$(ObjectSuffix): crearParticion.c $(IntermediateDirectory)/crearParticion.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1/crearParticion.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/crearParticion.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/crearParticion.c$(DependSuffix): crearParticion.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/crearParticion.c$(ObjectSuffix) -MF$(IntermediateDirectory)/crearParticion.c$(DependSuffix) -MM "crearParticion.c"

$(IntermediateDirectory)/crearParticion.c$(PreprocessSuffix): crearParticion.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/crearParticion.c$(PreprocessSuffix) "crearParticion.c"

$(IntermediateDirectory)/crearParticionPrimaria.c$(ObjectSuffix): crearParticionPrimaria.c $(IntermediateDirectory)/crearParticionPrimaria.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1/crearParticionPrimaria.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/crearParticionPrimaria.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/crearParticionPrimaria.c$(DependSuffix): crearParticionPrimaria.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/crearParticionPrimaria.c$(ObjectSuffix) -MF$(IntermediateDirectory)/crearParticionPrimaria.c$(DependSuffix) -MM "crearParticionPrimaria.c"

$(IntermediateDirectory)/crearParticionPrimaria.c$(PreprocessSuffix): crearParticionPrimaria.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/crearParticionPrimaria.c$(PreprocessSuffix) "crearParticionPrimaria.c"

$(IntermediateDirectory)/crearParticionLogica.c$(ObjectSuffix): crearParticionLogica.c $(IntermediateDirectory)/crearParticionLogica.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1/crearParticionLogica.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/crearParticionLogica.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/crearParticionLogica.c$(DependSuffix): crearParticionLogica.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/crearParticionLogica.c$(ObjectSuffix) -MF$(IntermediateDirectory)/crearParticionLogica.c$(DependSuffix) -MM "crearParticionLogica.c"

$(IntermediateDirectory)/crearParticionLogica.c$(PreprocessSuffix): crearParticionLogica.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/crearParticionLogica.c$(PreprocessSuffix) "crearParticionLogica.c"

$(IntermediateDirectory)/crearParticionExtendida.c$(ObjectSuffix): crearParticionExtendida.c $(IntermediateDirectory)/crearParticionExtendida.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1/crearParticionExtendida.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/crearParticionExtendida.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/crearParticionExtendida.c$(DependSuffix): crearParticionExtendida.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/crearParticionExtendida.c$(ObjectSuffix) -MF$(IntermediateDirectory)/crearParticionExtendida.c$(DependSuffix) -MM "crearParticionExtendida.c"

$(IntermediateDirectory)/crearParticionExtendida.c$(PreprocessSuffix): crearParticionExtendida.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/crearParticionExtendida.c$(PreprocessSuffix) "crearParticionExtendida.c"

$(IntermediateDirectory)/escanearMontarParticion.c$(ObjectSuffix): escanearMontarParticion.c $(IntermediateDirectory)/escanearMontarParticion.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1/escanearMontarParticion.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/escanearMontarParticion.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/escanearMontarParticion.c$(DependSuffix): escanearMontarParticion.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/escanearMontarParticion.c$(ObjectSuffix) -MF$(IntermediateDirectory)/escanearMontarParticion.c$(DependSuffix) -MM "escanearMontarParticion.c"

$(IntermediateDirectory)/escanearMontarParticion.c$(PreprocessSuffix): escanearMontarParticion.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/escanearMontarParticion.c$(PreprocessSuffix) "escanearMontarParticion.c"

$(IntermediateDirectory)/escanearDesmontarParticion.c$(ObjectSuffix): escanearDesmontarParticion.c $(IntermediateDirectory)/escanearDesmontarParticion.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1/escanearDesmontarParticion.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/escanearDesmontarParticion.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/escanearDesmontarParticion.c$(DependSuffix): escanearDesmontarParticion.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/escanearDesmontarParticion.c$(ObjectSuffix) -MF$(IntermediateDirectory)/escanearDesmontarParticion.c$(DependSuffix) -MM "escanearDesmontarParticion.c"

$(IntermediateDirectory)/escanearDesmontarParticion.c$(PreprocessSuffix): escanearDesmontarParticion.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/escanearDesmontarParticion.c$(PreprocessSuffix) "escanearDesmontarParticion.c"

$(IntermediateDirectory)/analizar.c$(ObjectSuffix): analizar.c $(IntermediateDirectory)/analizar.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/marvin/Documentos/MIA_Practica1/MIA_Practica1/analizar.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/analizar.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/analizar.c$(DependSuffix): analizar.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/analizar.c$(ObjectSuffix) -MF$(IntermediateDirectory)/analizar.c$(DependSuffix) -MM "analizar.c"

$(IntermediateDirectory)/analizar.c$(PreprocessSuffix): analizar.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/analizar.c$(PreprocessSuffix) "analizar.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


