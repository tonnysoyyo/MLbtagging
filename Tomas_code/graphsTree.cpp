#include <TString.h>
#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TLorentzVector.h"
#include <vector>
#include "iostream"
#include "fstream"
#include "MyClass.C"
using namespace std;

void graphsTree()
{
    // Creamos un objeto TChain para leer los rootfiles
    TChain *ch = new TChain("Delphes", "");
    ch->Add("../rootfiles/run_01.root");
    // ch->Add("../rootfiles/run_02.root");
    // ch->Add("../rootfiles/run_03.root");
    // ch->Add("../rootfiles/run_04.root");

    TTree *Delphes = (TTree*)ch;
    Delphes->MakeClass("MyClass"); // Crea la clase de lectura de la TTree
    MyClass t(Delphes); // Evalúa la clase de lectura de la TTree
    Long64_t nentries = 1000;//t.fChain->GetEntries(); // Obtiene el número de entradas en la TTree 

    // Jets por evento
    TH1F *hJetsPerEvent = new TH1F("hJetsPerEvent", "Numero de Jets por Evento", 100, 0, 6);
    // pT de los jets
    TH1F *hJetPT[4];
    for (int i = 0; i < 4; i++) {
    hJetPT[i] = new TH1F(Form("hJetPT%d", i), Form("pT del Jet %d", i+1), 100, 0, 150); // Ajusta los límites según sea necesario
    
    // Asigna un color único a cada histograma
    if(i == 0) hJetPT[i]->SetLineColor(kRed);
    else if(i == 1) hJetPT[i]->SetLineColor(kBlue);
    else if(i == 2) hJetPT[i]->SetLineColor(kGreen);
    else if(i == 3) hJetPT[i]->SetLineColor(kBlack);
    
    // Opcional: Establece el estilo de línea
    hJetPT[i]->SetLineStyle(i + 1); // Diferentes estilos de línea para cada histograma
    
    // Opcional: Establece el grosor de la línea
    hJetPT[i]->SetLineWidth(2);
}
    // Eta de los jets
    /*TH1F *hJetEta[4];
    for (int i = 0; i < 4; i++) {
        hJetEta[i] = new TH1F(Form("hJetEta%d", i), Form("Eta del Jet %d", i+1), 100, -5, 5); // Ajusta los límites según sea necesario
    
    }
    // Phi de los jets
    TH1F *hJetPhi[4];
    for (int i = 0; i < 4; i++) {
        hJetPhi[i] = new TH1F(Form("hJetPhi%d", i), Form("Phi del Jet %d", i+1), 100, -4, 4); // Ajusta los límites según sea necesario
    }*/

    cout << " Entries : " << nentries << endl;

    Int_t nTen = nentries / 10; // Para imprimir el porcentaje de avance
    Int_t k = 0;
    Int_t nbytes = 0, nb = 0;

    vector<TLorentzVector> jets; // Vector para almacenar los jets
    vector<TLorentzVector> particles; // Vector para almacenar las particles
    for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
        jets.clear();
        particles.clear();

        Long64_t ientry = t.LoadTree(jentry); 
        if (ientry < 0)                        // Para imprimir el porcentaje de avance
            break;
        nb = t.fChain->GetEntry(jentry);
        nbytes += nb;

        if (jentry % nTen == 0)
            cout << 10 * (jentry / nTen) << "%-" << flush;
        if (jentry == nentries - 1)
            cout << "100%"<< endl;

        if (t.Jet_size == 0) continue;

        // Escribe en el archivo CSV de los jets
        for (Int_t i = 0; i < t.Jet_size; i++)
        {
            TLorentzVector jetVector;
            jetVector.SetPtEtaPhiM(t.Jet_PT[i], t.Jet_Eta[i], t.Jet_Phi[i], t.Jet_Mass[i]);
            jets.push_back(jetVector);

        }
        
        // Escribe en el archivo CSV de las partículas
        for (Int_t i = 0; i < t.Particle_size; i++)
        {
            // Filling particles vector
            TLorentzVector particleVector;
            particleVector.SetPtEtaPhiM(t.Particle_PT[i], t.Particle_Eta[i], t.Particle_Phi[i], t.Particle_Mass[i]); // Assuming mass is negligible
            particles.push_back(particleVector);
        }

        vector<vector<Double_t>> deltaRValues(jets.size());
        for (size_t i = 0; i < jets.size(); ++i) {
        //deltaRValues[i].reserve(particles.size()); // Para optimizar la asignación de memoria

        for (size_t j = 0; j < particles.size(); ++j) {
            Double_t deltaR = jets[i].DeltaR(particles[j]);
            if (deltaR < 0.4){
            deltaRValues[i].push_back(deltaR); // Aquí debería ser seguro hacer push_back
        }
        }
    }
        // Histograma de jets por evento
        hJetsPerEvent->Fill(t.Jet_size);

        // Histograma de pT de los jets
        for (int i = 0; i < std::min(4, t.Jet_size); i++) {
        hJetPT[i]->Fill(t.Jet_PT[i]);
        }
        // Histograma de Eta de los jets
        /*for (int i = 0; i < std::min(4, t.Jet_size); i++) {
        hJetEta[i]->Fill(t.Jet_Eta[i]);
        }
        // Histograma de Phi de los jets
        for (int i = 0; i < std::min(4, t.Jet_size); i++) {
        hJetPhi[i]->Fill(t.Jet_Phi[i]);
        }*/

    }

    // Dibuja el histograma
    // Dibujar histograma de jets por evento
    //hJetsPerEvent->Draw();
    // Dibujar histograma de pT de los jets
    TCanvas *c1 = new TCanvas("c1", "pT de los Jets", 600, 400);
    gStyle->SetOptStat(0); // Desactiva la caja de estadísticas para todos los histogramas
    hJetPT[0]->Draw(); // Dibuja el primer histograma
    for (int i = 1; i < 4; i++) {
        hJetPT[i]->Draw("SAME"); // Superpone los siguientes histogramas
    }
    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9); // Ajusta la posición según sea necesario
    legend->SetHeader("Jets", "C"); // Opcional: título de la leyenda
    for (int i = 0; i < 4; i++) {
        legend->AddEntry(hJetPT[i], Form("Jet %d", i+1), "l");
    }
    legend->Draw();

    // Dibujar histograma de Eta de los jets
    /*for (int i = 0; i < 4; i++) {
    hJetEta[i]->Draw("SAME"); // Para superponer, o dibuja individualmente
    }
    // Dibujar histograma de Phi de los jets
    for (int i = 0; i < 4; i++) {
    hJetPhi[i]->Draw("SAME"); // Para superponer, o dibuja individualmente
    }*/
    c1->Print("plots/PTjets.png");  


    cout << "El archivo se escribió correctamente" << endl;

    cout << "Fin del programa" << endl;
}