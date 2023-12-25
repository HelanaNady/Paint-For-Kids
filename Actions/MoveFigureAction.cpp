#include "MoveFigureAction.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

MoveFigureAction::MoveFigureAction(ApplicationManager* pApp, bool muted) : Action(pApp)
{
	if (!muted)
	{
		PlaySound(TEXT("Sounds\\Click"), NULL, SND_SYNC);
	}
}

void MoveFigureAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//pOut->PrintMessage("Move a shape action");

	CFigure* SelectedFig = pManager->GetLastSelected();

	if (SelectedFig)
	{
		pOut->PrintMessage("Move figure action, Click where to move the figure ");
		//Read the point clicked
		pIn->GetPointClicked(P.x, P.y);
	}

	else
	{
		pOut->PrintMessage("Please select a shape to move first");
	}

	pOut->ClearStatusBar();
}

// ============= IN PROGRESS ===================//
void MoveFigureAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//if the recording isn't playing, read the action parameters first
	bool PlayingRecord = pManager->GetPlayingRecord();
	
	if (!PlayingRecord)
	{
		ReadActionParameters();
	}

	CFigure* SelectedFig = pManager->GetLastSelected();
	//SelectedFig->ChngDrawClr(UI.HighlightColor);
	pManager->UpdateInterface();

	if (SelectedFig)
	{
		SelectedFig->Move(P);
		while (!SelectedFig->IsValidMove())
		{
			pOut->PrintMessage("Invalid Move, Please pick another point");
			pIn->GetPointClicked(P.x, P.y);
			SelectedFig->Move(P);
			pOut->ClearStatusBar();
		}

		//clearing drawing area to delete the old position of the selected shape
		pManager->AddtoUndo(this);
		pOut->ClearDrawArea();
		pManager->UpdateInterface();
	}

	if (Recording())
	{
		pManager->AddRecordedAction(this);
	}
}

void MoveFigureAction::Undo()
{
	Output* pOut = pManager->GetOutput();
	SelectedFig->UndoMove();
	pManager->RemovefromUndo();
	pOut->ClearDrawArea();
	pManager->UpdateInterface();
}
