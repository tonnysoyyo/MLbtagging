#include "RooRealVar.h"
#include "RooDataSet.h"
#include <TString.h>
#include "TTree.h"
#include "TFile.h"
#include "iostream"
#include "fstream"
#include "MyClass.C"
using namespace std;

void TTreeToCsv()
{
    TChain *ch = new TChain("Delphes", "");
    ch->Add("run_04.root");
    TTree *Delphes = (TTree*)ch;
    Delphes->MakeClass("MyClass"); // Crea la clase de lectura de la TTree
    MyClass t(Delphes); // Evalúa la clase de lectura de la TTree
    Long64_t nentries = t.fChain->GetEntries(); // Obtiene el número de entradas en la TTree 

    cout << " Entries : " << nentries << endl;
    
    // Abre el archivo de salida fuera del bucle
    ofstream salida("Leer_de_TTree_a_csv/output0_2.csv");
    salida <<"Evento"<<","<<"Jet.Size"<<","<< "Jet.PT" <<","<< "Jet.Eta"<<","<< "Jet.Phi" << endl;

    Int_t nTen = nentries / 10; // Para imprimir el porcentaje de avance
    Int_t k = 0;
    Int_t nbytes = 0, nb = 0;

    for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
        Long64_t ientry = t.LoadTree(jentry); 
        if (ientry < 0)                        // Para imprimir el porcentaje de avance
            break;
        nb = t.fChain->GetEntry(jentry);
        nbytes += nb;
        if (jentry % nTen == 0)
            cout << 10 * (jentry / nTen) << "%-" << flush;
        if (jentry == nentries - 1)
            cout << "100%"<< endl;

        // Escribe en el archivo CSV
        for (Int_t i = 0; i < t.Jet_size; i++)
        {
            salida <<ientry<<","<< t.Jet_size <<","<< t.Jet_PT[i] <<","<< t.Jet_Eta[i] <<","<< t.Jet_Phi[i] << endl; // Para cada jet escribe en el archivo CSV
        }
    }

    cout << "El archivo se escribió correctamente" << endl;

    // Cierra el archivo CSV
    salida.close();
    // Cierra el root file
    delete ch;
    cout << "Fin del programa" << endl;
}
