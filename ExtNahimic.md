---
title: Nahimic Binaural module
permalink: /audiostack/Nahimic/
---

{% icon fa-exclamation-triangle  %} {% icon fa-exclamation-triangle  %} {% icon fa-exclamation-triangle  %} WARNING : Audiostack documentation is not up to date anymore. We are working on it to provide you a nice and simple new doc as soon as possible.

Aspic Audiostack Nahimic&trade; Binaural module provides binaural spatialization algorithms developed by A-Volute&trade;.

## Effects

### NahimicBinauralSpatialization

Provides Nahimic&trade; binaural spatialization. 

Due to optimized signal processing, spatializated audio is mixed in one output channel.

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`in`		|N						|1 (MONO)			|
|`out`		|1						|2 (STEREO)			|

#### Construction

No arguments 

Usage : 
```cpp
context.createEffect(EFFECT_ID, BUS_ID, NahimicBinauralSpatialization);
```

#### Parameters

- **sample_rate (*unsigned int*)** : sample rate of processed audio buffers.

	This parameter is mapped by default to `application/sample_rate`.

	Usage : 
```cpp
context.setParameter("application/sample_rate",48000);
// OR
context.setParameter("effect/ID/sample_rate",48000);
```

- **buffer_size (*unsigned int*)** : the length of processed audio buffers.

	This parameter is mapped by default to `application/buffer_size`.

	Usage : 
```cpp
context.setParameter("application/buffer_size",4096U);
// OR 
context.setParameter("effect/ID/buffer_size",4096U);
```

- **src_position (*vec3, multivalued*) :** position of each channel audio source

	This parameter will contain N values, with N equal to the number of channels reaching effect's input.

	Parameter is mapped by default to `source/%src_id/position`
	
- **listener_position (*vec3*) :** position of audio listener

	Parameter is mapped by default to `listener/%list_id/position`
	
- **listener_rotation (*vec3*) :** rotation of audio listener

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

#### Nahimic spatialization sample

This sample spatialize microphone for one listener.

For multilistener samples, please see Asio Extension samples.

```cpp
{% include_relative samples/Nahimic_1_Basics.cpp%}
```

