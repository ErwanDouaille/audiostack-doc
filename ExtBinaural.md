---
title: Binaural module
permalink: /audiostack/Binaural/
---

Aspic Audiostack Binaural module provides effects for binaural spatialization.

## Effects

### BinauralSpatializationAspic

Provides HRTF-based spatialization for binaural rendering. 

Each input channel is spatialized independently (no mixing), which enables you to add more "per-channel" effects after this spatialization.

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`in`		|N						|1 (MONO)			|
|`out`		|1						|2 (STEREO)			|

#### Construction

No arguments 

Usage : 
```cpp
context.createEffect(EFFECT_ID, BUS_ID, BinauralSpatializationAspic); // creates a binaural spatialization
```

#### Parameters

- **src_position (*vec3, multivalued*) :** position of audio source

	This parameter will contain N values, with N equal to the number of channels reaching effect's input.

	Parameter is mapped by default to `source/%src_id/position`
	
- **listener_position (*vec3, multivalued*) :** position of audio listener

	This parameter will contain N values, with N equal to the number of listeners.

	Parameter is mapped by default to `listener/%list_id/position`
	
- **listener_rotation (*vec3, multivalued*) :** rotation of audio listener

	This parameter will contain N values, with N equal to the number of listeners.

	Parameter is mapped by default to `listener/%list_id/rotation`
	
	Usage : 
	
``` cpp
float myPos[] = {1.0, 2.0, 3.0};
context.setParameter("source/ID/position", myPos);
```
	
> **Note :** coordinates in Aspic Audiostack are specified using right-hand axes (X right, Y up, Z backward).


------


## Code samples


### C++ API Samples

#### Binaural spatialization sample

This sample spatialize microphone for one listener.

For multilistener samples, please see Asio Extension samples.

```cpp
{% include_relative samples/Binaural_1_Basics.cpp %}
```
