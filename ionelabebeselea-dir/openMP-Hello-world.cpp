#include <omp.h> 
  
#include<iostream>
using namespace std;
  
int main(int argc, char* argv[]) 
{  
    #pragma omp parallel 
    { 
        cout<<"Hello World... from thread = ";
	cout<< omp_get_thread_num() <<endl; 
    } 
} 
