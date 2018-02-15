---
title: OSC module
permalink: /audiostack/OSC/
---


OSC (Open Sound Control) is a very handy and flexible network protocol. OSC messages consist of an address pattern, a type and arguments. OSC address pattern are very similar to Audiostack addresses, so that managing Audiostack through OSC is quite easy.

## Classes

### OSCServer

*OSCServer* is a class that enables to control *parameters*, *commands* and *callbacks* through OSC network protocol. These are aimed with the same address as they are usually. For callbacks, the value that has to be given is the remote handler of an other OSC server.

For advanced features, some methods are proposed to add user defined commands.

```cpp
OSCServer(AudiostackContext& _context)
```
>	Construct an OSCServer that can interact with an AudiostackContext *_context*.

```cpp
start(int _listeningPort)
```
>	starts listening dor OSC messages.

```cpp
void stop()
```
> stops listening to OSC messages.

```cpp
void setCallbackDestination(const char* _ipAddress, int _port)
```
> configures the OSC server to send audiostack callbacks to an other OSC server at *_ipAddress* that listen to port *_port*.

```cpp
void registerCommand(const char* _address, Fn _functionPointer, void* _context)
```
> registers a handler called when receiving an OSC message at address *_address*. The *_context* argument can be used to store custom user information. *_functionPointer* is a function pointer of a supported type. 
This method is useful to handle other message that those linked to parameters, commands and callbacks.

```cpp
void sendCallback(const char* _address, const char* _content)
```
**TO RENAME**
> sends an OSC message containing _content to callback destination with address _address.