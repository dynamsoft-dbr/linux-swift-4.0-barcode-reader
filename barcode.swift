
let count = CommandLine.arguments.count
if count < 2 {
    print("Please add a file name. E.g. ./barcode test.tif")
}
else {
    let fileName = CommandLine.arguments[1]

    createDBR()
    let ret = initLicense("t0068MgAAAGvV3VqfqOzkuVGi7x/PFfZUQoUyJOakuduaSEoI2Pc8+kMwjrojxQgE5aJphmhagRmq/S9lppTkM4w3qCQezxk=")
    if ret == 0 {
        // Read barcode
        let barcodeTypes : Int32 = 0x3FF | 0x2000000 | 0x8000000 |
                    0x4000000;  // 1D, QRCODE, PDF417, DataMatrix
        decodeFile(fileName, barcodeTypes);
    }
    destroyDBR()
}
