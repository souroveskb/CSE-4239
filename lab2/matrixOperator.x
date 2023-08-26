struct Matrix {
     int nRows;
     int nColumns;
     double data[100];
};

struct Massage {
    Matrix A;
    Matrix B;
};

program MATRIX_OPERATIONS{
   version MATRIX_VERSION{
       Matrix addition(Massage)=1;
       Matrix multiplication(Massage)=2;
       Matrix transpose(Massage)=3;
       Matrix inverse(Massage)=4;
   }=1;
}=0x123456;

