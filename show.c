#include <sstream>

void show()
{
	TFile* dataFile = new TFile("al_data.root");

	TGraph** graphs = new TGraph*[2];
	graphs[0] = (TGraph*) dataFile->GetKey("init")->ReadObj();
	graphs[1] = (TGraph*) dataFile->GetKey("last")->ReadObj();

	TCanvas* canvas = new TCanvas("fitting", "circle fitting", 1500, 500);

	TPad* left = new TPad("init", "init", 0, 0, 1./3., 1);
	TPad* mid = new TPad("last before fitting", "last origin", 1./3., 0, 2./3., 1);
	TPad* right = new TPad("last after fitting", "last", 2./3., 0, 1, 1);

	left->Draw();
	mid->Draw();
	right->Draw();

	////////////////////////////////////////////////
	left->cd();
	graphs[0]->Draw("AP");

	////////////////////////////////////////////////
	mid->cd();

	// zoom
	int arrange_min = -100;
	int arrange_max = 100;
	hpx = new TH2F("hpx","last (mm)",100, arrange_min, arrange_max, 100, arrange_min, arrange_max); // axis range
	hpx->SetStats(kFALSE);   // no statistics
	hpx->Draw();

	graphs[1]->Draw("P");

	////////////////////////////////////////////////
	right->cd();

	TGraph* gr = graphs[1];

	double n = gr->GetN();
	double* x = gr->GetX();
	double* y = gr->GetY();

	TH1D* histo = new TH1D("radius", "radius", 6000, 0, 60);
	for (int i = 0; i < n; i++)
	{
		double calc = sqrt(x[i] * x[i] + y[i] * y[i]);
		histo->Fill(calc);
	}

	// fitting

	std::stringstream ss;
	ss << "[0]+[1]*x^1";
	for (int i = 2; i <= 20; i++)
		ss << "+[" << i << "]" << "*x^" << i;

	TF1 *formula = new TF1("fit", ss.str().c_str(), -1000, 1000);

	double* params = histo->Fit("fit", "b")->GetParams();

	double total = formula->Integral(0, 60, params);

	double ratio = 0;
	for (int r = 10; r <= 60; r++)
	{
		double value = formula->Integral(0, r, params);
		ratio = value / total;

		std::cout << r << "mm : " << ratio * 100 << "%" << std::endl;
	}
}