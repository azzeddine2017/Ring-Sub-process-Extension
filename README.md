# Ring Subprocess Extension

A powerful subprocess management extension for the Ring programming language that provides a simple interface for creating and managing system processes.

## Features

- Create and manage system processes
- Capture process output
- Wait for process completion
- Terminate running processes
- Simple and intuitive API

## Installation

- clone `https://github.com/azzeddine2017/Ring-Sub-process-Extension.git` in folder ring/extensions

### Build Steps

- Build the extension using the provided `buildvc_x64.bat` script:
```batch
buildvc_x64.bat
```

## Usage

### Basic Example

```ring
load "subprocess.ring"

proc = new ProcessManager()
proc.runCommand("cmd.exe /c dir")
proc.waitForComplete()
? proc.readOutput()
proc.kill()
```

### API Reference

The extension provides a `ProcessManager` class with the following methods:

#### runCommand(command)
Creates and executes a new process with the specified command.
```ring
proc.runCommand("cmd.exe /c echo Hello World")
```

#### waitForComplete()
Waits for the process to complete and captures its output.
```ring
proc.waitForComplete()
```

#### readOutput()
Returns the captured output from the process.
```ring
output = proc.readOutput()
```

#### kill()
Terminates the running process.
```ring
proc.kill()
```

#### isActive()
Checks if the process is still running.
```ring
if proc.isActive()
    ? "Process is still running"
ok
```

## Implementation Details

The extension uses `_popen` for process creation and management, which provides several advantages:
- Simple and reliable process creation
- Built-in output capture functionality
- Avoids conflicts with Ring's existing system functions


## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contributing

Contributions are welcome! Here are some ways you can contribute:
1. Reporting bugs
2. Suggesting enhancements
3. Adding new features
4. Improving documentation

## Future Enhancements

Planned features for future releases:
- Exit code retrieval
- Asynchronous execution support
- Standard input (stdin) redirection
- Enhanced error handling
- Cross-platform support improvements
