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

//Initialisation of differents variables

TString save = Form("ProjectionLargeRebined.root");
//TString save2 = Form("ProjectionLargeTagITSTPC.root");
TString fileITSTPC = Form("AnalysisResultsLargeITSTPC1.root"); //You can choose the file here
TString file2ITSTPC = Form("AnalysisResultsLargeITSTPC2.root");
TString fileTPC = Form("AnalysisResultsLargeTPC1.root"); //You can choose the file here
TString file2TPC = Form("AnalysisResultsLargeTPC2.root");
TString fileITS = Form("AnalysisResultsLargeITS1.root"); //You can choose the file here
TString file2ITS = Form("AnalysisResultsLargeITS2.root");
//TString file3 = Form("AnalysisResults3.root");
TString table = Form("probe-third-track"); //You can choose the table here
std::string name = "Projection";
std::string proj_name = "";
TString final_name = Form("");
TString final_name2 = Form("");
TString final_name3 = Form("");


void DataPrepare(){
	//We recover the file and the table defined before
	TFile *myFileITSTPC = new TFile(fileITSTPC);
	TFile *myFile_secondITSTPC = new TFile(file2ITSTPC);

	//Here this can be used if you want to get the information about the same file but want to treat it differently
	//TFile *myFile2ITSTPC = new TFile(fileITSTPC);
	//TFile *myFile2_secondITSTPC = new TFile(file2ITSTPC);

	TFile *myFileTPC = new TFile(fileTPC);
	TFile *myFile_secondTPC = new TFile(file2TPC);
	//TFile *myFile2TPC = new TFile(fileTPC);
	//TFile *myFile2_secondTPC = new TFile(file2TPC);

	TFile *myFileITS = new TFile(fileITS);
	TFile *myFile_secondITS = new TFile(file2ITS);
	//TFile *myFile2ITS = new TFile(fileITS);
	//TFile *myFile2_secondITS = new TFile(file2ITS);

	// We get the histogram and their errors
	TString NameITSTPC = Form("hDplusToKPiPiVsPtProbeTag_ItsTpc");

	THnSparse *SparseITSTPC = (THnSparse*)myFileITSTPC->Get(NameITSTPC.Data());
	THnSparse *Sparse_secondITSTPC = (THnSparse*)myFile_secondITSTPC->Get(NameITSTPC.Data());
	SparseITSTPC->Add(Sparse_secondITSTPC); //The file were to big to be treated alone so we need to extract the Sparse only and add them, this can be very long

	/*TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2ITSTPC->Get(table);
	THnSparse *Sparse2ITSTPC = (THnSparse*)myFile2ITSTPC->Get(NameITSTPC.Data());
	THnSparse *Sparse2_secondITSTPC = (THnSparse*)myFile2_secondITSTPC->Get(NameITSTPC.Data());
	Sparse2ITSTPC->Add(Sparse2_secondITSTPC);*/

	TString NameTPC = Form("hDplusToKPiPiVsPtProbeTag_Tpc");

	THnSparse *SparseTPC = (THnSparse*)myFileTPC->Get(NameTPC.Data());
	THnSparse *Sparse_secondTPC = (THnSparse*)myFile_secondTPC->Get(NameTPC.Data());

	SparseTPC->Add(Sparse_secondTPC);

	/*THnSparse *Sparse2TPC = (THnSparse*)myFile2TPC->Get(NameTPC.Data());
	THnSparse *Sparse2_secondTPC = (THnSparse*)myFile2_secondTPC->Get(NameTPC.Data());
	Sparse2TPC->Add(Sparse2_secondTPC);*/

	TString NameITS = Form("hDplusToKPiPiVsPtProbeTag_Its");

	THnSparse *SparseITS = (THnSparse*)myFileITS->Get(NameITS.Data());
	THnSparse *Sparse_secondITS = (THnSparse*)myFile_secondITS->Get(NameITS.Data());
	SparseITS->Add(Sparse_secondITS);

	/*THnSparse *Sparse2ITS = (THnSparse*)myFile2ITS->Get(NameITS.Data());
	THnSparse *Sparse2_secondITS = (THnSparse*)myFile2_secondITS->Get(NameITS.Data());
	Sparse2ITS->Add(Sparse2_secondITS);*/

	std::string str1 = std::to_string(1); //Is used to name the different part
	std::string str2 = std::to_string(2);

	remove(save); //We erase the last output be carefull to save it if you wanted to keep it

	auto f = new TFile(save, "new");
	TDirectoryFile* ITSProbe = new TDirectoryFile("ITSProbe", "ITSProbe");
	//TDirectoryFile* ITSTag = new TDirectoryFile("ITSTag", "ITSTag");

	TDirectoryFile* TPCProbe = new TDirectoryFile("TPCProbe", "TPCProbe");
	//TDirectoryFile* TPCTag = new TDirectoryFile("TPCTag", "TPCTag");

	TDirectoryFile* ITSTPCProbe = new TDirectoryFile("ITSTPCProbe", "ITSTPCProbe");
	//TDirectoryFile* ITSTPCTag = new TDirectoryFile("ITSTPCTag", "ITSTPCTag");


	double_t cut[17] = {0.5,1,1.5,2,2.5,3,3.5,4,5,6,7,8,9,10,12,15,20};


	ITSTPCProbe->cd();

	for (int i=0; i<16; i++) {
		LOG(i); //Used to see where we are
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

		//We do the projection
		SparseITSTPC->GetAxis(2)->SetRange(binmin,binmax);
		TH2D *Projected2D = SparseITSTPC->Projection(4,0);

		int lastbin1 = Projected2D->GetXaxis()->FindBin(1.00001*2);
		int lastbin2 = Projected2D->GetYaxis()->FindBin(1.00001*20);

		for(int j=0; j<lastbin1; j++){
			for(int k=0; k<lastbin2; k++){
				Projected2D->SetBinContent(j,k,0);
			}
		} //In order to have better result we cut on the particles with a M(D) < 2.

		TH1D *Projected = Projected2D->ProjectionY();
		Projected->SetName(final_name);
		Projected->Rebin(3);
		Projected->Write();
	}



	//It you want to do exactly the same but with the Tag you can used it here
	//remove(save2);
	//TFile fi(save2, "new");

	/*ITSTPCTag->cd();

	for (int i=0; i<11; i++) {

		LOG(i);

		//The name of the differents part of the outfile is define here
		str1 = std::to_string(cut[i]);
		str2 = std::to_string(cut[i+1]);
		proj_name = name + str1;
		proj_name = proj_name + "-";
		proj_name = proj_name + str2;
		final_name2 = "tag"+proj_name;

		int binmin = Sparse2ITSTPC->GetAxis(1)->FindBin(1.00001*cut[i]);
		int binmax = Sparse2ITSTPC->GetAxis(1)->FindBin(0.99999*cut[i+1]);
		Sparse2ITSTPC->GetAxis(1)->SetRange(binmin,binmax);
		TH2D *Projected2D2 = Sparse2ITSTPC->Projection(4,0);
		int lastbin1 = Projected2D2->GetXaxis()->FindBin(1.00001*2);
		int lastbin2 = Projected2D2->GetYaxis()->FindBin(1.00001*20);
		for(int l=0; l<lastbin1; l++){
			for(int m=0; m<lastbin2; m++){
				Projected2D2->SetBinContent(l,m,0);
			}
		}
		TH1D *Projected2 = Projected2D2->ProjectionY();
		Projected2->SetName(final_name2);
		Projected2->Rebin(3);
		Projected2->Write();
	}*/


	TPCProbe->cd();

	for (int i=0; i<16; i++) {
		LOG(i);//Used to see where we are
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

		//We do the projection
		SparseTPC->GetAxis(2)->SetRange(binmin,binmax);
		TH2D *Projected2D = SparseTPC->Projection(4,0);

		int lastbin1 = Projected2D->GetXaxis()->FindBin(1.00001*2);
		int lastbin2 = Projected2D->GetYaxis()->FindBin(1.00001*20);

		for(int j=0; j<lastbin1; j++){
			for(int k=0; k<lastbin2; k++){
				Projected2D->SetBinContent(j,k,0);
			}
		}//In order to have better result we cut on the particles with a M(D) < 2.

		TH1D *Projected = Projected2D->ProjectionY();
		Projected->SetName(final_name);
		Projected->Rebin(3);
		Projected->Write();
	}

	//It you want to do exactly the same but with the Tag you can used it here
	//remove(save2);
	//TFile fi(save2, "new");

	/*TPCTag->cd();

	for (int i=0; i<11; i++) {

		LOG(i);

		//The name of the differents part of the outfile is define here
		str1 = std::to_string(cut[i]);
		str2 = std::to_string(cut[i+1]);
		proj_name = name + str1;
		proj_name = proj_name + "-";
		proj_name = proj_name + str2;
		final_name2 = "tag"+proj_name;

		int binmin = Sparse2TPC->GetAxis(1)->FindBin(1.00001*cut[i]);
		int binmax = Sparse2TPC->GetAxis(1)->FindBin(0.99999*cut[i+1]);
		Sparse2TPC->GetAxis(1)->SetRange(binmin,binmax);
		TH2D *Projected2D2 = Sparse2TPC->Projection(4,0);
		int lastbin1 = Projected2D2->GetXaxis()->FindBin(1.00001*2);
		int lastbin2 = Projected2D2->GetYaxis()->FindBin(1.00001*20);
		LOG(lastbin2);
		for(int l=0; l<lastbin1; l++){
			for(int m=0; m<lastbin2; m++){
				Projected2D2->SetBinContent(l,m,0);
			}
		}
		TH1D *Projected2 = Projected2D2->ProjectionY();
		Projected2->SetName(final_name2);
		Projected2->Rebin(3);
		Projected2->Write();
	}*/

	ITSProbe->cd();

	for (int i=0; i<16; i++) {
		LOG(i);//Used to see where we are
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

		//We do the projection
		SparseITS->GetAxis(2)->SetRange(binmin,binmax);
		TH2D *Projected2D = SparseITS->Projection(4,0);

		int lastbin1 = Projected2D->GetXaxis()->FindBin(1.00001*2);
		int lastbin2 = Projected2D->GetYaxis()->FindBin(1.00001*20);

		for(int j=0; j<lastbin1; j++){
			for(int k=0; k<lastbin2; k++){
				Projected2D->SetBinContent(j,k,0);
			}
		}//In order to have better result we cut on the particles with a M(D) < 2.

		TH1D *Projected = Projected2D->ProjectionY();
		Projected->SetName(final_name);
		Projected->Rebin(3);
		Projected->Write();
	}

	//It you want to do exactly the same but with the Tag you can used it here
	//remove(save2);
	//TFile fi(save2, "new");

	/*ITSTag->cd();

	for (int i=0; i<11; i++) {

		LOG(i);

		//The name of the differents part of the outfile is define here
		str1 = std::to_string(cut[i]);
		str2 = std::to_string(cut[i+1]);
		proj_name = name + str1;
		proj_name = proj_name + "-";
		proj_name = proj_name + str2;
		final_name2 = "tag"+proj_name;

		int binmin = Sparse2ITS->GetAxis(1)->FindBin(1.00001*cut[i]);
		int binmax = Sparse2ITS->GetAxis(1)->FindBin(0.99999*cut[i+1]);
		Sparse2ITS->GetAxis(1)->SetRange(binmin,binmax);
		TH2D *Projected2D2 = Sparse2ITS->Projection(4,0);
		int lastbin1 = Projected2D2->GetXaxis()->FindBin(1.00001*2);
		int lastbin2 = Projected2D2->GetYaxis()->FindBin(1.00001*20);
		LOG(lastbin2);
		for(int l=0; l<lastbin1; l++){
			for(int m=0; m<lastbin2; m++){
				Projected2D2->SetBinContent(l,m,0);
			}
		}
		TH1D *Projected2 = Projected2D2->ProjectionY();
		Projected2->SetName(final_name2);
		Projected2->Rebin(3);
		Projected2->Write();
	}*/
}
