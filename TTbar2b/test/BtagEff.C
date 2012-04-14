void CSVBtagEff(TString workingpoint){

    double x = 0; 

    if( workingpoint == "L"){
      x = 0.244; 
    }else if ( workingpoint == "M") {
      x = 0.679;
    }else if ( workingpoint == "T") {
      x = 0.898;
    }

    cout << "Working point = " << workingpoint << endl;

    double effb_data = -6.41591823466*x*x*x*x +  11.5812173893*x*x*x +  -6.94406444589*x*x +  1.13278339944*x +  0.889359753365;
    double effb_data_err_max = 0.00534302322474*x*x*x*x + -0.0244344541087*x*x*x + -0.0713621208038*x*x + 0.204715260085*x + 0.612116989996;
   
    cout << "DATA" << endl;
    cout << "b tagging efficiency= " << effb_data << " err= " << effb_data_err_max << endl;

    double effb = -1.73338329789*x*x*x*x +  1.26161794785*x*x*x +  0.784721653518*x*x +  -1.03328577451*x +  1.04305075822;
    double effc = -1.5734604211*x*x*x*x +  1.52798999269*x*x*x +  0.866697059943*x*x +  -1.66657942274*x +  0.780639301724;

    cout << "MC" << endl;
    cout << "b tagging efficiency= " << effb << endl ;
    cout << "c tagging efficiency= " << effc << endl;
  
}


void BtagEff(){

  CSVBtagEff("L");
  CSVBtagEff("M");
  CSVBtagEff("T");

}
