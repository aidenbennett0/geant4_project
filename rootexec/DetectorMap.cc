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
#include <TLine.h>
#include <TColor.h>

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

    Int_t copyNo;
    Int_t fEvent;

    Hits->SetBranchAddress("fEvent", &fEvent);
    Hits->SetBranchAddress("copyNo", &copyNo);

    int nEntries = Hits->GetEntries();
    int point = 0;
    int xVals[nEntries], yVals[nEntries];

    for (int i = 0; i < nEntries && point < nEntries; i++)
    {
        Hits->GetEntry(i);
        xVals[point] = copyNo % 100;
        yVals[point] = copyNo / 100;
        
        point++;
    }

    int nDecX = 100;
    int nDecY = 100;
    double xMin = 0, xMax = 100;
    double yMin = 0, yMax = 100;

    TGraph* graph = new TGraph(point, xVals, yVals);

    graph->SetMarkerStyle(20);
    graph->SetMarkerColor(kBlack);
    graph->GetXaxis()->SetLimits(0, 100);
    graph->GetYaxis()->SetRangeUser(0,100);

    TCanvas canvas("canvas", "Detector Map", 800, 600);

    canvas.cd();

    graph->Draw("AP");

/*
    // THE SPACE OF EACH DETECTOR
    double step = 1.0;

    // VERTICAL LINES
    for (int i = 0; i < nDecX; i++)
    {
        double x = xMin + i * step;
        TLine *line = new TLine(x, yMin, x, yMax);
        line->SetLineColor(16);
        line->Draw();
    }

    // VERTICAL LINES
    for (int j = 0; j < nDecX; j++)
    {
        double y = yMin + j * step;
        TLine *line = new TLine(xMin, y, xMax, y);
        line->SetLineColor(16);
        line->Draw();
    }
*/

    theApp.Run();

    delete graph;

    inputFile.Close();
    return 0;
}