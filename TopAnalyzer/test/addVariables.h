void addTopVariables(TopAnalyzerLite* analyzer){
  analyzer->addMonitorPlot("ZMass", "Z.mass()", "Dilepton mass;Dilepton Mass (GeV/c^{2});Events/5 GeV/c^{2}", 40, 0, 200, 0.1, 1500);
  analyzer->addMonitorPlot("ZMassFinal", "Z.mass()", "Dilepton mass;Dilepton Mass (GeV/c^{2});Events/40 GeV/c^{2}", 5, 0, 200, 0.1, 1500);
  analyzer->addMonitorPlot("nJetlog", "@jetspt30.size()", "Jet Multiplicity;Jet Multiplicity;Events", 5, 0, 5, 0.05, 2000);
  analyzer->addMonitorPlot("METlog", "MET", "Missing E_{T};Missing E_{T} (GeV);Events", 10, 0, 100, 0.1, 2000);
  analyzer->addMonitorPlot("nJet", "@jetspt30.size()", "Jet Multiplicity;Jet Multiplicity;Events", 5, 0, 5, 0.1, 3,false);
  analyzer->addMonitorPlot("MET", "MET", "Missing E_{T};Missing E_{T} (GeV);Events", 10, 0, 100, 0.1, 1.5, false);

  analyzer->addMonitorPlot("pt1", "Z.leg1().pt()", "Leading p_{T};p_{T} (GeV/c);Events/5 GeV/c", 20, 0, 100, 0.1, 4000);
  analyzer->addMonitorPlot("pt2", "Z.leg2().pt()", "Leading p_{T};p_{T} (GeV/c);Events/5 GeV/c", 20, 0, 100, 0.1, 2000);
  analyzer->addMonitorPlot("eta1", "Z.leg1().eta()", "Leading #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 20000);
  analyzer->addMonitorPlot("eta2", "Z.leg2().eta()", "Leading #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 20000);
  analyzer->addMonitorPlot("phi1", "Z.leg1().phi()", "Leading #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 20000);
  analyzer->addMonitorPlot("phi2", "Z.leg2().phi()", "Leading #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 20000);
  analyzer->addMonitorPlot("jet1pt", "jetspt30[0].pt()", "Leading p_{T};p_{T} (GeV/c);Events/5 GeV/c",20, 30, 130, 0.1, 5000);
  analyzer->addMonitorPlot("jet2pt", "jetspt30[1].pt()", "Leading p_{T};p_{T} (GeV/c);Events/5 GeV/c",20, 30, 130, 0.1, 5000);
  analyzer->addMonitorPlot("jet1eta", "jetspt30[0].eta()", "Leading #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 20000);
  analyzer->addMonitorPlot("jet2eta", "jetspt30[1].eta()", "Leading #eta;#eta;Events/0.2", 35, -3.5, 3.5, 0.1, 20000);
  analyzer->addMonitorPlot("jet1phi", "jetspt30[0].phi()", "Leading #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 20000);
  analyzer->addMonitorPlot("jet2phi", "jetspt30[1].phi()", "Leading #phi;#phi (Radian);Events/0.2 rad.", 35, -3.5, 3.5, 0.1, 20000);

  analyzer->addMonitorPlot("Iso04lep1","relIso04lep1","relIso04lep1;relIso;Events", 20, 0, 0.4, 0.1, 20000);
  analyzer->addMonitorPlot("chIso1","chIso1","chIso1;Charged Hadron #Sigma p_{T} (GeV);Events/0.2 GeV", 20, 0, 4, 0.1, 20000);
  analyzer->addMonitorPlot("nhIso1","nhIso1","nhIso1;Neutral Hadron #Sigma p_{T} (GeV);Events/0.2 GeV", 20, 0, 4, 0.1, 20000);
  analyzer->addMonitorPlot("phIso1","phIso1","phIso1;Photon #Sigma p_{T} (GeV);Events/0.2 GeV", 20, 0, 4, 0.1, 20000);

  analyzer->addMonitorPlot("Iso04lep2","relIso04lep2","relIso04lep2;relIso;Events", 20, 0, 0.4, 0.1, 20000);
  analyzer->addMonitorPlot("chIso2","chIso2","chIso2;Charged Hadron #Sigma p_{T} (GeV);Events/0.2 GeV", 20, 0, 4, 0.1, 20000);
  analyzer->addMonitorPlot("nhIso2","nhIso2","nhIso2;Neutral Hadron #Sigma p_{T} (GeV);Events/0.2 GeV", 20, 0, 4, 0.1, 20000);
  analyzer->addMonitorPlot("phIso2","phIso2","phIso2;Photon #Sigma p_{T} (GeV);Events/0.2 GeV", 20, 0, 4, 0.1, 20000);

  analyzer->addMonitorPlot("sumet", "pfMet.sumEt()", "#Sigma E_{T};#Sigma E_{T} (GeV);Events/20 GeV", 50, 0, 1000, 0.1, 20000);
  analyzer->addMonitorPlot("chargedhadet", "pfMet.chargedHadEt()", "#Sigma E_{T};Charged Hadron #Sigma E_{T} (GeV);Events/5 GeV", 40, 0, 200, 0.1, 20000);
  analyzer->addMonitorPlot("neutralhadet", "pfMet.neutralHadEt()", "#Sigma E_{T};Neutral Hadron #Sigma E_{T} (GeV);Events/5 GeV", 40, 0, 200, 0.1, 20000);
  analyzer->addMonitorPlot("photonet", "pfMet.photonEt()", "#Sigma E_{T};Photon #Sigma E_{T} (GeV);Events/5 GeV", 40, 0, 200, 0.1, 20000);
  analyzer->addMonitorPlot("HT","Z.leg1().pt()+Z.leg2().pt()+jetspt30[0].pt() + jetspt30[1].pt() + MET","HT; Events; H_{T} (GeV)", 40,0,1000,0.1,20000);

  analyzer->addMonitorPlot("metPhi", "met[0].phi()", "Azimuthal angle of Missing E_{T};Azimuthal angle #phi;Events/0.2 rad", 35, -3.5, 3.5, 0.1, 100);
  analyzer->addMonitorPlot("dphi1", "asin(sin(Z.leg1().phi()-met[0].phi()))", "Azimuthal angle difference between leading lepton - MET;Angle difference;Events/0.2 rad", 20, -2, 2, 0.1, 10000);
  analyzer->addMonitorPlot("dphi2", "asin(sin(Z.leg2().phi()-met[0].phi()))", "Azimuthal angle difference between leading lepton - MET;Angle difference;Events/0.2 rad", 20, -2, 2, 0.1, 10000);
  analyzer->addMonitorPlot("vsumM", "ttbar.M()", "ttbar invariant mass;t#bar{t} invaraint mass;Events/40 GeV", 20, 200, 1000, 0.1, 0.9, false);
  analyzer->addMonitorPlot("vsumMAlt", "ttbar.M()", "ttbar invariant mass;t#bar{t} invaraint mass;Events", "0 350 400 450 500 550 600 700 800 1400", 0.1, 1.1, false);
  analyzer->addMonitorPlot("genttbarM", "genttbarM", "ttbar invariant mass;t#bar{t} invaraint mass;Events", "0 350 400 450 500 550 600 700 800 1400", 0.1, 1.1, false);
  analyzer->addMonitorPlot("maosM", "ttbar.maosM()", "ttbar invariant mass;t#bar{t} invaraint mass;Events/40 GeV", 20, 200, 1000, 0.1, 0.9, false);
  analyzer->addMonitorPlot("nbJet", "@bjets.size()", "b-Jet Multiplicity;b-Jet Multiplicity;Events", 5, 0, 5, 0.1, 3,false);
}
