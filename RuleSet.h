/* bzflag
 * Copyright (c) 1993 - 2006 Tim Riker
 *
 * This package is free software;  you can redistribute it and/or
 * modify it under the terms of the license found in the file
 * named COPYING that should have accompanied this file.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef __RULESET_H__
#define __RULESET_H__

#include <string>
#include "Rule.h"
#include "Mesh.h"

class RuleSet {
  RuleMap rules;
public:
  RuleSet() {}
  int runMesh(Mesh* mesh, int face, std::string& rulename) {
    RuleMapIter itr = rules.find(rulename); 
    if (itr == rules.end()) return -1;
    return itr->second->runMesh(mesh,face);
  }
  void addRule(std::string& name, Rule* rule) { rules[name] = rule; }
  ~RuleSet() { 
    RuleMapIter itr;
    for (itr = rules.begin();itr != rules.end(); ++itr) delete itr->second; 
  }
};

#endif /* __RULESET_H__ */

// Local Variables: ***
// mode:C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
