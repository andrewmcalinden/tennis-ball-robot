
#include "tinyxml2.h"
#include <cstdlib>
#include <string>
#include <ctime>
#include <assert.h>

using namespace tinyxml2;
using namespace std;

#ifndef XMLCheckResult
        #define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif


//=============================================
//=============================================

int xmlm3_CEAN_Scope_channel( XMLElement * pRoot) {
  printf("\nIn xmlm3_CEAN_Scope_channel()..\n");
  assert(pRoot);
  XMLElement * pElement; XMLError  eResult;
  //......   unpack attributs
  int chanId; bool  enabled;
  eResult= pRoot->QueryIntAttribute("id",&chanId);
  XMLCheckResult(eResult);
  eResult= pRoot->QueryBoolAttribute("enabled",&enabled);
  XMLCheckResult(eResult); 
  printf("channelID=%d,  enabled=%d Description:\n%s\n\n",chanId,enabled,pRoot->GetText());
  if(!enabled) {
    printf(" SKIP detailes for disabled scope_channel %d\n",chanId);
    return 0;
  }


  string nameL[]={"post_trigger","num_events_BLT","link_board","conet_node","connection_type"};
  for(int i=0; i<5; i++){
    int iVal;
    pElement = pRoot->FirstChildElement(nameL[i].data());
    if (!pElement) return XML_ERROR_PARSING_ELEMENT;
    if(i>=4) break;
    eResult = pElement->QueryIntText(&iVal);
    XMLCheckResult(eResult);
    printf("i=%d '%s' =%d\n",i,nameL[i].data(),iVal);
  }

  string connType=pElement->GetText();
  printf(" connextion_type='%s'\n",connType.data());

}


//=============================================
//=============================================

int xmlm3_CEAN_Scope( XMLElement * pRoot) {
  printf("\nIn xmlm3_CEAN_Scope()..\n");
  assert(pRoot);
  XMLElement * pElement; XMLError  eResult;
  //......   unpack attributs
  bool  enabled;
  eResult= pRoot->QueryBoolAttribute("enabled",&enabled);
  XMLCheckResult(eResult);
  printf("enabled=%d,  Description:\n%s\n\n",enabled,pRoot->GetText());
  if(!enabled) {
    printf(" SKIP detailes for disabled scope\n");
    return 0;
  }

  string nameL[]={"buffer_size","record_length","nboards"};

  for(int i=0; i<3; i++){
    int iVal;
    pElement = pRoot->FirstChildElement(nameL[i].data());
    if (!pElement) return XML_ERROR_PARSING_ELEMENT;
    eResult = pElement->QueryIntText(&iVal);
    XMLCheckResult(eResult);
    printf("i=%d '%s' =%d\n",i,nameL[i].data(),iVal);
  }

  //.... unpacking list of elements using iterator
  XMLElement * pListElement = pRoot->FirstChildElement("channel");
  if (!pListElement) return XML_ERROR_PARSING_ATTRIBUTE;
  while (pListElement) {
    xmlm3_CEAN_Scope_channel(pListElement);
    // move to next element
    pListElement = pListElement->NextSiblingElement("channel");
  }
   
}

//=============================================
//=============================================

int xmlm3_CCD_Camera( XMLElement * pRoot) {
  printf("\nIn xmlm3_CCD_Camera()..\n");
  assert(pRoot);
  XMLElement * pElement; XMLError  eResult;
  printf("Description:\n%s\n\n",pRoot->GetText());
  
  string nameL[]={"xbin","ybin","exposure","temp","bufferSize","nFlushes"};

  for(int i=0; i<6; i++){
    int iVal;
    pElement = pRoot->FirstChildElement(nameL[i].data());
    if (!pElement) return XML_ERROR_PARSING_ELEMENT;
    eResult = pElement->QueryIntText(&iVal);
    XMLCheckResult(eResult);
    printf("i=%d '%s' =%d\n",i,nameL[i].data(),iVal);
  }
    
}

//=============================================
//=============================================

int xmlm3_runOptions( XMLElement * pRoot) {
  printf("In xmlm3_runOptions()..\n");
  assert(pRoot);
  XMLError  eResult; XMLElement * pElement;
  
  pElement = pRoot->FirstChildElement("outDir");
  if (!pElement) return XML_ERROR_PARSING_ELEMENT;
  std::string outDir=pElement->GetText();
  assert(outDir.size()>0); // probably null string provided
  //    printf("set outDir:%s: \n",outDir.data());
  
  pElement = pRoot->FirstChildElement("runTag");
  if (!pElement) return XML_ERROR_PARSING_ELEMENT;
  std::string runTag=pElement->GetText();
  assert(runTag.size()>0); // probably null string provided
  
  //......   unpack attributs
  bool fakeCameras, enableFliProline;
  int verbose;
  
  eResult= pRoot->QueryIntAttribute("verbose",&verbose);
  XMLCheckResult(eResult);
  
  eResult= pRoot->QueryBoolAttribute("fakeCameras",&fakeCameras);
  XMLCheckResult(eResult);
  
  eResult = pRoot->QueryBoolAttribute("enableFliProline",&enableFliProline);
  XMLCheckResult(eResult);
  
  printf("set outDir:%s:  runTag:%s: \nattributs: fakeCameras=%d  enableFliProline=%d  verbose=%d\n",outDir.data(),runTag.data(),fakeCameras,enableFliProline,verbose);
  return XML_SUCCESS;
}



//=============================================
//    M A I N 
//=============================================

int main( int argc, const char ** argv ){
  assert(argc > 1 );  

  const char *inpName= argv[1];
  printf("Opening %s ...\n", inpName);
  XMLDocument* doc = new XMLDocument( true, COLLAPSE_WHITESPACE);

  XMLError eResult =doc->LoadFile( inpName);
  printf( "XML file '%s' read-in, ErrorID=%d\n", inpName,  eResult );    
  assert(!eResult);

  printf("processing %s ...\n", argv[1]);  
  XMLElement *  pRoot = doc->FirstChildElement("m3RunCfg");
  if (!pRoot) return XML_ERROR_FILE_READ_ERROR;
  printf("found head of m3 run cfg  description:\n%s\n\n",pRoot->GetText());
  xmlm3_runOptions(pRoot);

  XMLElement *  pElement =pRoot->FirstChildElement("CCD_Camera");
  if (!pRoot) return XML_ERROR_FILE_READ_ERROR;
  xmlm3_CCD_Camera(pElement);

  pElement =pRoot->FirstChildElement("CEAN_Scope");
  if (!pRoot) return XML_ERROR_FILE_READ_ERROR;
  xmlm3_CEAN_Scope(pElement);
  
  printf("\n end of parsing of %s\n",inpName);
  return 1;  
}
