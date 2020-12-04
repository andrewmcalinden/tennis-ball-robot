#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

int main()
{
    std::filebuf fb;
  if (fb.open ("test.txt",std::ios::in))
  {
    std::istream is(&fb);
    while (is)
      std::cout << char(is.get());
    fb.close();
  
    const char * c;
    //c = "";
    
    
    cout << "xpress";
    while(true){

        getline(cin, c);

        if ((strcmp(c, "run")==0)){
            cout << "x";
        }
    
    }
  }
}
