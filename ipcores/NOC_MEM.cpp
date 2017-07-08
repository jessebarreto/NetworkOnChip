#include <vector>
#include <map>
#include <iostream>
#include "NOC_MEM.h"

#define size 0x40000000

using namespace std;

const int TASK_OK = 1; //true
const int TASK_FAIL = 0; //false
map<int, int> MEM;
enum cmd {read_mem=0, write_mem=1, move_mem=2};

nocmem::nocmem(sc_module_name name) :
    sc_module(name)
{
    
    SC_THREAD(notice);
    
}

void nocmem::notice(){
  while(true){
    int op_code;
    int adr;
    int adr2; 
    int num;
    int single_data;
    int aux_vec;
    vector<int> vec_data;
    op_code = memIn.read();
    if(op_code==read_mem){
      adr = memIn.read();
      num = memIn.read();
      if(num==1){
        if(mem_read(adr, &single_data)){
          memOut.write(TASK_OK);
          memOut.write(single_data);
          cout<<"leitura simples completa --->"<<single_data<<endl;
        }
        else{
          memOut.write(TASK_FAIL);
          cout<<"leitura simples falhou."<<endl;
        }
      }
      else if(num>1){
        if(mem_burst_read(adr, num, &vec_data)){
          memOut.write(TASK_OK);
          for(int s=0; s<num; s++)
            memOut.write(vec_data.at(s));
          cout<<"leitura em rajada completa."<<endl;
        }
        else{
          memOut.write(TASK_FAIL);
          cout<<"leitura em rajada falhou."<<endl;
        }
      }
    }
    else if(op_code==write_mem){
      adr = memIn.read();
      num = memIn.read();
      vec_data.clear();
      if(num==1){
        single_data= memIn.read();
        if(mem_write(adr, single_data)){
          memOut.write(TASK_OK);
          cout<<"escrita simples completa --->"<<single_data<<endl;
        }
        else{
          memOut.write(TASK_FAIL);
          cout<<"escrita simples falhou."<<endl;
        }
      }
      else if(num>1){
        for(int s=0; s<num; s++){
          //aux_vec = memIn.read();
          vec_data.push_back(memIn.read());
          cout<<vec_data.at(s)<<endl;
        }

        if(mem_burst_write(adr, num, &vec_data)){
          memOut.write(TASK_OK);
          for(int s=0; s<num; s++)
            memOut.write(vec_data.at(s));
          cout<<"escrita em rajada completa."<<endl;
        }
        else{
          memOut.write(TASK_FAIL);
          cout<<"escrita em rajada falhou."<<endl;
        };
      }
    }
    else if(op_code==move_mem){
      adr = memIn.read();
      num = memIn.read();
      adr2 = memIn.read();
      if(mem_move(adr, num, adr2)){
        memOut.write(TASK_OK);
        cout<<"traslacao de memoria completa."<<endl;
      }
      else{
        memOut.write(TASK_FAIL);
        cout<<"translacao de memoria falhou.";
      }
    }
  }

}

bool nocmem::mem_read(int ad, int *data){
  if((ad%4)!=0)
    return false;

  ad = ad/4;
  if(ad>=0 && ad<size){
    *data = MEM.find(ad)->second;
    return true;
  }
  else
    return false;
}

bool nocmem::mem_write(int ad, int data){
  if((ad%4)!=0)
    return false;

  ad = ad/4;
  if(ad>=0 && ad<size){
    MEM[ad] = data;
    return true;
  }
  else
    return false;
}

bool nocmem::mem_burst_write(int start_ad, int tam, vector<int> *w_data){
  int end_ad;

  if((start_ad%4)!=0)
    return false;

  start_ad = start_ad/4;
  end_ad = start_ad+tam;
  w_data->resize(tam+1);
  if(start_ad>=0 && end_ad<size){
    cout<< "escrevendo:" << endl;
    for(ulong k=start_ad; k<end_ad; k++){
      MEM[k] = w_data->at(k-start_ad);
      cout<< start_ad << "--->" << w_data->at(k-start_ad) << "--->" << MEM.find(k)->second << endl;
    }
    return true;
  }
  else
    return false;
}

bool nocmem::mem_burst_read(int start_ad, int tam, vector<int> *r_data){
  int end_ad;

  if((start_ad%4)!=0)
    return false;

  start_ad = start_ad/4;
  end_ad = start_ad+tam;
  r_data->resize(tam+1);
  if(start_ad>=0 && end_ad<size){
    cout<< "lendo:" << endl;
    for(int k=start_ad; k<end_ad; k++){
      r_data->at(k-start_ad) = MEM.find(k)->second;
      cout<< k-start_ad << "--->" << MEM.find(k)->second << endl;
    }
    return true;
  }
  else
    return false;
}

bool nocmem::mem_move(int start_ad, int tam, int end_ad){
  if((start_ad%4)!=0)
    return false;
  if((end_ad%4)!=0)
    return false;

  start_ad = start_ad/4;
  end_ad = end_ad/4;
  if(start_ad>=0 && end_ad<size){
    for(int k=0; k<tam; k++){
      MEM[end_ad+k] = MEM.find(start_ad+k)->second;
      cout<<"dado da memoria "<<(start_ad+k)*4<<" passado para memoria "<<(end_ad+k)*4<< endl;
    }
    return true;
  }
  else
    return false;
}