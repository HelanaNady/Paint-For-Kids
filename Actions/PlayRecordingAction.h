#ifndef  PLAYRECORDINGACTION_H
#define PLAYRECORDINGACTION_H

#include "Action.h"

class PlayRecordingAction : public Action
{
public:
	PlayRecordingAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	void Undo();

};

#endif 