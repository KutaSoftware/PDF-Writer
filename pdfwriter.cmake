add_library(pdfwriter STATIC IMPORTED)
set_target_properties(pdfwriter PROPERTIES IMPORTED_LOCATION ${CMAKE_DEPS}/pdfwriter/lib/libPDFWriter.a)
target_link_libraries(pdfwriter
        INTERFACE
        ${CMAKE_DEPS}/pdfwriter/lib/libLibJpeg.a
        ${CMAKE_DEPS}/pdfwriter/lib/libLibAesgm.a
        ${CMAKE_DEPS}/pdfwriter/lib/libFreeType.a
        ${CMAKE_DEPS}/pdfwriter/lib/libLibPng.a
        ${CMAKE_DEPS}/pdfwriter/lib/libLibTiff.a
        ${CMAKE_DEPS}/pdfwriter/lib/libZlib.a
        )

target_include_directories(pdfwriter INTERFACE
        ${CMAKE_DEPS}/pdfwriter/include/PDFWriter
        ${CMAKE_DEPS}/pdfwriter/include/LibTiff
        )