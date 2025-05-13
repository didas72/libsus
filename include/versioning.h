//versioning.h - Library versioning safeguard
#ifndef SUS_VERSION_H_
#define SUS_VERSION_H_

#define SUS_VERSION_PACK(major, minor, patch) ((major) * 10000 + (minor) * 100 + (patch))
#define SUS_VERSION_UNPACK_MAJOR(version) ((version) / 10000)
#define SUS_VERSION_UNPACK_MINOR(version) (((version) / 100) % 100)
#define SUS_VERSION_UNPACK_PATCH(version) ((version) % 100)

#define SUS_VERSION_MAJOR 1
#define SUS_VERSION_MINOR 0
#define SUS_VERSION_PATCH 0
#define SUS_VERSION SUS_VERSION_PACK(SUS_VERSION_MAJOR, SUS_VERSION_MINOR, SUS_VERSION_PATCH)

#ifdef _SUS_IMPLEMENTATION_
#define SUS_TARGET_VERSION SUS_VERSION
#endif

#ifndef SUS_TARGET_VERSION
#warning "SUS_TARGET_VERSION not defined. Assuming code exprects pre-versioning interface."
#define SUS_NO_VERSION
#else

#if SUS_VERSION_UNPACK_MAJOR(SUS_TARGET_VERSION) > SUS_VERSION_MAJOR
#error "Unsupported sus version: Expected major too high."
#elif SUS_VERSION_UNPACK_MAJOR(SUS_TARGET_VERSION) == SUS_VERSION_MAJOR
#if SUS_VERSION_UNPACK_MINOR(SUS_TARGET_VERSION) > SUS_VERSION_MINOR
#error "Unsupported sus version: Expected minor too high."
#endif
#elif SUS_VERSION_UNPACK_MAJOR(SUS_TARGET_VERSION) < SUS_VERSION_MAJOR
#warning "Expected sus major version is lower than present. Compatibility is attempted but not guaranteed."
//Add compatibility changes as needed
#endif

#endif

#endif
