<h1 align="center">Supple Crystal</h1>

<p align="center">
  <img alt="badge-lastcommit" src="https://img.shields.io/github/last-commit/GaryStriving/Supple-Crystal?style=for-the-badge">
  <img alt="badge-openissues" src="https://img.shields.io/github/issues-raw/GaryStriving/Supple-Crystal?style=for-the-badge">
  <img alt="badge-license" src="https://img.shields.io/github/license/GaryStriving/Supple-Crystal?style=for-the-badge">
  <img alt="badge-contributors" src="https://img.shields.io/github/contributors/GaryStriving/Supple-Crystal?style=for-the-badge">
  <img alt="badge-codesize" src="https://img.shields.io/github/languages/code-size/GaryStriving/Supple-Crystal?style=for-the-badge">
</p>

<p align="center">
  <img alt="logo" src="https://user-images.githubusercontent.com/46727048/141652770-78d07476-c5fa-40fd-8c49-9843be74d0ed.png" />
</p>

## Useful links
- [Contributing Guidelines](https://github.com/GaryStriving/Supple-Crystal/blob/main/docs/CONTRIBUTING.md).
- [Project's Style Guide (Webkit)](https://webkit.org/code-style-guidelines/).

## What is Supple Crystal?
Supple Crystal is an efficient and versatile **lightweight/advanced image viewer**.

Supple Crystal can change between 2 modes: Fast mode and polished mode.
- **Fast mode:** Lightweight, default mode. The only menu is the context menu. It contains only very basic features like zoom, rotating and the option to change to advanced mode. The purpose of this mode is to open images as fast as possible.
- **Polished mode (Soon available):** Advanced mode. It contains zoom and rotating features, but also more advanced features for browsing images like a color picker, a cropping tool and an image filetype convertor.

### Features
- **Efficient:** Supple Crystal lightweight mode is made to open as fast as possible. You won't have to wait to see your images!
- **Scalable:** Supple Crystal can open your images regardless of their size. 5000px * 5000px image? No problem! Supple Crystal can open it.
- **Free:** There aren't any pro modes nor ads. All Supple Crystal features are free for everyone.
- **Open-source:** The code of Supple Crystal is openly available on GitHub. You can download it and edit it to make it personal!
- **Versatile:** With its modes feature, Supple Crystal is a very versatile image viewer that will be able to adapt itself to your needs for sure.
- **Multiple formats:** Because it is built with SFML, Supple Crystal supports the same image formats that the library supports: `bmp`, `png`, `tga`, `jpg` (non-progressive), `gif` (unanimated), `psd`, `hdr` and `pic`.

### Platforms
- Cross-platform

### Dependencies
#### Development
- SFML
- GoogleTest
- CMake

## Motivation
Too often, I have trouble opening images. When I'm in a hurry, I want to open an image as fast as possible to check. Nonetheless, when I'm not in a hurry but inspecting an image, I would prefer having many features that helps me viewing the details. As a consequence, I have 2 image viewers. However, this is also a problem, because it's hard managing both - sometimes I open the advanced one when I'm in a hurry and my computer lags - and it causes a lot of desorganization.

Then, I got the idea of creating Supple Crystal. Supple Crystal solves this problem by giving the user both the fast mode and the polished mode. The fast mode is the default mode which opens as fast as possible so you won't have problem if you're in a hurry. The polished mode can be accessed from fast mode and has more advanced features. With those two modes, there is no need of having two image viewers nor causing yourself a lot of trouble.

## Installation and usage
To build and install Supple Crystal from source you must follow the next steps:
1. Prepare the external libraries:
   1. Get SFML 2.5.1.
        - You can look at how to get SFML [here](https://www.sfml-dev.org/tutorials/2.5/).
   2. Order the external libraries:
        1. Create a folder called `extlibs` in the root folder.
        2. Add the external libraries here. The minimal `extlibs` folder should look like this:
           ```
           | extlibs/
           |--- SFML-2.5.1/
           |------- bin/
           |------- include/
           |------- lib/
           ```
2. Build Supple Crystal:
   1. Fork the repository on GitHub.
   2. Go to your fork of the repository and copy the link to clone your repository.
   3. Go to Git on your local machine and use the command `git clone (your link)`.
   4. Set the variable CMAKE_BUILD_TYPE in `CMakefiles.txt` to "Release" or to "Debug" depending on what you want to build.
   5. Use CMake to generate makefiles from `CMakelists.txt`.
   6. Use the generated makefiles to build Supple Crystal

After doing this, Supple Crystal should appear inside a folder in `build/`.

For the release version, it should appear like this:
```
        | Release/
        |--- PublicSans-Regular.ttf
        |--- sfml-graphics-2.dll
        |--- sfml-system-2.dll
        |--- sfml-window-2.dll
        |--- ${Supple Crystal Executable}
        |--- assets/
        |------- logo_bg-true_resized.png
```

For the debug version, it should appear like this:
```
        | Debug/
        |--- PublicSans-Regular.ttf
        |--- sfml-graphics-d-2.dll
        |--- sfml-system-d-2.dll
        |--- sfml-window-d-2.dll
        |--- ${Supple Crystal Executable}
        |--- assets/
        |------- logo_bg-true_resized.png
```
Notice that you may not change the names of the TTFs, the DLLs nor the assets.

You can also install a precompiled version of Supple Crystal that comes ready to use. 

Once you have it, you can start using it:
- For activating it from the command line you can use this comand:
```cmd
(executable path) (filename) 
```
- You can grab an application and bring it towards the item in the file explorer to open it:

<p align="center"><img alt="grab-tutorial" src="https://user-images.githubusercontent.com/46727048/135758516-775036cf-de4f-4584-9734-1139ed00a5ce.gif"></p>

- In Windows, you can also use the option of "Open with", go to "Choose another app" an search for the Supple Crystal executable. Optionally, you can select "Always use this app" to open your files with Supple Crystal by default:

<p align="center"><img alt="open-with" src="https://user-images.githubusercontent.com/46727048/135758901-fa32d5d5-700e-420b-a62f-5c360cb8e53a.gif"></p>

## Contributors
Thanks to these wonderful people for making Supple Crystal possible!

<p align="center"><a href="https://github.com/GaryStriving/Supple-Crystal/graphs/contributors"><img src="https://contrib.rocks/image?repo=GaryStriving/Supple-Crystal" /></a></p>

## License
This work is licensed under a [Creative Commons Attribution 4.0 International License](https://github.com/GaryHilares/Supple-Crystal/blob/main/LICENSE).

Third party code and resources in this repository are under their own licenses:
- [PublicSans](https://github.com/GaryStriving/Supple-Crystal/tree/main/third-party/PublicSans) by Pablo Impallari and Rodrigo Fuenzalida (Modified by Dan O. Williams and USWDS) is under the [SIL Open Font License](https://github.com/GaryStriving/Supple-Crystal/blob/main/third-party/PublicSans/LICENSE).
- [Icons by Cole Bemis](https://github.com/GaryStriving/Supple-Crystal/tree/main/third-party/Icons%20by%20Cole%20Bemis) by Cole Bemis is under the [Attribution 4.0 International (CC BY 4.0) license](https:/GaryStriving/github.com//Supple-Crystal/blob/main/third-party/Icons%20by%20Cole%Bemis/LICENSE).
- [Icons by Kmg Design](https://github.com/GaryStriving/Supple-Crystal/tree/main/third-party/Icons%20by%20Kmg%20Design) by Kmg Design is under the [Creative Commons (Attribution 3.0 Unported) license](https://github.com/GaryStriving/Supple-Crystal/blob/main/third-party/Icons%20by%20Kmg%Design/LICENSE).
- [Icons by Steve Schoger](https://github.com/GaryStriving/Supple-Crystal/tree/main/third-party/Icons%20by%20Steve%20Schoger) by Steve Schoger is under the [Creative Commons (Attribution 3.0 Unported) license](https://github.com/GaryStriving/Supple-Crystal/blob/main/third-party/Icons%20by%20Steve%Schoger/LICENSE).
