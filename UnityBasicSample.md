---
title: Unity Basic Sample
permalink: /audiostack/UnityBasicSample/
---

{% icon fa-exclamation-triangle  %} {% icon fa-exclamation-triangle  %} {% icon fa-exclamation-triangle  %} WARNING : Audiostack documentation is not up to date anymore. We are working on it to provide you a nice and simple new doc as soon as possible.

The aim of this section is to construct step by step a simple Unity3d application using Aspic Audiostack.

### Setting up the plugin 
We advise you to test Audiostack plugin in a new Unity project.

The following steps assume that Unity3D Editor is launched and that a project is loaded.

-	Import package “AspicAudiostack_Unity5_x86-64_vX.Y.unitypackage” through Unity3D menus or using your file explorer,
-	When the import dialog box shows, ensure everything is checked,
-	Confirm by clicking “Import”.

You may have received a license file with your copy of Aspic Audiostack. This is a binary file whose extension must be ‘.bytes’ to be used by our plugin.

-	Please copy this file into your “Assets/Resources” folder.

In order to ensure that this sample will work, we must install OpenAL on your system. 

-	Please download this archive: [OpenAL official installer](https://www.openal.org/downloads/oalinst.zip) and execute aolinst.exe.


### Steps

-	Create an empty GameObject named AudiostackScriptHolder in your scene. It will handle every global Audiostack behaviours.
-	Select this node in the hierarchy. In the inspector, click "Add component" and choose "Aspic Audiostack/Config".
Aspic Audiostack Config holds two parameters: "Product Key" which must reference your licence file (drag and drop serious_name.bytes) you have copied previously in Assets/Resources folder. "Auto Start" must remain checked in this application. We will see when to uncheck it in our collaborative example.
-	In your scene, select Camera node or any node you want to use as listener. In the inspector, add component "Aspic Audiostack/Outputs/OpenAL". Set its key to "listener" and keep gain and stereo untouched.

[![Add OpenAL output to your camera](../img/unity_output_key.png)](../img/unity_output_key.png)

-	In project tab, go to Assets/AspicAudiostack/Prefabs. Drag and drop 3DBus in your "AudiostackScriptHolder" node. You may notice that the bus already holds the "bus_3d" key and is already connected to "listener" output. 
This prefab is composed of one Bus component, followed by effects. We will come back to this bus later to set its sends, effects and parameters.

[![It may be a good idea to store buses under a common persistent object.](../img/unity_add_bus.png)](../img/unity_add_bus.png)

-	In the hierarchy tab, create an object (a Sphere will do the job). It will be our audio source.
-	Select it and add component "Aspic Audiostack/Inputs/Audio file". Set its audio clip by selecting an asset called reactor.wav. This asset has been imported while unpacking the package and automatically put in `Assets/StreamingAssets` folder.
-	In the send section of the component, check "bus_3d". Your component must look like this:

[![Audio file input layout](../img/unity_file_input.png)](../img/unity_file_input.png)

-	At this point, we have created an input (file reactor.wav), a 3d bus (for spatialization and attenuation over distance) and an OpenAL output. Next step is to play.
-	Start your application in Unity editor. You should here a drone-like noise. In Scene view, you can move your camera or source to hear spatialization and attenuation effects.

### Build

Building your app to run it out of Unity editor is simple:

-	In build settings window, ensure that Windows is your target platform.
-	Since our package only provides 64bits libraries, you have to build your project for x86_64 architecture.

[![Build settings](../img/unity_build_settings.png)](../img/unity_build_settings.png)

All resources (license, audio clips, libraries and dependencies) are installed in your build dir. Your standalone application must run smoothly. If this is not the case, please check the logs and contact our support team.
