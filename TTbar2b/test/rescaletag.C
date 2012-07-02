// B-tag reweighting tool
// Author: Suyong Choi
// Created: June 5 2012

#include <vector>
#include "TLorentzVector.h"
#include <iostream>

using namespace std;

double probmc(const std::vector<TLorentzVector *> &jets, const std::vector<int> &jetflavor, int ntag, int fromi=0);
double probdata(const std::vector<TLorentzVector *> &jets, const std::vector<int> &jetflavor, int ntag, int fromi=0);

// Data/MC b-tag scale factor
double sfb(double pt, double eta)
{
    return 0.9;
}

// data/mc c-tag scale factor
double sfc(double pt, double eta)
{
    return 1.0;
}

// data/mc l-tag scale factor
double sfl(double pt, double eta)
{
    return 1.0;
}

// MC b-tag efficiency
double eb(double pt, double eta)
{
    return 0.6;
}

//MC c-tag efficiency
double ec(double pt, double eta)
{
    return 0.2;
}

//MC l-tag efficiency
double el(double pt, double eta)
{
    return 0.1;
}

double reweight(const std::vector<TLorentzVector *> &jets, const std::vector<int> &jetflavor, int ntag)
{
    double pmc = probmc(jets, jetflavor, ntag);
    double pdata = probdata(jets, jetflavor, ntag);

    return pdata/pmc;
}

// prepare a vector of pointers to TLorentzVector and jet flavors
// use recursion
double probmc(const std::vector<TLorentzVector *> &jets, const std::vector<int> &jetflavor, int ntag, int fromi)
{
    // something doesn't match
    if (jetflavor.size() != jets.size()) return 0.0;
    // can't have more ntags than the number of jets
    if (jets.size() < ntag) return 0.0;
    if (fromi>=jets.size()) return 1.0; // stopping condition for recursion

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
double probdata(const std::vector<TLorentzVector *> &jets, const std::vector<int> &jetflavor, int ntag, int fromi)
{
    // something doesn't match
    if (jetflavor.size() != jets.size()) return 0.0;
    // can't have more ntags than the number of jets
    if (jets.size() < ntag) return 0.0;
    if (fromi>=jets.size()) return 1.0; // stopping condition for recursion

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


// a test routine
void testrescaletag()
{
    std::vector<TLorentzVector *> jet(4);
    std::vector<int> jetflavor(4);

    for (int i=0; i<4; i++)
    {
        jet[i] = new TLorentzVector(1.0, 1.0, 1.0, 5.0);
    }

    cout << jet.size() << endl;
    jetflavor[0]=5;
    jetflavor[1]=5;
    jetflavor[2]=1;
    jetflavor[3]=1;

    double mc, data;
    for (int i=0; i<=4; i++)
    {
        mc = probmc(jet, jetflavor, i);
        data = probdata(jet, jetflavor, i);
        cout << i << " tag " << mc << " " << data << " rescale weight = " << data/mc <<  endl;
    }

}
