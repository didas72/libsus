#include "sus.h"

const char *sus_strerror(int error)
{
	switch (error)
	{
		case SUS_ERR: 
			return "Unspecified error";
		case SUS_INVALID_ARG:
			return "Invalid argument";
		case SUS_FAILED_ALLOC:
			return "Memory allocation failed";
		case SUS_INVALID_INDEX:
			return "Index out of bounds";
		case SUS_ENTRY_NOT_FOUND:
			return "Entry not found";
		case SUS_INVALID_RANGE:
			return "Invalid range";
		case SUS_INCOMPATIBLE_IVECTORS:
			return "Incompatible ivector types";
		case SUS_SUCCESS:
			return "No error";

		default:
			return "Unknown/invalid error value";
	}
}
