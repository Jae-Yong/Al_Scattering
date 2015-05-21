#include "AlSD.hh"

#include "store_hit_pos.hh"

#include "G4ThreeVector.hh"

AlSD* AlSD::instance = NULL;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AlSD::~AlSD() 
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void AlSD::Initialize(G4HCofThisEvent*)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool AlSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
	if (step->GetTrack()->GetTrackID() == 1 && isBeforeFirstHit)
	{
		THFile* file = THFile::getInstance();

		G4ThreeVector pos = step->GetTrack()->GetPosition();
		file->SetPoint(THFile::INIT, pos.getX(), pos.getY());

		isBeforeFirstHit = false;
	}

	return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void AlSD::EndOfEvent(G4HCofThisEvent*)
{

}

void AlSD::StartEvent()
{
	isBeforeFirstHit = true;
}

void AlSD::EndEvent()
{
	isBeforeFirstHit = false;
}