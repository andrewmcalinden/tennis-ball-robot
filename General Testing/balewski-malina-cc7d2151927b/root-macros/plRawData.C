plRawData( char *fname="raw1.dat"){

  int nb=300;
  TH1F *h=new TH1F("raw","ADC vs. time; time bins; ADC ",nb,0,nb);
  h->SetMinimum(-2);

  FILE *fp =   fopen(fname, "rb"); assert(fp);
  enum {mx=1000};
  char buf[mx];
  char *ret=0; 
  int nl=0;
  int ix,iy;
  while(  fgets( buf, mx, fp)) {
    nl++;
    if (strstr(buf,"#")>0) continue;
    int nv=sscanf(buf,"%d %d",&ix,&iy);
    //printf("nv=%d %d %d\n",nv,ix,iy);
    h->Fill(ix,iy);
    if(ix>nb) break;
  }
  fclose(fp);

  c=new TCanvas("aa","aa",600,350);
  h->Draw();
}
