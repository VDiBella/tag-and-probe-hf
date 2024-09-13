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
TString save = Form("ProjectionMCa.root");
//TString save2 = Form("ProjectionLargeTagITSTPC.root");
TString fileITSTPC = Form("AnalysisResultsMCa.root"); //You can choose the file here
TString fileTPC = Form("AnalysisResultsMCa.root"); //You can choose the file here
TString fileITS = Form("AnalysisResultsMCa.root"); //You can choose the file here
//TString file3 = Form("AnalysisResults3.root");
TString table = Form("probe-third-track"); //You can choose the table here
std::string name = "Projection";
std::string proj_name = "";
TString final_name = Form("");
TString final_name2 = Form("");
TString final_name3 = Form("");


//void DataPrepare(TString const ML){
void Truth_Ratio(){

	//We recover the file and the table defined before
	TFile *myFileITSTPC = new TFile(fileITSTPC);

	TFile *myFileTPC = new TFile(fileTPC);

	TFile *myFileITS = new TFile(fileITS);

	// We get the histogram
	TString NameITSTPC = Form("hDplusToKPiPiVsPtProbeTag_ItsTpc");

	TDirectoryFile *FolderITSTPC = (TDirectoryFile*)myFileITSTPC->Get(table);
	THnSparse *SparseITSTPC = (THnSparse*)FolderITSTPC->Get(NameITSTPC.Data());

	TString NameTPC = Form("hDplusToKPiPiVsPtProbeTag_Tpc");

	TDirectoryFile *FolderTPC = (TDirectoryFile*)myFileTPC->Get(table);
	THnSparse *SparseTPC = (THnSparse*)FolderTPC->Get(NameTPC.Data());

	TString NameITS = Form("hDplusToKPiPiVsPtProbeTag_Its");

	TDirectoryFile *FolderITS = (TDirectoryFile*)myFileITS->Get(table);
	THnSparse *SparseITS = (THnSparse*)FolderITS->Get(NameITS.Data());

	std::string str1 = std::to_string(1);
	std::string str2 = std::to_string(2);

	//We erase the last output file be carefull to do a backup if you want to keep it
	remove(save);

	//We define directories in order to do the full analysis in one time
	auto f = new TFile(save, "new");
	TDirectoryFile* ITSProbe = new TDirectoryFile("ITSProbe", "ITSProbe");
	TDirectoryFile* TPCProbe = new TDirectoryFile("TPCProbe", "TPCProbe");
	TDirectoryFile* ITSTPCProbe = new TDirectoryFile("ITSTPCProbe", "ITSTPCProbe");


	double_t cut[17] = {0.5,1,1.5,2,2.5,3,3.5,4,5,6,7,8,9,10,12,15,20};

	TH1 *IntegrationITSTPC = new TH1D("Integration of the number of particle for TPCITS","Number_of_particle;Pt(Gev);Number_of_particles",16, cut);
	TH1 *IntegrationTPC = new TH1D("Integration of the number of particle for TPC","Number_of_particle;Pt(Gev);Number_of_particles",16, cut);
	TH1 *IntegrationITS = new TH1D("Integration of the number of particle for ITS","Number_of_particle;Pt(Gev);Number_of_particles",16, cut);


	ITSTPCProbe->cd();

	for (int i=0; i<17; i++) {
		//The name of the differents part of the outfile is define here
		str1 = std::to_string(cut[i]);
		str2 = std::to_string(cut[i+1]);
		proj_name = name + str1;
		proj_name = proj_name + "-";
		proj_name = proj_name + str2;
		final_name = proj_name;

		//We define the Range
		int binmin = SparseITSTPC->GetAxis(2)->FindBin(1.00001*cut[i]);
		int binmax = SparseITSTPC->GetAxis(2)->FindBin(0.99999*cut[i+1]);
		SparseITSTPC->GetAxis(2)->SetRange(binmin,binmax); //We define the Pt bin
		TH1D *Projected = SparseITSTPC->Projection(4);

		Projected->SetName(final_name);
		IntegrationITSTPC->SetBinContent(i,Projected->Integral());

		Projected->Write();
	}
	IntegrationITSTPC->Write();

	//We change the directory in the root file
	TPCProbe->cd();

	for (int i=0; i<17; i++) {
		//The name of the differents part of the outfile is define here
		str1 = std::to_string(cut[i]);
		str2 = std::to_string(cut[i+1]);
		proj_name = name + str1;
		proj_name = proj_name + "-";
		proj_name = proj_name + str2;
		final_name = proj_name;

		//We define the Range
		int binmin = SparseTPC->GetAxis(2)->FindBin(1.00001*cut[i]);
		int binmax = SparseTPC->GetAxis(2)->FindBin(0.99999*cut[i+1]);
		SparseTPC->GetAxis(2)->SetRange(binmin,binmax); //We define the Pt bin
		TH1D *Projected = SparseTPC->Projection(4);
		Projected->SetName(final_name);
		IntegrationTPC->SetBinContent(i,Projected->Integral());

		Projected->Write();
	}
	IntegrationTPC->Write();

	//We change the directory in the root file
	ITSProbe->cd();

	for (int i=0; i<17; i++) {
		//The name of the differents part of the outfile is define here
		str1 = std::to_string(cut[i]);
		str2 = std::to_string(cut[i+1]);
		proj_name = name + str1;
		proj_name = proj_name + "-";
		proj_name = proj_name + str2;
		final_name = proj_name;

		//We define the Range
		int binmin = SparseITS->GetAxis(2)->FindBin(1.00001*cut[i]);
		int binmax = SparseITS->GetAxis(2)->FindBin(0.99999*cut[i+1]); 
		SparseITS->GetAxis(2)->SetRange(binmin,binmax); //We define the Pt bin
		TH1D *Projected = SparseITS->Projection(4);
		Projected->SetName(final_name);
		IntegrationITS->SetBinContent(i,Projected->Integral());

		Projected->Write();
	}
	IntegrationITS->Write();

	f->cd();

	//When divinding we overwrite the TH1 so we clone it before because we need to divide it 2 times
	TH1 *IntegrationITSTPC2 = (TH1*)IntegrationITSTPC->Clone("IntegrationITSTPC2");
	TH1 *ratio1 = IntegrationITSTPC;
	ratio1->Divide(ratio1, IntegrationTPC, 1, 1,"b");
	TH1 *ratio2 = IntegrationITSTPC2;
	ratio2->Divide(ratio2, IntegrationITS, 1, 1, "b");
	TH1 *ratio3 = IntegrationITS;
	ratio3->Divide(ratio3, IntegrationTPC, 1, 1, "b");

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