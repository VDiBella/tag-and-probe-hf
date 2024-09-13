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

TString savefinalITSTPCTPC = Form("Last_Result/AITSTPCoverTPC.png");
TString savefinalITSTPCITS = Form("Last_Result/AITSTPCoverITS.png");
TString savefinalITSTPC = Form("Last_Result/AITSoverTPC.png");
//TString save2 = Form("ProjectionLargeTagITSTPC.root");
TString fileData = Form("End_Ratio.root"); //You can choose the file here
TString fileMC = Form("ProjectionMCa.root"); //You can choose the file here
//TString file3 = Form("AnalysisResults3.root");
TString table = Form("probe-third-track"); //You can choose the table here
std::string name = "Ratio";
std::string proj_name = "";
TString final_name = Form("");
TString final_name2 = Form("");
TString final_name3 = Form("");


//We define the pad
void myPadSetUp(TPad *currentPad, float currentLeft=0.11, float currentTop=0.04, float currentRight=0.04, float currentBottom=0.15){
  currentPad->SetLeftMargin(currentLeft);
  currentPad->SetTopMargin(currentTop);
  currentPad->SetRightMargin(currentRight);
  currentPad->SetBottomMargin(currentBottom);
  return;
}

//We define the style
void myOptions(){
  // Set gStyle
  int font = 42;
  gStyle->SetDrawBorder(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetTextFont(font);
  gStyle->SetStatFont(font);
  gStyle->SetStatFontSize(0.05);
  gStyle->SetStatX(0.97);
  gStyle->SetStatY(0.98);
  gStyle->SetStatH(0.03);
  gStyle->SetStatW(0.3);
  gStyle->SetTickLength(0.02,"y");
  gStyle->SetEndErrorSize(10);
  gStyle->SetLabelSize(0.05,"xyz");
  gStyle->SetLabelFont(font,"xyz"); 
  gStyle->SetLabelOffset(0.01,"xyz");
  gStyle->SetTitleFont(font);  
  gStyle->SetTitleOffset(1.0,"xyz");  
  gStyle->SetTitleSize(0.06,"xyz");  
  gStyle->SetMarkerSize(1);
  gStyle->SetPalette(1,0); 
  if (0){
    gStyle->SetOptTitle(1);
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(1111);
    }
  else {
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
  }
}

void ImageCreator(){


	TCanvas *c1 = new TCanvas("c1","c1");

	TPad *myPad1 = new TPad("myPad1","myPad1",0,0.4,1,1);
	myPadSetUp(myPad1,0.13,0.04,0.04,0.00);
	TPad *myPad2 = new TPad("myPad2","myPad2",0,0,1,0.4);
	myPadSetUp(myPad2,0.13,0.00,0.04,0.3);
	myPad1->Draw();
	myPad2->Draw(); //We define the differents pad to have the two graphics on one image

	TFile *myFileData = new TFile(fileData);
	TFile *myFileMC = new TFile(fileMC);

	TString Name1 = Form("ITSTPCoverTPC");
	TString Name2 = Form("ITSTPCoverITS");
	TString Name3 = Form("ITSoverTPC");

	TH1D *Yield1Data = (TH1D*)myFileData->Get(Name1.Data());
	TH1D *Yield1MC = (TH1D*)myFileMC->Get(Name1.Data());
	TH1D *Yield2Data = (TH1D*)myFileData->Get(Name2.Data()); //We will rewrite over it while divinding so we need to define a new TH1
	TH1D *Yield2MC = (TH1D*)myFileMC->Get(Name2.Data());
	TH1D *Yield3Data = (TH1D*)myFileData->Get(Name3.Data());
	TH1D *Yield3MC = (TH1D*)myFileMC->Get(Name3.Data());

	Yield1Data->SetLineColor(4);
	Yield2Data->SetLineColor(4);
	Yield3Data->SetLineColor(4);
	Yield1MC->SetLineColor(2);
	Yield2MC->SetLineColor(2);
	Yield3MC->SetLineColor(2);

	//We define the legend
	TLegend *tleg = new TLegend(0.65,0.8,0.15,0.87);
	tleg->AddEntry(Yield1Data,"ALICE Data","l");
	tleg->AddEntry((TObject*)nullptr, "", ""); //We put a empty legend to make space between legends
	tleg->AddEntry(Yield1MC,"MonteCarlo Data","l");
	tleg->SetTextSize(0.03);
	tleg->SetBorderSize(0);
	tleg->Draw();

	//We go on the first Pad
	myPad1->cd();
  	myPad1->SetTicks(1,1);

	//We redefine the range to have a more visible result
	Yield1Data->GetYaxis()->SetRangeUser(0.8,1.2);
	Yield1Data->GetXaxis()->SetRangeUser(0,15);
	Yield1Data->SetStats(kFALSE);
	Yield1Data->Draw();
	Yield1MC->Draw("same");
	tleg->Draw();

	//We do the division of the two
	TH1D *fratio = (TH1D*)myFileMC->Get(Name1.Data());
	fratio->Divide(Yield1Data,Yield1MC);
	fratio->GetYaxis()->SetRangeUser(0.8,1.1);

	//We go on the second pad
	myPad2->cd();
	myPad2->SetTicks(1,1);

	fratio->SetTitle("MonteCarlo/Data");
	fratio->SetYTitle("");
	fratio->SetLineColor(32);
	fratio->SetStats(kFALSE);
	fratio->GetXaxis()->SetRangeUser(0,15);
	fratio->Fit("pol0"); //We do the mean line
	fratio->Draw();

	c1->SaveAs(savefinalITSTPCTPC);

	myPad1->cd();
  	myPad1->SetTicks(1,1);

	//We redefine the range to have a more visible result
	Yield2Data->GetYaxis()->SetRangeUser(0.8,1.2);
	Yield2Data->GetXaxis()->SetRangeUser(0,15);
	Yield2Data->SetStats(kFALSE);
	Yield2Data->Draw();
	Yield2MC->Draw("same");
	tleg->Draw();

	//We do the division of the two
	TH1D *fratio2 = (TH1D*)myFileMC->Get(Name2.Data());
	fratio2->Divide(Yield2Data,Yield2MC);
	fratio2->GetYaxis()->SetRangeUser(0.8,1.1);

	//We go on the second pad
	myPad2->cd();
	myPad2->SetTicks(1,1);

	fratio2->SetTitle("MonteCarlo/Data");
	fratio2->SetYTitle("");
	fratio2->SetLineColor(32);
	fratio2->SetStats(kFALSE);
	fratio2->GetXaxis()->SetRangeUser(0,15);
	fratio2->Fit("pol0"); //We do the mean line
	fratio2->Draw();

	c1->SaveAs(savefinalITSTPCITS);

	myPad1->cd();
  	myPad1->SetTicks(1,1);

	//We redefine the range to have a more visible result
	Yield3Data->GetYaxis()->SetRangeUser(0.8,1.2);
	Yield3Data->GetXaxis()->SetRangeUser(0,15);
	Yield3Data->SetStats(kFALSE);
	Yield3Data->Draw();
	Yield3MC->Draw("same");
	tleg->Draw();

	TH1D *fratio3 = (TH1D*)myFileMC->Get(Name3.Data());
	fratio3->Divide(Yield3Data,Yield3MC);
	fratio3->GetYaxis()->SetRangeUser(0.8,1.1);

	//We go on the second pad
	myPad2->cd();
	myPad2->SetTicks(1,1);


	fratio3->SetTitle("Data/MonteCarlo");
	fratio3->SetYTitle("");
	fratio3->SetLineColor(32);
	fratio3->SetStats(kFALSE);
	fratio3->GetXaxis()->SetRangeUser(0,15);
	fratio3->Fit("pol0"); //We do the mean line
	fratio3->Draw();

	c1->SaveAs(savefinalITSTPC);


}