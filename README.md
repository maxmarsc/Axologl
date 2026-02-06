# Axologl

<img src="assets/axologl.png" alt="Axologl logo" width="256">

A simple logging library for Nintendo Switch homebrew designed to integrate with `libnx` and `nxlink`.

---

# Table of Contents

- [Background](#background)
    - [Why Axologl?](#why-axologl)
- [Install](#install)
- [Usage](#usage)
- [Configuration](#configuration)
    - [Runtime Configuration](#runtime-configuration)
- [API](#api)
- [Thanks](#thanks)
- [Contributing](#contributing)
- [Licence](#licence)

# Background

Logging can seem fairly trivial in most projects, and it's really no different in a Switch homebrew project. While
working on another project, I soon found myself reaching for a simple way to log messages to the console. Rather than
implementing a solution directly in that project, I figured why not create a simple library that I can share with the
community?

## Why Axologl?

Sure, it's an odd name. Honestly, no idea what was going through my head at the time, but I knew the name had to somehow
reflect the fact that it was a logging library. While trying to shoehorn in something about `libnx` or `nxlink`,
Axologl popped in to my head.

---

# Install

Axologl is a header-only library and as such the `include` folder can be easily dropped in to any Switch homebrew
project based on `libnx`/devkitPro. Alternatively, you can link it as a submodule in your project with:

```shell
git submodule add https://github.com/ixalsera/Axologl <your_dependency_folder>/Axologl
```

Then don't forget to include it in your Makefile under `INCLUDES`!

```makefile
INCLUDES    :=  include <your_dependency_folder>/Axologl/include
```

---

# Usage

1. Include `axologl.h` in your main header or source file.
2. Set your configuration options (Optional).
3. Initialize Axologl.
4. Use any of the Axologl logging functions.

```c++
// main.cpp
#include <switch.h>
#include <axologl.h>

int main()
{
    consoleInit(NULL);
    const axologl::AxologlOptions options;
    axologl::configure(options);
    
    /*
     * Your amazing homebrew code goes here
     */
    
    axologl::debug("Axologl is great!")
    
    consoleExit(NULL);
    return 0;
}
```

Check out [the test file](https://github.com/ixalsera/Axologl/blob/main/test/main.cpp) for a detailed look.

---

# Configuration

You can configure Axologl by passing in some options when initializing the library, either by creating a full
`AxologlOptions` object or by instantiating a default one and changing whichever options are relevant for you.

Below is the default configuration when instantiating an `AxologlOptions` struct:

```c++
 {
     logLevel = axologl::Warning, // The logging level to use; less urgent messages get discarded
     nxLinkOpts = {
         enabled = false,         // nxlink will not be configured
         redirectStdout = false,  // nxlink will not send stdout (irrelevant if `enable` is false)
         redirectStderr = false   // nxlink will not send stderr (irrelevant if `enable` is false)
     },
     ansiOutput = true,           // ANSI colorization will be enabled
     logPath = ?                  // No log file provided; file logging will be disabled
 };
```

Thus, changing just the ANSI setting would look something like:

```c++
const axologl::AxologlOptions options;
options.ansiOutput = false;
```

## Runtime Configuration

Some options may be altered during runtime:

|      Option      | Function                               |
|:----------------:|:---------------------------------------|
|   Enable ANSI    | `axologl::enableAnsi()`                |
|   Disable ANSI   | `axologl::disableAnsi()`               |
| Change Log Level | `axologl::setLogLevel(LogLevel level)` |

---

# API

The following functions are available for logging, with prespecified ANSI colorization (if enabled) and prefixes:

| Function            |   Prefix   | Colour |
|:--------------------|:----------:|:------:|
| `axologl::debug()`  | `[DEBUG]`  | Purple |
| `axologl::info()`   |  `[INFO]`  |  Blue  |
| `axologl::notice()` | `[NOTICE]` |  Blue  |
| `axologl::warn()`   |  `[WARN]`  | Yellow |
| `axologl::error()`  | `[ERROR]`  |  Red   |
| `axologl::fatal()`  | `[FATAL]`  |  Red   |

Additionally, the following functions are available with prespecified ANSI colours (if enabled):

| Function             | Colour |
|:---------------------|:------:|
| `axologl::success()` | Green  |
| `axologl::failure()` |  Red   |

---

# Thanks

- The [devkitPro team](https://devkitpro.org) for their amazing suite of tools that have made homebrewing for Nintendo
  consoles possible
- [XorTroll](https://github.com/XorTroll) for the great tools they've created whose source code has helped me learn so
  much

---

# Contributing

Please report any issues (and I'm sure there will be plenty; this is my first C++ library!)
using [GitHub Issues](https://github.com/ixalsera/Axologl/issues).

PRs are welcome (especially if you can teach me something while improving the code!)

---

# Licence

Axologl is released under the GNU General Public License v3.0. You can find the full licence [here](LICENSE).