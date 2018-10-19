# Welcome to ViennaMS
This is the source code of the Vienna UT MSTEx contest approach. 
It is licensed under the GPLv2 license (so feel free to use it).
The Matlab source code of the second approach submitted to MSTEx can be found here:
https://github.com/hollaus/MSTEx-CVL-matlab

| Author         | E-Mail                  |
|----------------|-------------------------|
| Markus Diem    | diem@cvl.tuwien.ac.at   |
| Fabian Hollaus | holl@cvl.tuwien.ac.at   |

## Using ViennaMS

- You can either build ViennMS (see below) or download the latest stable [release](https://github.com/diemmarkus/MSTEx-CVL/releases). 
- Open a command line and dir to the folder that contains `ViennaMS.exe` then type:
````cmd
> ViennaMS.exe C:/%your_path%/MSTEx-CVL/img/z35 C:/%your_path%/MSTEx-CVL/img/z35-bw.png

MSI mode is active...
F1s.png loaded into channel 0
F2s.png loaded into channel 1
F3s.png loaded into channel 2
F4s.png loaded into channel 3
F5s.png loaded into channel 4
F6s.png loaded into channel 5
F7s.png loaded into channel 6
F8s.png loaded into channel 7
[z35GT.png] does not fit the specification - ignoring...

````

![input-image](./img/z35/F4s.png)
![output-image](./img/z35-bw.png)

## Build ViennaMS (Windows)

### Dependencies

- [CMake] (https://cmake.org/)
- [OpenCV](https://github.com/TUWien/opencv) (>= 3.4)

### Build Steps

- copy `CMakeUserPathsGit.cmake` and rename it to `CMakeUserPaths.cmake`
- add your library paths to the `${CMAKE_PREFIX_PATH}` in `CMakeUserPaths.cmake`
- Open CMake GUI
- set this folder to `where is the source code`
- choose a build folder (i.e. `build2017-x64`)
- Hit `Configure`then `Generate`
- Open the Project
- Compile the Solution

## Abstract:
The proposed approach incorporates three methods for MultiSpectral Text Extraction. First, a rough foreground estimation is performed by thresholding a cleaned channel using the Su et al. [1] binarization. In order to compute a cleaned channel, the background channel F8 (1100nm) is removed from a visible channel F2 (500 nm). This rough foreground estimation is used in a second step to train an Adaptive Coherence Estimator (ACE) proposed by Scharf and Whorter [2]. The ACE detects a spectral subspace which enhances ink while the contrast of other elements (e.g. stains) is reduced.  Finally we combine the cleaned channel with the mean and standard deviation images and perform a GrabCut [3]. The GrabCut is guided by a mask which is based on the results of the ACE. Our source code is available at https://github.com/diemmarkus/MSTEx-CVL.git

## Literature:
1. Lu, Shijian, Bolan Su, and Chew Lim Tan. "Document image binarization using background estimation and stroke edges." International Journal on Document Analysis and Recognition (IJDAR) 13.4 (2010): 303-314.
2. Scharf, L.L., and McWhorter, L.T., "Adaptive matched subspace detectors and adaptive coherence estimators," Signals, Systems and Computers, 1996. Conference Record of the Thirtieth Asilomar Conference on , vol., no., pp.1114,1117 vol.2, 3-6 Nov. 1996
3. C. Rother, V. Kolmogorov, and A. Blake, GrabCut: Interactive foreground extraction using iterated graph cuts, ACM Trans. Graph., vol. 23, pp. 309-314, 2004.


## Usefull links:
- [MSTEx Contest]    http://www.synchromedia.ca/competition/ICDAR/mstexicdar2015.html
- [CVL]              http://www.caa.tuwien.ac.at/cvl/	
- [nomacs]           http://www.nomacs.org

If you need the original binary of the challenge - feel free to contact us.
