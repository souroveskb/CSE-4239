struct Matrix{
     int nRows;
     int nColumns;
     float data[1000];
};

struct Input{
    
    int numOfMatrices;
    Matrix matrices[2];
};

struct Output{
    
    Matrix result;
    int errorCode;
    char errorMessage[50];

};

program MATRIX_OPERATIONS{
   version MATRIX_VERSION{
       Output add(Input)=1;
       Output multiply(Input)=2;
       Output inverse(Input)=3;
       Output transpose(Input)=4;        
   }=1;
}=0x18771877;