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

TString save = Form("AnalysisResultsLargeITS2.root");
TString save2 = Form("AnalysisResultsLargeTPC2.root");
TString save3 = Form("AnalysisResultsLargeITSTPC2.root");
TString file = Form("AnalysisResults7.root"); //You can choose the file here
TString table = Form("probe-third-track"); //You can choose the table here
std::string name = "Projection";
std::string proj_name = "";
TString final_name = Form("");


//void DataPrepare(TString const ML){
void Merger(){
	/*if(ML == "with") {
		file = Form("AnalysisResults_with_ML.root");
		save = Form("prepared_with_ML.root");
	}
	else if(ML == "wt") {
		file = Form("AnalysisResults_wt_ML.root");
		save = Form("prepared_wt_ML.root");
	}
	else {
		file = Form("AnalysisResults.root");
		save = Form("prepared__ML.root");
	}*/




	//We recover the file and the table defined before
	TString Name = Form("hDplusToKPiPiVsPtProbeTag_Tpc");
	TString Name2 = Form("hDplusToKPiPiVsPtProbeTag_Its");
	TString Name3 = Form("hDplusToKPiPiVsPtProbeTag_ItsTpc");
	TFile *myFile = new TFile(file);
	TDirectoryFile *Folder = (TDirectoryFile*)myFile->Get(table);
	THnSparse *SparseITS = (THnSparse*)Folder->Get(Name.Data());
	THnSparse *SparseTPC = (THnSparse*)Folder->Get(Name2.Data());
	THnSparse *SparseITSTPC = (THnSparse*)Folder->Get(Name3.Data());



	/*for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults2.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2ITS = (THnSparse*)Folder2->Get(Name.Data());
		THnSparse *Sparse2TPC = (THnSparse*)Folder2->Get(Name2.Data());
		THnSparse *Sparse2ITSTPC = (THnSparse*)Folder2->Get(Name3.Data());

		LOG(2);

		SparseITS->Add(Sparse2ITS);
		SparseTPC->Add(Sparse2TPC);
		SparseITSTPC->Add(Sparse2ITSTPC);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults3.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2ITS = (THnSparse*)Folder2->Get(Name.Data());
		THnSparse *Sparse2TPC = (THnSparse*)Folder2->Get(Name2.Data());
		THnSparse *Sparse2ITSTPC = (THnSparse*)Folder2->Get(Name3.Data());

		LOG(3);

		SparseITS->Add(Sparse2ITS);
		SparseTPC->Add(Sparse2TPC);
		SparseITSTPC->Add(Sparse2ITSTPC);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults4.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2ITS = (THnSparse*)Folder2->Get(Name.Data());
		THnSparse *Sparse2TPC = (THnSparse*)Folder2->Get(Name2.Data());
		THnSparse *Sparse2ITSTPC = (THnSparse*)Folder2->Get(Name3.Data());

		LOG(4);

		SparseITS->Add(Sparse2ITS);
		SparseTPC->Add(Sparse2TPC);
		SparseITSTPC->Add(Sparse2ITSTPC);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults5.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2ITS = (THnSparse*)Folder2->Get(Name.Data());
		THnSparse *Sparse2TPC = (THnSparse*)Folder2->Get(Name2.Data());
		THnSparse *Sparse2ITSTPC = (THnSparse*)Folder2->Get(Name3.Data());

		LOG(5);

		SparseITS->Add(Sparse2ITS);
		SparseTPC->Add(Sparse2TPC);
		SparseITSTPC->Add(Sparse2ITSTPC);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults6.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2ITS = (THnSparse*)Folder2->Get(Name.Data());
		THnSparse *Sparse2TPC = (THnSparse*)Folder2->Get(Name2.Data());
		THnSparse *Sparse2ITSTPC = (THnSparse*)Folder2->Get(Name3.Data());

		LOG(6);

		SparseITS->Add(Sparse2ITS);
		SparseTPC->Add(Sparse2TPC);
		SparseITSTPC->Add(Sparse2ITSTPC);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults7.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2ITS = (THnSparse*)Folder2->Get(Name.Data());
		THnSparse *Sparse2TPC = (THnSparse*)Folder2->Get(Name2.Data());
		THnSparse *Sparse2ITSTPC = (THnSparse*)Folder2->Get(Name3.Data());

		LOG(7);

		SparseITS->Add(Sparse2ITS);
		SparseTPC->Add(Sparse2TPC);
		SparseITSTPC->Add(Sparse2ITSTPC);
	}*/

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults8.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2ITS = (THnSparse*)Folder2->Get(Name.Data());
		THnSparse *Sparse2TPC = (THnSparse*)Folder2->Get(Name2.Data());
		THnSparse *Sparse2ITSTPC = (THnSparse*)Folder2->Get(Name3.Data());

		LOG(8);

		SparseITS->Add(Sparse2ITS);
		SparseTPC->Add(Sparse2TPC);
		SparseITSTPC->Add(Sparse2ITSTPC);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults9.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2ITS = (THnSparse*)Folder2->Get(Name.Data());
		THnSparse *Sparse2TPC = (THnSparse*)Folder2->Get(Name2.Data());
		THnSparse *Sparse2ITSTPC = (THnSparse*)Folder2->Get(Name3.Data());

		LOG(9);

		SparseITS->Add(Sparse2ITS);
		SparseTPC->Add(Sparse2TPC);
		SparseITSTPC->Add(Sparse2ITSTPC);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults10.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2ITS = (THnSparse*)Folder2->Get(Name.Data());
		THnSparse *Sparse2TPC = (THnSparse*)Folder2->Get(Name2.Data());
		THnSparse *Sparse2ITSTPC = (THnSparse*)Folder2->Get(Name3.Data());

		LOG(10);

		SparseITS->Add(Sparse2ITS);
		SparseTPC->Add(Sparse2TPC);
		SparseITSTPC->Add(Sparse2ITSTPC);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults11.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2ITS = (THnSparse*)Folder2->Get(Name.Data());
		THnSparse *Sparse2TPC = (THnSparse*)Folder2->Get(Name2.Data());
		THnSparse *Sparse2ITSTPC = (THnSparse*)Folder2->Get(Name3.Data());

		LOG(11);

		SparseITS->Add(Sparse2ITS);
		SparseTPC->Add(Sparse2TPC);
		SparseITSTPC->Add(Sparse2ITSTPC);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults12.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2ITS = (THnSparse*)Folder2->Get(Name.Data());
		THnSparse *Sparse2TPC = (THnSparse*)Folder2->Get(Name2.Data());
		THnSparse *Sparse2ITSTPC = (THnSparse*)Folder2->Get(Name3.Data());

		LOG(12);

		SparseITS->Add(Sparse2ITS);
		SparseTPC->Add(Sparse2TPC);
		SparseITSTPC->Add(Sparse2ITSTPC);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults13.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2ITS = (THnSparse*)Folder2->Get(Name.Data());
		THnSparse *Sparse2TPC = (THnSparse*)Folder2->Get(Name2.Data());
		THnSparse *Sparse2ITSTPC = (THnSparse*)Folder2->Get(Name3.Data());

		LOG(13);

		SparseITS->Add(Sparse2ITS);
		SparseTPC->Add(Sparse2TPC);
		SparseITSTPC->Add(Sparse2ITSTPC);
	}

	/*for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults14.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2 = (THnSparse*)Folder2->Get(Name.Data());

		LOG(14);

		Sparse->Add(Sparse2);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults15.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2 = (THnSparse*)Folder2->Get(Name.Data());

		LOG(15);

		Sparse->Add(Sparse2);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults16.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2 = (THnSparse*)Folder2->Get(Name.Data());

		LOG(16);

		Sparse->Add(Sparse2);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults17.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2 = (THnSparse*)Folder2->Get(Name.Data());

		LOG(17);

		Sparse->Add(Sparse2);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults18.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2 = (THnSparse*)Folder2->Get(Name.Data());

		LOG(18);

		Sparse->Add(Sparse2);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults19.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2 = (THnSparse*)Folder2->Get(Name.Data());

		LOG(19);

		Sparse->Add(Sparse2);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults20.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2 = (THnSparse*)Folder2->Get(Name.Data());

		LOG(20);

		Sparse->Add(Sparse2);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults21.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2 = (THnSparse*)Folder2->Get(Name.Data());

		LOG(21);

		Sparse->Add(Sparse2);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults22.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2 = (THnSparse*)Folder2->Get(Name.Data());

		LOG(22);

		Sparse->Add(Sparse2);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults23.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2 = (THnSparse*)Folder2->Get(Name.Data());

		LOG(23);

		Sparse->Add(Sparse2);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults24.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2 = (THnSparse*)Folder2->Get(Name.Data());

		LOG(24);

		Sparse->Add(Sparse2);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults25.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2 = (THnSparse*)Folder2->Get(Name.Data());

		LOG(25);

		Sparse->Add(Sparse2);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults26.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2 = (THnSparse*)Folder2->Get(Name.Data());

		LOG(26);

		Sparse->Add(Sparse2);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults27.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2 = (THnSparse*)Folder2->Get(Name.Data());

		LOG(27);

		Sparse->Add(Sparse2);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults28.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2 = (THnSparse*)Folder2->Get(Name.Data());

		LOG(28);

		Sparse->Add(Sparse2);
	}

	for(int i=0; i<1; i++){
		TFile *myFile2 = new TFile("AnalysisResults29.root");
		TDirectoryFile *Folder2 = (TDirectoryFile*)myFile2->Get(table);
		THnSparse *Sparse2 = (THnSparse*)Folder2->Get(Name.Data());

		LOG(29);

		Sparse->Add(Sparse2);
	}*/

	//remove("Merged.root");

	LOG("Writting");

	for(int i=0; i<1; i++){
		TFile f(save, "new");
		SparseTPC->Write();
	}

	for(int i=0; i<1; i++){
		TFile f2(save2, "new");
		SparseITS->Write();
	}

	for(int i=0; i<1; i++){
		TFile f3(save3, "new");
		SparseITSTPC->Write();
	}
}
