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

  analyzer->addMonitorPlot("pt1", "lepton1.pt()", "Leading lepton p_{T};p_{T} (GeV/c);Events/5 GeV/c", 20, 0, 100, 0.1, 20000);
  analyzer->addMonitorPlot("pt2", "lepton2.pt()", "Second leading lepton p_{T};p_{T} (GeV/c);Events/5 GeV/c", 20, 0, 100, 0.1, 20000);
  analyzer->addMonitorPlot("eta1", "lepton1.eta()", "Leading #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("eta2", "lepton2.eta()", "Second leading lepton #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("jet1pt30", "jets[0].pt()", "Leading jet p_{T};p_{T} (GeV/c);Events/10 GeV/c",48, 20, 500, 0.1, 100000);
  analyzer->addMonitorPlot("jet1eta30", "jets[0].eta()", "Leading #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("jet1phi30", "jets[0].phi()", "Leading #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("jet2pt30", "jets[1].pt()", "Second leading jet p_{T};p_{T} (GeV/c);Events/10 GeV/c",48, 20, 500, 0.1, 100000);
  analyzer->addMonitorPlot("jet2eta30", "jets[1].eta()", "Second leading jet #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("jet2phi30", "jets[1].phi()", "Second leading jet #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("jet3pt30", "jets[2].pt()", "Third jet p_{T};p_{T} (GeV/c);Events/10 GeV/c",48, 20, 500, 0.1, 100000);
  analyzer->addMonitorPlot("jet3eta30", "jets[2].eta()", "Third jet #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("jet3phi30", "jets[2].phi()", "Third jet #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("jet4pt30", "jets[3].pt()", "Fourth jet p_{T};p_{T} (GeV/c);Events/10 GeV/c",48, 20, 500, 0.1, 100000);
  analyzer->addMonitorPlot("jet4eta30", "jets[3].eta()", "Fourth jet #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("jet4phi30", "jets[3].phi()", "Fourth jet #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("Iso03lep1","lepton1.relIso03()","relIso03lep1;relIso;Events", 40, 0, 0.4, 0.1, 20000);
  analyzer->addMonitorPlot("Iso03lep2","lepton2.relIso03()","relIso03lep2;relIso;Events", 40, 0, 0.4, 0.1, 20000);

  analyzer->addMonitorPlot("nbJet30_CSVL", "nbjets30_CSVL", "b-Jet Multiplicity;b-Jet Multiplicity (CSVL);Events", 5, 0, 5, 0.1, 10,true);
  analyzer->addMonitorPlot("nbJet30_CSVM", "nbjets30_CSVM", "b-Jet Multiplicity;b-Jet Multiplicity (CSVM);Events", 5, 0, 5, 0.1, 10,true);
  analyzer->addMonitorPlot("nbJet30_CSVT", "nbjets30_CSVT", "b-Jet Multiplicity;b-Jet Multiplicity (CSVT);Events", 5, 0, 5, 0.1, 10,true);

  analyzer->addMonitorPlot("Mbb","ttbarKin.Mbb()","M_{bb};M_{bb};Events", 50, 0, 500, 0.01, 0.05, false);
}
