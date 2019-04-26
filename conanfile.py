from conans import ConanFile, CMake, tools
import os
import glob
import re

class LlvmConan(ConanFile):
    name = "llvm"
    version = "8.0.0"
    license = "MIT"
    author = "<Put your name here> <And your email here>"
    url = "https://github.com/woidpointer/conan-llvm"
    description = "<Description of Llvm here>"
    topics = ("llvm", "clang")
    settings = "os", "compiler", "build_type", "arch"
    options = {
            "shared": [True, False],
            "enable_zlib": [True, False] 
            }
    default_options = {
            "shared": False,
            "enable_zlib": False
            }
    generators = "cmake"
    self_dir = os.getcwd()

    
    exports_sources = '*.patch'

    def source(self):
        cmd = []
        cmd.append("git clone")
        cmd.append("https://github.com/llvm/llvm-project.git -b")
        cmd.append("llvmorg-{} --depth 1".format(self.version))
        self.run(" ".join(cmd))

        # apply the cmake patch
        source_dir = "{}/llvm-project".format(self.source_folder)
        tools.patch(patch_file="{}/cmake_include_interface.patch".format(self.self_dir), base_path=source_dir)

    def build(self):
        
        if self.settings.compiler == 'Visual Studio':
            cmake = CMake(self, toolset="v141")            
        else:
            cmake = CMake(self) 

        cmake.definitions["LLVM_ENABLE_PROJECTS"] = "clang"
        cmake.definitions["LLVM_ENABLE_ZLIB"] = "ON" if self.options.enable_zlib else "OFF"

        source_sub_folder = "{}/llvm-project/llvm".format(self.source_folder)
        #print(cmake.command_line)
        cmake.configure(source_folder=source_sub_folder)                      
        cmake.build()
        cmake.install()

    def package(self):
        # copy all artefacts which where generated by LLVM/clang build process
        self.copy(pattern="*", dst="", src="package")
        source_sub_folder = "{}/llvm-project/llvm".format(self.source_folder)
        self.copy("license*", src=source_sub_folder, dst="licenses",  ignore_case=True, keep_path=False)

    def package_info(self):
        self.cpp_info.libdirs = ["lib"]
        self.cpp_info.bindirs = ["bin"]
        # Add everything what we build into the package:
        files = [os.path.basename(f) for f in glob.glob("lib/*.lib")]
        files = [os.path.basename(f) for f in glob.glob("lib/*.a")]
        # replace file extension to nothing, to get the "raw" library name
        # in order to register this name to conan/cmake
        files = list(map(lambda f: os.path.splitext(f)[0], files))
        # In the case of Linux: replace the ^lib* to nothing
        files = list(map(lambda f: re.sub(r'^lib(.*)$', r'\1', f), files))
        self.cpp_info.libs = list(files)



