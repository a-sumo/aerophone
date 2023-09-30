aerophone

## Introduction

The core objective of this project is to define a class of intuitive, sound generating physical processes. These processes are envisioned to span a broad spectrum of sounds, extending far beyond the audio feature regions typically associated with their real-world counterparts. Unlike conventional instruments, the envisioned class is tailored for Extended Reality (XR), factoring in the absence of haptic feedback, and emphasizing the evocativeness and intuitiveness of visual representations in relation to audio features.

## Reference Material

The inception of this project has been significantly influenced by a variety of academic and practical works. The real-time audio synthesis capability demonstrated by AngeTheGreat in his [Real-time Trumpet Simulation](https://youtu.be/rGNUHigqUBM) and [Engine Simulator 2.0 Initial Audio Testing](https://www.youtube.com/watch?v=FJatcAkC8XI) projects, for instance, served as a notable inspiration. Further insights were derived from the publication "Aerophones in Flatland", which explores interactive wave simulation of wind instruments, and the series on Shader-based Physical Modelling, which delves into real-time physical modelling synthesis on the GPU using OpenGL shaders.

## Approaches Explored

Initial explorations were conducted within game engine environments such as Unity; however, the stringent requirement for real-time audio synthesis proved to be a limiting factor. Temporarily setting aside the real-time constraint led to the discovery of pertinent academic work on audio synthesis from physical simulation. Although operating at audio rates presents a formidable challenge, the work of AngeTheGreat provided a glimpse into the realm of possibilities.

Several frameworks and libraries have been experimented with so far:

- **OpenGL and Vulkan:** Explored for their GPU programming and real-time rendering capabilities, but encountered setup issues particularly on the MacOS M1 setup.
- **Taichi:** An open-source, parallel programming language embedded in Python, considered for offloading compute-intensive tasks to the GPU or CPU. However, its lack of advanced GUI capabilities posed a challenge.
- **bgfx:** Investigated for rendering capabilities, but the complexity in setting up with window handlers like GLFW was a hindrance.
- **Qt6:** Offered UI and graphics capabilities but felt somewhat isolated in its approach, as opposed to a more modular framework that would allow for easier transitions as project requirements evolve.

These explorations highlight the intricate balance between real-time audio synthesis, GPU programming, and interactive visualization in crafting the envisioned class of virtual instruments.

## References

- Mohapatra, Debasish Ray. "Talking tube: a novel approach for vocal tract acoustic modelling using the finite-difference time-domain method."
- [Aerophones in Flatland: Interactive Wave Simulation of Wind Instruments](https://www.microsoft.com/en-us/research/publication/aerophones-flatland-interactive-wave-simulation-wind-instruments/)
- [Shader-based Physical Modelling for the Design of Massive Digital Musical Instruments](https://zenodo.org/record/1176203)
- OpenGL FDTD Tutorial Series: [Episode 0](https://toomuchidle.com/opengl-fdtd/), [Episode 1](https://toomuchidle.com/opengl-fdtd-tutorial-episode-1-simulation-initialization/), [Episode 2](https://toomuchidle.com/opengl-fdtd-tutorial-episode-2-simulation-cycle-and-shader-programs/)
- [Real-time Trumpet Simulation by AngeTheGreat](https://youtu.be/rGNUHigqUBM)
- [Engine Simulator 2.0 Initial Audio Testing by AngeTheGreat](https://www.youtube.com/watch?v=FJatcAkC8XI)
- [Taichi Library](https://pypi.org/project/taichi/)

