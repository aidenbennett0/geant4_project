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

    Int_t copyNo, fEvent;
    std::string userIn, lineIn;
    Double_t fX, fY, fZ;

    Hits->SetBranchAddress("fEvent", &fEvent);
    Hits->SetBranchAddress("fX", &fX);
    Hits->SetBranchAddress("fY", &fY);
    Hits->SetBranchAddress("copyNo", &copyNo);

    int nEntries = Hits->GetEntries();
    int point = 0;
    int xVals[nEntries], yVals[nEntries];

    // PROMPT 
    while (true) {
        std::cout << "Enter '1' for coordinate map or '2' for copy map ('q' to quit): ";
        std::cin >> userIn;
        // FLUSHES USER INPUT
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (userIn == "q") {
            std::cout << "Quitting...";
            return 0;
        }

        else if (userIn == "1" || userIn == "2") {
            break;
        }

        else {
            std::cout << "Invalid value entered (Enter 1, 2, or q): " << std::endl;
            std::cin >> userIn;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    /*
    // PROMPT FOR LINES
    while (true) {
        std::cout << "Would you like lines (y/n): ";
        std::cin >> lineIn;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (lineIn == "y" || lineIn == "n") {
            break;
        }

        else {
            std::cout << "Invalid value entered (Enter y or n): " << std::endl;
            std::cin >> userIn;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    */

    if (userIn == "1") {    
        for (int i = 0; i < nEntries && point < nEntries; i++) {
            Hits->GetEntry(i);
            xVals[point] = fX;
            yVals[point] = fY;
            
            point++;
        }   
    }

    else if (userIn == "2") {
        for (int i = 0; i < nEntries && point < nEntries; i++) {
    
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

    // SET BOUNDS OF GRAPH
    int nDetX, nDetY;
    double xMin, yMin, xMax, yMax;

    if (userIn == "1") {
        nDetX = 300;
        nDetY = 300;
        xMin = -150; xMax = 150;
        yMin = -150; yMax = 150;
    }

    else if (userIn == "2") {
        nDetX = 100;
        nDetY = 100;
        xMin = 0; xMax = 100;
        yMin = 0; yMax = 100;
    }

    graph->Draw("AP");

    /*
    if (lineIn == "y") {
        // THE SPACE OF EACH DETECTOR
        double step = 1.0;

        // VERTICAL LINES
        for (int i = 0; i < nDetX; i++)
        {
            double x = xMin + i * step;
            TLine *line = new TLine(x, yMin, x, yMax);
            line->SetLineColor(16);
            line->Draw();
        }

        // VERTICAL LINES
        for (int j = 0; j < nDetX; j++)
        {
            double y = yMin + j * step;
            TLine *line = new TLine(xMin, y, xMax, y);
            line->SetLineColor(16);
            line->Draw();
        }
    }
    */

    graph->GetXaxis()->SetLimits(xMin, xMax);
    graph->GetYaxis()->SetRangeUser(yMin, yMax);
    
    theApp.Run();

    delete graph;

    inputFile.Close();
    return 0;
}