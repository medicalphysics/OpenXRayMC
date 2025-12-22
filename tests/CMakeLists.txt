set(TEST_SOURCES "testqtgraph.cpp")


foreach(sourcefile ${TEST_SOURCES})
    get_filename_component(filename ${sourcefile} NAME_WLE)
    add_executable(${filename} ${sourcefile})    
    target_link_libraries(${filename} 
    libxraymc 
    Qt${QT_VERSION_MAJOR}::Widgets
	Qt${QT_VERSION_MAJOR}::Core
	Qt${QT_VERSION_MAJOR}::Gui
	Qt${QT_VERSION_MAJOR}::Graphs )
    add_test(NAME ${filename} COMMAND ${filename})    
   
endforeach()