#include "WallSD.hh"

#include "store_hit_pos.hh"

#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

#include "G4ios.hh"
#include "G4Track.hh"

WallSD* WallSD::instance = NULL;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WallSD::~WallSD() 
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WallSD::Initialize(G4HCofThisEvent*)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool WallSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
	G4Track* track = step->GetTrack();

	if (track->GetTrackID() == 1 && isBeforeFirstHit)
	{
		THFile* file = THFile::getInstance();

		G4ThreeVector pos = step->GetTrack()->GetPosition();
		file->SetPoint(THFile::LAST, pos.getX(), pos.getY());

		isBeforeFirstHit = false;
	}

	return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WallSD::EndOfEvent(G4HCofThisEvent*)
{

}

void WallSD::StartEvent()
{
	isBeforeFirstHit = true;
}

void WallSD::EndEvent()
{
	isBeforeFirstHit = false;
}