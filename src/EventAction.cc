#include "EventAction.hh"

#include "AlSD.hh"
#include "WallSD.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
: G4UserEventAction()
{ } 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{    
	AlSD* alInstance = AlSD::GetInstance();
	WallSD* wallInstance = WallSD::GetInstance();
	
	alInstance->StartEvent();
	wallInstance->StartEvent();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*)
{
	AlSD* alInstance = AlSD::GetInstance();
	WallSD* wallInstance = WallSD::GetInstance();
	
	alInstance->EndEvent();
	wallInstance->EndEvent();
}