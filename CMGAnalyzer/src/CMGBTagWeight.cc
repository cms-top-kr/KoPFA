// B-tag reweighting tool
// Author: Suyong Choi
// Created: June 5 2012
#include "KoPFA/CMGAnalyzer/interface/CMGBTagWeight.h"

double BTagWeight::reweight(const std::vector<TLorentzVector *> &jets, const std::vector<int> &jetflavor, int ntag, AlgoType algo, SYS sys)
{
    algo_ = algo;
    sys_ = sys;

    double pmc = probmc(jets, jetflavor, ntag);
    double pdata = probdata(jets, jetflavor, ntag);
   
    return pdata/pmc;
}

// prepare a vector of pointers to TLorentzVector and jet flavors
// use recursion
double BTagWeight::probmc(const std::vector<TLorentzVector *> &jets, const std::vector<int> &jetflavor, int ntag, int fromi)
{
    // something doesn't match
    if (jetflavor.size() != jets.size()) return 0.0;
    // can't have more ntags than the number of jets
    if ((int) jets.size() < ntag) return 0.0;
    if (fromi>= (int) jets.size()) return 1.0; // stopping condition for recursion

    int njetsize = jets.size();
    double probability=0.0;
    int i = fromi;
    //for (int i=fromi; i<njetsize; i++)
    {
        double jpt = jets[i]->Pt();
        double jeta = jets[i]->Eta();
        if (njetsize-i == ntag) // the number of remaining jets equals the ntags, so they must be tagged
        {
            if (jetflavor[i]==5) probability =eb(jpt, jeta)*probmc(jets, jetflavor, ntag-1, i+1);
            else if (jetflavor[i]==4) probability =ec(jpt, jeta)*probmc(jets, jetflavor, ntag-1, i+1);
            else probability =el(jpt, jeta)*probmc(jets, jetflavor, ntag-1, i+1);
        }
        else if (ntag>0) {
            if (jetflavor[i]==5) {
                probability = eb(jpt, jeta)*probmc(jets, jetflavor, ntag-1, i+1) // jet i tagged
                    + (1.0-eb(jpt, jeta))*probmc(jets, jetflavor, ntag, i+1);  // jet i not tagged
            }
            else if (jetflavor[i]==4) {
                probability = ec(jpt, jeta)*probmc(jets, jetflavor, ntag-1, i+1)
                    + (1.0-ec(jpt, jeta))*probmc(jets, jetflavor, ntag, i+1);  // jet i not tagged
            }
            else {
                probability = el(jpt, jeta)*probmc(jets, jetflavor, ntag-1, i+1)
                    + (1.0-el(jpt, jeta))*probmc(jets, jetflavor, ntag, i+1);  // jet i not tagged
            }
        }
        else
        {
            if (jetflavor[i]==5) probability = (1.0-eb(jpt, jeta))*probmc(jets, jetflavor, 0, i+1); // no tag
            else if (jetflavor[i]==4) probability = (1.0-ec(jpt, jeta))*probmc(jets, jetflavor, 0, i+1); // no tag
            else probability = (1.0-el(jpt, jeta))*probmc(jets, jetflavor, 0, i+1); // no tag
        }
    }
    return probability;
}

// prepare a vector of pointers to TLorentzVector and jet flavors
// use recursion
double BTagWeight::probdata(const std::vector<TLorentzVector *> &jets, const std::vector<int> &jetflavor, int ntag, int fromi)
{
    // something doesn't match
    if (jetflavor.size() != jets.size()) return 0.0;
    // can't have more ntags than the number of jets
    if ((int) jets.size() < ntag) return 0.0;
    if (fromi>= (int) jets.size()) return 1.0; // stopping condition for recursion

    int njetsize = jets.size();
    double probability=0.0;
    int i = fromi;
    //for (int i=fromi; i<njetsize; i++)
    {
        double jpt = jets[i]->Pt();
        double jeta = jets[i]->Eta();
        if (njetsize-i == ntag) // the number of remaining jets equals the ntags, so they must be tagged
        {
            if (jetflavor[i]==5) probability =sfb(jpt,jeta)*eb(jpt, jeta)*probdata(jets, jetflavor, ntag-1, i+1);
            else if (jetflavor[i]==4) probability =sfc(jpt,jeta)*ec(jpt, jeta)*probdata(jets, jetflavor, ntag-1, i+1);
            else probability =sfl(jpt,jeta)*el(jpt, jeta)*probdata(jets, jetflavor, ntag-1, i+1);
        }
        else if (ntag>0) {
            if (jetflavor[i]==5) {
                probability = sfb(jpt,jeta)*eb(jpt, jeta)*probdata(jets, jetflavor, ntag-1, i+1) // jet i tagged
                    + (1.0-sfb(jpt,jeta)*eb(jpt, jeta))*probdata(jets, jetflavor, ntag, i+1);  // jet i not tagged
            }
            else if (jetflavor[i]==4) {
                probability = sfc(jpt,jeta)*ec(jpt, jeta)*probdata(jets, jetflavor, ntag-1, i+1)
                    + (1.0-sfc(jpt,jeta)*ec(jpt, jeta))*probdata(jets, jetflavor, ntag, i+1);  // jet i not tagged
            }
            else {
                probability = sfl(jpt,jeta)*el(jpt, jeta)*probdata(jets, jetflavor, ntag-1, i+1)
                    + (1.0-sfl(jpt,jeta)*el(jpt, jeta))*probdata(jets, jetflavor, ntag, i+1);  // jet i not tagged
            }
        }
        else
        {
            if (jetflavor[i]==5) probability = (1.0-sfb(jpt,jeta)*eb(jpt, jeta))*probdata(jets, jetflavor, 0, i+1); // no tag
            else if (jetflavor[i]==4) probability = (1.0-sfc(jpt,jeta)*ec(jpt, jeta))*probdata(jets, jetflavor, 0, i+1); // no tag
            else probability = (1.0-sfl(jpt,jeta)*el(jpt, jeta))*probdata(jets, jetflavor, 0, i+1); // no tag
        }
    }
    return probability;
}
