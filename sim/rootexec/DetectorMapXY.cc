#include <TFile.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TDirectory.h>
#include <TMath.h>
#include <TLatex.h>
#include <iostream>
#include <sstream>
#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TH2D.h>
#include <string.h>
#include <stdlib.h>
#include <TString.h>
#include <ctype.h>

int main(int argc, char** argv)
{
    TApplication theApp("App", &argc, argv);

    TFile inputFile("/home/acb1145/geant4_project/sim/build/output.root");
    if (!inputFile.IsOpen())
    {
        std::cerr << "ERROR: Could not open input file!" << std::endl;
        return 1;
    }
    
    TTree *Hits = nullptr;
    inputFile.GetObject("Hits", Hits);
    if (!Hits)
    {
        std::cerr << "ERROR: Could not retrieve tree!" << std::endl;
        return 1;
    }

    Int_t copyNo, userIn;
    Double_t fEvent, fX, fY, fZ;
    Hits->SetBranchAddress("fEvent", &fEvent);
    Hits->SetBranchAddress("fX", &fX);
    Hits->SetBranchAddress("fY", &fY);
    Hits->SetBranchAddress("copyNo", &copyNo);

    int nEntries = Hits->GetEntries();
    int point = 0;
    int xVals[nEntries], yVals[nEntries];


    std::cout << "Enter '1' for coordinate map or '2' for copy map: ";
    std::cin >> userIn;

    if (userIn != 1 && userIn != 2)
    {
        std::cout << "Invalid Value";
        std::cin >> userIn;
    }
    else if (userIn == 1)
    {
        for (int i = 0; i < nEntries && point < nEntries; i++)
        {
            Hits->GetEntry(i);
            xVals[point] = fX;
            yVals[point] = fY;
            
            point++;
        }    
    }

    else if (userIn == 2)
    {
        for (int i = 0; i < nEntries && point < nEntries; i++)
        {
            Hits->GetEntry(i);
            xVals[point] = copyNo % 100;
            yVals[point] = copyNo / 100;
            
            point++;
        }
    }
    
    TGraph* graph = new TGraph(point, xVals, yVals);

    graph->SetMarkerStyle(20);
    graph->SetMarkerColor(kBlack);

    TCanvas canvas("canvas", "Detector Map", 800, 600);

    canvas.cd();

    graph->Draw("AP");

    theApp.Run();

    delete graph;

    inputFile.Close();
    return 0;
}