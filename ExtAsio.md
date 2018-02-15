---
title: Asio module
permalink: /audiostack/Asio/
---

ASIO (Audio Stream Input/Output) is a computer sound card driver protocol. It enables to address inputs and outputs from many professional sound card.

> Only one driver can be used simultaneously in one Audiostack instance.

##Inputs

### AsioInput

Provides access to multiple inputs from a connected sound card with ASIO support.

> Multiple AsioInput can be used but all must use the same driver. 

| I/O		| Channel count 		| Sub channel count					|
-|:-:|-:
|`out`		|1						|audio slot size (see construction)	|



#### Construction

- **audioSlot (*const char* *)** : a string composed of the driver name and a list of input names. The input will have as many subchannels as input names in the list.

Usage for a Focusrite sound card creating a two subchannels input:

```cpp
context.createInput(ID,AsioInput,"Focusrite USB 2.0 Audio Driver:Input 1,Input 2");
```

- **audioSlot (*AudioSlot&*)** : an AudioSlot object representing the driver and the list of inputs (see [AudioSlot](#AudioSlot)).

#### Parameters

- **buffer_size (*unsigned int*)** : the length of microphone audio buffers.

	This parameter is mapped by default to `application/buffer_size`.

	Usage : 
```cpp
context.setParameter("application/buffer_size",4096U)
// OR
context.setParameter("input/ID/buffer_size",4096U)
```

##Outputs

### AsioOutput

Provides access to multiple outputs from a connected sound card with ASIO support.

> Multiple AsioOutput can be used but all must use the same driver. 

| I/O		| Channel count 		| Sub channel count					|
-|:-:|-:
|`in`		|N						|audio slot size (see construction)	|



#### Construction

- **audioSlot (*const char* *)** : a string composed of the driver name and a list of output names. The output will have as many subchannels as output names in the list.

Usage for a Focusrite sound card creating a two subchannels output:

```cpp
context.createOutput(ID,AsioOutput,"Focusrite USB 2.0 Audio Driver:Output 1,Output 2");
```

- **TODO** **audioSlot (*AudioSlot&*)** : an AudioSlot object representing the driver and the list of outputs (see [AudioSlot](#AudioSlot)).

#### Parameters

- **buffer_size (*unsigned int*)** : the length of microphone audio buffers.

	This parameter is mapped by default to `application/buffer_size`.

	Usage : 
```cpp
context.setParameter("application/buffer_size",4096U)
// OR
context.setParameter("input/ID/buffer_size",4096U)
```

## Classes

### AudioDriverList
```cpp 
unsigned int getNbDrivers()
```
```cpp 
const char* getDriverName(unsigned int _driverId)
```
```cpp 
const char* getDefaultDriver()
```

### AudioDriver


```cpp 
const char* getDriverName()
```
> returns the name of the represented ASIO driver

```cpp 
unsigned int getNbInputs()
```
> returns the number of inputs available on the connected soundcard

```cpp
unsigned int getNbOutputs()
```
> returns the number of outputs available on the connected soundcard

```cpp
const char* getInputName(unsigned int _inputId)
```
> returns the name of the nth input

```cpp
const char* getOuputName(unsigned int _outputId)
```
> returns the name of the nth output

```cpp
void getAvailableBufferSize(unsigned int& _current, unsigned int& _min, unsigned int& _max, unsigned int& _preferred)
```


```cpp
bool hasInput(const char* _inputName)
```
> returns true if _inputName is an available input 


```cpp
bool hasOuput(const char* _outputName)
```
> returns true if _outputName is an available output 

### AudioSlot



```cpp
AudioSlot(AudioDriver& _driver, bool _isInput)
```


```cpp
void bind(const char* _inOutName)
```


```cpp
void bindWithPosition(const char* _inOutName, float* _pos)
```


```cpp
const char* asString()
```


------


## Code samples


### C++ API Samples

> **Note: ** Our Asio Inspector program, provided with Aspic Audiostack, enables you to get info about available asio drivers on your computer.

#### ASIO Basics

This sample spatialize hello input for one listener with 2 speakers on an asio device.

```cpp
{!../samples/Asio_1_Basics.cpp!}
```

#### Multilistener using ASIO

This sample spatialize hello input for two listeners on the same host. Each listener gets individualized spatialization.

```cpp
{% include_relative samples/Asio_2_Multilistener.cpp %}
```


