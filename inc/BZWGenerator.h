/* bzflag
 * Copyright (c) 1993 - 2007 Tim Riker
 *
 * This package is free software;  you can redistribute it and/or
 * modify it under the terms of the license found in the file
 * named COPYING that should have accompanied this file.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef __BZWGENERATOR_H__
#define __BZWGENERATOR_H__

#include <fstream>
#include <iostream>
#include <sstream>
#include "time.h"

#include "globals.h"

#include "Output.h"
#include "Generator.h"
#include "GridGenerator.h"
#include "Material.h"
#include "commandArgs.h"
#include "Zone.h"
#include "RuleSet.h"
#if COMPILE_PLUGIN
#include "bzfsAPI.h"
#include "plugin_utils.h"
#endif
#include "BZWGenerator.h"

class BZWGenerator 
#if COMPILE_PLUGIN
  : public bz_EventHandler 
#endif
{
  CCommandLineArgs  cmd;
  COSDir ruledir;
  RuleSet* ruleset;
  char* cstr;
  std::string texturepath;
  bool worldGenerated;
public:
  BZWGenerator() : worldGenerated(false) {}
  int parseCommandLine(int argc, char* argv[]);
  int setup();
  ~BZWGenerator() {}
  void generate(std::ostream* outstream);
  void loadConfig(const char* configFile);
  std::string outname;
#if COMPILE_PLUGIN
  virtual void process(bz_EventData * eventData);
#endif
private:
  bool getOptionI ( int &val, char* shortName, char* longName );
  bool getOptionS ( std::string &val, char* shortName, char* longName );
  void printHelp();
  void printHelpCommand ( const char* shortName, const char* longName, const char* description );
};

#endif /* __BZWGENERATOR_H__ */

// Local Variables: ***
// mode:C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8