// reads one leaf directly from the tree
{
 TChain *chain = new TChain("Hel_Tree");  
 chain->Add("./Qweak_1234.000.root");
 chain->Print();
 chain->Show(0); // event id startting from 0
 Double_t *Z=chain->GetLeaf("beam_nx/hw_sum")->GetValuePointer();
 chain->GetEntry(0);
 printf("Z=%f\n",*Z);

}
