#include "LCDElement.h"
#include "LCDLock.h"
#include <unistd.h>
#include <pthread.h>
#include <sstream>
#include <iostream>

using namespace std;

set<std::string> LCDElement::_elementsList;
LCDMutex LCDElement::_elementMutex;
unsigned int LCDElement::_elementCounter = 0;

LCDElement::LCDElement(const string &id, const string &addCommand, const string &addParam, LCDElement *parent)
{
  if (id.size() == 0)
  {
    LCDLock l(&LCDElement::_elementMutex);
    ostringstream idBuffer;
    idBuffer << "LCDAPI_"
             << getpid()
             << "_"
             << LCDElement::_elementCounter;

    LCDElement::_elementCounter++;
    _id = idBuffer.str();
  }
  else
  {
    _id = id;
  }
  _elementAddCmd = addCommand;
  _elementAddParam = addParam;
  _parent = parent;
  if (_parent)
  {
    _parent->addToList(this);
  }
  notifyCreated();
}

LCDElement::~LCDElement()
{
  notifyDestroyed();
}

void LCDElement::notifyCreated()
{
  LCDLock l(&LCDElement::_elementMutex);
  sendCommand(_elementAddCmd, _elementAddParam);
  _iAmDead = false;
  LCDElement::_elementsList.insert(_id);
}

void LCDElement::notifyDestroyed()
{
  LCDLock l(&LCDElement::_elementMutex);
  if (!_iAmDead)
  {
    LCDElement::_elementsList.erase(_id);
    ElementMap::iterator it;
    for (it = _childrenList.begin(); it != _childrenList.end(); it++)
    {
      it->second->notifyDestroyed();
    }
    _childrenList.clear();
    sendCommand(_elementDel);
    if (_parent)
    {
      _parent->removeFromList(this);
    }
    _iAmDead = true;
  }
}

bool LCDElement::exists(string id)
{
  LCDLock l(&LCDElement::_elementMutex);
  return ( (LCDElement::_elementsList.find(id)) != (LCDElement::_elementsList.end()) );
}

const string &LCDElement::getId()
{
  return _id;
}

void LCDElement::sendCommand(const std::string &cmd, const std::string &parameters)
{
  LCDLock l(&LCDElement::_elementMutex);
  if (cmd.size() > 0)
  {
    if (_parent)
    {
      string realParams = _id + " " + parameters;
      _parent->sendCommand(cmd, realParams);
    }
    else
    {
      _commandBuffer.push_back(Command(cmd, parameters));
    }
  }
}

void LCDElement::setParent(LCDElement *parent)
{
  _parent = parent;
  notifyAdded();
}

void LCDElement::add(LCDElement *child)
{
  child->setParent(this);
  addToList(child);
}

void LCDElement::addToList(LCDElement *elt)
{
  _childrenList[elt->getId()] = elt;
}

void LCDElement::removeFromList(LCDElement *elt)
{
  _childrenList.erase(elt->getId());
}

void LCDElement::notifyAdded()
{
  CommandList::iterator it;

  for (it = _commandBuffer.begin(); it != _commandBuffer.end(); it++)
  {
    sendCommand(it->_cmd, it->_params);
  }
}
