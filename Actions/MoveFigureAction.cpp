#include "MoveFigureAction.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

MoveFigureAction::MoveFigureAction(ApplicationManager* pApp) : Action(pApp)
{}

void MoveFigureAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Move a shape, Click where to move the figure ");

	//Read the point clicked
	pIn->GetPointClicked(P.x, P.y);
	pOut->ClearStatusBar();
}

// ============= IN PROGRESS ===================//
void MoveFigureAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	CFigure* SelectedFig = pManager->GetLastSelected();

	if (SelectedFig)
	{
		bool IsFirstIteration = true;
		//int counter = 1;
		do
		{
			ReadActionParameters();
			SelectedFig->Move(P);
			if (!IsFirstIteration)
			{
				// for some reason this message isn't displaying
				pOut->PrintMessage("Invalid Move, Please pick another point");
			}
			//counter++;
			IsFirstIteration = false;
			pOut->ClearStatusBar();
		} while (!(SelectedFig->IsValid()));


		pOut->ClearDrawArea();
		//move coordinates of selected figure to new position
		//clearing drawing area to delete the old position of the selected shape
	}

	else
	{
		pOut->PrintMessage("Please select a shape to move first");
	}

}
