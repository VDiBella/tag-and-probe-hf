#include <iostream>
#include <cmath>
#include "TString.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TDirectoryFile.h"
#include "TF1.h"
#include <list>
#include <string>

#define LOG(x) std::cout<<"-------------------------"<<x<<std::endl

//-----------------------------------------------------------------------------------------------------------------------------------------------
//Initialisation of differents variables
//TString ML = Form("with");

TString save = Form("MonteCarloTruthA.root");
TString file = Form("AnalysisResultsMCa.root"); //You can choose the file here
//TString file2 = Form("AnalysisResults2.root");
//TString file3 = Form("AnalysisResults3.root");
TString table = Form("tag-two-prong-displaced-vertices"); //You can choose the table here
std::string name = "Projection";
std::string proj_name = "";
TString final_name = Form("");

//void DataPrepare(TString const ML){
void CarloTruth(){

	//We recover the file and the table defined before
	TFile *myFile = new TFile(file);

	// We get the histogram and their errors
	TString Name = Form("hPromptMlScore1");

	TDirectoryFile *Folder = (TDirectoryFile*)myFile->Get(table);
	TH2D *MlTruth = (TH2D*)Folder->Get(Name.Data());

	std::string str1 = std::to_string(1);
	std::string str2 = std::to_string(2);

	remove(save);

	TFile f(save, "new");

	double_t cut[12] = {0.5,1,1.5,2,2.5,3,3.5,4,5,6,7,8};

	TH1 *total_number = new TH1D("Number_of_Particles","Number_of_particle_per_pt;Pt(Gev);Number_of_particles",11, cut);

	TAxis *xaxis = MlTruth->GetXaxis();
	TAxis *yaxis = MlTruth->GetYaxis();

	for (int i=0; i<11; i++) {

		//LOG(i);

		//The name of the differents part of the outfile is define here
		str1 = std::to_string(cut[i]);
		str2 = std::to_string(cut[i+1]);
		proj_name = name + str1;
		proj_name = proj_name + "-";
		proj_name = proj_name + str2;
		final_name = proj_name;
		final_name = "probe"+proj_name;

		//We define the Range
		int binmin = xaxis->FindBin(1.00001*cut[i]);
		int binmax = xaxis->FindBin(0.99999*cut[i+1]);
		int ybinmin = yaxis->FindBin(1.00001*0.9);
		int ybinmax = yaxis->FindBin(0.999999*1);
		yaxis->SetRange(ybinmin,ybinmax);
		int lastbin2 = MlTruth->GetNbinsX();
		int lastbin1 = MlTruth->GetNbinsY();
		
		for(int j=0; j<lastbin1; j++){
			for(int k=0; k<lastbin2; k++){
				if (yaxis->GetBinLowEdge(j) <= 0.9){
					MlTruth->SetBinContent(k,j,0);
				}
			}
		}
		TH1D *Projected = MlTruth->ProjectionY(final_name,binmin,binmax);
		total_number->SetBinContent(i,Projected->GetEntries());
		Projected->Write();
	}
	total_number->Write();
}
