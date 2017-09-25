#include "DynamsoftBarcodeReader.h"

int initLicense(const char* pszLicense);
char* decodeFile(const char* pFileName, int iFormat);
int createDBR();
void destroyDBR();