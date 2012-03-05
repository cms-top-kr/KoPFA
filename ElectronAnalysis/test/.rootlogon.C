{
  gSystem->Load("libFWCoreFWLite.so");
  loadFWLite();
  AutoLibraryLoader::enable();
  gSystem->Load("libCintex.so");
  ROOT::Cintex::Cintex::Enable();
  defstyle();
}

