#ifndef KoPFA_TopAnalyzer_Histograms_H
#define KoPFA_TopAnalyzer_Histograms_H

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include <TH1F.h>
#include <vector>

struct Histograms
{
  Histograms(TFileDirectory* dir)
  {
    hNEvents = dir->make<TH1F>("hNEvents", "Number of events", 2, 0, 2);

    // Generator level info
    hgenttbarM = dir->make<TH1F>("hgenttbarM", "Generator level ttbar mass;Generator level ttbar mass (GeV/^{2};Events/1GeV", 5000, 0, 5000);

    // Per event variables
    hnpileup = dir->make<TH1F>("hnpileup", "Number of pileup;Number of pileup;Events", 50, 0, 50);
    hnvertex = dir->make<TH1F>("hnvertex", "Number of vertex;Number of vertex;Events", 50, 0, 50);
    hNLepton1 = dir->make<TH1F>("hNLepton1", "Number of lepton1;Number of leptons;Events", 10, 0, 10);
    hNLepton2 = dir->make<TH1F>("hNLepton2", "Number of lepton2;Number of leptons;Events", 10, 0, 10);
    hNJet = dir->make<TH1F>("hNJet", "Number of jets;Number of jets;Events", 10, 0, 10);

    // Lepton variables
    hpt1 = dir->make<TH1F>("hpt1", "Leading  lepton p_{T};p_{T} (GeV/c);Events/1 GeV/c", 100, 0, 100);
    hpt2 = dir->make<TH1F>("hpt2", "Trailing lepton p_{T};p_{T} (GeV/c);Events/1 GeV/c", 100, 0, 100);
    heta1 = dir->make<TH1F>("heta1", "Leading  lepton #eta;#eta;Events/0.2", 35, -3.5, 3.5);
    heta2 = dir->make<TH1F>("heta2", "Trailing lepton #eta;#eta;Events/0.2", 35, -3.5, 3.5);
    hrelIso1 = dir->make<TH1F>("hrelIso1", "Leading  lepton Relative isolation;Relative isolation;Events/0.01", 100, 0, 1);
    hrelIso2 = dir->make<TH1F>("hrelIso2", "Trailing lepton Relative isolation;Relative isolation;Events/0.01", 100, 0, 1);

    // Jet variables
    hjet1pt = dir->make<TH1F>("hjet1pt", "Leading  jet p_{T};p_{T} (GeV/c);Events/1 GeV/c", 500, 0, 500);
    hjet2pt = dir->make<TH1F>("hjet2pt", "Trailing jet p_{T};p_{T} (GeV/c);Events/1 GeV/c", 500, 0, 500);
    hjet3pt = dir->make<TH1F>("hjet3pt", "Tertiary jet p_{T};p_{T} (GeV/c);Events/1 GeV/c", 500, 0, 500);
    hjet4pt = dir->make<TH1F>("hjet4pt", "Fourth   jet p_{T};p_{T} (GeV/c);Events/1 GeV/c", 500, 0, 500);

    hjet1eta = dir->make<TH1F>("hjet1eta", "Leading  jet #eta;#eta;Events/0.2", 35, -3.5, 3.5);
    hjet2eta = dir->make<TH1F>("hjet2eta", "Trailing jet #eta;#eta;Events/0.2", 35, -3.5, 3.5);
    hjet3eta = dir->make<TH1F>("hjet3eta", "Tertiary jet #eta;#eta;Events/0.2", 35, -3.5, 3.5);
    hjet4eta = dir->make<TH1F>("hjet4eta", "Fourth   jet #eta;#eta;Events/0.2", 35, -3.5, 3.5);

    hjet1phi = dir->make<TH1F>("hjet1phi", "Leading  jet #phi;#phi (Radian);Events/0.2 Radian", 35, -3.5, 3.5);
    hjet2phi = dir->make<TH1F>("hjet2phi", "Trailing jet #phi;#phi (Radian);Events/0.2 Radian", 35, -3.5, 3.5);
    hjet3phi = dir->make<TH1F>("hjet3phi", "Tertiary jet #phi;#phi (Radian);Events/0.2 Radian", 35, -3.5, 3.5);
    hjet4phi = dir->make<TH1F>("hjet4phi", "Fourth   jet #phi;#phi (Radian);Events/0.2 Radian", 35, -3.5, 3.5);

    // B tagging variables
    hBDiscriminatorCSVJet3 = dir->make<TH1F>("hBDiscriminatorCSVJet3","hBDiscriminatorCSVJet3; b-Discriminator (CSV); Events/0.05" ,20, 0, 1);
    hBDiscriminatorCSVJet4 = dir->make<TH1F>("hBDiscriminatorCSVJet4","hBDiscriminatorCSVJet4; b-Discriminator (CSV); Events/0.05" ,20, 0, 1);   

    // MET/SumET variables
    hMET = dir->make<TH1F>("hMET", "Missing E_{T};Transverse missing momentum (GeV/c);Events/1 GeV/c", 200, 0, 200);
    hMETPhi = dir->make<TH1F>("hMETPhi", "Azimuthal angle of Missing E_{T};Azimuthal angle #phi;Events/0.2 rad", 35, -3.5, 3.5);
    hSumET = dir->make<TH1F>("hSumET",  "#Sigma E_{T};#Sigma E_{T} (GeV);Events/1 GeV", 1000, 0, 1000);
    hChET = dir->make<TH1F>("hChET", "#Sigma E_{T};Charged Hadron #Sigma E_{T} (GeV);Events/1 GeV", 200, 0, 200);
    hNhET = dir->make<TH1F>("hNhET", "#Sigma E_{T};Neutral Hadron #Sigma E_{T} (GeV);Events/1 GeV", 200, 0, 200);
    hPhET = dir->make<TH1F>("hPhET", "#Sigma E_{T};Photon #Sigma E_{T} (GeV);Events/1 GeV", 200, 0, 200);
    hHT = dir->make<TH1F>("hHT", "HT; H_{T} (GeV/c);Events/1 GeV", 1000, 0, 1000);

    // Composite object variables
    hZMass = dir->make<TH1F>("hZMass", "Dilepton mass;Dilepton Mass (GeV/c^{2})", 250, 0, 250);
    hDphiMETLepton1 = dir->make<TH1F>("hDphiMETLepton1", "Azimuthal angle between leading  lepton - MET;#Delta#Phi between leading  lepton and MET;Events/0.1 rad", 40, 0, 4);
    hDphiMETLepton2 = dir->make<TH1F>("hDphiMETLepton2", "Azimuthal angle between trailing lepton - MET;#Delta#Phi between trailing lepton and MET;Events/0.1 rad", 40, 0, 4);
    hDphiMETJet1 = dir->make<TH1F>("hDphiMETJet1", "Azimuthal angle between leading  jet - MET;#Delta#Phi between leading  jet and MET;Events/0.1 rad", 40, 0, 4);
    hDphiMETJet2 = dir->make<TH1F>("hDphiMETJet2", "Azimuthal angle between trailing jet - MET;#Delta#Phi between trailing jet and MET;Events/0.1 rad", 40, 0, 4);

    // Top mass
    hvsumM = dir->make<TH1F>("hvsumM", "ttbar invariant mass;t#bar{t} invariant mass (GeV/c^{2});Events/1 GeV", 5000, 0, 5000);
    hmaosM = dir->make<TH1F>("hmaosM", "ttbar invariant mass;t#bar{t} invariant mass (GeV/c^{2});Events/1 GeV", 5000, 0, 5000);
    htopMass1 = dir->make<TH1F>("htopMass1", "blv mass;blv mass (GeV/c^{2});Events/1 GeV", 300, 0, 300);
    htopMass2 = dir->make<TH1F>("htopMass2", "blv mass;blv mass (GeV/c^{2});Events/1 GeV", 300, 0, 300);

    // Top mass by JPsi
    hNLepton3 = dir->make<TH1F>("hNLepton3", "Number of lepton3;Number of leptons;Events", 10, 0, 10);
    hNLepton4 = dir->make<TH1F>("hNLepton4", "Number of lepton4;Number of leptons;Events", 10, 0, 10);
    hNJPsi = dir->make<TH1F>("hNJPsi", "Number of JPsis;Number of JPsis;Events", 10, 0, 10);
    hNLepJPsi1 = dir->make<TH1F>("hNLepJPsi1", "Number of LepJPsi1;Number of LepJPsi1;Events", 10, 0, 10);
    hNLepJPsi2 = dir->make<TH1F>("hNLepJPsi2", "Number of LepJPsi2;Number of LepJPsi2;Events", 10, 0, 10);
    hpt3 = dir->make<TH1F>("hpt3", "Leading J/Psi lepton p_{T};p_{T} (GeV/c);Events/1 GeV/c", 100, 0, 100);
    heta3 = dir->make<TH1F>("heta3", "Second leading J/Psi lepton #eta;#eta;Events/0.2", 35, -3.5, 3.5);
    hpt4 = dir->make<TH1F>("hpt4", "Leading J/Psi lepton p_{T};p_{T} (GeV/c);Events/1 GeV/c", 100, 0, 100);
    heta4 = dir->make<TH1F>("heta4", "Second leading J/Psi lepton #eta;#eta;Events/0.2", 35, -3.5, 3.5);
    hJPsiMass = dir->make<TH1F>("hJPsiMass", "Dilepton mass;Dilepton Mass (GeV/c^{2});Events/0.1", 100, 0, 10);
    hLepJPsiMass1 = dir->make<TH1F>("hLepJPsiMass1", "lepton+JPsi mass 1;Dilepton Mass (GeV/c^{2});Events", 150, 0, 150);
    hLepJPsiMass2 = dir->make<TH1F>("hLepJPsiMass2", "lepton+JPsi mass 2;Dilepton Mass (GeV/c^{2});Events", 150, 0, 150);
    hgenRecobJPsiDR = dir->make<TH1F>("hgenRecobJPsiDR", "#Delta R for BtoJPsi MC Truth;#Delta R;Events/0.1", 100, 0, 10);
    hgenbJPsiLepId = dir->make<TH1F>("hgenbJPsiLepId", "gen B->JPsi lepton ID;ID;#Events",20,0,20);

  }

  typedef TH1F* H;

  H hNEvents;

  H hgenttbarM;

  H hnpileup, hnvertex;
  H hNLepton1, hNLepton2, hNJet;

  H hpt1, heta1, hrelIso1;
  H hpt2, heta2, hrelIso2;

  H hjet1pt, hjet1eta, hjet1phi;
  H hjet2pt, hjet2eta, hjet2phi;
  H hjet3pt, hjet3eta, hjet3phi;
  H hjet4pt, hjet4eta, hjet4phi;

  std::vector<H> hnBJets;
  H hBDiscriminatorCSVJet3;
  H hBDiscriminatorCSVJet4;

  H hMET, hMETPhi;
  H hSumET, hChET, hNhET, hPhET;
  H hHT;

  H hZMass;
  H hDphiMETLepton1, hDphiMETLepton2;
  H hDphiMETJet1, hDphiMETJet2;

  H hvsumM, hmaosM;
  H htopMass1, htopMass2;

  H hNLepton3, hNLepton4, hpt3, heta3, hpt4, heta4;
  H hNJPsi, hNLepJPsi1, hNLepJPsi2, hJPsiMass, hLepJPsiMass1, hLepJPsiMass2, hgenRecobJPsiDR, hgenbJPsiLepId;
};

#endif

