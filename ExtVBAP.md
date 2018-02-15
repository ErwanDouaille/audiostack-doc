---
title: VBAP module
permalink: /audiostack/VBAP/
---

{% icon fa-exclamation-triangle  %} {% icon fa-exclamation-triangle  %} {% icon fa-exclamation-triangle  %} WARNING : Audiostack documentation is not up to date anymore. We are working on it to provide you a nice and simple new doc as soon as possible.

Aspic Audiostack VBAP module provides effects for spatialization over multiple speaker. The effects of this module will apply the appriate gain on all speakers to perceive sound from the correct direction.

> **Note :** To address multiple harware outputs see [Asio Module](ExtASIO.md.html)

> **Note :** Effects in this module are currently in Core Module, and will be moved in VBAP module in a near future.

## Effects

### MultiChannelSpatialization

Provides VBAP-based spatialization for rendering over speakers positioned on an azimutal circle. 

Each input channel is spatialized independently (no mixing), which enables you to add more "per-channel" effects after this spatialization.

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`in`		|N						|1 (MONO)				|
|`out`		|N						|multichannel[^1]			|

[^1]: specified by *nbSubChannel* at construction


#### Construction

- **nbSubChannel (*unsigned int*) :** count of output subchannels.

> **Warning :** nbSubChannel must equals the installation speaker count

- **defaultSpeakerPositions (*float*)** : array of default speaker positions

Example for a 3 speakers positions array :

|0|1|2|3|4|5|6|7|8|
|-|-|-|-|-|-|-|-|-|
| S1.x | S1.y |S1.z|S2.x|S2.y|S2.z|S3.x|S3.y|S3.z|

> **Note :** coordinates in Aspic Audiostack are specified using right-hand axes (X right, Y up, Z backward).

Usage : 

```cpp
float[] speakerPos{-1,0,1,1,0,1,1,0,-1,-1,0,-1};
context.createEffect(EFFECT_ID, BUS_ID, MultiChannelSpatialization, 4, speakerPos);
```

#### Parameters



- **sound_decay_coeff(*float*)**
	
	** Deprecation in progress ** since the Attenuation effect is now available in Core module, attenuation mecanism will be removed from MultiChannelSpatialization.
	
	This paramater is still available in your version of Aspic Audiostack. It takes values int he range ]0;+inf[ and drivers the smoothness of an inverse attenuation law.

- **src_position(*vec3, multivalued, runtime*):** position of audio sources
	This parameter will contain N values, with N equal to the number of channels reaching effect's input.

	Parameter is mapped by default to `source/%src_id/position`
	
- **listener_position(*vec3, multivalued, runtime*):** position of audio listener

	This parameter will contain N values, with N equal to the number of listeners.

	Parameter is mapped by default to `listener/%list_id/position`
	
- **listener_rotation(*vec3, multivalued, runtime*):** rotation of audio listener

	This parameter will contain N values, with N equal to the number of listeners.

	Parameter is mapped by default to `listener/%list_id/rotation`
	
- **hardware_position(*vec3, multivalued*) :** position of each speaker
	
	This parameter will contain N values, with N equal to the number of speakers/subchannels.

	Parameter is mapped by default to `hardware/%speaker_id/position`

	
> **Note :** coordinates in Aspic Audiostack are specified using right-hand axes (X right, Y up, Z backward).


------


## Code samples


### C++ API Samples

> **Note: ** our VBAP samples use ASIO output, in order to provide multiple speakers

#### VBAP spatialization sample

This sample spatialize hello input for one listener with 4 speakers.

```cpp
{% include_relative samples/VBAP_1_Basics.cpp%}
```

