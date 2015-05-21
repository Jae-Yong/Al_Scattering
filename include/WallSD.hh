#ifndef __WALL_SD_HH__
#define __WALL_SD_HH__

#include "G4VSensitiveDetector.hh"

class WallSD : public G4VSensitiveDetector
{
private:
	static WallSD* instance;

	WallSD(const G4String& name, const G4String& hitsCollectionName)
		: G4VSensitiveDetector(name)
	{
		collectionName.insert(hitsCollectionName);
	}

	bool isBeforeFirstHit;

public:
	static WallSD* GetInstance()
	{
		if (instance == NULL)
			instance = new WallSD("Fe_LV", "Wall_SD");

		return instance;
	}
	
	virtual ~WallSD();

	// methods from base class
	virtual void   Initialize(G4HCofThisEvent* hitCollection);
	virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
	virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

	void StartEvent();
	void EndEvent();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif // __WALL_SD_HH__