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

#include "bspf.hxx"
#include "BrowserDialog.hxx"
#include "EditTextWidget.hxx"
#include "FSNode.hxx"
#include "Font.hxx"
#include "LauncherDialog.hxx"
#include "PopUpWidget.hxx"
#include "Settings.hxx"
#include "ConfigPathDialog.hxx"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
ConfigPathDialog::ConfigPathDialog(
      OSystem& osystem, DialogContainer& parent,
      const GUI::Font& font, GuiObject* boss)
  : Dialog(osystem, parent),
    CommandSender(boss),
    myFont(font),
    myBrowser(nullptr),
    myIsGlobal(boss != nullptr)
{
  const int lineHeight   = font.getLineHeight(),
            fontWidth    = font.getMaxCharWidth(),
            buttonWidth  = font.getStringWidth("Properties file") + 20,
            buttonHeight = font.getLineHeight() + 4;
  const int vBorder = 8;
  const int hBorder = 10;
  int xpos, ypos;
  WidgetArray wid;
  ButtonWidget* b;

  // Set real dimensions
  _w = 56 * fontWidth + 8;
  _h = 9 * (lineHeight + 4) + 10;

  xpos = hBorder;  ypos = vBorder;

  // ROM path
  ButtonWidget* romButton =
    new ButtonWidget(this, font, xpos, ypos, buttonWidth, buttonHeight,
                     "ROM path" + ELLIPSIS, kChooseRomDirCmd);
  wid.push_back(romButton);
  xpos += buttonWidth + 10;
  myRomPath = new EditTextWidget(this, font, xpos, ypos + 2,
                                 _w - xpos - 10, lineHeight, "");
  wid.push_back(myRomPath);

  // Cheat file
  xpos = hBorder;  ypos += romButton->getHeight() + 3;
  b = new ButtonWidget(this, font, xpos, ypos, buttonWidth, buttonHeight,
                       "Cheat file" + ELLIPSIS, kChooseCheatFileCmd);
  wid.push_back(b);
  xpos += buttonWidth + 10;
  myCheatFile = new EditTextWidget(this, font, xpos, ypos + 2,
                                   _w - xpos - 10, lineHeight, "");
  wid.push_back(myCheatFile);

  // Palette file
  xpos = hBorder;  ypos += b->getHeight() + 3;
  b = new ButtonWidget(this, font, xpos, ypos, buttonWidth, buttonHeight,
                       "Palette file" + ELLIPSIS, kChoosePaletteFileCmd);
  wid.push_back(b);
  xpos += buttonWidth + 10;
  myPaletteFile = new EditTextWidget(this, font, xpos, ypos + 2,
                                     _w - xpos - 10, lineHeight, "");
  wid.push_back(myPaletteFile);

  // Properties file
  xpos = hBorder;  ypos += b->getHeight() + 3;
  b = new ButtonWidget(this, font, xpos, ypos, buttonWidth, buttonHeight,
                       "Properties file" + ELLIPSIS, kChoosePropsFileCmd);
  wid.push_back(b);
  xpos += buttonWidth + 10;
  myPropsFile = new EditTextWidget(this, font, xpos, ypos + 2,
                                   _w - xpos - 10, lineHeight, "");
  wid.push_back(myPropsFile);

  // State directory
  xpos = hBorder;  ypos += b->getHeight() + 3;
  b = new ButtonWidget(this, font, xpos, ypos, buttonWidth, buttonHeight,
                       "State path" + ELLIPSIS, kChooseStateDirCmd);
  wid.push_back(b);
  xpos += buttonWidth + 10;
  myStatePath = new EditTextWidget(this, font, xpos, ypos + 2,
                                   _w - xpos - 10, lineHeight, "");
  wid.push_back(myStatePath);

  // NVRAM directory
  xpos = hBorder;  ypos += b->getHeight() + 3;
  b = new ButtonWidget(this, font, xpos, ypos, buttonWidth, buttonHeight,
                       "NVRAM path" + ELLIPSIS, kChooseNVRamDirCmd);
  wid.push_back(b);
  xpos += buttonWidth + 10;
  myNVRamPath = new EditTextWidget(this, font, xpos, ypos + 2,
                                   _w - xpos - 10, lineHeight, "");
  wid.push_back(myNVRamPath);

  // Add Defaults, OK and Cancel buttons
  b = new ButtonWidget(this, font, 10, _h - buttonHeight - 10,
                       font.getStringWidth("Defaults") + 20, buttonHeight,
                       "Defaults", GuiObject::kDefaultsCmd);
  wid.push_back(b);
  addOKCancelBGroup(wid, font);

  addToFocusList(wid);

  // All ROM settings are disabled while in game mode
  if(!myIsGlobal)
  {
    romButton->clearFlags(WIDGET_ENABLED);
    myRomPath->setEditable(false);
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
ConfigPathDialog::~ConfigPathDialog()
{
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ConfigPathDialog::loadConfig()
{
  const Settings& settings = instance().settings();
  myRomPath->setText(settings.getString("romdir"));
  myCheatFile->setText(settings.getString("cheatfile"));
  myPaletteFile->setText(settings.getString("palettefile"));
  myPropsFile->setText(settings.getString("propsfile"));
  myNVRamPath->setText(settings.getString("nvramdir"));
  myStatePath->setText(settings.getString("statedir"));
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ConfigPathDialog::saveConfig()
{
  instance().settings().setValue("romdir", myRomPath->getText());
  instance().settings().setValue("cheatfile", myCheatFile->getText());
  instance().settings().setValue("palettefile", myPaletteFile->getText());
  instance().settings().setValue("propsfile", myPropsFile->getText());
  instance().settings().setValue("statedir", myStatePath->getText());
  instance().settings().setValue("nvramdir", myNVRamPath->getText());

  // Flush changes to disk and inform the OSystem
  instance().saveConfig();
  instance().setConfigPaths();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ConfigPathDialog::setDefaults()
{
  FilesystemNode node;
  const string& basedir = instance().baseDir();

  node = FilesystemNode("~");
  myRomPath->setText(node.getShortPath());

  const string& cheatfile = basedir + "stella.cht";
  node = FilesystemNode(cheatfile);
  myCheatFile->setText(node.getShortPath());

  const string& palettefile = basedir + "stella.pal";
  node = FilesystemNode(palettefile);
  myPaletteFile->setText(node.getShortPath());

  const string& propsfile = basedir + "stella.pro";
  node = FilesystemNode(propsfile);
  myPropsFile->setText(node.getShortPath());

  const string& nvramdir = basedir + "nvram";
  node = FilesystemNode(nvramdir);
  myNVRamPath->setText(node.getShortPath());

  const string& statedir = basedir + "state";
  node = FilesystemNode(statedir);
  myStatePath->setText(node.getShortPath());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ConfigPathDialog::handleCommand(CommandSender* sender, int cmd,
                                     int data, int id)
{
  switch (cmd)
  {
    case GuiObject::kOKCmd:
      saveConfig();
      close();
      if(myIsGlobal)  // Let the boss know romdir has changed
        sendCommand(LauncherDialog::kRomDirChosenCmd, 0, 0);
      break;

    case GuiObject::kDefaultsCmd:
      setDefaults();
      break;

    case kChooseRomDirCmd:
      // This dialog is resizable under certain conditions, so we need
      // to re-create it as necessary
      createBrowser();
      myBrowser->show("Select ROM directory", myRomPath->getText(),
                      BrowserDialog::Directories, LauncherDialog::kRomDirChosenCmd);
      break;

    case kChooseCheatFileCmd:
      // This dialog is resizable under certain conditions, so we need
      // to re-create it as necessary
      createBrowser();
      myBrowser->show("Select cheat file", myCheatFile->getText(),
                      BrowserDialog::FileLoad, kCheatFileChosenCmd);
      break;

    case kChoosePaletteFileCmd:
      // This dialog is resizable under certain conditions, so we need
      // to re-create it as necessary
      createBrowser();
      myBrowser->show("Select palette file", myPaletteFile->getText(),
                      BrowserDialog::FileLoad, kPaletteFileChosenCmd);
      break;

    case kChoosePropsFileCmd:
      // This dialog is resizable under certain conditions, so we need
      // to re-create it as necessary
      createBrowser();
      myBrowser->show("Select properties file", myPropsFile->getText(),
                      BrowserDialog::FileLoad, kPropsFileChosenCmd);
      break;

    case kChooseNVRamDirCmd:
      // This dialog is resizable under certain conditions, so we need
      // to re-create it as necessary
      createBrowser();
      myBrowser->show("Select NVRAM directory", myNVRamPath->getText(),
                      BrowserDialog::Directories, kNVRamDirChosenCmd);
      break;

    case kChooseStateDirCmd:
      // This dialog is resizable under certain conditions, so we need
      // to re-create it as necessary
      createBrowser();
      myBrowser->show("Select state directory", myStatePath->getText(),
                      BrowserDialog::Directories, kStateDirChosenCmd);
      break;

    case LauncherDialog::kRomDirChosenCmd:
      myRomPath->setText(myBrowser->getResult().getShortPath());
      break;

    case kCheatFileChosenCmd:
      myCheatFile->setText(myBrowser->getResult().getShortPath());
      break;

    case kPaletteFileChosenCmd:
      myPaletteFile->setText(myBrowser->getResult().getShortPath());
      break;

    case kPropsFileChosenCmd:
      myPropsFile->setText(myBrowser->getResult().getShortPath());
      break;

    case kNVRamDirChosenCmd:
      myNVRamPath->setText(myBrowser->getResult().getShortPath());
      break;

    case kStateDirChosenCmd:
      myStatePath->setText(myBrowser->getResult().getShortPath());
      break;

    case LauncherDialog::kReloadRomDirCmd:
      sendCommand(LauncherDialog::kReloadRomDirCmd, 0, 0);
      break;

    default:
      Dialog::handleCommand(sender, cmd, data, 0);
      break;
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ConfigPathDialog::createBrowser()
{
  uInt32 w = 0, h = 0;
  getResizableBounds(w, h);

  // Create file browser dialog
  if(!myBrowser || uInt32(myBrowser->getWidth()) != w ||
                   uInt32(myBrowser->getHeight()) != h)
    myBrowser = make_unique<BrowserDialog>(this, myFont, w, h);
}
