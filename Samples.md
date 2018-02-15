---
title: Code samples
permalink: /audiostack/Samples/
---

{% icon fa-exclamation-triangle  %} {% icon fa-exclamation-triangle  %} {% icon fa-exclamation-triangle  %} WARNING : Audiostack documentation is not up to date anymore. We are working on it to provide you a nice and simple new doc as soon as possible.

### Extension specific samples

You can find code samples for each extension :

- [Core samples](../Core)
- [Audio file samples](../AudioFile)
- [Binaural samples](../Binaural)
- [Nahimic samples](../Nahimic)
- [ASIO samples](../Asio)
- [VBAP samples](../VBAP)
- *[OSC samples](../OSC)*

### Error handling

A wide majority of code samples in this documentation does not include any error handling, for readability.

The following sample detects context errors and provides exceptions.

```cpp
{% include_relative samples/Error.cpp %}
```