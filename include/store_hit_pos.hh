#ifndef __STORE_HIT_POS_HH__
#define __STORE_HIT_POS_HH__

#include "TFile.h"
#include "TGraph.h"
#include "TAxis.h"

class THFile
{
private:
	static THFile* instance;

	TFile* file;

	TGraph** gr;
	int* idx;

	THFile()
	{
		gr = new TGraph*[2];
		idx = new int[2];

		for (int i = 0; i < 2; i++)
		{
			gr[i] = NULL;
			idx[i] = 0;
		}
	}

public:
	static THFile* getInstance()
	{
		if (instance == NULL)
		{
			instance = new THFile();
			return instance;
		}

		return instance;
	}

	enum POS { INIT = 0, LAST };

	void SetPoint(POS pos, double x, double y);
	void close();
};

#endif // __STORE_HIT_POS_HH__