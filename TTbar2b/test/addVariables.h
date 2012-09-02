void addTopVariables(TopAnalyzerLite* analyzer){
  analyzer->addMonitorPlot("ZMass", "ZMass", "Dilepton mass;Dilepton Mass (GeV/c^{2});Events/5 GeV/c^{2}", 40, 0, 250, 0.1, 1500);
  analyzer->addMonitorPlot("ZMassFinal", "ZMass", "Dilepton mass;Dilepton Mass (GeV/c^{2});Events/40 GeV/c^{2}", 5, 0, 250, 0.1, 1500);

  analyzer->addMonitorPlot("nJetlog", "@jetspt30.size()", "Jet Multiplicity;Jet Multiplicity;Events", 10, 0, 10, 0.05, 20000);
  analyzer->addMonitorPlot("nVertexlog", "nvertex", "Vertex Multiplicity;Vertex Multiplicity;Events", 25, 0, 25, 0.05, 5000);
  analyzer->addMonitorPlot("nVertex", "nvertex", "Vertex Multiplicity;Vertex Multiplicity;Events", 30, 0, 30, 0, 1,false);
  analyzer->addMonitorPlot("METlog", "MET", "Missing E_{T};Missing E_{T} (GeV);Events", 18, 0, 180, 0.1, 5000);
  analyzer->addMonitorPlot("nJet", "@jetspt30.size()", "Jet Multiplicity;Jet Multiplicity;Events", 10, 0, 10, 0.1, 9,false);
  analyzer->addMonitorPlot("MET", "MET", "Missing E_{T};Missing E_{T} (GeV);Events", 18, 0, 180, 0.1, 1.5, false);
  analyzer->addMonitorPlot("METQCD", "MET", "Missing E_{T};Missing E_{T} (GeV);Events", 18, 0, 180, 0.1, 150.0, false);

  analyzer->addMonitorPlot("pt1", "pt1", "Leading lepton p_{T};p_{T} (GeV/c);Events/5 GeV/c", 20, 0, 100, 0.1, 20000);
  analyzer->addMonitorPlot("pt2", "pt1", "Second leading lepton p_{T};p_{T} (GeV/c);Events/5 GeV/c", 20, 0, 100, 0.1, 20000);
  analyzer->addMonitorPlot("eta1", "eta1", "Leading #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("eta2", "eta1", "Second leading lepton #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("jet1pt20", "jetspt20[0].pt()", "Leading jet p_{T};p_{T} (GeV/c);Events/10 GeV/c",48, 20, 500, 0.1, 100000);
  analyzer->addMonitorPlot("jet1eta20", "jetspt20[0].eta()", "Leading #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("jet1phi20", "jetspt20[0].phi()", "Leading #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("jet2pt20", "jetspt20[1].pt()", "Second leading jet p_{T};p_{T} (GeV/c);Events/10 GeV/c",48, 20, 500, 0.1, 100000);
  analyzer->addMonitorPlot("jet2eta20", "jetspt20[1].eta()", "Second leading jet #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("jet2phi20", "jetspt20[1].phi()", "Second leading jet #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("jet3pt20", "jetspt20[2].pt()", "Third jet p_{T};p_{T} (GeV/c);Events/10 GeV/c",48, 20, 500, 0.1, 100000);
  analyzer->addMonitorPlot("jet3eta20", "jetspt20[2].eta()", "Third jet #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("jet3phi20", "jetspt20[2].phi()", "Third jet #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("jet4pt20", "jetspt20[3].pt()", "Fourth jet p_{T};p_{T} (GeV/c);Events/10 GeV/c",48, 20, 500, 0.1, 100000);
  analyzer->addMonitorPlot("jet4eta20", "jetspt20[3].eta()", "Fourth jet #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("jet4phi20", "jetspt20[3].phi()", "Fourth jet #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("jet1pt30", "jetspt30[0].pt()", "Leading jet p_{T};p_{T} (GeV/c);Events/10 GeV/c",48, 20, 500, 0.1, 100000);
  analyzer->addMonitorPlot("jet1eta30", "jetspt30[0].eta()", "Leading #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("jet1phi30", "jetspt30[0].phi()", "Leading #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("jet2pt30", "jetspt30[1].pt()", "Second leading jet p_{T};p_{T} (GeV/c);Events/10 GeV/c",48, 20, 500, 0.1, 100000);
  analyzer->addMonitorPlot("jet2eta30", "jetspt30[1].eta()", "Second leading jet #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("jet2phi30", "jetspt30[1].phi()", "Second leading jet #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("jet3pt30", "jetspt30[2].pt()", "Third jet p_{T};p_{T} (GeV/c);Events/10 GeV/c",48, 20, 500, 0.1, 100000);
  analyzer->addMonitorPlot("jet3eta30", "jetspt30[2].eta()", "Third jet #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("jet3phi30", "jetspt30[2].phi()", "Third jet #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("jet4pt30", "jetspt30[3].pt()", "Fourth jet p_{T};p_{T} (GeV/c);Events/10 GeV/c",48, 20, 500, 0.1, 100000);
  analyzer->addMonitorPlot("jet4eta30", "jetspt30[3].eta()", "Fourth jet #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 100000);
  analyzer->addMonitorPlot("jet4phi30", "jetspt30[3].phi()", "Fourth jet #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 100000);

  analyzer->addMonitorPlot("Iso03lep1","relIso1","relIso03lep1;relIso;Events", 40, 0, 0.4, 0.1, 20000);
  analyzer->addMonitorPlot("Iso03lep2","relIso2","relIso03lep2;relIso;Events", 40, 0, 0.4, 0.1, 20000);

  analyzer->addMonitorPlot("sumet", "sumEt", "#Sigma E_{T};#Sigma E_{T} (GeV);Events/20 GeV", 50, 0, 1000, 0.1, 20000);
  analyzer->addMonitorPlot("chargedhadet", "pfMet.chargedHadEt()", "#Sigma E_{T};Charged Hadron #Sigma E_{T} (GeV);Events/5 GeV", 40, 0, 200, 0.1, 20000);
  analyzer->addMonitorPlot("neutralhadet", "pfMet.neutralHadEt()", "#Sigma E_{T};Neutral Hadron #Sigma E_{T} (GeV);Events/5 GeV", 40, 0, 200, 0.1, 20000);
  analyzer->addMonitorPlot("photonet", "pfMet.photonEt()", "#Sigma E_{T};Photon #Sigma E_{T} (GeV);Events/5 GeV", 40, 0, 200, 0.1, 20000);
  analyzer->addMonitorPlot("HT","Z.leg1().pt()+Z.leg2().pt()+jetspt20[0].pt() + jetspt20[1].pt() + MET","HT; H_{T} (GeV); Events", 40,0,1000,0.1,20000);

  analyzer->addMonitorPlot("metPhi", "met[0].phi()", "Azimuthal angle of Missing E_{T};Azimuthal angle #phi;Events/0.2 rad", 35, -3.5, 3.5, 0.1, 100);
  analyzer->addMonitorPlot("dphimetlepton1", "dphimetlepton1", "Azimuthal angle between leading lepton - MET;#Delta#Phi between leading lepton and MET;Events/0.1 rad", 40, 0, 4, 0, 0.5,false);
  analyzer->addMonitorPlot("dphimetlepton2", "dphimetlepton2", "Azimuthal angle between second lepton - MET;#Delta#Phi between second lepton and MET;Events/0.1 rad", 40, 0, 4, 0, 0.5,false);
  analyzer->addMonitorPlot("dphimetjet1", "dphimetjet1", "Azimuthal angle between leading jet - MET;#Delta#Phi between leading jet and MET;Events/0.1 rad", 40, 0, 4, 0, 0.5,false);
  analyzer->addMonitorPlot("dphimetjet2", "dphimetjet2", "Azimuthal angle between second jet - MET;#Delta#Phi between second jet and MET;Events/0.1 rad", 40, 0, 4, 0, 0.5,false);

  analyzer->addMonitorPlot("vsumMhigh", "ttbar.M()", "ttbar invariant mass;t#bar{t} invariant mass;Events/50 GeV", 3000, 0, 3000, 0.1, 0.9, false);
  analyzer->addMonitorPlot("vsumM", "ttbar.M()", "ttbar invariant mass;t#bar{t} invariant mass;Events/50 GeV", 32, 200, 1800, 0.1, 0.9, false);
  analyzer->addMonitorPlot("vsumMAlt", "ttbar.M()", "ttbar invariant mass;t#bar{t} invariant mass;Events", "0 345 400 450 500 550 600 680 800 1800", 0.1, 1.8, false);
  analyzer->addMonitorPlot("genttbarM", "genttbarM", "ttbar invariant mass;t#bar{t} invariant mass;Events", "0 345 400 450 500 550 600 680 800 1800", 0.1, 1.8, false);
  analyzer->addMonitorPlot("maosM", "ttbar.maosM()", "ttbar invariant mass;t#bar{t} invariant mass;Events/50 GeV", 32, 200, 1800, 0.1, 0.9, false);
  analyzer->addMonitorPlot("topMass1", "ttbar.leg1().M()", "blv mass;blv mass;Events/10 GeV", 30, 0, 300, 0.1, 0.9, false);
  analyzer->addMonitorPlot("topMass2", "ttbar.leg2().M()", "blv mass;blv mass;Events/10 GeV", 30, 0, 300, 0.1, 0.9, false);
  analyzer->addMonitorPlot("nbJet_TCHEL", "nbjets_TCHEL", "b-Jet Multiplicity;b-Jet Multiplicity (TCHEL);Events", 6, 0, 6, 0.1, 3,false);

  analyzer->addMonitorPlot("nbJet20_CSVL", "nbjets20_CSVL", "b-Jet Multiplicity;b-Jet Multiplicity (CSVL);Events", 5, 0, 5, 0.1, 0.6,false);
  analyzer->addMonitorPlot("nbJet20_CSVM", "nbjets20_CSVM", "b-Jet Multiplicity;b-Jet Multiplicity (CSVM);Events", 5, 0, 5, 0.1, 0.6,false);
  analyzer->addMonitorPlot("nbJet20_CSVT", "nbjets20_CSVT", "b-Jet Multiplicity;b-Jet Multiplicity (CSVT);Events", 5, 0, 5, 0.1, 0.6,false);

  analyzer->addMonitorPlot("nbJet30_CSVL", "nbjets30_CSVL", "b-Jet Multiplicity;b-Jet Multiplicity (CSVL);Events", 5, 0, 5, 0.1, 0.6,false);
  analyzer->addMonitorPlot("nbJet30_CSVM", "nbjets30_CSVM", "b-Jet Multiplicity;b-Jet Multiplicity (CSVM);Events", 5, 0, 5, 0.1, 0.6,false);
  analyzer->addMonitorPlot("nbJet30_CSVT", "nbjets30_CSVT", "b-Jet Multiplicity;b-Jet Multiplicity (CSVT);Events", 5, 0, 5, 0.1, 0.6,false);

  analyzer->addMonitorPlot("nbJet30_CSVMT", "nbjets30_CSVMT", "b-Jet Multiplicity;b-Jet Multiplicity;Events", 5, 0, 5, 0.1, 0.6,false);

  analyzer->addMonitorPlot("jet30bDiscriminator0", "jet30bDiscriminator[0]", "CSV distriminator;discriminator (CSV);Entries", 100, 0, 1, 0.1, 0.6,false);
  analyzer->addMonitorPlot("jet30bDiscriminator1", "jet30bDiscriminator[1]", "CSV distriminator;discriminator (CSV);Entries", 100, 0, 1, 0.1, 0.6,false);
  analyzer->addMonitorPlot("jet30bDiscriminator2", "jet30bDiscriminator[2]", "CSV distriminator;discriminator (CSV);Entries", 100, 0, 1, 0.1, 0.6,false);
  analyzer->addMonitorPlot("jet30bDiscriminator3", "jet30bDiscriminator[3]", "CSV distriminator;discriminator (CSV);Entries", 100, 0, 1, 0.1, 0.6,false);

  analyzer->addMonitorPlot("jet30ptrel1", "ptrel30[0]", "jet;p_{T}^{rel};Entries", 100, 0, 10, 0.1, 0.6,false);
  analyzer->addMonitorPlot("jet30ptrel2", "ptrel30[1]", "jet;p_{T}^{rel};Entries", 100, 0, 10, 0.1, 0.6,false);
  analyzer->addMonitorPlot("jet30ptrel3", "ptrel30[2]", "jet;p_{T}^{rel};Entries", 100, 0, 10, 0.1, 0.6,false);
  analyzer->addMonitorPlot("jet30ptrel4", "ptrel30[3]", "jet;p_{T}^{rel};Entries", 100, 0, 10, 0.1, 0.6,false);
  analyzer->addMonitorPlot("Mbb","sqrt( ( jetspt30[2].e()+jetspt30[3].e() )^2  - ( jetspt30[2].x()+jetspt30[3].x() )^2 - ( jetspt30[2].y()+jetspt30[3].y() )^2 -  ( jetspt30[2].z()+jetspt30[3].z() )^2)","Mbb:Mbb", 50, 0, 500, 0.1, 0.6, false);
}
