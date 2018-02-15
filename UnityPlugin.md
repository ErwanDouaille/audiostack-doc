---
title: Unity5 Plugin
permalink: /audiostack/UnityPlugin/
---

Prerequisites
-----

At this point, we assume you are familiar with Aspic Audiostack concepts such as input, output, bus, effect or diagram. Theses concepts can be easily understood reading the first paragraphs of [Aspic Audiostack diagram](../Index.md). Understanding what subchannels are could also be usefull if you plan to use advanced features of the plugin.

Get started
-----

### Components
Input, output, bus and effect are available in the plugin through Unity components. For example, there are components representing audio file reader (input), OpenAL output, binaural spatialization effect, etc.

### Audio objects identifier
A near-unique key as to be affected to each audio object (inputs, buses and outputs). These key are used for connection between audio objects.
When you create a bus or output, you must fill the key field with a near-unique identifier (ex: "listener" or "spatialization_bus"). In editor mode, multiple outputs/buses may hold the same key, BUT at runtime, only one output/bus must be enabled for each key. This "near-unique key" feature may be useful to switch at runtime between a headphone listener prefab and a multispeaker prefab.

[![Output is identified with its key](../img/unity_output_key.png)](../img/unity_output_key.png)

### Audio routing
Each input/bus provides a GUI to specify to which audio objects (designated by there key(s)) it will send audio. It enables you to route audio signal from inputs to bus and then to outputs. If this seems unclear to you, the [building your first application](#building-your-first-application) section below should be helpfull.

[![Each input or bus must be send to at least one bus/output](../img/unity_send_to_keys.png)](../img/unity_send_to_keys.png)

### Global configuration
Besides the variety of components representing inputs, outputs, effects and buses, you will also find the Aspic Audiostack Config component. Its job is to hold your license and general properties. Every Unity application using Audiostack must instanciate this component at some point.


### Building your first application
Your first audiostack app will involve an audio file reader, binaural spatialization and output sound through standard windows APIs.

Please read [this page](../UnityBasicSample.md) to follow our tutorial.


Common mistakes
-----

If you encounter some errors creating your first apps, a short list of common mistakes is displayed below. Since documentation redaction is in progress, feel free to ask us for any support you might need.

-	Some of your inputs/buses/outputs are not connected properly.
-	You are using audio clips stored outside StreamingAssets folder.
-	Your audio clips are not 48kHz, monophonic WAV files.
-	You forgot to add your license file in your Resources folder or you forgot to set it in Aspic Audiostack Config component.
-	OpenAL is not installed on your system.
-	You unchecked Auto Start on Aspic Audiostack Config component.
-	If subchannel mismatch are detected, please ensure that connections respects subchannel equality rule. Since this is a tricky yet powerfull part of Audiostack, contact us to get some support.


Code samples
-----

- Building your first app : basic usage of Audiostack components at [this page](../UnityBasicSample.md)
- Building a collaborative app : Creating a collaborative application will have us facing new challenges. Please read the [dedicated section](../UnityCollaborativeSample.md).
