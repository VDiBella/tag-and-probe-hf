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

TString save = Form("End_Ratio.root");
//TString save2 = Form("ProjectionLargeTagITSTPC.root");
TString fileITSTPC = Form("Sigma_mu_LargeRebinedITSTPC.root"); //You can choose the file here
TString fileTPC = Form("Sigma_mu_LargeRebinedTPC.root"); //You can choose the file here
TString fileITS = Form("Sigma_mu_LargeRebinedITS.root"); //You can choose the file here
//TString file3 = Form("AnalysisResults3.root");
TString table = Form("probe-third-track"); //You can choose the table here
std::string name = "Ratio";
std::string proj_name = "";
TString final_name = Form("");
TString final_name2 = Form("");
TString final_name3 = Form("");


//void DataPrepare(TString const ML){
void Ratio(){

	//We recover the file and the table defined before

	TFile *myFileITSTPC = new TFile(fileITSTPC);
	TFile *myFileITSTPC2 = new TFile(fileITSTPC);
	TFile *myFileTPC = new TFile(fileTPC);
	TFile *myFileITS = new TFile(fileITS);

	TString NameITSTPC = Form("Raw_Yields");
	TString NameTPC = Form("Raw_Yields");
	TString NameITS = Form("Raw_Yields");

	TH1D *YieldITSTPC = (TH1D*)myFileITSTPC->Get(NameITSTPC.Data());
	TH1D *YieldITSTPC2 = (TH1D*)myFileITSTPC2->Get(NameITSTPC.Data());
	TH1D *YieldTPC = (TH1D*)myFileTPC->Get(NameTPC.Data());
	TH1D *YieldITS = (TH1D*)myFileITS->Get(NameITS.Data());

	std::string str1 = std::to_string(1);
	std::string str2 = std::to_string(2);

	remove(save);

	auto f = new TFile(save, "new");

	double_t cut[17] = {0.5,1,1.5,2,2.5,3,3.5,4,5,6,7,8,9,10,12,15,20};


	//We do the differents ratio with the good take on errors
	TH1D *ratio1 = YieldITSTPC;
	ratio1->Divide(ratio1, YieldTPC, 1, 1, "b");
	TH1D *ratio2 = YieldITSTPC2;
	ratio2->Divide(ratio2, YieldITS, 1, 1, "b");
	TH1D *ratio3 = YieldITS;
	ratio3->Divide(ratio3, YieldTPC, 1, 1, "b");

	ratio1->SetTitle("ITSTPC/TPC");
	ratio2->SetTitle("ITSTPC/ITS");
	ratio3->SetTitle("ITS/TPC");
	ratio1->SetXTitle("Pt(Gev)");
	ratio1->SetYTitle("Ratio");
	ratio2->SetXTitle("Pt(Gev)");
	ratio2->SetYTitle("Ratio");
	ratio3->SetXTitle("Pt(Gev)");
	ratio3->SetYTitle("Ratio");

	ratio1->Write("ITSTPCoverTPC");
	ratio2->Write("ITSTPCoverITS");
	ratio3->Write("ITSoverTPC");
}
