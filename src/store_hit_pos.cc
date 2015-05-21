#include "store_hit_pos.hh"

THFile* THFile::instance = NULL;

void THFile::SetPoint(POS pos, double x, double y)
{
	int sel = (int) pos;

	if (gr[sel] == NULL)
	{
		gr[sel] = new TGraph();
		gr[sel]->SetMarkerStyle(1);

		if (sel == 0)
			gr[sel]->SetNameTitle("init", "init (mm)");
		else
			gr[sel]->SetNameTitle("last", "last (mm)");
	}

	gr[sel]->SetPoint(idx[sel]++, x, y);
}

void THFile::close()
{
	file = new TFile("al_data.root", "recreate");

	for (int i = 0; i < 2; i++)
	{
		gr[i]->GetXaxis()->SetTitle("(mm)");
		gr[i]->GetYaxis()->SetTitle("(mm)");

		gr[i]->GetXaxis()->CenterTitle();
		gr[i]->GetYaxis()->CenterTitle();

		gr[i]->Write();
		delete gr[i];
	}

	delete[] gr;
	delete[] idx;

	gr = NULL;
	idx = NULL;

	file->Close();
	delete file;

	instance = NULL;
}