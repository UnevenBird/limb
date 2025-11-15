#ifndef LIMB_CONFIG_H
#define LIMB_CONFIG_H

#if defined(WIN32) || defined(_WIN32)
	#define LIMB_WINDOWS 1
#endif

#ifndef LIMB_UNUSED
#	define LIMB_UNUSED(x) (void)sizeof(x)
#endif

#if !defined(LIMB_WINDOWS)
#	error Current target platform isn't supported.
#endif

#endif // LIMB_CONFIG_H
