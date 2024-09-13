#Fitter of the Invariant Masses

import numpy as np
import matplotlib.pyplot as plt
import uproot
import ROOT
from ROOT import TFile
from flarefly.data_handler import DataHandler
from flarefly.fitter import F2MassFitter


Type = "LargeRebined" #The name of the input file is define here and with DetectorType so be careful
DetectorType = "ITS" #Here we define what will be used it could be put as an input parameter


name = DetectorType + "Probe/Projection"
cut = [0.500000,1.000000,1.500000,2.000000,2.500000,3.000000,3.500000,4.000000,5.000000,6.000000,7.000000,8.000000,9.000000,10.000000,12.000000,15.000000,20.000000]
cutfor = [0.500000,1.000000,1.500000,2.000000,2.500000,3.000000,3.500000,4.000000,5.000000,6.000000,7.000000,8.000000,9.000000,10.000000,12.000000,15.000000]
#The differents cut cutfor and pycut are use in different part of the code do to comparaison
#What that should be know is that if you want to do the analyse on only a sub part of what you can do, you can modify the cutfor for it to be a sub part of cut
pycut = np.array([0.500000,1.000000,1.500000,2.000000,2.500000,3.000000,3.500000,4.000000,5.000000,6.000000,7.000000,8.000000,9.000000,10.000000,12.000000,15.000000,20.000000])
end_name = ""
Depository = "Final_Fit/Large/Probe/" + DetectorType + "/"

fitting_range = None

sig = ROOT.TH1F("sigma", "test", 16, pycut)
mu = ROOT.TH1F("mu", "test", 16, pycut)
raw = ROOT.TH1F("Raw_Yields", "test", 16, pycut)

File = ROOT.TFile("Projection"+Type+".root")

j=0 #Here we use a j because for the name we will need to see what will be the next item in cutfor and its possible only if we count the forloop


#Something need to be said here, the analysis is really complicated and should be done carefully with each interval
#That is why the code seems like a spaghetti code, for my analysis the different if condition where the best one, but this can change
#So this code should not be used as it but needs to be modify to adjust for a better result for your input
for i in cutfor :
    end_name = str(cut[j])+"00000-"+str(cut[j+1])+"00000"
    end_name_ = str(cut[j])+"-"+str(cut[j+1])
    end_name_ = end_name_.replace(".",",")
    j+=1

    signal_pdfs = ["gaussian"]
    #fitting_range = [1.7,1.975]
    fitting_range = [1.65,2.09]



    #signal_pdfs = ["gaussian"]
    background_pdfs = ["expo"]
    if i <= 1 :
        background_pdfs = ["expopowext"]

    data = DataHandler(data="Projection"+Type+".root", limits = fitting_range, histoname= name+end_name)

    gaussian_id = 0
    expo_id = 0
    fitter = F2MassFitter(data_handler=data, name_signal_pdf=signal_pdfs,name_background_pdf=background_pdfs,name = f"fitter{i}")

    fitter.set_particle_mass(gaussian_id, pdg_id=411)
    fitter.set_signal_initpar(gaussian_id, "frac", 0.1, limits=[0.,0.2])
    fitter.set_signal_initpar(gaussian_id, "sigma", 0.105, limits=[0.,0.150])
    if i >= 4 and (name == "TPCProbe/Projection") :
        fitter.set_signal_initpar(gaussian_id, "sigma", 0.105, limits=[0.,0.150])
    if i == 1.5 :
        fitter.set_signal_initpar(gaussian_id, "sigma", 0.005, limits=[0.,0.050])
    if i <= 1.5 or i == 1 :
        fitter.set_background_initpar(0,"c0",0.1, limits=[-5000.,2000.500])
        fitter.set_background_initpar(0,"c1",0.1, limits=[-5000.,2000.500])
        fitter.set_background_initpar(0,"c2",0.1, limits=[-5000.,2000.500])
        fitter.set_background_initpar(0,"c3",0.1, limits=[-5000.,2000.500])

    #fitter.set_background_initpar(expo_id, "lam", -20.5)

    fitter.mass_zfit()

    plot_mass_fit = fitter.plot_mass_fit(style="ATLAS",axis_title=r"$M_\mathrm{\pi^{\pm}K^{\mp}\pi^{\pm}}$ (GeV/$c^{2})$",show_extra_info=True,extra_info_loc=['upper left', 'center right'])
    plt.savefig(Depository+"Fit_interval-"+end_name_+".pdf")
    plt.savefig(Depository+"Fit_interval-"+end_name_+".png")

    plot_residual = fitter.plot_raw_residuals(style="ATLAS",axis_title=r"$M_\mathrm{\pi^{\pm}K^{\mp}\pi^{\pm}}$ (GeV/$c^{2})$",show_extra_info=True,extra_info_loc=['upper left', 'center right'])
    plt.savefig(Depository+"Residual_interval-"+end_name_+".pdf")
    plt.savefig(Depository+"Residual_interval-"+end_name_+".png")
    muu = fitter.get_signal_parameter(0,"mu")[0]
    sigmaa = fitter.get_signal_parameter(0,"sigma")[0]


    sig.SetBinContent(j+1, fitter.get_signal_parameter(0,"sigma")[0])
    sig.SetBinError(j+1, fitter.get_signal_parameter(0,"sigma")[1])
    mu.SetBinContent(j+1, fitter.get_signal_parameter(0,"mu")[0])
    mu.SetBinError(j+1, fitter.get_signal_parameter(0,"mu")[1])
    raw.SetBinContent(j,fitter.get_signal(idx=0)[0])
    raw.SetBinError(j,fitter.get_signal(idx=0)[1])


with TFile("Sigma_mu_"+Type+DetectorType+".root", "recreate") as outfile:
    outfile.WriteObject(sig, "sigma")
    outfile.WriteObject(mu, "mu")
    outfile.WriteObject(raw, "Raw_Yields")