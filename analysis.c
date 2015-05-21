TGraph *gr;

void myfcn(Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t) {
   //minimisation function computing the sum of squares of residuals
   Int_t np = gr->GetN();
   f = 0;
   Double_t *x = gr->GetX();
   Double_t *y = gr->GetY();
   for (Int_t i=0;i<np;i++) {
      Double_t u = x[i] - par[0];
      Double_t v = y[i] - par[1];
      Double_t dr = par[2] - TMath::Sqrt(u*u+v*v);
      f += dr*dr;
   }
}

void init(int n)
{
	gr = new TGraph(n);
	gr->SetMarkerStyle(3);
}

void analysis()
{
	TFile* dataFile = new TFile("al_data.root");
	TH2D* last = (TH2D*) dataFile->GetKey("last")->ReadObj();

	int n = last->GetNbinsX();
	init(n);

	TCanvas* canvas = new TCanvas("canvas", "circle fitting", 800, 600);

   //Fit a circle to the graph points
   TVirtualFitter::SetDefaultFitter("Minuit");  //default is Minuit
   TVirtualFitter *fitter = TVirtualFitter::Fitter(0, 3);
   fitter->SetFCN(myfcn);

   fitter->SetParameter(0, "x0",   0, 0.1, 0,0);
   fitter->SetParameter(1, "y0",   0, 0.1, 0,0);
   fitter->SetParameter(2, "R",    1, 0.1, 0,0);

   Double_t arglist[1] = {0};
   fitter->ExecuteCommand("MIGRAD", arglist, 0);

   //Draw the circle on top of the points
   TArc *arc =
		new TArc(fitter->GetParameter(0),
				fitter->GetParameter(1),
				fitter->GetParameter(2));
   arc->SetLineColor(kRed);
   arc->SetLineWidth(4);
   arc->Draw();
}