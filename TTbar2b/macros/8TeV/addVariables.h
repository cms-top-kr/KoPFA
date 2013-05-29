void addTopVariables(TopAnalyzerLite* analyzer){
  analyzer->addMonitorPlot("ZMass", "ZMass", "Dilepton mass;Dilepton Mass (GeV/c^{2});Events/5 GeV/c^{2}", 40, 0, 250, 0.1, 1500);
  analyzer->addMonitorPlot("ZMassFinal", "ZMass", "Dilepton mass;Dilepton Mass (GeV/c^{2});Events/40 GeV/c^{2}", 5, 0, 250, 0.1, 1500);

  analyzer->addMonitorPlot("nJetlog", "nJet30", "Jet Multiplicity;Jet Multiplicity;Events", 10, 0, 10, 0.05, 20000);
  analyzer->addMonitorPlot("nVertexlog", "nvertex", "Vertex Multiplicity;Vertex Multiplicity;Events", 25, 0, 25, 0.05, 5000);
  analyzer->addMonitorPlot("nVertex", "nvertex", "Vertex Multiplicity;Vertex Multiplicity;Events", 30, 0, 30, 0, 1,false);
  analyzer->addMonitorPlot("METlog", "MET", "Missing E_{T};Missing E_{T} (GeV);Events", 18, 0, 180, 0.1, 5000);
  analyzer->addMonitorPlot("nJet", "nJet30", "Jet Multiplicity;Jet Multiplicity;Events", 10, 0, 10, 0.1, 9,false);
  analyzer->addMonitorPlot("MET", "MET", "Missing E_{T};Missing E_{T} (GeV);Events", 18, 0, 180, 0.1, 1.5, false);
  analyzer->addMonitorPlot("METQCD", "MET", "Missing E_{T};Missing E_{T} (GeV);Events", 18, 0, 180, 0.1, 150.0, false);

  analyzer->addMonitorPlot("pt1", "lep1_pt", "Leading lepton p_{T};p_{T} (GeV/c);Events/5 GeV/c", 20, 0, 100, 0.1, 20000);
  analyzer->addMonitorPlot("pt2", "lep2_pt", "Second leading lepton p_{T};p_{T} (GeV/c);Events/5 GeV/c", 20, 0, 100, 0.1, 20000);
  analyzer->addMonitorPlot("eta1", "lep1_eta", "Leading #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("eta2", "lep2_eta", "Second leading lepton #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("jet1pt30", "jets_pt[0]", "Leading jet p_{T};p_{T} (GeV/c);Events/10 GeV/c",48, 20, 500, 0.1, 100000);
  analyzer->addMonitorPlot("jet1eta30", "jets_eta[0]", "Leading #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("jet1phi30", "jets_phi[0]", "Leading #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("jet2pt30", "jets_pt[1]", "Second leading jet p_{T};p_{T} (GeV/c);Events/10 GeV/c",48, 20, 500, 0.1, 100000);
  analyzer->addMonitorPlot("jet2eta30", "jets_eta[1]", "Second leading jet #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("jet2phi30", "jets_phi[1]", "Second leading jet #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("jet3pt30", "jets_pt[2]", "Third jet p_{T};p_{T} (GeV/c);Events/10 GeV/c",48, 20, 500, 0.1, 100000);
  analyzer->addMonitorPlot("jet3eta30", "jets_eta[2]", "Third jet #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("jet3phi30", "jets_phi[2]", "Third jet #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("jet4pt30", "jets_pt[3]", "Fourth jet p_{T};p_{T} (GeV/c);Events/10 GeV/c",48, 20, 500, 0.1, 100000);
  analyzer->addMonitorPlot("jet4eta30", "jets_eta[3]", "Fourth jet #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("jet4phi30", "jets_phi[3]", "Fourth jet #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("Iso03lep1","lep1_relIso03","relIso03lep1;relIso;Events", 40, 0, 0.4, 0.1, 20000);
  analyzer->addMonitorPlot("Iso03lep2","lep2_relIso03","relIso03lep2;relIso;Events", 40, 0, 0.4, 0.1, 20000);

  analyzer->addMonitorPlot("nbJet30_CSVL", "nbjets30_CSVL", "b-Jet Multiplicity;b-Jet Multiplicity (CSVL);Events", 5, 0, 5, 0.1, 10,true);
  analyzer->addMonitorPlot("nbJet30_CSVM", "nbjets30_CSVM", "b-Jet Multiplicity;b-Jet Multiplicity (CSVM);Events", 5, 0, 5, 0.1, 10,true);
  analyzer->addMonitorPlot("nbJet30_CSVT", "nbjets30_CSVT", "b-Jet Multiplicity;b-Jet Multiplicity (CSVT);Events", 5, 0, 5, 0.1, 10,true);
  analyzer->addMonitorPlot("nbJet30_JPM", "nbjets30_JPM", "b-Jet Multiplicity;b-Jet Multiplicity (JPM);Events", 5, 0, 5, 0.1, 10,true);
  analyzer->addMonitorPlot("nbJet30_JPT", "nbjets30_JPT", "b-Jet Multiplicity;b-Jet Multiplicity (JPT);Events", 5, 0, 5, 0.1, 10,true);

  analyzer->addMonitorPlot("jet1_bDis", "jets_bDiscriminatorCSV[0]","b-Discriminator; b-Discriminator (CSV);Events/0.1", 20, 0.0, 1.0, 0.1,10,true);
  analyzer->addMonitorPlot("jet2_bDis", "jets_bDiscriminatorCSV[1]","b-Discriminator; b-Discriminator (CSV);Events/0.1", 20, 0.0, 1.0, 0.1,10,true);

  analyzer->addMonitorPlot("jet1_bDisCSV", "jets_bDiscriminatorCSV[csvd_jetid[0]]","b-Discriminator; b-Discriminator (CSV);Events/0.1", 20, 0.0, 1.0, 0.1,10,true);
  analyzer->addMonitorPlot("jet2_bDisCSV", "jets_bDiscriminatorCSV[csvd_jetid[1]]","b-Discriminator; b-Discriminator (CSV);Events/0.1", 20, 0.0, 1.0, 0.1,10,true);
  analyzer->addMonitorPlot("jet1pt_bDisCSV", "jets_pt[csvd_jetid[0]]", "Leading jet p_{T};p_{T} (GeV/c);Events/10 GeV/c",48, 20, 500, 0.1, 100000);
  analyzer->addMonitorPlot("jet2pt_bDisCSV", "jets_pt[csvd_jetid[1]]", "Second leading jet p_{T};p_{T} (GeV/c);Events/10 GeV/c",48, 20, 500, 0.1, 100000);
  analyzer->addMonitorPlot("jet1eta_bDisCSV", "jets_eta[csvd_jetid[0]]", "Leading jet #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("jet2eta_bDisCSV", "jets_eta[csvd_jetid[1]]", "Second leading jet #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("addjet1_bDisCSV", "jets_bDiscriminatorCSV[csvd_jetid[2]]","b-Discriminator; b-Discriminator (CSV);Events/0.1", 20, 0.0, 1.0, 0.1,10,true);
  analyzer->addMonitorPlot("addjet2_bDisCSV", "jets_bDiscriminatorCSV[csvd_jetid[3]]","b-Discriminator; b-Discriminator (CSV);Events/0.1", 20, 0.0, 1.0, 0.1,10,true);

  analyzer->addMonitorPlot("addjet1_bDisCSV_rebin", "jets_bDiscriminatorCSV[csvd_jetid[2]]","b-Discriminator; b-Discriminator (CSV);Events/0.1", "0 0.05 0.1 0.15 0.2 0.25 0.3 0.35 0.4 0.45 0.5 0.55 0.6 0.65 0.7 0.75 0.8 0.85 0.9 0.95 1.0", 0.1,10,true);
  analyzer->addMonitorPlot("addjet2_bDisCSV_rebin", "jets_bDiscriminatorCSV[csvd_jetid[3]]","b-Discriminator; b-Discriminator (CSV);Events/0.1", "0 0.05 0.1 0.15 0.2 0.25 0.3 0.35 0.4 0.45 0.5 0.55 0.6 0.7 0.8 0.9 1.0", 0.1,10,true);
 
  analyzer->addMonitorPlot("addjet1_bDisJP", "jets_bDiscriminatorJP[jpd_jetid[2]]", "b-Discriminator; b-Discriminator (JP);Events", 20, 0.0, 1.0, 0.1, 10,true);
  analyzer->addMonitorPlot("addjet2_bDisJP", "jets_bDiscriminatorJP[jpd_jetid[3]]", "b-Discriminator; b-Discriminator (JP);Events", 20, 0.0, 1.0, 0.1, 10,true);

  analyzer->addMonitorPlot("addjet1_secvtxm", "jets_secvtxmass[csvd_jetid[2]]", "Secondary Vertex Mass;Secondary Vertex Mass (GeV);Events", 10, 0.0, 5.0, 0.1, 10,true);
  analyzer->addMonitorPlot("addjet2_secvtxm", "jets_secvtxmass[csvd_jetid[3]]", "Secondary Vertex Mass;Secondary Vertex Mass (GeV);Events", 10, 0.0, 5.0, 0.1, 10,true);

}
