#ifndef __AL_SD_HH__
#define __AL_SD_HH__

#include "G4VSensitiveDetector.hh"

class AlSD : public G4VSensitiveDetector
{
private:
	static AlSD* instance;

	AlSD(const G4String& name, const G4String& hitsCollectionName)
		: G4VSensitiveDetector(name)
	{
		collectionName.insert(hitsCollectionName);
	}

	bool isBeforeFirstHit;

public:
	static AlSD* GetInstance()
	{
		if (instance == NULL)
			instance = new AlSD("Al_LV", "INIT_HIT");

		return instance;
	}
	
	virtual ~AlSD();

	// methods from base class
	virtual void   Initialize(G4HCofThisEvent* hitCollection);
	virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
	virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

	void StartEvent();
	void EndEvent();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif // __AL_SD_HH__