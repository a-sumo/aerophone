
aerophone

Active development has moved to https://github.com/a-sumo/lattice/ to focus on automata physics. 
I'm preserving this project for documentation and note-taking purposes.

## Introduction

The core objective of this project is to define a class of intuitive, sound generating physical processes. These processes should span a broad spectrum of sounds, extending beyond the audio feature regions typically associated with their real-world counterparts. Unlike real-world instruments, this class of processes is tailored for Extended Reality (XR) applications often characterized by an absence of haptic feedback. Another key requirement is the evocativeness and intuitiveness of visual representations in relation to audio features.

## Requirements

### Dependencies:
- Qt6
- RtAudio
- Python (for some scripts)
- Taichi (Python library)
- Numpy (Python library)

### Note:
The Taichi code uses the Vulkan backend. Ensure that Vulkan is installed on your system.

### Setup Guide:
1. **Clone the Repository**: 
    ```bash
    git clone https://github.com/a-sumo/aerophone.git
    cd aerophone
    ```
2. **Install the Dependencies**:
   - **Windows**: Use the respective package managers or installers for the dependencies.
   - **Linux**: 
     ```bash
     sudo apt-get install qt6-default
     sudo apt-get install librtaudio-dev
     pip install taichi numpy
     ```
   - **MacOS**:
     ```bash
     brew install qt6
     brew install rtaudio
     pip install taichi numpy
     ```

3. **Build and Run**:
    ```bash
    ./build_project.sh
    ```

## Approaches Explored

Aeroacoustics seems to be the class of sound-generating processes most likely to satisfy my requirements. Within this, I need to find one that is most evocative and adapted for XR. So far, I've tried the following: 
- **Water sounds (bubble vibrations)** are very intuitive but too computationally intensive for real-time applications as they require the use of [wavesolvers](https://graphics.stanford.edu/papers/coupledbubbles/)
- **Brass wind instruments** can be simulated using either sound propagation simulations with the Finite-Difference Time Domain(FDTD) method or Digital Waveguide Synthesis. 
FDTD is hard to do in real time.  Digital waveguide synthesis lacks physical intuitiveness.
- **Aeolian tones** are a promising avenue that I'm currently exploring.
<img width="679" src="https://github.com/a-sumo/aerophone/assets/75185852/6d94e6c9-1262-4fef-be6a-a4d6e1e5e0e7">

## Reference material
- [Real-Time Synthesis of an Aeolian tone](https://intelligentsoundengineering.wordpress.com/2016/05/19/real-time-synthesis-of-an-aeolian-tone/)
- [Creating Real-Time Aeroacoustic Sound Effects Using Physically Informed Models](https://www.aes.org/journal/online/JAES_V66/7_8/#paper6)
- [Aerophones in Flatland: Interactive Wave Simulation of Wind Instruments](https://www.microsoft.com/en-us/research/publication/aerophones-flatland-interactive-wave-simulation-wind-instruments/)
- [Real-time Trumpet Simulation by AngeTheGreat](https://youtu.be/rGNUHigqUBM)
- [Engine Simulator 2.0 Initial Audio Testing by AngeTheGreat](https://www.youtube.com/watch?v=FJatcAkC8XI)
- [Hyper Drumhead, An Innovative Way to Create and Control Sounds](https://blog.siggraph.org/2022/08/an-innovative-way-to-create-and-control-sounds.html/)
- [Shader-based Physical Modelling for the Design of Massive Digital Musical Instruments](https://zenodo.org/record/1176203)

## Screenshots 
<details>
    <summary>Iteration 1</summary>
    <img width="400" alt="First Iteration" src="https://github.com/a-sumo/aerophone/assets/75185852/b3d1c133-dc60-4297-be0b-677be3e33d40">
</details>



