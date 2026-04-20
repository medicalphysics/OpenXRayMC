# OpenXRayMC
Monte Carlo radiation dose scoring application for diagnostic x-ray imaging

OpenXRayMC is an application for calculation and visualization of dose distributions in diagnostic x-ray examinations. Its primary audience are medical physicists and researchers who want to perform Monte Carlo dose calculations for typical diagnostic x-ray examinations except mammography. The Monte Carlo code is not yet validated and use of this application should be for educational purposes only.

Dose calculations are done by a Monte Carlo method for voxelized geometry. Only photons are modelled and essentially only KERMA is scored. The application supports dose calculations on CT series of individual patients and standard human reference phantoms made by ICRP (see report [110](https://www.icrp.org/publication.asp?id=ICRP%20Publication%20110) and [143](https://journals.sagepub.com/doi/full/10.1177/0146645320915031)). Source code for the simulation library can be found at https://github.com/medicalphysics/XRayMClib.

![Dose calculation of dual source Flash scan](docs/screenshot/dethorax.png?raw=true)
Screenshot of dose calculation from a dual source CT scanner. The simulation shows radiation dose deposited in a patient from a dual source coronary angiography scan technique.

Please do not hesitate if you encounter bugs or errors in the application, or simply missing a feature. The easiest way to report bugs or feature requests is to open an issue: https://github.com/medicalphysics/OpenXRayMC/issues.

## Installation
Precompiled binaries are distributed for Windows 64 bits only and may be obtained here: https://github.com/medicalphysics/OpenXRayMC/releases

## Build from source
OpenXRayMC requires a C++23 compiler and is built with CMake. It depends on the following libraries:

* **VTK Visualization Toolkit**: https://vtk.org/. OpenXRayMC is tested with VTK version 9.3. When building VTK, set the flag `VTK_MODULE_ENABLE_vtkDICOM` to `YES` since OpenXRayMC requires this module. Recommended VTK CMake options:
  ```
  -DVTK_SMP_ENABLE_SEQUENTIAL:BOOL="0"
  -DVTK_SMP_IMPLEMENTATION_TYPE:STRING="STDThread"
  -DCMAKE_CXX_MP_FLAG:BOOL="1"
  -DVTK_ENABLE_KITS:BOOL="1"
  -DVTK_MODULE_ENABLE_VTK_vtkDICOM:STRING="YES"
  -DVTK_MODULE_ENABLE_VTK_GUISupportQt:STRING="YES"
  ```
* **Qt**: https://www.qt.io/, version >= 6.7.
* **HDF5**: https://www.hdfgroup.org/.
* **LibTorch** (optional): https://pytorch.org/get-started/locally/, version >= 2.3.1, required for CT organ segmentation.

The simulation library [XRayMClib](https://github.com/medicalphysics/XRayMClib) is automatically fetched and built via CMake FetchContent — no manual installation is needed.

### CMake configuration

After installing the required libraries, run CMake with standard settings to generate build files for your platform. The application is tested on Windows 11 and Linux, but should also compile on macOS. Build failures on Windows, Linux, and macOS are considered bugs.

By default, CMake will not download any data from the internet. To enable automatic download of photon attenuation data and optionally LibTorch models for CT organ segmentation, set the following options during the CMake configuration step:

```
-DXRAYMCLIB_EPICS_DOWNLOAD:BOOL="ON"
-DCTSEGMENTATOR_MODELS_DOWNLOAD:BOOL="ON"
```

To enable the optional deep learning CT organ segmentation feature, also set:

```
-DOPENXRayMC_USECTSEGMENTATOR:BOOL="ON"
```
