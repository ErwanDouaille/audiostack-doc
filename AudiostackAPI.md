---
title: C++ API Documentation
permalink: /audiostack/AudiostackAPI/
---

{% icon fa-exclamation-triangle  %} {% icon fa-exclamation-triangle  %} {% icon fa-exclamation-triangle  %} WARNING : Audiostack documentation is not up to date anymore. We are working on it to provide you a nice and simple new doc as soon as possible.

Getting started
-----
During the installation process, several directories were created at the installation location.

- **bin**: contains runtime libraries, asio inspector and audiostack server
- **cmake**: contains CMake scripts to help CMake find the library
- **depends**: contains third party installers like OpenAL
- **doc**: the directory where this documentation is stored
- **include** : contains the C and C++ header files
- **lib32 and lib64** : contains the dynamic libraries to ship with your application
- **samples** : contains some ready to test code sample and cmake projects 

The C API is provided for cross-compiler compatibility and is not designed to be used directly.
The C++ API is then strongly recommended. The current API documentation will only focus on the C++ version.

### Requirements

* C++ compiler with C++11 support and correctly chosen architecture
* CMake to build given *samples*
* The installation process should have created an environment variable *AUDIOSTACK_CMAKE* containing the path to the *cmake/* directory located in the installation directory. Please ensure that this variable is correctly filled.

### Building *samples*
To build all the samples, please execute the following commands. If not available on your system, there must exist close alternatives.

```console
cd samples/
mkdir build
cd build
cmake ..
make
```

### Helloworld using *Aspic Audiostack* and *CMake*
Create a new project directory

* CMakeLists.txt  

```cmake
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{AUDIOSTACK_CMAKE}")

project(helloworld)
add_executable(helloworld hello.cpp)

find_package (AspicAudiostack)
if (AspicAudiostack_FOUND)
  include_directories(${AspicAudiostack_INCLUDE_DIRS})
  target_link_libraries (helloworld ${AspicAudiostack_LIBRARIES})
endif (AspicAudiostack_FOUND)
```
* hello.cpp

```c++
#include <iostream>
#include "Audiostack.hpp"

int main(){
	AudiostackContext context;
	context.setLicenseKeyFromFile("LICENSE_FILE.aslc");
	
	int input=0
	int output=1;
	context.createInput(input,HelloInput);
	context.createOutput(output,OpenALOutput);
	
	context.connect(input,output);
	
	context.play();
	
	char c;
	do{
		std::cin>> c;
	}while(c!='q');
	
	context.stop();
	
	return 0;
}
```

AudiostackContext
-----

*AudiostackContext* is the main class of *Aspic Audiostack*. 

### Construction/Destruction

```c++
AudiostackContext()
```
> Construct an *AudiostackContext*.

```c++
~AudiostackContext()
```
> Destroy the *AudiostackContext*. While destroying, the diagram is totally cleared

```c++
void clear()
```
> Clear the diagram. All inputs, outputs, buses, effects and parameters are destroyed.

```c++
void setLicenseKeyFromFile(const char* _keyFile);
```

> Set a license file. A valid license file must be loaded to ensure diagram construction will work properly. License files holds information about the modules you have access to (Binaural, Asio, Vbap).

```c++
void setLicenseKeyFromMemory(const char* _address, int _length);
```

> Load license data from memory. License content must be stored in a char[].


### Diagram edition

```c++
int createInput(int _objectId, int _inputType, Args...)
```	
					
> Create an audio input of *_inputType* with *objectId* as identifier. Returns the identifier of the object if the operation is successful, -1 otherwise.

> Please also note that *_objectId* must be unique among all inputs, outputs, buses and effects.

> See [API Extensions sections](#api-extensions) to learn more about available inputs and their parameters.


```c++
int createOutput(int _objectId, int _outputType, Args...)
```
> Create an audio output of *_ouputType* with *_objectId* as identifier. Returns the identifier of the object if the operation is successful, -1 otherwise.

> *_objectId* must be unique among all inputs, outputs, buses and effects.

> See API Extensions sections to learn more about available outputs and their parameters.
		

```c++		
int createBus(int _objectId)
```
> Create an audio bus with *_objectId* as identifier. Returns the identifier of the object if the operation is successful, -1 otherwise.

> *_objectId* must be unique among all inputs, outputs, buses and effects.

```c++		
void setLastEffectCount(int _busId, int _lastEffectCount)
```
> Set the number of instance of the last effect in the bus *_busId* to *_lastEffectCount*. Effects in the bus will be duplicated to enable differentiated processing, like independent spatialization and attenuation for multiple listeners. The bus will have multiple inputs and outputs (see [naming section](#naming)).

> See our samples to go further.

```c++
int createEffect(int _objectId, int _busId, int _effectType, Args...)
```
> Create an audio effect of type *_effectType* at the back of bus *_busId* with *_objectId* as identifier. Returns the identifier of the object if the operation is successful, -1 otherwise.

> *_objectId* must be unique among all inputs, outputs, buses and effects.

> See API Extensions sections to learn more about available effects and their parameters.



```c++
void removeInput(int _objectId)
``` 																

> Remove audio input holding identifier *_objectId*.


```c++
void removeOutput(int _objectId)
``` 																
> Remove audio output holding identifier *_objectId*.


```c++
void removeBus(int _objectId)
``` 																    
> Remove audio bus holding identifier *_objectId* and all of its effects.


```c++
void removeEffect(int _objectId)
``` 																
> Remove audio effect holding identifier *_objectId*.



```c++
void connect(int _outObjectId, const char* _outputName, int _inObjectId, const char* _inputName)
```
> Connects the output *_outputName* of object *_outObjectId* to the input *_inputName* of object *_inObjectId*. Use this method to connect all your  inputs, buses and outputs. 

#### Naming

Audio inputs own a sole output called "out".

Audio outputs own a sole input called "in".

Buses may own many inputs/outputs. For instance, a spatialization bus effect for 2 listeners holds 2 outputs and inputs. Therefore, these inputs/outputs are named : `in_0`, `in_1`, `out_0`, `out_1`, etc.


```c++
void connect(int _outObjectId, int _inObjectId)
```													 
> This method is easier to use for objects owning only one input/output. In case of ambiguity, for instance when *_inObjectId* or *_outObjectId* owns many inputs or outputs, this method will raise an error (see Error handling section).


```c++
void disconnect(int _outObjectId, const char* _outputName, int _inObjectId, const char* _inputName)
```
> Disconnect given objects.








### Parameters

Parameters are declared and owned by inputs, outputs or effects. The following function may prove useful to modify these parameters. Please refer to [dedicated doc](../index#parameters) to get a better grasp on parameters, and to [API Extensions sections](#api-extensions) to learn more about available parameters.

```c++
void setParameter(const char* _param, T _value)
```
> Apply the value *_value* to the parameter at address *_param*

> Please note that parameters mapping on multivalued parameters is only resolved **at runtime**. It means that you can use setParameter to modify parameters at all time, but that multivalued effects mapping (like `listener/ID/position` or `source/ID/gain`) will only be available after play() has been called.

> Therefore, before play(), you can either :
> - modify parameters using non mapped addresses (`effect/EFFECT_ID/listener_position/CHANNEL_ID` or `effect/EFFECT_ID/src_gain/CHANNEL_ID`), which is probably the least interesting way,
> - use setParameterAtInit() methods. They accept mapped addresses and apply values when play() is called.
> After play(), use setParameter().

> This approach relates to multivalued parameters (ex: position, gain, mute, rotation) whose parameter mapping requires runtime resolution. For all other parameters (ex : buffer size, sample rate), mapping (ex: application/buffer_size) is resolved automatically allowing offline modification.

#### Samples

> SetParameter sample (non runtime parameter):
```cpp
// Valid
context.setParameter("application/buffer_size", 4096U);

context.play();

// NOT Valid
context.setParameter("application/buffer_size", 4096U);
```

> SetParameter sample (runtime parameter):
```cpp
// NOT Valid
context.setParameter("source/SOURCE_ID/position", sourcePos);

context.play();

// Valid
context.setParameter("source/SOURCE_ID/position", sourcePos);
```

> SetParameter and SetParameterAtInit :
```cpp
// Valid
context.setParameterAtInitVec3("source/SOURCE_ID/position", sourcePos);

context.play();

// Also Valid
context.setParameter("source/SOURCE_ID/position", sourcePos);
```

------

```c++
void setParameterAtInit(const char* _param, T _value)
```
> Apply the value *_value* to the parameter at address *_param* when play() is called on AudiostackContext. 

```c++
void setParameterAtInitVec3(const char* _param, const float* _value)
```
> Apply the value *_value* to the parameter at address *_param* when play() is called on AudiostackContext. Value must be a table of 3 float.


```c++
void sendCommand(const char* _param, Args...)
```
> Send command *Args* to address *_param*. 

```c++
void setCallback(const char* _param, void(*_f)(Args...))
```
> Set callback *_f* to address *_param*. 



```c++
void beginParameterBundle()
```
> Begin a new parameter bundle. If a bundle is opened, all parameter modifications are stored and applied at bundle's closure.
			
```c++
void endParameterBundle()
```
> End the current parameter bundle, applies all parameters modifications called since the last call to beginParameterBundle().
					 
```c++
void setParameterPattern(int _objectId, const char* _param, const char* _pattern)
```

> Apply the pattern *_pattern* to the parameter *_param* of object *_objectId*. If successful, the parameter will be mapped to the pattern.
 			 
```c++
void setVariable(int _objectId, const char* _variable, T _value)
```

> Set a variable named *_variable* of value *_value* on the object designated by id *_objectId*.
		






		

### Play/Stop

```c++
void play()
```
> Start audio processing. No diagram modification may be applied after play() (except for runtime parameters).

```c++
void stop()
```
> Stop audio processing.


### Extensions

Aspic Audiostack API is divided into modules. Each module offer specific features (such as Binaural rendering or Network streaming).

Since these methods are wrapped, please refer to API Extensions section for more information.

```c++
void loadModule(const char* _module)
```
> Load module of name *_module* in current context. If successful, the context will now enable the developer to access methods and inputs/outputs/effects of this module.

```c++
void* getSymbol(const char* _module, const char* _symbol)
```
> Modules may contain specific functions. This method returns a pointer to the symbol named *_symbol*. Please see Extensions sections to learn more about available symbols.


### Error handling

AudiostackContext will not throw any exception. Instead, each method call may set an error flag that you have to check.

```c++
static int getError()
```
> Return error status of the API. A value equal to 0 means there is no error. A value equal to 1 means an error has been raised.

> Please note that calling this method will **reset the internal error flag** to 0.

```c++
static const char* getLastErrorMessage()
```
> Contains the description of the last error raised. You typically want to get this message right after a getError call returned 1.

> Since this method doesn't change any internal state, an empty error message doesn't mean there are no error.


API Extensions
-----
To use complementary features proposed along with *Aspic Audiostack*. There exists some extension API. These functionalities are complementary outputs, inputs and effects types but also helper functions and objects to handle ASIO, OSC, Audio file, etc. more easily.

### Loading extensions
Extensions are loaded through the *AudiostackContext* using *loadModule* and *getSymbol*. Alternatively, most of the extension are proposed with a C++ wrapper that is able to load all symbols through the *AudiostackContext*.

Given an extension called *MyExtension*, a sample program loading that extension may look like this :

```c++
#include "Audiostack.hpp"
#include "AudiostackExtension.h"

int main(){
	AudiostackContext context;
	context.setLicenseKeyFromFile("LICENSE_FILE.aslc");

	MyExtentionInterface::Load(context.impl);
	
	MyExtention extension;
	extension.myFunction()
	...
```

In the previous example, constructing a *MyExtention* before the call *MyExtensionInterface::Load* would have caused a segmentation fault.

### Available extensions
 
Here is a list of available extensions for *Aspic Audiostack*. Those that you can use depends on the license you have agreed to.

| Extension 								| Features 	|
| -----										| -----		|
| [Core](../ExtCore)					| OpenAL stereo output and microphone input, mixing, simple 3D sound (attenuation over distance and simple panning), gain			|
| [AudioFile](../ExtAudioFile)			| Read audio files, access file information (samplerate, length, etc.) and keep them in a easy to use library.									|
| *Extended-core*							| Additional effects (Low pass filter, high pass filter, equalizer, delay, simple reverberation)									|
| [Binaural](../ExtBinaural)			| Binaural spatialization based on HRTF for precise perception of sound incoming direction.											|
| [Nahimic4Audiostack](../ExtNahimic)	| Binaural spatialization based on HRTF for precise perception of sound incoming direction. Developed by *A-Volute*					|
| *Aspic Engine*							| Realistic geometry-based rendering (with echo, occlusion and convolution reverb) 													|			
| [Asio](../ExtAsio)					| Professionnal sound card handling for multi-headset or multi-speaker addressing. Enable lowest latencies.							|
| [VBAP](../ExtVBAP)					| Enable spatialization over multiple speakers on a 2d or 3d layout.																|
| [OpenSoundControl](../ExtOSC)		| Binding for OSC; enable to control parameters, command and callbacks. Custom method can be added											|
| *Rtp*										| Audio streaming between clients and server can be done. A handshake service is provided for NAT punchthrough and peer discovery.	|
| *PluginAPI*								| User can register custom effects, inputs and outputs																				|

*Work In Progress*
