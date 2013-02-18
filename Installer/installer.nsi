!include "MUI2.nsh"
!define VERSION '0.1.0'

Name "Crysis VR"

OutFile ".\output\crysis-vr-${VERSION}.exe"


;TODO: 
!define MUI_ICON '.\images\crysis.ico'
;!define MUI_HEADERIMAGE images\header.bmp ;150x57

!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Header\nsis.bmp" ; optional
  
;Welcome Page Settings
!define MUI_WELCOMEFINISHPAGE_BITMAP ".\images\welcome.bmp"; 164x314 
!define MUI_WELCOMEPAGE_TITLE 'Welcome to the installation for Crysis VR v${VERSION}'
!define MUI_WELCOMEPAGE_TEXT 'Thanks for installing Crysis Virtual Reality Mod, this should only take a few seconds.  \
Keep in mind this is a very early version so if you have any issues or ideas please send feedback so we can improve the mod'

!define MUI_DIRECTORYPAGE_TEXT 'Please verify the location of your Steam sourcemods folder.'

!define MUI_FINISHPAGE_TITLE 'Installation Completed Successfully.'
!define MUI_FINISHPAGE_TEXT 'Restart steam to see the mod in your games list on Steam.'


!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

Section "" 

	SetOutPath $INSTDIR\Mods\CrysisVR
	File /r .\package\*

	SetOutPath $INSTDIR\Bin32
	File .\package\Dependencies\*

SectionEnd

Function .onInit
	ReadRegStr $R1 HKCU "Software\Valve\Steam" "SourceModInstallPath"
	StrCpy $INSTDIR "$R1\..\common\crysis"
FunctionEnd