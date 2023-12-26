#ifndef ACTION_H
#define ACTION_H

#include "..\DefS.h"

class ApplicationManager; //forward class declaration
class CFigure;

//Base class for all possible actions
class Action
{
protected:
	ApplicationManager* pManager;	//Actions needs AppMngr to do their job

public:

	Action(ApplicationManager* pApp) { pManager = pApp; }	//constructor

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters() = 0;

	//Execute action (code depends on action type)
	virtual void Execute() = 0;

	//non-virtual function to check if the action can be recorded or not
	bool Recording();

	virtual void Undo() = 0;
	virtual void Redo() = 0;
};

#endif