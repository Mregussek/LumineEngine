
import subprocess
import argparse
import platform
import logging
import json
import os


WIN64 = "win64"
LINUX64 = "linux64"
RELEASE = "release"
DEBUG = "debug"
VULKAN = "vulkan"
DIRECTX12 = "directx12"
CMAKE_BUILD_DIR = "build"


def ensure_path_exists(path):
    if os.path.exists(path):
        return

    msg = f"Path does not exist: {path}"
    logging.error(msg)
    raise FileNotFoundError(msg)


def get_entries_in(path):
    return [f.path for f in os.scandir(path) if f.is_dir()]


def select_first_path_from(paths):
    if paths:
        first = paths[0]
        return first

    msg = "Paths list is empty."
    logging.error(msg)
    raise FileNotFoundError(msg)


class ArgParser:
    def __init__(self):
        parser = argparse.ArgumentParser(description='LumineEngine runner script')
        parser.add_argument('-m', '--mode', choices=[DEBUG, RELEASE], default=RELEASE,
                            help='Specify generate/build mode (default: {})'.format(RELEASE))
        parser.add_argument('-g', '--graphics', choices=[VULKAN, DIRECTX12], default=VULKAN,
                            help='Specify graphics API (default: {})'.format(VULKAN))
        parser.add_argument('--generate', action='store_true',
                            help='Generates the project (--graphics flag dependent)')
        parser.add_argument('--build', action='store_true',
                            help='Generates and builds the project (--graphics flag dependent)')
        parser.add_argument('--clean', action='store_true',
                            help='Cleans the build project (--graphics flag dependent)')
        parser.add_argument('--run', action='store_true', help='Runs the sandbox')
        self.__args = parser.parse_args()

    def should_generate(self):
        return self.__args.generate

    def should_build(self):
        return self.__args.build

    def should_clean(self):
        return self.__args.clean

    def should_run(self):
        return self.__args.run

    def get_build_mode(self):
        if self.__args.mode == DEBUG:
            return DEBUG
        return RELEASE
    
    def get_graphics_api(self):
        if self.__args.graphics == DIRECTX12:
            return DIRECTX12
        return VULKAN


class Platform:
    def is_win64():
        return platform.system().lower() == "windows"

    def is_linux():
        return platform.system().lower() == "linux"


class CMakePresetsParser:

    __DEFAULT_PRESETS_FILE = "CMakePresets.json"

    def __init__(self):
        logging.debug("Loading CMake presets...")
        presets_file = CMakePresetsParser.__DEFAULT_PRESETS_FILE

        with open(presets_file, 'r') as file:
            presets = json.load(file)
            if not presets:
                msg = "Could not load CMake presets from {}.".format(presets_file)
                logging.error(msg)
                raise FileNotFoundError(msg)

        logging.debug("Loaded {}".format(presets_file))
        self.build_presets = presets.get('buildPresets', [])
        self.configure_presets = presets.get('configurePresets', [])

    def get_configure_preset(self, platform, mode):
        preset = CMakePresetsParser.__get_preset_name(self.configure_presets, platform, mode)
        logging.info("Selected configure preset: {}".format(preset))
        return preset

    def get_build_preset(self, platform, mode):
        preset = CMakePresetsParser.__get_preset_name(self.build_presets, platform, mode)
        logging.info("Selected build preset: {}".format(preset))
        return preset

    def __get_preset_name(presets, platform, mode):
        logging.debug(f"Getting preset for {mode}...")
        for preset in presets:
            name = preset.get('name', '').lower()
            if platform in name and mode in name:
                logging.debug(f"Selected preset: {preset}")
                return name
        
        msg = 'No valid preset found.'
        logging.error(msg)
        raise RuntimeError(msg)


class CMakeRunner:

    __USE_VK = "-DLUMINE_USE_VULKAN={}"
    __USE_DX12 = "-DLUMINE_USE_DIRECTX12={}"

    @staticmethod
    def get_generate_cmd(preset, graphics_api):
        return CMakeRunner.__get_graphics_dependent_cmd("cmake --preset={}".format(preset),
                                                        graphics_api)

    @staticmethod
    def get_build_cmd(preset):
        return "cmake --build --preset={}".format(preset)

    @staticmethod
    def get_fresh_cmd(preset, graphics_api):
        return CMakeRunner.__get_graphics_dependent_cmd("cmake --fresh --preset={}".format(preset),
                                                        graphics_api)

    @staticmethod
    def __get_graphics_dependent_cmd(cmd, graphics_api):
        if graphics_api == DIRECTX12:
            dx12 = CMakeRunner.__USE_DX12.format("1")
            vk = CMakeRunner.__USE_VK.format("0")
        else:
            dx12 = CMakeRunner.__USE_DX12.format("0")
            vk = CMakeRunner.__USE_VK.format("1")
        return "{} {} {}".format(cmd, dx12, vk)


class WindowsRunner:

    __DEFAULT_VS_BASE_PATHS = [
        "C:\\Program Files (x86)\\Microsoft Visual Studio\\2022",
        "C:\\Program Files\\Microsoft Visual Studio\\2022"
    ]

    __DEFAULT_SANDBOX_FILENAME = "LumineSandbox.exe"

    def __init__(self):
        vs_base = WindowsRunner.__get_vs_base_path(WindowsRunner.__DEFAULT_VS_BASE_PATHS)
        vs_edition = WindowsRunner.__get_available_vs_edition(vs_base)

        self.vs_dev_cmd = WindowsRunner.__get_dev_cmd_prompt(vs_edition)

    def run_dev_command(self, command):
        dev_command = 'cmd.exe /c \"\"{}\" && {}\"'.format(self.vs_dev_cmd, command)
        logging.info(f"Running dev command: {dev_command}\n")
        process = WindowsRunner.__run_cmd(dev_command)

        print("\n")
        if process.returncode == 0:
            logging.info("Command \"{}\" in VsDevCmd.bat executed successfully.".format(command))
            return
        else:
            _, stderr = process.communicate()
            msg =\
                "Command \"{}\" in VsDevCmd.bat failed with {} rc:\n\n{}".format(command,
                                                                                 process.returncode,
                                                                                 stderr)
            logging.error(msg)
            raise RuntimeError(msg)

    def run_sandbox(self, build_mode):
        sandbox = os.path.join(os.getcwd(), "build", "bin", build_mode,
                               WindowsRunner.__DEFAULT_SANDBOX_FILENAME)
        ensure_path_exists(sandbox)
        logging.info(f"Running: {sandbox}\n")
        WindowsRunner.__run_cmd(sandbox)

    def __run_cmd(command):
        process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                   text=True, encoding='utf-8', bufsize=1, errors='replace')
        for line in process.stdout:
            print(line.strip())
        process.wait()
        return process

    def __get_vs_base_path(vs_base_paths):
        logging.debug("Getting VS base path...")
    
        for vbp in vs_base_paths:
            if os.path.exists(vbp):
                logging.debug(f"Selected VS base path: {vbp}")
                return vbp

        msg = "VS base path not found."
        logging.error(msg)
        raise FileNotFoundError(msg)

    def __get_available_vs_edition(vs_base_path):
        logging.debug("Getting VS edition path...")
        selected_vs_edition = select_first_path_from(get_entries_in(vs_base_path))

        logging.debug("Selected VS edition path: {selected_vs_edition}")
        return selected_vs_edition

    def __get_dev_cmd_prompt(vs_edition_path):
        logging.debug("Getting VsDevCmd.bat...")
        vsdevcmd = os.path.join(vs_edition_path, "Common7", "Tools", "VsDevCmd.bat")
        ensure_path_exists(vsdevcmd)
        logging.debug(f"Selected VsDevCmd.bat: {vsdevcmd}")
        return vsdevcmd


def main():
    logging_format = '{} %(asctime)s -%(levelname)s- %(message)s'.format(os.path.basename(__file__))
    logging.basicConfig(level=logging.INFO,
                        format=logging_format,
                        datefmt='%H:%M:%S')
    if Platform.is_win64():
        runner = WindowsRunner()
        platform_os = WIN64
    else:
        logging.error("Unsupported platform.")
        exit(1)

    args = ArgParser()
    cmake_presets = CMakePresetsParser()
    cmake_runner = CMakeRunner()

    if args.should_clean():
        clean_preset = cmake_presets.get_configure_preset(platform_os, args.get_build_mode())
        runner.run_dev_command(cmake_runner.get_fresh_cmd(clean_preset, args.get_graphics_api()))
        return

    if args.should_generate():
        conf_preset = cmake_presets.get_configure_preset(platform_os, args.get_build_mode())
        runner.run_dev_command(cmake_runner.get_generate_cmd(conf_preset, args.get_graphics_api()))

    if args.should_build():
        build_preset = cmake_presets.get_build_preset(platform_os, args.get_build_mode())
        runner.run_dev_command(cmake_runner.get_build_cmd(build_preset))

    if args.should_run():
        runner.run_sandbox(args.get_build_mode())
        return


if __name__ == "__main__":
    main()
