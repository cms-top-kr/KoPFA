cmsBatch.py 2 dimuonanalyzer_InclusiveMu15_cfg.py -o Out/2 -r /castor/cern.ch/user/t/tjkim/ntuple/MC/Spring10_topref/InclusiveMu15/vallot.root -b 'bsub -q 8nm < batchScript.sh'
cmsBatch.py 1 dimuonanalyzer_TTbar_cfg.py -o Out/3 -r /castor/cern.ch/user/t/tjkim/ntuple/MC/Spring10_topref/TTbar/vallot.root -b 'bsub -q 1nh < batchScript.sh'
cmsBatch.py 1 dimuonanalyzer_Zmumu_cfg.py -o Out/4 -r /castor/cern.ch/user/t/tjkim/ntuple/MC/Spring10_topref/Zmumu/vallot.root -b 'bsub -q 1nh < batchScript.sh'
cmsBatch.py 1 dimuonanalyzer_Ztautau_cfg.py -o Out/6 -r /castor/cern.ch/user/t/tjkim/ntuple/MC/Spring10_topref/Ztautau/vallot.root -b 'bsub -q 1nh < batchScript.sh'
cmsBatch.py 1 dimuonanalyzer_ZJets_cfg.py -o Out/7 -r /castor/cern.ch/user/t/tjkim/ntuple/MC/Spring10_topref/ZJets/vallot.root -b 'bsub -q 1nh < batchScript.sh'
cmsBatch.py 1 dimuonanalyzer_WJets_cfg.py -o Out/8 -r /castor/cern.ch/user/t/tjkim/ntuple/MC/Spring10_topref/WJets/vallot.root -b 'bsub -q 1nh < batchScript.sh'
cmsBatch.py 1 dimuonanalyzer_VVJets_cfg.py -o Out/9 -r /castor/cern.ch/user/t/tjkim/ntuple/MC/Spring10_topref/VVJets/vallot.root -b 'bsub -q 1nh < batchScript.sh'
cmsBatch.py 1 dimuonanalyzer_SingleTop_cfg.py -o Out/10 -r /castor/cern.ch/user/t/tjkim/ntuple/MC/Spring10_topref/SingleTop/vallot.root -b 'bsub -q 1nh < batchScript.sh'
cmsBatch.py 1 dimuonanalyzer_DYmumu_cfg.py -o Out/11 -r /castor/cern.ch/user/t/tjkim/ntuple/MC/Spring10_topref/DYmumu/vallot.root -b 'bsub -q 1nh < batchScript.sh'


