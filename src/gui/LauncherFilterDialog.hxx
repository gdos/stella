//============================================================================
//
//   SSSS    tt          lll  lll
//  SS  SS   tt           ll   ll
//  SS     tttttt  eeee   ll   ll   aaaa
//   SSSS    tt   ee  ee  ll   ll      aa
//      SS   tt   eeeeee  ll   ll   aaaaa  --  "An Atari 2600 VCS Emulator"
//  SS  SS   tt   ee      ll   ll  aa  aa
//   SSSS     ttt  eeeee llll llll  aaaaa
//
// Copyright (c) 1995-2018 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#ifndef LAUNCHER_FILTER_DIALOG_HXX
#define LAUNCHER_FILTER_DIALOG_HXX

class CommandSender;
class DialogContainer;
class FilesystemNode;
class CheckboxWidget;
class PopUpWidget;
class OSystem;

#include "bspf.hxx"
#include "Dialog.hxx"
#include "Settings.hxx"

class LauncherFilterDialog : public Dialog, public CommandSender
{
  public:
    LauncherFilterDialog(GuiObject* boss, const GUI::Font& font);
    virtual ~LauncherFilterDialog() = default;

    /** Add valid extensions from 'exts' to the given StringList */
    static void parseExts(StringList& list, const string& exts);

    /**
      Is this a valid ROM filename (does it have a valid extension from
      those specified in the list of extensions).

      @param name  Filename of potential ROM file
      @param exts  The list of extensions to consult
     */
    static bool isValidRomName(const string& name, const StringList& exts);

    /**
      Is this a valid ROM filename (does it have a valid extension?).

      @param name  File node of potential ROM file
      @param ext   The extension extracted from the given file
     */
    static bool isValidRomName(const FilesystemNode& name, string& ext);

  private:
    void loadConfig() override;
    void saveConfig() override;
    void setDefaults() override;

    void handleFileTypeChange(const string& type);
    void handleCommand(CommandSender* sender, int cmd, int data, int id) override;

  private:
    PopUpWidget*    myFileType;
    CheckboxWidget* myRomType[5];

    enum {
      kFileTypeChanged = 'LFDc'
    };

    // Holds static strings representing ROM types
    static const char* const ourRomTypes[2][5];

  private:
    // Following constructors and assignment operators not supported
    LauncherFilterDialog() = delete;
    LauncherFilterDialog(const LauncherFilterDialog&) = delete;
    LauncherFilterDialog(LauncherFilterDialog&&) = delete;
    LauncherFilterDialog& operator=(const LauncherFilterDialog&) = delete;
    LauncherFilterDialog& operator=(LauncherFilterDialog&&) = delete;
};

#endif
