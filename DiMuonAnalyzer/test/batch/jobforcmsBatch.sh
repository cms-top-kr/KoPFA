cmsBatch.py 1 dimuonanalyzer_data_1_cfg.py -o Out/11 -r /castor/cern.ch/user/t/tjkim/ntuple/RD/Aug13_topref/1/vallot.root -b 'bsub -q 1nh < batchScript.sh'  
#cmsBatch.py 1 dimuonanalyzer_data_2_cfg.py -o Out/12 -r /castor/cern.ch/user/t/tjkim/ntuple/RD/Aug13_topref/2/vallot.root -b 'bsub -q 1nh < batchScript.sh'
#cmsBatch.py 1 dimuonanalyzer_data_3_cfg.py -o Out/13 -r /castor/cern.ch/user/t/tjkim/ntuple/RD/Aug13_topref/3/vallot.root -b 'bsub -q 1nh < batchScript.sh'
#cmsBatch.py 1 dimuonanalyzer_data_4_cfg.py -o Out/14 -r /castor/cern.ch/user/t/tjkim/ntuple/RD/Aug13_topref/4/vallot.root -b 'bsub -q 1nh < batchScript.sh'

#Turn off trigger filter for MC for the time being
# Summer10
#cmsBatch.py 6 dimuonanalyzer_InclusiveMu15_cfg.py -o Out/2 -r /castor/cern.ch/user/t/tjkim/ntuple/MC/Summer10/InclusiveMu15/vallot.root -b 'bsub -q 8nm < batchScript.sh'
#cmsBatch.py 1 dimuonanalyzer_TTbar_cfg.py -o Out/3 -r /castor/cern.ch/user/t/tjkim/ntuple/MC/Summer10/TTbar/vallot.root -b 'bsub -q 1nh < batchScript.sh'
#cmsBatch.py 1 dimuonanalyzer_Zmumu_cfg.py -o Out/4 -r /castor/cern.ch/user/t/tjkim/ntuple/MC/Summer10/Zmumu/vallot.root -b 'bsub -q 1nh < batchScript.sh'
#cmsBatch.py 1 dimuonanalyzer_Ztautau_cfg.py -o Out/6 -r /castor/cern.ch/user/t/tjkim/ntuple/MC/Summer10/Ztautau/vallot.root -b 'bsub -q 1nh < batchScript.sh'
#cmsBatch.py 1 dimuonanalyzer_Wmunu_cfg.py -o Out/7 -r /castor/cern.ch/user/t/tjkim/ntuple/MC/Summer10/Wmunu/vallot.root -b 'bsub -q 1nh < batchScript.sh'
#cmsBatch.py 1 dimuonanalyzer_Wtaunu_cfg.py -o Out/9 -r /castor/cern.ch/user/t/tjkim/ntuple/MC/Summer10/Wtaunu/vallot.root -b 'bsub -q 1nh < batchScript.sh'
