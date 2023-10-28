#include "TLeaf.h"
#include "TBuffer.h"
#include "TBranch.h"
#include "TTree.h"
#include "TVirtualPad.h"
#include "TBrowser.h"
#include "TClass.h"
#include <TString.h>
#include "TTree.h"
#include "TFile.h"
#include "iostream"
#include "fstream"
#include "MyClass.C"
#include "TClonesArray.h"



void TTreeToCsv_copy()
{
    TChain *ch = new TChain("Delphes", "");
    ch->Add("Events/run_01/tag_1_delphes_events.root/Delphes");
    TTree *Delphes = (TTree*)ch;
    MyClass t(Delphes);
    TLeaf *hoja = t.fChain->GetLeaf("Jet.Eta");//esto si funciona
    Int_t nentries = 50000;
    
    cout << " Entries : " << nentries << endl;

    using namespace std;

    // Abre el archivo de salida fuera del bucle
    ofstream salida("output0.1.csv");
    salida << "Jet_Eta" <<" "<< "Jet_Phi"<<" "<< "Particle_Eta" <<" "<< "Particle_Phi"<< endl;

    Int_t lefn = 25;
    
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

        // Imprimir todos los elementos de los arrays Jet_Eta y Jet_Phi
        for (Int_t i = 0; i < lefn; ++i) {
            salida << t.Jet_Eta[i]<<" "<< t.Jet_Phi[i]<<" "<< t.Particle_Eta[i]<<" "<< t.Particle_Phi[i]<< endl;
        }
    }
}
