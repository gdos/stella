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

#include <cstdlib>

#include "OSystemUNIX.hxx"

/**
  Each derived class is responsible for calling the following methods
  in its constructor:

  setBaseDir()
  setConfigFile()

  See OSystem.hxx for a further explanation
*/

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
OSystemUNIX::OSystemUNIX()
  : OSystem()
{
  // Use XDG_CONFIG_HOME if defined, otherwise use the default
  const char* configDir = getenv("XDG_CONFIG_HOME");
  if(configDir == nullptr)  configDir = "~/.config";

  string stellaDir = string(configDir) + "/stella";

  setBaseDir(stellaDir);
  setConfigFile(stellaDir + "/stellarc");
}
