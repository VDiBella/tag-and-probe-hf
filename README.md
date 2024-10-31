# tag-and-probe-hf
Repository for tag &amp; probe studies with signals
I have decided to separate the code in several differents files.
I prefer it that way because a full run can be long, so now we can do it part by part without taking to much testing time.
The idea is that each code will take in input the last code and create an output.

There is files for MC data and file for real data.

There is no input file to put in the command line, so each code is launch with :
root name_of_code.C
Except of course for the Fitter one who is launch with :
python3 Fitter_Inv_Mass.py

The input file are decide at the begining of the codes.

The order to use it is :

For real data : DataPrepare.C -> Fitter_Inv_Mass.py -> Ratio.C
For Monte Carlo : CarloTruth.C -> Truth_Ratio.C

In last is the ImageCreator.C that will use the output of the Monte Carlo and the real Data.

It is important to see that the in the Fitter, the different parameter can and should be different if you study other data.
It is really tricky to do good fit so there is a lot of if function and its not sufficient, some try must be done before its finish.

If you want information about the training of the BDT there is a ReadMe in the BDT Folder.

If your file is not merge you can use the merge folde, even if the code is not optimize at all.
