---
title: Unity Collaborative Sample
permalink: /audiostack/UnityCollaborativeSample/
---

{% icon fa-exclamation-triangle  %} {% icon fa-exclamation-triangle  %} {% icon fa-exclamation-triangle  %} WARNING : Audiostack documentation is not up to date anymore. We are working on it to provide you a nice and simple new doc as soon as possible.

Creating a collaborative application will have us facing new challenges. We will cover some of theses challenges before starting our tutorial.

## Prerequisites
In this tutorial, you are expected to have knowledge of Unity 5 Network system and basic knwoledge of Aspic Audiostack.

## New challenges

### Listener prefabs

At some point, in a collaborative demo, our scene will probably contain two GameObject representing players. However, in an audio prospective, these two objects must differ :

-	the "local" listener will use system's sound card to access microphone, audio output and send voice over network for our fellow player.
-	the "distant" listener will capture audio over computer network interface.

This problem requires us to build to listener prefab, that we will call local and distant listeners.

### Audio start

In our previous sample, Audiostack started automatically. This behaviour was possible because all audio related GameObjects were available at application startup. Therefore, in our collaborative sample, a new player will join at a different instant.

In current Audiostack version, all inputs, buses and outputs must be created before starting the engine. Since "dynamic diagrams" will only be available in our next release, we must design our collaborative demo to wait for every inputs/outputs to be instanciated to start the audio engine.

This will be achieved by disabling Audiostack "Auto Start" and by sending a "Play" RPC Call when all player are connected.

## Tutorial

Instead of following a step by step tutorial, we will study the scene provided in "AspicAudiostack_Unity5_collaborative_demo.unitypackage".

Please create a new project, import the provided package and load the scene AudiostackDemo.unity

Now lets review this scene content.

### NetworkManager and SceneManager.cs
The provided scene contains a "NetworkManager" node, composed of a Unity NetworkManager and a SceneManager script.

This script is responsible for:

-	Providing a GUI to start as host or join as client.
-	Master server handling,
-	Spawning players when they join the demo,
-	Sharing players IP addresses (usefull for audio networking),
-	Calling RPC such as startAudio.

### Listener prefab and Player.cs
AspicListenerPrefab is the prefab instanciated by the network manager when a player spawns. The prefab is mainly composed of a network identity, a network transform and Player.cs script.

This script is linked to:

-	one camera prefab, instanciated only for local player,
-	one local listener prefab, instanciated only for local player,
-	one distant listener prefab, instanciated on distant player.

Player.cs jobs are:

-	instanciating child prefabs according to network configuration,
-	notifying Scene Manager when players are ready (in order to start audio),
-	handling player movement.

### Audio 

The scene contains an audio source connected to a 2D Bus. This means that the source will not be spatialized and heard at the same volume from anywhere in the scene.

Each local listener captures microphone and sends it over network to the distant listener.

2D and 3D buses sends audio to local listener's OpenAL output.

Distant listener node receives audio from network and sends it to 3D bus to spatialize voices.

### Master server and facilitator

When using Unet (Unity network features) on a local area network, you have to use a local master server and nat facilitator to enable your clients to join the host. SceneManger scripts must be modified to setup properly master server and facilitator ip addresses.

## Playing the demo

In order to try this app, you have to :

-	Import your license file in your project and set it on Audiostack Config.
-	On "NetworkManager" node, in Network Manager component, you have to set "Network Address" to the host ip address (located in the "Network info" group).
-	Modify the two IP addresses (master server and network facilitator) in SceneManager.cs Start function.
-	Start a master server and network facilitator on the host
- 	Build the demo (x86_64) and install it on another computer on the same LAN.
-	Ensure both host and client computers have OpenAL installed on their system.
-	Plug microphone and headphones to both computer.
-	Start the host and choose "Start hosting".
-	Start the client, refresh server list and join the host.

Each player should hear its comrade's voice spatialized and a 2D audio source in the background. Both can move using ZQSD and rotate using arrow keys.
