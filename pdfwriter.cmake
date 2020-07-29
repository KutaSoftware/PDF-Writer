add_library(PDFWriter STATIC IMPORTED)
set_target_properties(PDFWriter PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/libPDFWriter.a)
target_link_libraries(PDFWriter
        INTERFACE
        #${CMAKE_CURRENT_LIST_DIR}/lib/libLibJpeg.a
        ${CMAKE_CURRENT_LIST_DIR}/lib/libLibAesgm.a
        ${CMAKE_CURRENT_LIST_DIR}/lib/libFreeType.a
        ${CMAKE_CURRENT_LIST_DIR}/lib/libLibPng.a
        ${CMAKE_CURRENT_LIST_DIR}/lib/libLibTiff.a
        ${CMAKE_CURRENT_LIST_DIR}/lib/libZlib.a
        )

target_include_directories(PDFWriter INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/include/PDFWriter
        ${CMAKE_CURRENT_LIST_DIR}/include/LibTiff
        )
