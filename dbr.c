#include <stdio.h>
#include "dbr.h"

#define DBR_NO_MEMORY 0
#define DBR_SUCCESS   1

// Barcode reader handler
void* hBarcode = NULL; 

/**
 * Create DBR instance
 */
int createDBR() 
{
    if (!hBarcode) {
        hBarcode = DBR_CreateInstance();
        if (!hBarcode)
        {
            printf("Cannot allocate memory!\n");
            return DBR_NO_MEMORY;
        }
    }

    return DBR_SUCCESS;
}

/**
 * Destroy DBR instance
 */
void destroyDBR()
{
    if (hBarcode) {
        DBR_DestroyInstance(hBarcode);
    }
}

/**
 * Set Dynamsoft Barcode Reader license.  
 * To get valid license, please contact support@dynamsoft.com
 * Invalid license is acceptable. With an invalid license, SDK will return an imcomplete result.
 */
int initLicense(const char* pszLicense)
{
    if (!createDBR()) 
    {
        return -1;
    }

	return DBR_InitLicenseEx(hBarcode, pszLicense);
}

char* createPyResults(SBarcodeResultArray *pResults)
{
    // Get barcode results
    int count = pResults->iBarcodeCount;
	SBarcodeResult** ppBarcodes = pResults->ppBarcodes;
    SBarcodeResult* tmp = NULL;
    int i = 0;
    for (; i < count; i++)
    {
        tmp = ppBarcodes[i];
        printf("Result: %s, Format: %s\n", tmp->pBarcodeData, tmp->pBarcodeFormatString);
    }

    // Release memory
    DBR_FreeBarcodeResults(&pResults);

    return NULL;
}

/**
 * Decode barcode from a file 
 */
char* decodeFile(const char* pFileName, int iFormat)
{
    if (!createDBR()) 
    {
        return NULL;
    }

    // Initialize Dynamsoft Barcode Reader
	int iMaxCount = 0x7FFFFFFF;
	SBarcodeResultArray *pResults = NULL;
	DBR_SetBarcodeFormats(hBarcode, iFormat);
	DBR_SetMaxBarcodesNumPerPage(hBarcode, iMaxCount);

    // Barcode detection
    int ret = DBR_DecodeFileEx(hBarcode, pFileName, &pResults);

    // Wrap results
    return createPyResults(pResults);
}

