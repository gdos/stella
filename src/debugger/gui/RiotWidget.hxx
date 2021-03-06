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

#ifndef RIOT_WIDGET_HXX
#define RIOT_WIDGET_HXX

class GuiObject;
class ButtonWidget;
class DataGridWidget;
class PopUpWidget;
class ToggleBitWidget;
class ControllerWidget;
class Controller;

#include "Widget.hxx"
#include "Command.hxx"

class RiotWidget : public Widget, public CommandSender
{
  public:
    RiotWidget(GuiObject* boss, const GUI::Font& lfont, const GUI::Font& nfont,
               int x, int y, int w, int h);
    virtual ~RiotWidget() = default;

  private:
    ControllerWidget* addControlWidget(GuiObject* boss, const GUI::Font& font,
        int x, int y, Controller& controller);

    void handleConsole();
    void handleCommand(CommandSender* sender, int cmd, int data, int id) override;
    void loadConfig() override;

  private:
    ToggleBitWidget* mySWCHAReadBits;
    ToggleBitWidget* mySWCHAWriteBits;
    ToggleBitWidget* mySWACNTBits;
    ToggleBitWidget* mySWCHBReadBits;
    ToggleBitWidget* mySWCHBWriteBits;
    ToggleBitWidget* mySWBCNTBits;

    DataGridWidget* myLeftINPT;
    DataGridWidget* myRightINPT;
    CheckboxWidget* myINPTLatch;
    CheckboxWidget* myINPTDump;

    DataGridWidget* myTimWrite;
    DataGridWidget* myTimRead;

    ControllerWidget *myLeftControl, *myRightControl;
    PopUpWidget *myP0Diff, *myP1Diff;
    PopUpWidget *myTVType;
    CheckboxWidget* mySelect;
    CheckboxWidget* myReset;
    CheckboxWidget* myPause;

    EditTextWidget*    myConsole;

    // ID's for the various widgets
    // We need ID's, since there are more than one of several types of widgets
    enum {
      kTim1TID, kTim8TID, kTim64TID, kTim1024TID, kTimWriteID,
      kSWCHABitsID, kSWACNTBitsID, kSWCHBBitsID, kSWBCNTBitsID,
      kP0DiffChanged, kP1DiffChanged, kTVTypeChanged, kSelectID, kResetID,
      kSWCHARBitsID, kPauseID
    };

  private:
    // Following constructors and assignment operators not supported
    RiotWidget() = delete;
    RiotWidget(const RiotWidget&) = delete;
    RiotWidget(RiotWidget&&) = delete;
    RiotWidget& operator=(const RiotWidget&) = delete;
    RiotWidget& operator=(RiotWidget&&) = delete;
};

#endif
