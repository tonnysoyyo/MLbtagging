#include "RooRealVar.h"
#include "RooDataSet.h"
#include <TString.h>
#include "TTree.h"
#include "TFile.h"
#include "iostream"
#include "fstream"
#include "MyClass.C"


void TTreeToCsv()
{
    TChain *ch = new TChain("Delphes", "");
    ch->Add("Events/run_01/tag_1_delphes_events.root/Delphes");
    TTree *Delphes = (TTree*)ch;
    MyClass t(Delphes);
    Long64_t nentries = t.fChain->GetEntries();

    cout << " Entries : " << nentries << endl;

    using namespace RooFit;
    using namespace std;

    // Abre el archivo de salida fuera del bucle
    ofstream salida("output0.1.csv");
    salida << "Jet_Eta" <<" "<< "Jet_Phi"<<" "<< "Particle_Eta"<<" "<< "Particle_Phi" << endl;

    Int_t nTen = nentries / 10;
    Int_t k = 0;
    Int_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
        Long64_t ientry = t.LoadTree(jentry);
        if (ientry < 0)
            break;
        nb = t.fChain->GetEntry(jentry);
        nbytes += nb;
        if (jentry % nTen == 0)
            cout << 10 * (jentry / nTen) << "%-" << flush;
        if (jentry == nentries - 1)
            cout << endl;

        salida << t.Jet_Eta[0] <<" "<< t.Jet_Phi[0]<<" "<< t.Particle_Eta[0] <<" "<< t.Particle_Phi[0] << endl; // Accede al primer elemento del arreglo
    }

    cout << "El archivo se escribió correctamente" << endl;

    // Cierra el archivo CSV
    salida.close();
}
