---
title: Core module
permalink: /audiostack/Core/
---

Aspic Audiostack Core module offers main features of the library such as OpenAL driver interfacing or regular audio effects.

## Effects

### SimpleGain

May be used to apply a gain to specific audio channels. 

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`in`		|N						|1 (MONO)			|
|`out`		|N						|1 (MONO)			|

#### Construction

No arguments 

Usage : 
```cpp
context.createEffect(EFFECT_ID, BUS_ID, SimpleGain);
```

#### Parameters

- **src_gain (*float, multivalued*) :** controls the gain applied to audio [channels](/#channels). Default value is `1.0f` for each [channel](/#channels). The higher the value, the loudest the sound will be. A value equal to `0.0f` won't let pass any signal.

	This parameter will contain N values, with N equal to the number of channels reaching effect's input.

	Parameter is mapped by default to ```source/%src_id/gain```

- **mute (*bool, multivalued*) :** if set to TRUE, mutes one audio [channel](/#channels). Default value is FALSE.

	This parameter will contain N values, with N equal to the number of channels reaching effect's input.
	
	Parameter is mapped by default to ```source/%src_id/mute```
	

------

### MultiChannelSimpleGain

Behaves exactly like SimpleGain except that this effect also **splits** the input into N [sub channels](/#subchannels). It is usefull to transform a mono signal in a stereo (or multichannel) output, for instance on a 2D bus before outputing to your stereo/multichannel outputs. The gain applied to one signal is applied equally to each one of its [sub channels](/#subchannels).

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`in`		|N						|1 (MONO)			|
|`out`		|N						|multichannel[^1]	|

[^1]: specified by *nbSubChannel* at construction

#### Construction

- **nbSubChannel (*unsigned int*) :** set sub channel count of the output.

	Usage :
	
```cpp
context.createEffect(EFFECT_ID, BUS_ID, MultiChannelSimpleGain, 2) // creates a stereo gain
context.createEffect(EFFECT_ID, BUS_ID, MultiChannelSimpleGain, 8) // creates a 7.1 master gain.
```
	
		
#### Parameters

Same as [SimpleGain](#simplegain)

------

### Mixer 

Mix down many **mono** audio [channel](/#channels) into one **mono** [channel](/#channels). Mixers are usefull because they enable following effects to process fewer audio data. However, effects after a mixer cannot apply source-specific effects (like spatialization or attenuation).

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`in`		|N						|1 (MONO)			|
|`out`		|1						|1 (MONO)			|

#### Construction

No arguments 

Usage : 

```cpp
context.createEffect(EFFECT_ID, BUS_ID, Mixer);
```

#### Parameters

- **volume (*float, multivalued*) :** controls amount of each input channel that goes to the output. Default value is `1.0f` and values must be between `0.0f` and `1.0f`

	This parameter will contain N values, with N equal to the number of channels reaching effect's input.

	Parameter is mapped by default to `source/%src_id/volume`

------

### StereoMixer 

Behaves like [Mixer](#mixer) but with **stereo** inputs and output.

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`in`		|N						|2 (STEREO)			|
|`out`		|1						|2 (STEREO)			|

#### Construction

No arguments 

Usage : 
```cpp
context.createEffect(EFFECT_ID, BUS_ID, StereoMixer);
```

#### Parameters

Same as [Mixer](#mixer).

------

### MultiChannelMixer 

#### Description

Behaves like [Mixer](#mixer) but with custom [subchannel](/#subchannels) count. 

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`in`		|N						|multichannel[^2]			|
|`out`		|1						|multichannel[^2]			|

[^2]: specified by *nbSubChannel* at construction

#### Construction

- **nbSubChannel (*unsigned int*) :** set sub channel count of input and output channels.

	Usage : 
	
```cpp
context.createEffect(EFFECT_ID, BUS_ID, MultiChannelMixer, 2) // creates a stereo mixer
context.createEffect(EFFECT_ID, BUS_ID, MultiChannelMixer, 8) // creates a 7.1 mixer
```
		
#### Parameters

See [Mixer](#mixer).

------

### AttenuationEffect

This effects uses distance between sources and listeners to apply custom audio volume. It may be used to reproduce attenuation of sound over distance in real life.

Currently available attenuation profiles are linear and inverse.

Linear attenuation requires you to set a min and max distance. When distance between source and listener is below min, volume is set to 1.0f; when distance goes over max, volume is set to 0.0f.

Inverse attenuation requires a min distance and a decay coefficient. Audio volume is set to `1.0f` below min distance, and then follow a inverse law (1/distance). The decay coefficient enable a fine tuning of the strength of attenuation.

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`in`		|N						|multichannel[^3]			|
|`out`		|N						|multichannel[^3]			|

[^3]: specified by *nbSubChannel* at construction

#### Construction

- **attenuationType (*unsigned int*) :** choose between attenuation laws, use 0 for linear, use 1 for inverse.

- **nbSubChannel (*unsigned int*)** : set [subchannel](/#subchannels) count of input and output channels.

	Usage : 
	
```cpp
context.createEffect(EFFECT_ID, BUS_ID, AttenuationEffect, 0, 1) // creates linear attenuation effect for mono signals
context.createEffect(EFFECT_ID, BUS_ID, AttenuationEffect, 1, 2) // creates inverse attenuation effect for stereo signals
```
		
#### Parameters

- **src_position (*vec3, multivalued*) :** position of audio source

	This parameter will contain N values, with N equal to the number of channels reaching effect's input.

	Parameter is mapped by default to `source/%src_id/position`
	
- **listener_position (*vec3, multivalued*) :** position of audio listener

	This parameter will contain N values, with N equal to the number of buses output.

	Parameter is mapped by default to `listener/%list_id/position`
	
- **min_distance (*float*) :** available for linear and inverse attenuation. Default is `0.0f`.

- **max_distance (*float*) :** available for linear attenuation only. Default is `25.0f`.

- **sound_decay_coef (*float*) :** available for inverse attenuation only. Default is `1e-6`. Try to tune this value to makes attenuation more or less efficient.

-----

## Inputs

### HelloInput

This is a simple input which automatically outputs the following generic sentence: "Aspic Audiostack says hello". 

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`out`		|1						|1 (MONO)			|


#### Construction

No arguments 

Usage : 
```cpp
context.createInput(ID,HelloInput);
```


#### Parameters

- **buffer_size (*unsigned int*)** : the length of audio buffers.

	This parameter is mapped by default to `application/buffer_size`.

	Usage : 
```cpp
context.setParameter("application/buffer_size",4096U)
// OR
context.setParameter("input/ID/buffer_size",4096U)
```

### OpenALInput

This input uses OpenAL API to access computer microphones. If you have multiple input devices, this OpenAL wrapper will choose the default one.

On windows, you can change default microphone in the control panel, section Sound, tab recording.

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`out`		|1						|1 (MONO)			|

#### Construction

No arguments 

Usage : 
```cpp
context.createInput(ID,OpenALInput);
```

#### Parameters

- **buffer_size (*unsigned int*)** : the length of microphone audio buffers. Due to OpenAL drivers latency, values less than 2048 will create sound cracks. Recommanded value is 4096.

	This parameter is mapped by default to `application/buffer_size`.

	Usage : 
```cpp
context.setParameter("application/buffer_size",4096U)
// OR
context.setParameter("input/ID/buffer_size",4096U)
```

------

## Outputs

### OpenALOutput

Uses OpenAL API to output audio on speakers/headphone. Will use the default device if your computer have multiple outputs.

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`in`		|N						|1 or 2 (see construction)|

#### Construction

- **stereo (*int*)** : output will be stereo if value is set to 1 or to mono if value is set to 0. When building a diagram, please ensure effects and outputs have compatible channel count : stereo effects may be plugged into stereo outputs.

	Usage : 
	
```cpp
context.createOutput(ID,OpenALOutput,1); // creates a stereo output 
context.createOutput(ID,OpenALOutput,0); // creates a mono output
```

#### Parameters

No parameters

## Code samples


### C++ API Samples

#### OpenAL simple application

This sample connects microphone to computer output using OpenAL drivers.

Please note this sample doesn't handle errors, please go direclty to the next sample for error handling.

```cpp
{% include_relative samples/Core_1_OpenAL.cpp %}
```

##### Error handling

The previous sample doesn't catch any error, here is the sample application with error handling.

```cpp
{% include_relative samples/Core_1_OpenAL_Error.cpp %}
```


#### 2D Bus and gain

The following sample is provided without error handling for code clarity.

```cpp
{% include_relative samples/Core_2_Bus2D_Gain.cpp %}
```

#### Distance attenuation

The following samples uses AttenuationEffect and introduces source and listener position modification.

```cpp
{% include_relative samples/Core_3_Attenuation.cpp %}
```