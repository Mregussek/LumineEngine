
# Lumine Engine

## How to setup project

```bash
./rr --help
usage: run.py [-h] [-m {debug,release}] [-g {vulkan,dx12}] [--generate] [--build] [--clean] [--run] [--open]

LumineEngine runner script

options:
  -h, --help            show this help message and exit
  -m, --mode {debug,release}
                        Specify generate/build mode (default: release)
  -g, --graphics {vulkan,dx12}
                        Specify graphics API (default: vulkan)
  --generate            Generates the project (--graphics flag dependent)
  --build               Generates and builds the project (--graphics flag dependent)
  --clean               Cleans the build project (--graphics flag dependent)
  --run                 Runs the sandbox
  --open                Opens the project in IDE (Visual Studio)
```
