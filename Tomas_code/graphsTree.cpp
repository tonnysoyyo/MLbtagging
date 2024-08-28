#include <TString.h>
#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TLorentzVector.h"
#include <vector>
#include "iostream"
#include "fstream"
#include "/home/juan27/MLbtagging/Tomas_code/MyClass.C"
using namespace std;

void graphsTree()
{
    // Creamos un objeto TChain para leer los rootfiles
    TChain *ch = new TChain("Delphes", "");
    ch->Add("tag_1_delphes_events.root");
    // ch->Add("../rootfiles/run_02.root");
    // ch->Add("../rootfiles/run_03.root");
    // ch->Add("../rootfiles/run_04.root");

    TTree *Delphes = (TTree*)ch;
    Delphes->MakeClass("MyClass"); // Crea la clase de lectura de la TTree
    MyClass t(Delphes); // Evalúa la clase de lectura de la TTree
    Long64_t nentries = 10000;//t.fChain->GetEntries(); // Obtiene el número de entradas en la TTree 

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
    TH1F *hJetEta[4];
    for (int i = 0; i < 4; i++) {
        hJetEta[i] = new TH1F(Form("hJetEta%d", i), Form("Eta del Jet %d", i+1), 100, -5, 5); // Ajusta los límites según sea necesario
    
    // Asigna un color único a cada histograma
    if(i == 0) hJetEta[i]->SetLineColor(kRed);
    else if(i == 1) hJetEta[i]->SetLineColor(kBlue);
    else if(i == 2) hJetEta[i]->SetLineColor(kGreen);
    else if(i == 3) hJetEta[i]->SetLineColor(kBlack);
    
    // Opcional: Establece el estilo de línea
    hJetEta[i]->SetLineStyle(i + 1); // Diferentes estilos de línea para cada histograma
    
    // Opcional: Establece el grosor de la línea
    hJetEta[i]->SetLineWidth(2);
    }

    // Phi de los jets
    TH1F *hJetPhi[4];
    for (int i = 0; i < 4; i++) {
        hJetPhi[i] = new TH1F(Form("hJetPhi%d", i), Form("Phi del Jet %d", i+1), 100, -4, 4); // Ajusta los límites según sea necesario
        // Asigna un color único a cada histograma
    if(i == 0) hJetPhi[i]->SetLineColor(kRed);
    else if(i == 1) hJetPhi[i]->SetLineColor(kBlue);
    else if(i == 2) hJetPhi[i]->SetLineColor(kGreen);
    else if(i == 3) hJetPhi[i]->SetLineColor(kBlack);
    
    // Opcional: Establece el estilo de línea
    hJetPhi[i]->SetLineStyle(i + 1); // Diferentes estilos de línea para cada histograma
    
    // Opcional: Establece el grosor de la línea
    hJetPhi[i]->SetLineWidth(2);
    }

    // Número de partículas cargadas por jet
    TH1F *hChargedParticles[4];
    for (int i = 0; i < 4; i++) {
        hChargedParticles[i] = new TH1F(Form("hChargedParticles%d", i), Form("Numero de Partículas Cargadas del Jet %d", i+1), 100, -0.5, 3.5);
    // Asigna un color único a cada histograma
    if(i == 0) hChargedParticles[i]->SetLineColor(kRed);
    else if(i == 1) hChargedParticles[i]->SetLineColor(kBlue);
    else if(i == 2) hChargedParticles[i]->SetLineColor(kGreen);
    else if(i == 3) hChargedParticles[i]->SetLineColor(kBlack);
    
    hChargedParticles[i]->SetLineStyle(i + 1); // Diferentes estilos de línea para cada histograma
    hChargedParticles[i]->SetLineWidth(2);
    }

    // Número de neutras cargadas por jet
    TH1F *hNeutralsParticles[4];
    for (int i = 0; i < 4; i++) {
        hNeutralsParticles[i] = new TH1F(Form("hNeutralsParticles%d", i), Form("Numero de Partículas Cargadas del Jet %d", i+1), 100, -0.5, 3.5);
    // Asigna un color único a cada histograma
    if(i == 0) hNeutralsParticles[i]->SetLineColor(kRed);
    else if(i == 1) hNeutralsParticles[i]->SetLineColor(kBlue);
    else if(i == 2) hNeutralsParticles[i]->SetLineColor(kGreen);
    else if(i == 3) hNeutralsParticles[i]->SetLineColor(kBlack);
    
    hNeutralsParticles[i]->SetLineStyle(i + 1); // Diferentes estilos de línea para cada histograma
    hNeutralsParticles[i]->SetLineWidth(2);
    }

    // Histograma de fracción de pT cargado del jet
    TH1F *hChargedPTFraction[4];
    for (int i = 0; i < 4; i++) {
    hChargedPTFraction[i] = new TH1F(Form("hChargedPTFraction%d", i), Form("Fracción de pT cargado del Jet %d", i+1), 100, 0, 1);
    
    // Asigna un color único a cada histograma
    if(i == 0) hChargedPTFraction[i]->SetLineColor(kRed);
    else if(i == 1) hChargedPTFraction[i]->SetLineColor(kBlue);
    else if(i == 2) hChargedPTFraction[i]->SetLineColor(kGreen);
    else if(i == 3) hChargedPTFraction[i]->SetLineColor(kBlack);
    
    hChargedPTFraction[i]->SetLineStyle(i + 1); // Different line styles for each histogram
    hChargedPTFraction[i]->SetLineWidth(2);
    }

    // Histograma de fracción de pT neutro del jet
    TH1F *hNeutralPTFraction[4];
    for (int i = 0; i < 4; i++) {
    hNeutralPTFraction[i] = new TH1F(Form("hNeutralPTFraction%d", i), Form("Fracción de pT neutro del Jet %d", i+1), 100, 0, 1);
    
    // Asigna un color único a cada histograma
    if(i == 0) hNeutralPTFraction[i]->SetLineColor(kRed);
    else if(i == 1) hNeutralPTFraction[i]->SetLineColor(kBlue);
    else if(i == 2) hNeutralPTFraction[i]->SetLineColor(kGreen);
    else if(i == 3) hNeutralPTFraction[i]->SetLineColor(kBlack);
    
    hNeutralPTFraction[i]->SetLineStyle(i + 1); // Different line styles for each histogram
    hNeutralPTFraction[i]->SetLineWidth(2);
    }

    // Histograma del pT promedio de las partículas de cada jet
    TH1F *hAveragePT[4];
    for (int i = 0; i < 4; i++) {
    hAveragePT[i] = new TH1F(Form("hAveragePT%d", i), Form("pT promedio de las partículas del Jet %d", i+1), 100, 0, 150);
    
    // Asigna un color único a cada histograma
    if(i == 0) hAveragePT[i]->SetLineColor(kRed);
    else if(i == 1) hAveragePT[i]->SetLineColor(kBlue);
    else if(i == 2) hAveragePT[i]->SetLineColor(kGreen);
    else if(i == 3) hAveragePT[i]->SetLineColor(kBlack);
    
    hAveragePT[i]->SetLineStyle(i + 1); // Different line styles for each histogram
    hAveragePT[i]->SetLineWidth(2);
    }

    // Histograma del número de partículas pertenecientes a un jet con pT por debajo del pT promedio por cada jet
    TH1F *hParticlesBelowAvgPT[4];
    for (int i = 0; i < 4; i++) {
    hParticlesBelowAvgPT[i] = new TH1F(Form("hParticlesBelowAvgPT%d", i), Form("Número de partículas con pT < pT promedio del Jet %d", i+1), 100, 0, 50);
    
    // Asigna un color único a cada histograma
    if(i == 0) hParticlesBelowAvgPT[i]->SetLineColor(kRed);
    else if(i == 1) hParticlesBelowAvgPT[i]->SetLineColor(kBlue);
    else if(i == 2) hParticlesBelowAvgPT[i]->SetLineColor(kGreen);
    else if(i == 3) hParticlesBelowAvgPT[i]->SetLineColor(kBlack);
    
    hParticlesBelowAvgPT[i]->SetLineStyle(i + 1); // Different line styles for each histogram
    hParticlesBelowAvgPT[i]->SetLineWidth(2);
    }

    // Histograma del número de partículas pertenecientes a un jet con pT por encima del pT promedio por cada jet
    TH1F *hParticlesAboveAvgPT[4];
    for (int i = 0; i < 4; i++) {
    hParticlesAboveAvgPT[i] = new TH1F(Form("hParticlesAboveAvgPT%d", i), Form("Número de partículas con pT > pT promedio del Jet %d", i+1), 100, 0, 50);
        
    // Asigna un color único a cada histograma
    if(i == 0) hParticlesAboveAvgPT[i]->SetLineColor(kRed);
    else if(i == 1) hParticlesAboveAvgPT[i]->SetLineColor(kBlue);
    else if(i == 2) hParticlesAboveAvgPT[i]->SetLineColor(kGreen);
    else if(i == 3) hParticlesAboveAvgPT[i]->SetLineColor(kBlack);
    
    hParticlesAboveAvgPT[i]->SetLineStyle(i + 1); // Different line styles for each histogram
    hParticlesAboveAvgPT[i]->SetLineWidth(2);
    }

    // Histograma de pT(par_max_pT) / pT(j_r).
    TH1F *hMaxPTRatio[4];
    for (int i = 0; i < 4; i++) {
    hMaxPTRatio[i] = new TH1F(Form("hMaxPTRatio%d", i), Form("pT(par_max_pT) / pT(j_r) del Jet %d", i+1), 100, 0, 1.5);
    
    // Asigna un color único a cada histograma
    if(i == 0) hMaxPTRatio[i]->SetLineColor(kRed);
    else if(i == 1) hMaxPTRatio[i]->SetLineColor(kBlue);
    else if(i == 2) hMaxPTRatio[i]->SetLineColor(kGreen);
    else if(i == 3) hMaxPTRatio[i]->SetLineColor(kBlack);
    
    hMaxPTRatio[i]->SetLineStyle(i + 1); // Different line styles for each histogram
    hMaxPTRatio[i]->SetLineWidth(2);
    }

    // Histograma de pT(par_min_pT) / pT(j_r).
    TH1F *hMinPTRatio[4];
    for (int i = 0; i < 4; i++) {
    hMinPTRatio[i] = new TH1F(Form("hMinPTRatio%d", i), Form("pT(par_min_pT) / pT(j_r) del Jet %d", i+1), 100, 0, 0.2);
    
    // Asigna un color único a cada histograma
    if(i == 0) hMinPTRatio[i]->SetLineColor(kRed);
    else if(i == 1) hMinPTRatio[i]->SetLineColor(kBlue);
    else if(i == 2) hMinPTRatio[i]->SetLineColor(kGreen);
    else if(i == 3) hMinPTRatio[i]->SetLineColor(kBlack);
    
    hMinPTRatio[i]->SetLineStyle(i + 1); // Different line styles for each histogram
    hMinPTRatio[i]->SetLineWidth(2);
    }

    // Histograma de pT(par_max_DR) / pT(j_r)
    TH1F *hMaxDRRatio[4];
    for (int i = 0; i < 4; i++) {
    hMaxDRRatio[i] = new TH1F(Form("hMaxDRRatio%d", i), Form("pT(par_max_DR) / pT(j_r) del Jet %d", i+1), 100, 0, 1.5);
    
    // Asigna un color único a cada histograma
    if(i == 0) hMaxDRRatio[i]->SetLineColor(kRed);
    else if(i == 1) hMaxDRRatio[i]->SetLineColor(kBlue);
    else if(i == 2) hMaxDRRatio[i]->SetLineColor(kGreen);
    else if(i == 3) hMaxDRRatio[i]->SetLineColor(kBlack);
    
    hMaxDRRatio[i]->SetLineStyle(i + 1); // Different line styles for each histogram
    hMaxDRRatio[i]->SetLineWidth(2);
    }

    // Histogram de pT(par_min_DR) / pT(j_r)
    TH1F *hMinDRRatio[4];
    for (int i = 0; i < 4; i++) {
    hMinDRRatio[i] = new TH1F(Form("hMinDRRatio%d", i), Form("pT(par_min_DR) / pT(j_r) del Jet %d", i+1), 100, 0, 1.5);
    
    // Asigna un color único a cada histograma
    if(i == 0) hMinDRRatio[i]->SetLineColor(kRed);
    else if(i == 1) hMinDRRatio[i]->SetLineColor(kBlue);
    else if(i == 2) hMinDRRatio[i]->SetLineColor(kGreen);
    else if(i == 3) hMinDRRatio[i]->SetLineColor(kBlack);
    
    hMinDRRatio[i]->SetLineStyle(i + 1); // Different line styles for each histogram
    hMinDRRatio[i]->SetLineWidth(2);
    }

    // Histograma de DeltaR(par_max_pT, j_r)
    TH1F *hDeltaRMaxPT[4];
    for (int i = 0; i < 4; i++) {
    hDeltaRMaxPT[i] = new TH1F(Form("hDeltaRMaxPT%d", i), Form("DeltaR(par_max_pT, j_r) del Jet %d", i+1), 100, 0, 0.5);
    
    // Asigna un color único a cada histograma
    if(i == 0) hDeltaRMaxPT[i]->SetLineColor(kRed);
    else if(i == 1) hDeltaRMaxPT[i]->SetLineColor(kBlue);
    else if(i == 2) hDeltaRMaxPT[i]->SetLineColor(kGreen);
    else if(i == 3) hDeltaRMaxPT[i]->SetLineColor(kBlack);
    
    hDeltaRMaxPT[i]->SetLineStyle(i + 1); // Different line styles for each histogram
    hDeltaRMaxPT[i]->SetLineWidth(2);
    }

    // Histograma de DeltaR(par_min_pT, j_r)
    TH1F *hDeltaRMinPT[4];
    for (int i = 0; i < 4; i++) {
    hDeltaRMinPT[i] = new TH1F(Form("hDeltaRMinPT%d", i), Form("DeltaR(par_min_pT, j_r) del Jet %d", i+1), 100, 0, 0.5);
    
    // Asigna un color único a cada histograma
    if(i == 0) hDeltaRMinPT[i]->SetLineColor(kRed);
    else if(i == 1) hDeltaRMinPT[i]->SetLineColor(kBlue);
    else if(i == 2) hDeltaRMinPT[i]->SetLineColor(kGreen);
    else if(i == 3) hDeltaRMinPT[i]->SetLineColor(kBlack);
    
    hDeltaRMinPT[i]->SetLineStyle(i + 1); // Different line styles for each histogram
    hDeltaRMinPT[i]->SetLineWidth(2);
    }

    // Histograma de DeltaR(par_max_DR, j_r)
    TH1F *hDeltaRMaxDR[4];
    for (int i = 0; i < 4; i++) {
    hDeltaRMaxDR[i] = new TH1F(Form("hDeltaRMaxDR%d", i), Form("DeltaR(par_max_DR, j_r) del Jet %d", i+1), 100, 0, 0.5);
    
    // Asigna un color único a cada histograma
    if(i == 0) hDeltaRMaxDR[i]->SetLineColor(kRed);
    else if(i == 1) hDeltaRMaxDR[i]->SetLineColor(kBlue);
    else if(i == 2) hDeltaRMaxDR[i]->SetLineColor(kGreen);
    else if(i == 3) hDeltaRMaxDR[i]->SetLineColor(kBlack);
    
    hDeltaRMaxDR[i]->SetLineStyle(i + 1); // Different line styles for each histogram
    hDeltaRMaxDR[i]->SetLineWidth(2);
    }

    // Histograma de DeltaR(par_min_DR, j_r)
    TH1F *hDeltaRMinDR[4];
    for (int i = 0; i < 4; i++) {
    hDeltaRMinDR[i] = new TH1F(Form("hDeltaRMinDR%d", i), Form("DeltaR(par_min_DR, j_r) del Jet %d", i+1), 100, 0, 0.5);
    
    // Asigna un color único a cada histograma
    if(i == 0) hDeltaRMinDR[i]->SetLineColor(kRed);
    else if(i == 1) hDeltaRMinDR[i]->SetLineColor(kBlue);
    else if(i == 2) hDeltaRMinDR[i]->SetLineColor(kGreen);
    else if(i == 3) hDeltaRMinDR[i]->SetLineColor(kBlack);
    
    hDeltaRMinDR[i]->SetLineStyle(i + 1); // Different line styles for each histogram
    hDeltaRMinDR[i]->SetLineWidth(2);
    }

    // Histogram de pT(par_max_pT) - pT(par_min_pT)
    TH1F *hPTDifference[4];
    for (int i = 0; i < 4; i++) {
    hPTDifference[i] = new TH1F(Form("hPTDifference%d", i), Form("pT(par_max_pT) - pT(par_min_pT) del Jet %d", i+1), 100, 0, 150);
    
    // Assign a unique color to each histogram
    if(i == 0) hPTDifference[i]->SetLineColor(kRed);
    else if(i == 1) hPTDifference[i]->SetLineColor(kBlue);
    else if(i == 2) hPTDifference[i]->SetLineColor(kGreen);
    else if(i == 3) hPTDifference[i]->SetLineColor(kBlack);
    
    hPTDifference[i]->SetLineStyle(i + 1); // Different line styles for each histogram
    hPTDifference[i]->SetLineWidth(2);
    }

    // Histogram for R containing 50% of the total pT from the jet center for each jet
    TH1F *hR50PercentPT[4];
    for (int i = 0; i < 4; i++) {
    hR50PercentPT[i] = new TH1F(Form("hR50PercentPT%d", i), Form("R para 50%% pT total del Jet %d", i+1), 100, 0, 0.4);
    
    // Assign a unique color to each histogram
    if(i == 0) hR50PercentPT[i]->SetLineColor(kRed);
    else if(i == 1) hR50PercentPT[i]->SetLineColor(kBlue);
    else if(i == 2) hR50PercentPT[i]->SetLineColor(kGreen);
    else if(i == 3) hR50PercentPT[i]->SetLineColor(kBlack);
    
    hR50PercentPT[i]->SetLineStyle(i + 1); // Different line styles for each histogram
    hR50PercentPT[i]->SetLineWidth(2);
    }


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
        for (int i = 0; i < std::min(4, t.Jet_size); i++) {
        hJetEta[i]->Fill(t.Jet_Eta[i]);
        }

        // Histograma de Phi de los jets
        for (int i = 0; i < std::min(4, t.Jet_size); i++) {
        hJetPhi[i]->Fill(t.Jet_Phi[i]);
        }

        // Histograma de Número de partículas cargadas por jet
        for (int i = 0; i < std::min(4, t.Jet_size); i++) {
        hChargedParticles[i]->Fill(t.Jet_NCharged[i]);
        }

        // Histograma de Número de partículas neutras por jet
        for (int i = 0; i < std::min(4, t.Jet_size); i++) {
        hNeutralsParticles[i]->Fill(t.Jet_NNeutrals[i]);
        }

        // Fracción de pT cargado del jet
        for (Int_t i = 0; i < std::min(4, t.Jet_size); i++) {
        TLorentzVector jetVector;
        jetVector.SetPtEtaPhiM(t.Jet_PT[i], t.Jet_Eta[i], t.Jet_Phi[i], t.Jet_Mass[i]);

        TLorentzVector chargedPTSum(0, 0, 0, 0); // Initialize to zero
        
        TLorentzVector neutralPTSum(0, 0, 0, 0); // Initialize to zero
        
        Double_t sumPT = 0.0;
        Int_t countParticles = 0;

        TLorentzVector maxPTParticle(0, 0, 0, 0); // Initialize to zero
        
        TLorentzVector minPTParticle(1e9, 0, 0, 0); // Initialize with a very large pT

        TLorentzVector maxDRParticle(0, 0, 0, 0); // Initialize to zero
        Double_t maxDR = -1; // Initialize to a negative value to ensure proper comparison

        TLorentzVector minDRParticle(0, 0, 0, 0); // Initialize to zero
        Double_t minDR = 1e9; // Initialize to a very large value to ensure proper comparison


        // Loop over particles to sum charged ones
        for (Int_t j = 0; j < t.Particle_size; j++) {
            TLorentzVector particleVector;

            if (t.Particle_Charge[j] != 0) { // Check if particle is charged
                particleVector.SetPtEtaPhiM(t.Particle_PT[j], t.Particle_Eta[j], t.Particle_Phi[j], t.Particle_Mass[j]);
                chargedPTSum += particleVector; // Vector sum
            }
            
            if (t.Particle_Charge[j] == 0) { // Check if particle is neutral
                particleVector.SetPtEtaPhiM(t.Particle_PT[j], t.Particle_Eta[j], t.Particle_Phi[j], t.Particle_Mass[j]);
                neutralPTSum += particleVector; // Vector sum
            }

            particleVector.SetPtEtaPhiM(t.Particle_PT[j], t.Particle_Eta[j], t.Particle_Phi[j], t.Particle_Mass[j]);

            if (jetVector.DeltaR(particleVector) < 0.4) { // Check if the particle is within the jet
                sumPT += particleVector.Pt();
                countParticles++;

            if (particleVector.Pt() > maxPTParticle.Pt()) {
                    maxPTParticle = particleVector; // Update to the particle with the maximum pT
                }
            
            if (particleVector.Pt() < minPTParticle.Pt()) {
                    minPTParticle = particleVector; // Update to the particle with the minimum pT
                }

            if (jetVector.DeltaR(particleVector) > maxDR) { // Check if the particle is within the jet and has a larger DeltaR
                maxDR = jetVector.DeltaR(particleVector);
                maxDRParticle = particleVector; // Update to the particle with the maximum DeltaR
            }

            if (jetVector.DeltaR(particleVector) < minDR) { // Check if the particle is within the jet and has a smaller DeltaR
                minDR = jetVector.DeltaR(particleVector);
                minDRParticle = particleVector; // Update to the particle with the minimum DeltaR
            }
            }
        }

        // Calculate fraction of charged pT
        Double_t chargedPTFraction = chargedPTSum.Pt() / jetVector.Pt();
        Double_t neutralPTFraction = neutralPTSum.Pt() / jetVector.Pt();
        Double_t averagePT = (countParticles > 0) ? (sumPT / countParticles) : 0;

        Double_t maxPTRatio = (jetVector.Pt() > 0) ? (maxPTParticle.Pt() / jetVector.Pt()) : 0;
        Double_t minPTRatio = (jetVector.Pt() > 0) ? (minPTParticle.Pt() / jetVector.Pt()) : 0;
        Double_t maxDRRatio = (jetVector.Pt() > 0) ? (maxDRParticle.Pt() / jetVector.Pt()) : 0;
        Double_t minDRRatio = (jetVector.Pt() > 0) ? (minDRParticle.Pt() / jetVector.Pt()) : 0;

        Double_t deltaRMaxPT = jetVector.DeltaR(maxPTParticle);
        Double_t deltaRMinPT = jetVector.DeltaR(minPTParticle);
        Double_t deltaRMaxDR = jetVector.DeltaR(maxDRParticle);
        Double_t deltaRMinDR = jetVector.DeltaR(minDRParticle);

        Double_t ptDifference = maxPTParticle.Pt() - minPTParticle.Pt();

        // Count particles with pT below the average pT
        Int_t particlesBelowAvgPT = 0;
        // Count particles with pT above the average pT
        Int_t particlesAboveAvgPT = 0;
        for (Int_t j = 0; j < t.Particle_size; j++) {
            TLorentzVector particleVector;
            particleVector.SetPtEtaPhiM(t.Particle_PT[j], t.Particle_Eta[j], t.Particle_Phi[j], t.Particle_Mass[j]);

            if (jetVector.DeltaR(particleVector) < 0.4 && particleVector.Pt() < averagePT) {
                particlesBelowAvgPT++;
            }
            if (jetVector.DeltaR(particleVector) < 0.4 && particleVector.Pt() > averagePT) {
                particlesAboveAvgPT++;
            }
        }

        // Fill the histogram for the current jet
        if (i < 4) {
        hChargedPTFraction[i]->Fill(chargedPTFraction);
        hNeutralPTFraction[i]->Fill(neutralPTFraction);
        hAveragePT[i]->Fill(averagePT);

        hParticlesBelowAvgPT[i]->Fill(particlesBelowAvgPT);
        hParticlesAboveAvgPT[i]->Fill(particlesAboveAvgPT);

        hMaxPTRatio[i]->Fill(maxPTRatio);
        hMinPTRatio[i]->Fill(minPTRatio);
        hMaxDRRatio[i]->Fill(maxDRRatio);
        hMinDRRatio[i]->Fill(minDRRatio);

        hDeltaRMaxPT[i]->Fill(deltaRMaxPT);
        hDeltaRMinPT[i]->Fill(deltaRMinPT);
        hDeltaRMaxDR[i]->Fill(deltaRMaxDR);
        hDeltaRMinDR[i]->Fill(deltaRMinDR);

        hPTDifference[i]->Fill(ptDifference);
        }
        }
    }

    // Dibuja el histograma
    // Dibujar histograma de jets por evento
    TCanvas *cJets = new TCanvas("cJets", "Jets por evento", 600, 400);
    hJetsPerEvent->Draw();

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

    TCanvas *cEta = new TCanvas("cEta", "Eta de los Jets", 600, 400);
    gStyle->SetOptStat(0); // Desactiva la caja de estadísticas para todos los histogramas
    hJetEta[0]->Draw(); // Dibuja el primer histograma
    for (int i = 1; i < 4; i++) {
        hJetEta[i]->Draw("SAME"); // Superpone los siguientes histogramas
    }
    TLegend *legendEta = new TLegend(0.7, 0.7, 0.9, 0.9); // Ajusta la posición según sea necesario
    legendEta->SetHeader("Jets", "C"); // Opcional: título de la leyenda
    for (int i = 0; i < 4; i++) {
        legendEta->AddEntry(hJetEta[i], Form("Jet %d", i+1), "l");
    }
    legendEta->Draw();

    TCanvas *cPhi = new TCanvas("cPhi", "Phi de los Jets", 600, 400);
    gStyle->SetOptStat(0); // Desactiva la caja de estadísticas para todos los histogramas
    hJetPhi[0]->Draw(); // Dibuja el primer histograma
    for (int i = 1; i < 4; i++) {
        hJetPhi[i]->Draw("SAME"); // Superpone los siguientes histogramas
    }
    TLegend *legendPhi = new TLegend(0.7, 0.7, 0.9, 0.9); // Ajusta la posición según sea necesario
    legendPhi->SetHeader("Jets", "C"); // Opcional: título de la leyenda
    for (int i = 0; i < 4; i++) {
        legendPhi->AddEntry(hJetPhi[i], Form("Jet %d", i+1), "l");
    }
    legendPhi->Draw();

    TCanvas *cNCharged = new TCanvas("cNCharged", "Numero de partículas cargadas por jet", 600, 400);
    gStyle->SetOptStat(0); // Desactiva la caja de estadísticas para todos los histogramas
    hChargedParticles[0]->Draw(); // Dibuja el primer histograma
    for (int i = 1; i < 4; i++) {
        hChargedParticles[i]->Draw("SAME"); // Superpone los siguientes histogramas
    }
    TLegend *legendNCharged = new TLegend(0.7, 0.7, 0.9, 0.9); // Ajusta la posición según sea necesario
    legendNCharged->SetHeader("Jets", "C"); // Opcional: título de la leyenda
    for (int i = 0; i < 4; i++) {
        legendNCharged->AddEntry(hChargedParticles[i], Form("Jet %d", i+1), "l");
    }
    legendNCharged->Draw();

    TCanvas *cNNeutrals = new TCanvas("cNNeutrals", "Numero de partículas neutras por jet", 600, 400);
    gStyle->SetOptStat(0); // Desactiva la caja de estadísticas para todos los histogramas
    hNeutralsParticles[0]->Draw(); // Dibuja el primer histograma
    for (int i = 1; i < 4; i++) {
        hNeutralsParticles[i]->Draw("SAME"); // Superpone los siguientes histogramas
    }
    TLegend *legendNNeutrals = new TLegend(0.7, 0.7, 0.9, 0.9); // Ajusta la posición según sea necesario
    legendNNeutrals->SetHeader("Jets", "C"); // Opcional: título de la leyenda
    for (int i = 0; i < 4; i++) {
        legendNNeutrals->AddEntry(hNeutralsParticles[i], Form("Jet %d", i+1), "l");
    }
    legendNNeutrals->Draw();

    TCanvas *cChargedPTFraction = new TCanvas("cChargedPTFraction", "Fracción de pT cargado del Jet", 600, 400);
    gStyle->SetOptStat(0); // Disable the statistics box for all histograms
    hChargedPTFraction[0]->Draw(); // Draw the first histogram
    for (int i = 1; i < 4; i++) {
        hChargedPTFraction[i]->Draw("SAME"); // Overlay the other histograms
    }
    TLegend *legendChargedPTFraction = new TLegend(0.7, 0.7, 0.9, 0.9); // Adjust the position as necessary
    legendChargedPTFraction->SetHeader("Jets", "C"); // Optional: legend title
    for (int i = 0; i < 4; i++) {
        legendChargedPTFraction->AddEntry(hChargedPTFraction[i], Form("Jet %d", i+1), "l");
    }
    legendChargedPTFraction->Draw();

    TCanvas *cNeutralPTFraction = new TCanvas("cNeutralPTFraction", "Fracción de pT neutro del Jet", 600, 400);
    gStyle->SetOptStat(0); // Disable the statistics box for all histograms
    hNeutralPTFraction[0]->Draw(); // Draw the first histogram
    for (int i = 1; i < 4; i++) {
        hNeutralPTFraction[i]->Draw("SAME"); // Overlay the other histograms
    }
    TLegend *legendNeutralPTFraction = new TLegend(0.7, 0.7, 0.9, 0.9); // Adjust the position as necessary
    legendNeutralPTFraction->SetHeader("Jets", "C"); // Optional: legend title
    for (int i = 0; i < 4; i++) {
        legendNeutralPTFraction->AddEntry(hNeutralPTFraction[i], Form("Jet %d", i+1), "l");
    }
    legendNeutralPTFraction->Draw();

    TCanvas *cAveragePT = new TCanvas("cAveragePT", "pT promedio de las partículas del Jet", 600, 400);
    gStyle->SetOptStat(0); // Disable the statistics box for all histograms
    hAveragePT[0]->Draw(); // Draw the first histogram
    for (int i = 1; i < 4; i++) {
        hAveragePT[i]->Draw("SAME"); // Overlay the other histograms
    }
    TLegend *legendAveragePT = new TLegend(0.7, 0.7, 0.9, 0.9); // Adjust the position as necessary
    legendAveragePT->SetHeader("Jets", "C"); // Optional: legend title
    for (int i = 0; i < 4; i++) {
        legendAveragePT->AddEntry(hAveragePT[i], Form("Jet %d", i+1), "l");
    }
    legendAveragePT->Draw();

    TCanvas *cParticlesBelowAvgPT = new TCanvas("cParticlesBelowAvgPT", "Número de partículas con pT < pT promedio del Jet", 600, 400);
    gStyle->SetOptStat(0); // Disable the statistics box for all histograms
    hParticlesBelowAvgPT[0]->Draw(); // Draw the first histogram
    for (int i = 1; i < 4; i++) {
        hParticlesBelowAvgPT[i]->Draw("SAME"); // Overlay the other histograms
    }
    TLegend *legendParticlesBelowAvgPT = new TLegend(0.7, 0.7, 0.9, 0.9); // Adjust the position as necessary
    legendParticlesBelowAvgPT->SetHeader("Jets", "C"); // Optional: legend title
    for (int i = 0; i < 4; i++) {
        legendParticlesBelowAvgPT->AddEntry(hParticlesBelowAvgPT[i], Form("Jet %d", i+1), "l");
    }
    legendParticlesBelowAvgPT->Draw();

    TCanvas *cParticlesAboveAvgPT = new TCanvas("cParticlesAboveAvgPT", "Número de partículas con pT > pT promedio del Jet", 600, 400);
    gStyle->SetOptStat(0); // Disable the statistics box for all histograms
    hParticlesAboveAvgPT[0]->Draw(); // Draw the first histogram
    for (int i = 1; i < 4; i++) {
        hParticlesAboveAvgPT[i]->Draw("SAME"); // Overlay the other histograms
    }
    TLegend *legendParticlesAboveAvgPT = new TLegend(0.7, 0.7, 0.9, 0.9); // Adjust the position as necessary
    legendParticlesAboveAvgPT->SetHeader("Jets", "C"); // Optional: legend title
    for (int i = 0; i < 4; i++) {
        legendParticlesAboveAvgPT->AddEntry(hParticlesAboveAvgPT[i], Form("Jet %d", i+1), "l");
    }
    legendParticlesAboveAvgPT->Draw();

    TCanvas *cMaxPTRatio = new TCanvas("cMaxPTRatio", "pT(par_max_pT) / pT(j_r) del Jet", 600, 400);
    gStyle->SetOptStat(0); // Disable the statistics box for all histograms
    hMaxPTRatio[0]->Draw(); // Draw the first histogram
    for (int i = 1; i < 4; i++) {
        hMaxPTRatio[i]->Draw("SAME"); // Overlay the other histograms
    }
    TLegend *legendMaxPTRatio = new TLegend(0.7, 0.7, 0.9, 0.9); // Adjust the position as necessary
    legendMaxPTRatio->SetHeader("Jets", "C"); // Optional: legend title
    for (int i = 0; i < 4; i++) {
        legendMaxPTRatio->AddEntry(hMaxPTRatio[i], Form("Jet %d", i+1), "l");
    }
    legendMaxPTRatio->Draw();

    TCanvas *cMinPTRatio = new TCanvas("cMinPTRatio", "pT(par_min_pT) / pT(j_r) del Jet", 600, 400);
    gStyle->SetOptStat(0); // Disable the statistics box for all histograms
    hMinPTRatio[0]->Draw(); // Draw the first histogram
    for (int i = 1; i < 4; i++) {
        hMinPTRatio[i]->Draw("SAME"); // Overlay the other histograms
    }
    TLegend *legendMinPTRatio = new TLegend(0.7, 0.7, 0.9, 0.9); // Adjust the position as necessary
    legendMinPTRatio->SetHeader("Jets", "C"); // Optional: legend title
    for (int i = 0; i < 4; i++) {
        legendMinPTRatio->AddEntry(hMinPTRatio[i], Form("Jet %d", i+1), "l");
    }
    legendMinPTRatio->Draw();

    TCanvas *cMaxDRRatio = new TCanvas("cMaxDRRatio", "pT(par_max_DR) / pT(j_r) del Jet", 600, 400);
    gStyle->SetOptStat(0); // Disable the statistics box for all histograms
    hMaxDRRatio[0]->Draw(); // Draw the first histogram
    for (int i = 1; i < 4; i++) {
        hMaxDRRatio[i]->Draw("SAME"); // Overlay the other histograms
    }
    TLegend *legendMaxDRRatio = new TLegend(0.7, 0.7, 0.9, 0.9); // Adjust the position as necessary
    legendMaxDRRatio->SetHeader("Jets", "C"); // Optional: legend title
    for (int i = 0; i < 4; i++) {
        legendMaxDRRatio->AddEntry(hMaxDRRatio[i], Form("Jet %d", i+1), "l");
    }
    legendMaxDRRatio->Draw();

    TCanvas *cMinDRRatio = new TCanvas("cMinDRRatio", "pT(par_min_DR) / pT(j_r) del Jet", 600, 400);
    gStyle->SetOptStat(0); // Disable the statistics box for all histograms
    hMinDRRatio[0]->Draw(); // Draw the first histogram
    for (int i = 1; i < 4; i++) {
        hMinDRRatio[i]->Draw("SAME"); // Overlay the other histograms
    }
    TLegend *legendMinDRRatio = new TLegend(0.7, 0.7, 0.9, 0.9); // Adjust the position as necessary
    legendMinDRRatio->SetHeader("Jets", "C"); // Optional: legend title
    for (int i = 0; i < 4; i++) {
        legendMinDRRatio->AddEntry(hMinDRRatio[i], Form("Jet %d", i+1), "l");
    }
    legendMinDRRatio->Draw();

    TCanvas *cDeltaRMaxPT = new TCanvas("cDeltaRMaxPT", "DeltaR(par_max_pT, j_r) del Jet", 600, 400);
    gStyle->SetOptStat(0); // Disable the statistics box for all histograms
    hDeltaRMaxPT[0]->Draw(); // Draw the first histogram
    for (int i = 1; i < 4; i++) {
        hDeltaRMaxPT[i]->Draw("SAME"); // Overlay the other histograms
    }
    TLegend *legendDeltaRMaxPT = new TLegend(0.7, 0.7, 0.9, 0.9); // Adjust the position as necessary
    legendDeltaRMaxPT->SetHeader("Jets", "C"); // Optional: legend title
    for (int i = 0; i < 4; i++) {
        legendDeltaRMaxPT->AddEntry(hDeltaRMaxPT[i], Form("Jet %d", i+1), "l");
    }
    legendDeltaRMaxPT->Draw();

    TCanvas *cDeltaRMinPT = new TCanvas("cDeltaRMinPT", "DeltaR(par_min_pT, j_r) del Jet", 600, 400);
    gStyle->SetOptStat(0); // Disable the statistics box for all histograms
    hDeltaRMinPT[0]->Draw(); // Draw the first histogram
    for (int i = 1; i < 4; i++) {
        hDeltaRMinPT[i]->Draw("SAME"); // Overlay the other histograms
    }
    TLegend *legendDeltaRMinPT = new TLegend(0.7, 0.7, 0.9, 0.9); // Adjust the position as necessary
    legendDeltaRMinPT->SetHeader("Jets", "C"); // Optional: legend title
    for (int i = 0; i < 4; i++) {
        legendDeltaRMinPT->AddEntry(hDeltaRMinPT[i], Form("Jet %d", i+1), "l");
    }
    legendDeltaRMinPT->Draw();

    TCanvas *cDeltaRMaxDR = new TCanvas("cDeltaRMaxDR", "DeltaR(par_max_DR, j_r) del Jet", 600, 400);
    gStyle->SetOptStat(0); // Disable the statistics box for all histograms
    hDeltaRMaxDR[0]->Draw(); // Draw the first histogram
    for (int i = 1; i < 4; i++) {
        hDeltaRMaxDR[i]->Draw("SAME"); // Overlay the other histograms
    }
    TLegend *legendDeltaRMaxDR = new TLegend(0.7, 0.7, 0.9, 0.9); // Adjust the position as necessary
    legendDeltaRMaxDR->SetHeader("Jets", "C"); // Optional: legend title
    for (int i = 0; i < 4; i++) {
        legendDeltaRMaxDR->AddEntry(hDeltaRMaxDR[i], Form("Jet %d", i+1), "l");
    }
    legendDeltaRMaxDR->Draw();

    TCanvas *cDeltaRMinDR = new TCanvas("cDeltaRMinDR", "DeltaR(par_min_DR, j_r) del Jet", 600, 400);
    gStyle->SetOptStat(0); // Disable the statistics box for all histograms
    hDeltaRMinDR[0]->Draw(); // Draw the first histogram
    for (int i = 1; i < 4; i++) {
        hDeltaRMinDR[i]->Draw("SAME"); // Overlay the other histograms
    }
    TLegend *legendDeltaRMinDR = new TLegend(0.7, 0.7, 0.9, 0.9); // Adjust the position as necessary
    legendDeltaRMinDR->SetHeader("Jets", "C"); // Optional: legend title
    for (int i = 0; i < 4; i++) {
        legendDeltaRMinDR->AddEntry(hDeltaRMinDR[i], Form("Jet %d", i+1), "l");
    }
    legendDeltaRMinDR->Draw();

    TCanvas *cPTDifference = new TCanvas("cPTDifference", "pT(par_max_pT) - pT(par_min_pT) del Jet", 600, 400);
    gStyle->SetOptStat(0); // Disable the statistics box for all histograms
    hPTDifference[0]->Draw(); // Draw the first histogram
    for (int i = 1; i < 4; i++) {
        hPTDifference[i]->Draw("SAME"); // Overlay the other histograms
    }
    TLegend *legendPTDifference = new TLegend(0.7, 0.7, 0.9, 0.9); // Adjust the position as necessary
    legendPTDifference->SetHeader("Jets", "C"); // Optional: legend title
    for (int i = 0; i < 4; i++) {
        legendPTDifference->AddEntry(hPTDifference[i], Form("Jet %d", i+1), "l");
    }
    legendPTDifference->Draw();

    // Guardar los histogramas en un archivo
    cJets->Print("plots/JetsPerEvent.png");
    c1->Print("plots/PTjets.png");
    cEta->Print("plots/Etajets.png");
    cPhi->Print("plots/Phijets.png");
    cNCharged->Print("plots/NCharged.png");
    cNNeutrals->Print("plots/NNeutrals.png");
    cChargedPTFraction->Print("plots/ChargedPTFraction.png");
    cNeutralPTFraction->Print("plots/NeutralPTFraction.png");
    cAveragePT->Print("plots/AveragePT.png");
    cParticlesBelowAvgPT->Print("plots/ParticlesBelowAvgPT.png");
    cParticlesAboveAvgPT->Print("plots/ParticlesAboveAvgPT.png");
    cMaxPTRatio->Print("plots/MaxPTRatio.png");
    cMinPTRatio->Print("plots/MinPTRatio.png");
    cMaxDRRatio->Print("plots/MaxDRRatio.png");
    cMinDRRatio->Print("plots/MinDRRatio.png");
    cDeltaRMaxPT->Print("plots/DeltaRMaxPT.png");
    cDeltaRMinPT->Print("plots/DeltaRMinPT.png");
    cDeltaRMaxDR->Print("plots/DeltaRMaxDR.png");
    cDeltaRMinDR->Print("plots/DeltaRMinDR.png");
    cPTDifference->Print("plots/PTDifference.png");

    cout << "El archivo se escribió correctamente" << endl;

    cout << "Fin del programa" << endl;
}
