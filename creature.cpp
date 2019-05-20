#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>

#include "common.h"
#include "creature.h"

Creature* Basic::proto = new Basic();
Creature* Friendly::proto = new Friendly();
Creature* Unfriendly::proto = new Unfriendly();

bool Basic::isSurviving(int neighbours) const
{
     return (neighbours != 0 && neighbours <= 4) ? true : false;
}

bool Friendly::isSurviving(int neighbours) const
{
     return (neighbours >= 2 && neighbours <= 4) ? true : false;
}

bool Unfriendly::isSurviving(int neighbours) const 
{
     return (neighbours >= 0 && neighbours <= 4) ? true : false;
}


Creature* CreatureFactory::make(std::string type)
{
     if (type== "b")
     {
          return new Basic;
     }
     else if (type== "f")
     {
          return new Friendly;
     }
     else if (type== "u")
     {
          return new Unfriendly;
     }
     else
     {
          throw std::runtime_error("undefined creature type");
     }
}

std::string Basic::symbol() const
{
     return "b";
}

std::string Friendly::symbol() const
{
     return "f";
}

std::string Unfriendly::symbol() const
{
     return "u";
}

Creature* Basic::prototype() const
{
     return proto;
}

Creature* Friendly::prototype() const
{
     return proto;
}

Creature* Unfriendly::prototype() const
{
     return proto;
}
