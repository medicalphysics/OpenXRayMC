
qt_add_library(libopenxraymc STATIC	
	basepipeline.cpp
	beamsettingsview.cpp
	beamsettingsmodel.cpp
	beamactorcontainer.cpp
	beamsettingsdelegate.cpp
	bowtiefilterreader.cpp
	datacontainer.cpp	
	ctimageimportpipeline.cpp
	ctorgansegmentatorpipeline.cpp
	ctsegmentationpipeline.cpp
	ctaecplot.cpp
	colormaps.cpp
	custominteractorstyleimage.cpp
	dosetablepipeline.cpp
	dosetablewidget.cpp
	hdf5wrapper.cpp
	h5io.cpp	
	niftiwrapper.cpp
	icrpphantomimportpipeline.cpp
	otherphantomimportpipeline.cpp
	renderwidgetscollection.cpp	
	slicerenderwidget.cpp		
	simulationpipeline.cpp
	simulationwidget.cpp
	volumerenderwidget.cpp
	volumerendersettingswidget.cpp
	volumelutwidget.cpp
	volumerendersettings.cpp
	xraymc_specialization.cpp
	)

# We expose headers for all targets consuming libopenxraymc
target_include_directories(libopenxraymc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Adding HDF5 headers internally for libopenxraymc, maybe move to its own library?
target_include_directories(libopenxraymc PRIVATE ${HDF5_INCLUDE_DIRS})
target_compile_definitions(libopenxraymc PRIVATE ${HDF5_DEFINITIONS})

target_link_libraries(libopenxraymc PUBLIC	
	Qt${QT_VERSION_MAJOR}::Widgets
	Qt${QT_VERSION_MAJOR}::Core
	Qt${QT_VERSION_MAJOR}::Gui
	Qt${QT_VERSION_MAJOR}::Charts
	Qt${QT_VERSION_MAJOR}::Concurrent
	libxraymc	
	VTK::CommonCore
	VTK::GUISupportQt
	VTK::DICOM
	VTK::RenderingImage
	VTK::RenderingVolumeOpenGL2
	VTK::ImagingStatistics
	VTK::IOExodus
	VTK::jsoncpp
	VTK::InteractionImage
	VTK::InteractionStyle
	VTK::ImagingGeneral
	VTK::CommonColor
	VTK::RenderingAnnotation
	PRIVATE	
	${HDF5_LIBRARIES}
	)

if(${OPENXRayMC_USECTSEGMENTATOR})
	target_link_libraries(libopenxraymc PRIVATE libctsegmentator)
	target_compile_definitions(libopenxraymc PRIVATE USECTSEGMENTATOR=1)
endif()

# Rather than defining a single `VTK_DEFINITIONS` for use by all relevant
# targets, the definitions are made as needed with the exact set needed for the
# listed modules.
vtk_module_autoinit(
	TARGETS libopenxraymc
	MODULES
	VTK::CommonCore
	VTK::GUISupportQt
	VTK::DICOM
	VTK::RenderingVolumeOpenGL2
	VTK::ImagingStatistics
	VTK::IOExodus	
	VTK::jsoncpp
	VTK::InteractionImage
	VTK::InteractionStyle
	VTK::ImagingGeneral
	VTK::RenderingImage
	VTK::CommonColor
	VTK::RenderingAnnotation
)