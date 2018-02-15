---
title: Audio file module
permalink: /audiostack/AudioFile/
---

{% icon fa-exclamation-triangle  %} {% icon fa-exclamation-triangle  %} {% icon fa-exclamation-triangle  %} WARNING : Audiostack documentation is not up to date anymore. We are working on it to provide you a nice and simple new doc as soon as possible.

Aspic Audiostack Audio file module enables applications to read audio file on your drive. The only file format supported is .wav. More extension will be supported soon. Please contact us for more details.

## Inputs

### AudioFileReader

This input read a file on your drive and outputs its audio content. It provides commands to pause or resume reading.

> **WAV Files** : must be monophonic and encoded at 48kHz/16bits.

| I/O		| Channel count 		| Sub channel count	|
-|:-:|-:
|`out`		|1						|1 (MONO)			|

#### Construction

No arguments 

Usage : 
```cpp
context.createInput(ID,AudioFileReader);
```

#### Parameters

- **filename (*const char* *) :** path (with filename and extension) to the audio file to read. May be an absolute path or a relative path (relative to the executable location).

	This parameter is mapped by default to `source/%src_id/file`.

	Usage : 
	
```cpp
context.setParameter("input/ID/filename","./hello.wav");
// OR
context.setParameter("source/ID/file","./hello.wav");
```
	
- **buffer_size (*unsigned int*) :** the length of audio buffers read by this input.

	This parameter is mapped by default to `application/buffer_size`.

	Usage : 
	
```cpp
context.setParameter("application/buffer_size",4096U);
// OR
context.setParameter("input/ID/buffer_size",4096U);
```

- **loop (*bool*) :** if set to TRUE, audiofile will be played in loops, which may prove usefull for background sounds. Default is FALSE.

	This parameter is mapped by default to `source/%src_id/loop`.

	Usage : 
```cpp
context.setParameter("source/ID/loop",true);
// OR 
context.setParameter("input/ID/loop",true);
```

- **start_on_awake (*bool*) :** if set to TRUE, file is played when application starts, which is usefull for background sounds. Default value is FALSE (usefull for event sounds).

	This parameter is mapped by default to `source/%src_id/start_on_awake`.

	Usage : 
	
```cpp
context.setParameter("source/ID/start_on_awake",true);
// OR
context.setParameter("input/ID/start_on_awake",true);
```

#### Commands

- **play :** resume file reading.

	This parameter is mapped by default to `source/%src_id/play`.

	Usage : 
	
```cpp
context.sendCommand("source/ID/play");
```

- **pause :** pause file reading. Reader head remains at its current position.

	This parameter is mapped by default to `source/%src_id/pause`.

	Usage : 
	
```cpp
context.sendCommand("source/ID/pause");
```
	
- **stop :** stop file reading and place reader head to the beginning of the file.

	This parameter is mapped by default to `source/%src_id/stop`.

	Usage : 
```cpp
context.sendCommand("source/ID/stop");
```
	
- **seek (*int*) :** move the header head N samples afer begin. *Seek* doesn't start or stop file reading.

	This parameter is mapped by default to `source/%src_id/seek`.

	Usage : 
```cpp
context.sendCommand("source/ID/seek",4800);
```
	
#### Callbacks
	
- **at_end :** this callback is called when file reading reaches the end of the file. You can use it to notify your application and trigger an event.

	This parameter is mapped by default to `source/%src_id/at_end`.

	Usage : 
```cpp
context.setCallback("src/ID/at_end",&atEndCallback); // atEndCallback is an argument-less function returning void.
``` 

## Helpers



## Code samples


### C++ API Samples

#### AudioFile simple application

This sample connects an audio file reader to computer output using OpenAL drivers.

Please note this sample doesn't handle errors for code clarity.

```cpp
{% include_relative samples/AudioFile_1_Basics.cpp %}
```

#### AudioFile callbacks

This sample provides hints to use callbacks on file reader.

In this use case, the application stops once the file reading reaches end of file.

```cpp
{% include_relative samples/AudioFile_2_Callback.cpp %}
```

## Helpers