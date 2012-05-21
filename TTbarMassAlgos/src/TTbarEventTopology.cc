#include "KoPFA/TTbarMassAlgos/interface/TTbarEventTopology.h"
#include "KoPFA/DataFormats/interface/Maos.h"

#include <iostream>

TTbarEventTopology::TTbarEventTopology()
{
  std::vector<double> nuPars(5);
  nuPars[0] = 30.7137;
  nuPars[1] = 56.2880;
  nuPars[2] = 23.0744;
  nuPars[3] = 59.1015;
  nuPars[4] = 24.9145;
  kinSolver_ = new TtFullLepKinSolver(0, 250, 1, nuPars);
}

TTbarEventTopology::~TTbarEventTopology()
{
  if ( kinSolver_ ) delete kinSolver_;
}

void TTbarEventTopology::set(const reco::Candidate* l1, const reco::Candidate* l2,
                             const reco::Jet* j1, const reco::Jet* j2,
                             const reco::MET* met)
{
  if ( !l1 or !l2 or !j1 or !l2 or !met ) return;

  l1_ = l1->p4();
  l2_ = l2->p4();
  j1_ = j1->p4();
  j2_ = j2->p4();
  met_ = reco::Candidate::LorentzVector(met->px(), met->py(), 0, met->pt());

  vis11_ = l1_+j1_;
  vis12_ = l1_+j2_;
  vis21_ = l2_+j1_;
  vis22_ = l2_+j2_;

  combination_nwt_ = 0;
  combination_maos_ = 0;
  combination_kin_ = 0;
  metErr_ = 1.0;
}

void TTbarEventTopology::solve()
{
  solveNWT();
  solveMAOS();
  solveSymbolic();
  solveKin();
}

reco::Candidate::LorentzVector TTbarEventTopology::vsum()
{
  return vis11_+vis22_+met_;
}

reco::Candidate::LorentzVector TTbarEventTopology::nwt()
{
  return vis11_+vis22_+nu1_nwt_+nu2_nwt_;
}

reco::Candidate::LorentzVector TTbarEventTopology::maos()
{
  return vis11_+vis22_+nu1_maos_+nu2_maos_;
}

reco::Candidate::LorentzVector TTbarEventTopology::kin()
{
  return vis11_+vis22_+nu1_kin_+nu2_kin_;
}

void TTbarEventTopology::solveNWT()
{
  const double mTopMin = 0;
  const double mTopMax = 200;

  // Scan over top mass
  double maxWeight = -999;
  reco::Candidate::LorentzVector nuASol, nuBSol;
  int combination = 0;

  for ( double mTop = mTopMin; mTop <= mTopMax; mTop += 1 )
  {
    for ( double eta1 = -3; eta1 <= 3; eta1 += 0.1 )
    {
      std::vector<reco::Candidate::LorentzVector> nu11Sol;
      std::vector<reco::Candidate::LorentzVector> nu12Sol;
      solveNu(eta1, mTop, l1_, j1_, nu11Sol);
      solveNu(eta1, mTop, l1_, j2_, nu12Sol);

//if ( !nu11Sol.empty() ) std::cout << (nu11Sol[0]+l1_).mass() << std::endl;

      for ( double eta2 = -3; eta2 <= 3; eta2 += 0.1 )
      {
        std::vector<reco::Candidate::LorentzVector> nu22Sol;
        std::vector<reco::Candidate::LorentzVector> nu21Sol;

        solveNu(eta2, mTop, l2_, j2_, nu22Sol);
        solveNu(eta2, mTop, l2_, j1_, nu21Sol);

        for ( int i=0, n=nu11Sol.size(); i<n; ++i )
        {
          for ( int j=0, m=nu22Sol.size(); j<m; ++j )
          {
            double w = 1;
            w *= exp(-0.5*sqr((nu11Sol[i].px() + nu22Sol[j].px() - met_.px())/metErr_));
            w *= exp(-0.5*sqr((nu11Sol[i].py() + nu22Sol[j].py() - met_.py())/metErr_));

            if ( w > maxWeight )
            {
              maxWeight = w;
              combination = 1;
              nuASol = nu11Sol[i];
              nuBSol = nu22Sol[j];
            }
          }
        }

        for ( int i=0, n=nu12Sol.size(); i<n; ++i )
        {
          for ( int j=0, m=nu21Sol.size(); j<m; ++j )
          {
            double w = 1;
            w *= exp(-0.5*sqr((nu12Sol[i].px() + nu21Sol[j].px() - met_.px())/metErr_));
            w *= exp(-0.5*sqr((nu12Sol[i].py() + nu21Sol[j].py() - met_.py())/metErr_));

            if ( w > maxWeight )
            {
              maxWeight = w;
              combination = -1;
              nuASol = nu12Sol[i];
              nuBSol = nu21Sol[j];
            }
          }
        }
      }
    }
  }

  combination_nwt_ = combination;
  if ( combination != 0 )
  {
    nu1_nwt_ = nuASol;
    nu2_nwt_ = nuBSol;
  }

}

void TTbarEventTopology::solveNu(const double eta, const double mTop, 
                                 const reco::Candidate::LorentzVector& lep,
                                 const reco::Candidate::LorentzVector& jet,
                                 std::vector<reco::Candidate::LorentzVector>& nuSol)
{
  nuSol.clear();

  const double mBot = 5.0;
  const double mW = 80.2;
  const double mLep = lep.mass();

  static const double alfa = (mTop*mTop - mBot*mBot - mW*mW)/2;
  static const double beta = (mW*mW - mLep*mLep)/2;

  const double fb = TMath::Hypot(jet.P(), mBot)*sinh(eta)-jet.pz()*cosh(eta);
  const double fl = lep.energy()*sinh(eta)-lep.pz()*cosh(eta);

  if ( fb == 0 or fl == 0 ) return;

  const double ab = jet.px()/fb;
  const double bb = jet.py()/fb;
  const double cb = alfa/fb;
  const double al = lep.px()/fl;
  const double bl = lep.py()/fl;
  const double cl = beta/fl;

  if ( ab == al ) return;

  const double k = (bl-bb)/(ab-al);
  const double e = (cl-cb)/(ab-al);

  const double a = k*k*(ab*ab-1) + bb*bb -1; 
  const double b = e*k*(ab*ab-1) + ab*cb*k + bb*cb;
  const double c = (ab*ab-1)*e*e + 2*e*ab*cb + cb*cb;
  // Now solve ax^2 + 2bx + c = 0

  if ( a == 0 )
  {
    if ( b == 0 ) return;

    const double py = -c/2/b;
    const double px = k*py + e;
    const double pz = TMath::Hypot(px, py)*cosh(eta);
    const double e = sqrt(px*px + py*py + pz*pz);

    nuSol.push_back(reco::Candidate::LorentzVector(px, py, pz, e));

    return;
  }

  const double detsq = b*b-a*c;

  if ( detsq < 0 ) return;
  else if ( detsq == 0 )
  {
    const double py = -b/a;
    const double px = k*py + e;
    const double pz = TMath::Hypot(px, py)*cosh(eta);
    const double e = sqrt(px*px + py*py + pz*pz);

    nuSol.push_back(reco::Candidate::LorentzVector(px, py, pz, e));

    return;
  }
  else
  {
    const double py1 = (-b+sqrt(detsq))/a;
    const double py2 = (-b-sqrt(detsq))/a;

    const double px1 = k*py1 + e;
    const double px2 = k*py2 + e;

    const double pz1 = 0;//TMath::Hypot(px1, py1)*cosh(eta);
    const double pz2 = 0;//TMath::Hypot(px2, py2)*cosh(eta);

    const double e1 = TMath::Hypot(px1, py1);//*sinh(eta); //sqrt(px1*px1 + py1*py1 + pz1*pz1);
    const double e2 = TMath::Hypot(px2, py2);//*sinh(eta); //sqrt(px2*px2 + py2*py2 + pz2*pz2);

    nuSol.push_back(reco::Candidate::LorentzVector(px1, py1, pz1, e1));
    nuSol.push_back(reco::Candidate::LorentzVector(px2, py2, pz2, e2));

//using namespace std;
//cout << nuSol[0].mass() << ' ' << nuSol[1].mass() << ' ' << (nuSol[0]+lep).mass() << ' ' << (nuSol[1]+lep).mass() << endl;

    return;
  }

  return;
}

void TTbarEventTopology::solveMAOS()
{
  static Ko::Maos maos1, maos2;
  const double m1 = sqrt(maos1.MAOS(convLV(met_), convLV(vis11_), convLV(vis22_), 0, 0, false));
  const double m2 = sqrt(maos2.MAOS(convLV(met_), convLV(vis12_), convLV(vis21_), 0, 0, false));
  //const double m = sqrt(maos.MAOS(convLV(met_), convLV(l1_), convLV(l2_), 0, 0, false));

  if ( m1 < m2 )
  {
    combination_maos_ = 1;
    nu1_maos_ = convLV(maos1.leg1());
    nu2_maos_ = convLV(maos1.leg2());
    mt2_maos_ = m1;
  }
  else
  {
    combination_maos_ = -1;
    nu1_maos_ = convLV(maos2.leg1());
    nu2_maos_ = convLV(maos2.leg2());
    mt2_maos_ = m2;
  }
}

void TTbarEventTopology::solveSymbolic()
{
  double b1  = j1_.E();
  double bt1 = j1_.Et();
  double bx1 = j1_.Px();
  double by1 = j1_.Py();
  double bz1 = j1_.Pz();

  double b2  = j2_.E();
  double bt2 = j2_.Et();
  double bx2 = j2_.Px();
  double by2 = j2_.Py();
  double bz2 = j2_.Pz();

  double e1  = l1_.E();
  double pt1 = l1_.Et();
  double px1 = l1_.Px();
  double py1 = l1_.Py();
  double pz1 = l1_.Pz();

  double e2  = l2_.E();
  //double pt2 = le2.Et();
  double px2 = l2_.Px();
  double py2 = l2_.Py();
  double pz2 = l2_.Pz();

  double Met = met_.Pt();
  double Mex = met_.Px();
  double Mey = met_.Py();

  double invmass2 = 3*b1*b2 + b2*bt2 - bt2*bz2 - bz1*bz2 + 2*b2*e1 + 4*b1*e2 + 5*e1*e2 + 4*bt2*Met + 4*e1*Met + e2*Met - (bx1 + bx2)*Mex - 2*by2*Mey + bt2*pt1 + by1*px1 - 2*Mex*px1 - (bx1 + bx2)*px2 - 2*Mex*px2 - 3*Mey*py1 - 2*Mey*py2 - 3*((bx1 + bx2)*Mex + by1*py2) + 4*Met*(bt1 - pz1) - bz2*(bz1 + pz1) + (-bz2 - py2)*(bz1 + pz1) + (bz1 + pz1)*(py2 - pz2) - 2*(bz1 + pz1)*pz2 - (bt1 + bz1 + 2*pz1)*pz2;

  m_symb_ = sqrt(invmass2);  
}

void TTbarEventTopology::solveKin()
{
  const double x = l1_.px() + l2_.px() + j1_.px() + j2_.px() + met_.px();
  const double y = l1_.py() + l2_.py() + j1_.py() + j2_.py() + met_.py();
  
  kinSolver_->SetConstraints(x, y);
  TtFullLepKinSolver::NeutrinoSolution nuSol1 = kinSolver_->getNuSolution(convLV(l1_), convLV(l2_), convLV(j1_), convLV(j2_));
  TtFullLepKinSolver::NeutrinoSolution nuSol2 = kinSolver_->getNuSolution(convLV(l1_), convLV(l2_), convLV(j2_), convLV(j1_));

  const double weight1 = nuSol1.weight;
  const double weight2 = nuSol2.weight;

  if ( weight1 > 0 and weight1 > weight2 )
  {
    combination_kin_ = 1;
    nu1_kin_ = nuSol1.neutrino.p4();
    nu2_kin_ = nuSol1.neutrinoBar.p4();
    weight_kin_ = weight1;
  }
  else if ( weight2 > 0 and weight2 > weight1 ) 
  {
    combination_kin_ = -1;
    nu1_kin_ = nuSol2.neutrino.p4();
    nu2_kin_ = nuSol2.neutrinoBar.p4();
    weight_kin_ = weight2;
  }
  else
  {
    combination_kin_ = 0;
  }
}
