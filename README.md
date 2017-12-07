# Dungeon Tease

I have been working on a personal rendering engine these days. Although there are lots needed to deal with and it is really just a beginning, finally here comes the first tease! :tada:

<a href="https://www.youtube.com/embed/Hp1O_UeuIm8?loop=1&playlist=Hp1O_UeuIm8&modestbranding=1&autohide=1&showinfo=0&controls=0" target="blank">
<img src="http://img.youtube.com/vi/Hp1O_UeuIm8/0.jpg"
alt="dungeon tease" width="1280" height="720" border="10" /></a>

## Features

Features currently supported:

- `PBR` real time physics base rendering algorithm and HDR.
- `render queue` a node based render queue, that contributes to performance by reducing api calls.
- `render pass` separated render pass, such as G-buffer, effect, lighting, shadow, making the whole process more controllable and also contributing to rendering performance.
- `frustum culling` cull everything that is not inside the camera.
- `shadow mapping` real time shader based shadow mapping.
- `SSAO` real time screen-space SSAO.
- `particles system` better looking and performance, easy to implement.
- `instance object` implement of OpenGL instance draw feature.
- `ECS` Entity Component & GameObject System just like Unity Engine.
- `motion blending` bone animation blending, supporting all the animations from mixamo.com.
- `third person controller` player-camera controller just like all the third person game, supporting PS4 controller.
- `import blender file` blender is an awesome software. All the stages were edited in blender.

And some new features are one the way, such like `baked shadow and lighting` `LUT filter` `bloom and blur`.

## Download
- Source code available on GitHub (without assets).
- Download this demo here. (Password required && OSX 10.12 or later && PS4 controller).

{% include image.html path="2017-11-26-dungeon-demo/dungeon_screen@2x.png" path-detail="2017-11-26-dungeon-demo/dungeon_screen_full@2x.png" alt="dungeon tease" %}

## Frameworks

- `OpenGL ES 3.2 & GLM` Core graphic api and core math library.

- `Assimp` Although I have wrote some model loader program by myself, Assimp is more professional library and can handle more complex situations. [Open Asset Import Library (short name: Assimp)](http://assimp.sourceforge.net) is a portable Open Source library to import various well-known 3D model formats in a uniform manner.

- `stb` Public domain C image loading library by [nothings](http://nothings.org).

## Assets

- Character and animation from [mixamo](https://www.mixamo.com).
- Model by SilverTm from [UE4 Marketplace](https://www.unrealengine.com/marketplace).

## Bibliography
- [Background: Physics and Math of Shading by Naty Hoffmann](http://blog.selfshadow.com/publications/s2013-shading-course/hoffman/s2013_pbs_physics_math_notes.pdf).
- [Real shading in Unreal Engine 4](http://blog.selfshadow.com/publications/s2013-shading-course/karis/s2013_pbs_epic_notes_v2.pdf).
- [Frustum Culling LegacyOpenGL](https://gdbooks.gitbooks.io/legacyopengl/Chapter8/frustum.html).
- [Unity User Manual](https://docs.unity3d.com/Manual/index.html).
- [MipMap Texturing](https://graphics.ethz.ch/teaching/former/vc_master_06/Downloads/Mipmaps_1.pdf).
- [Deferred vs Forward+ Rendering with DirectX 113D Game Engine Programming](https://www.3dgep.com/forward-plus/).
- [Forward+: Bringing Deferred Lighting to the Next Level](https://takahiroharada.files.wordpress.com/2015/04/forward_plus.pdf).
- [Google I/O 2011: WebGL Techniques and Performance](https://www.youtube.com/watch?v=rfQ8rKGTVlg).
- [Efficient Gaussian blur with linear sampling](http://rastergrid.com/blog/2010/09/efficient-gaussian-blur-with-linear-sampling/).
- [How to do good bloom for HDR rendering](http://kalogirou.net/2006/05/20/how-to-do-good-bloom-for-hdr-rendering/).
- [Transparency Sorting](https://www.khronos.org/opengl/wiki/Transparency_Sorting).
- [Learn OpenGL, extensive tutorial resource for learning Modern OpenGL](https://learnopengl.com).
