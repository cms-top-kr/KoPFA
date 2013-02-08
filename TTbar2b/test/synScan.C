void synScan(int ii)
{

  TFile * f = new TFile("/afs/cern.ch/work/t/tjkim/public/store/top/Syn/vallot_syn_trigger_noGen_ttbar_mu24_jet24.root");
  TTree * t_mm = (TTree *) f->Get("MuMu/tree");
  TTree * t_ee = (TTree *) f->Get("ElEl/tree");
  TTree * t_em = (TTree *) f->Get("MuEl/tree");
 
  TH1F * h_mm = (TH1F *) f->Get("MuMu/EventSummary");
  TH1F * h_ee = (TH1F *) f->Get("ElEl/EventSummary");
  TH1F * h_em = (TH1F *) f->Get("MuEl/EventSummary");

  TCut run = "";

  TCut step1 = "ZMass > 20 && isIso > 0 && PairSign < 0" + run;
  TCut step2 = "abs(ZMass-91.2) > 15";
  TCut step3 = "nJet30 >= 2";
  TCut step4 = "MET > 40";
  TCut step5 = "nbjets30_CSVL >= 1";


   if(ii==0)
   {
      cout << "* * MuMu" << endl;
      cout << "* * tot * S0 * S1 * S2 * S3 * S4 * S5 " << endl;
      cout << " * * " << (int) h_mm->GetBinContent(1) << " * " << (int) h_mm->GetBinContent(3) << " * " 
           << t_mm->GetEntries(step1)      << " * " << t_mm->GetEntries(step2+step1)      << " * " << t_mm->GetEntries(step3+step2+step1)  << " * "
           << t_mm->GetEntries(step4+step3+step2+step1)      << " * " << t_mm->GetEntries(step5+step4+step3+step2+step1)    
           << endl;
      t_mm->Scan("RUN:EVENT:lep1_pt:lep2_pt:lep1_relIso03:lep2_relIso03:ZMass:nJet30: jets_pt[0]: jets_pt[1]:MET:nbjets30_CSVL","ZMass > 20 && isIso > 0 && PairSign < 0 &&abs(ZMass-91.2) > 15 && nJet30 >= 2 && MET > 40 && nbjets30_CSVL >= 1","",1000000,0);
   }
   else if(ii==1)
   {
      cout << "* *ElEl" << endl;
      cout << "* * tot * S0 * S1 * S2 * S3 * S4 * S5 " << endl;
      cout << " * * " << (int) h_ee->GetBinContent(1) << " * " << (int) h_ee->GetBinContent(3) << " * "  
           << t_ee->GetEntries(step1)      << " * " << t_ee->GetEntries(step2+step1)      << " * " << t_ee->GetEntries(step3+step2+step1)  << " * "
           << t_ee->GetEntries(step4+step3+step2+step1)      << " * " << t_ee->GetEntries(step5+step4+step3+step2+step1)    
           << endl;
      t_ee->Scan("RUN:EVENT:lep1_pt:lep2_pt:lep1_relIso03:lep2_relIso03:ZMass:nJet30: jets_pt[0]: jets_pt[1]:MET:nbjets30_CSVL","ZMass > 20 && isIso > 0 && PairSign < 0 &&abs(ZMass-91.2) > 15 && nJet30 >= 2 && MET > 40 && nbjets30_CSVL >= 1","",100000000,0);
   }
   else if(ii==2)
   {
      cout << "* * MuEl" << endl;
      cout << "* * tot * S0 * S1 * S2 * S3 * S4 * S5 " << endl;
      cout << " * * " << (int) h_em->GetBinContent(1) << " * " << (int) h_em->GetBinContent(3) << " * " 
           << t_em->GetEntries(step1)      << " * " << t_em->GetEntries(step1)      << " * " << t_em->GetEntries(step3+step1)  << " * "
           << t_em->GetEntries(step3+step1)      << " * " << t_em->GetEntries(step5+step3+step1)    
           << endl;
      t_em->Scan("RUN:EVENT:lep1_pt:lep2_pt:lep1_relIso03:lep2_relIso03:ZMass:nJet30: jets_pt[0]: jets_pt[1]:MET:nbjets30_CSVL","ZMass > 20 && isIso > 0 && PairSign < 0 && nJet30 >= 2 && nbjets30_CSVL >= 1","",100000000,0);
   }
}
