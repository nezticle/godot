import os
import string
import sys

def is_active():
    return True


def get_name():
    return "EGLFS"

def can_build():
    return True

def get_opts():
    return [
        ('EGLFS_TOOLCHAIN_PATH', 'Location of GCC Cross-Compile Toolchain', ''),
        ('EGLFS_SYSROOT', 'Location of Target system Sysroot', ''),
        ('EGLFS_TOOLCHAIN_TRIPLE', 'Tripple name for toolchain', ''),
        ('EGLFS_DEVICE', 'Target device name', '')
    ]

def get_flags():

    return [
        ('tools', False),
    ]

def configure(env):

    ## Build type
    if (env["target"].startswith("release")):
        env.Append(CPPFLAGS=['-DNDEBUG'])
        if (env["optimize"] == "speed"): #optimize for speed (default)
            env.Append(CPPFLAGS=['-O2', '-ftree-vectorize', '-fomit-frame-pointer', '-ffast-math', '-funsafe-math-optimizations'])
            env.Append(LINKFLAGS=['-O2'])
        else: #optimize for size
            env.Append(CPPFLAGS=['-Os', '-ftree-vectorize'])
            env.Append(LINKFLAGS=['-Os'])

        if env["target"] == "release_debug":
            env.Append(CPPFLAGS=['-DDEBUG_ENABLED'])

    elif (env["target"] == "debug"):
        env.Append(CPPFLAGS=['-D_DEBUG', '-DDEBUG=1', '-g', '-O0', '-DDEBUG_ENABLED', '-DDEBUG_MEMORY_ENABLED'])

    if (env["use_lto"]):
        env.Append(CPPFLAGS=['-flto'])
        env.Append(LINKFLAGS=['-flto'])

    ## Arch
    if env["arch"] == "x86":
        env["bits"] = "32"
    elif env["arch"] == "x86_64":
        env["bits"] = "64"
    elif (env["arch"] == "arm" or env["arch"] == "arm32" or env["arch"] == "armv7" or env["bits"] == "32"):  # arm
        env["arch"] = "arm"
        env["bits"] = "32"
    else:  # armv64
        env["arch"] = "arm64"
        env["bits"] = "64"

    ## Compiler config
    env['ENV']['PATH'] = env['EGLFS_TOOLCHAIN_PATH'] + env['ENV']['PATH']

    env['CC'] = env['EGLFS_TOOLCHAIN_TRIPLE'] + 'gcc'
    env['CXX'] = env['EGLFS_TOOLCHAIN_TRIPLE'] + 'g++'
    env['AR'] = env['EGLFS_TOOLCHAIN_TRIPLE'] + 'ar'
    env['RANLIB'] = env['EGLFS_TOOLCHAIN_TRIPLE'] + 'ranlib'

    ## Compiler flags
    if (env["arch"] == "x86"):
        env.Append(CCFLAGS=['-m32'])
    if (env["arch"] == "x86_64"):
        env.Append(CCFLAGS=['-m64'])
    elif (env["arch"] == "arm"):
        env.Append(CCFLAGS='-march=armv7-a -marm -mthumb-interwork -mfpu=neon-vfpv4 -mtune=cortex-a7 -mabi=aapcs-linux -mfloat-abi=hard'.split())
    elif (env["arch"] == "arm64"):
        env.Append(CCFLAGS='-march=armv8-a -mtune=cortex-a53 -mfpu=crypto-neon-fp-armv8 '.split())

    env.Append(CCFLAGS=['--sysroot ', '$EGLFS_SYSROOT'])

    ## Link flags
    env.Append(LINKFLAGS=['--sysroot ', '$EGLFS_SYSROOT'])

    if (env["arch"] == "x86"):
        env.Append(LINKFLAGS=[])
    if (env["arch"] == "x86_64"):
        env.Append(LINKFLAGS=[])
    elif (env["arch"] == "arm"):
        env.Append(LINKFLAGS='-mfloat-abi=hard -lEGL -lGLESv2'.split())
    elif (env["arch"] == "arm64"):
        env.Append(LINKFLAGS='-mfloat-abi=hard -lEGL -lGLESv2'.split())

    ## features