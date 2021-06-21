!include MUI2.nsh
!include LogicLib.nsh
!include x64.nsh

;--------------------------------
; General

Name "OpenMic"
OutFile "OpenMic_Windows_Installer.exe"
Unicode true

InstallDir "$PROGRAMFILES\GrzybDev\OpenMic"
InstallDirRegKey HKCU "Software\GrzybDev\OpenMic" "InstallDir"
RequestExecutionLevel admin

;--------------------------------
; UI

!define MUI_ICON "src\res\icon.ico"
!define MUI_ABORTWARNING
!define MUI_WELCOMEPAGE_TITLE "OpenMic Setup"

;--------------------------------
; Pages

; Installer pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "LICENSE.md"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

; Set UI language
!insertmacro MUI_LANGUAGE "English"

;--------------------------------
; Section - Install App

Section "-hidden app"
    SectionIn RO
    SetOutPath "$INSTDIR"
    File /r "final_build\*" 
    WriteRegStr HKCU "Software\GrzybDev\OpenMic" "InstallDir" $INSTDIR
    WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd

;--------------------------------
; Section - Android Debug Bridge

Section "Android Debug Bridge" adb
    SetOutPath "$INSTDIR"
    File /r "bin\*"
    DetailPrint "Extracting Android Debug Bridge files..."
SectionEnd

;--------------------------------
; Section - VB-Cable

Section "VB-Audio Virtual Cable" vbcable
    SetOutPath "$INSTDIR\redist\VB-Cable"
    File /r "win_vbcable\*"
    DetailPrint "Installing VB-Audio Virtual Cable..."
    ${If} ${RunningX64}
        ExecWait '"$INSTDIR\redist\VB-Cable\VBCABLE_Setup_x64.exe" -i -h'
    ${Else}
        ExecWait '"$INSTDIR\redist\VB-Cable\VBCable_Setup.exe" -i -h'
    ${EndIf}

    MessageBox MB_OK "While reboot is not strictly required, you may (or may not) encounter some difficulties using VB-Cable without rebooting your computer. If that's the case please reboot your computer"
SectionEnd

;--------------------------------
; Section - Microsoft Visual C++ 2019

Section "Microsoft Visual C++" msvc
    SetOutPath "$INSTDIR\redist\vcredist\2019"
    File /nonfatal "vc_redist.x64.exe"
    File /nonfatal "vc_redist.x86.exe"

    DetailPrint "Installing Visual C++ 2019 redist..."

    ${If} ${RunningX64}
        ExecWait '"$INSTDIR\redist\vcredist\2019\vc_redist.x64.exe" /Q'
    ${Else}
        ExecWait '"$INSTDIR\redist\vcredist\2019\vc_redist.x86.exe" /Q'
    ${EndIf}
SectionEnd

;--------------------------------
; Section - Shortcut

Section "Desktop Shortcut" DeskShort
    CreateShortCut "$DESKTOP\OpenMic.lnk" "$INSTDIR\OpenMic.exe"
SectionEnd

;--------------------------------
; Descriptions

;Language strings
LangString DESC_DeskShort ${LANG_ENGLISH} "Create Shortcut on Desktop."
LangString DESC_msvc ${LANG_ENGLISH} "Microsoft Visual C++ 2019 (required to run OpenMic)"
LangString DESC_vbcable ${LANG_ENGLISH} "VB-Cable (www.vb-cable.com) by VB-Audio spawns virtual audio devices that are required in order to be able to use OpenMic. This project is a donationware, all participations are welcome."
LangString DESC_adb ${LANG_ENGLISH} "Android Debug Bridge is required if you want to connect phone via USB"

;Assign language strings to sections
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${DeskShort} $(DESC_DeskShort)
    !insertmacro MUI_DESCRIPTION_TEXT ${msvc} $(DESC_msvc)
    !insertmacro MUI_DESCRIPTION_TEXT ${vbcable} $(DESC_vbcable)
    !insertmacro MUI_DESCRIPTION_TEXT ${adb} $(DESC_adb)
!insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
; Remove empty parent directories

Function un.RMDirUP
    !define RMDirUP '!insertmacro RMDirUPCall'

    !macro RMDirUPCall _PATH
          push '${_PATH}'
          Call un.RMDirUP
    !macroend

    ; $0 - current folder
    ClearErrors

    Exch $0
    ;DetailPrint "ASDF - $0\.."
    RMDir "$0\.."

    IfErrors Skip
    ${RMDirUP} "$0\.."
    Skip:

    Pop $0

FunctionEnd

;--------------------------------
; Section - Uninstaller

Section "Uninstall"

  ;Delete Shortcut
  Delete "$DESKTOP\OpenMic.lnk"

  ;Delete Uninstall
  Delete "$INSTDIR\Uninstall.exe"

  ;Delete Folder
  RMDir /r "$INSTDIR"
  ${RMDirUP} "$INSTDIR"

  DeleteRegKey /ifempty HKCU "Software\GrzybDev\OpenMic"

SectionEnd