/*****************************************************************//**
 * @file   fileio.h
 * @brief  Basic wrapper for c++ std::filesystem and related algorithms
 *
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#ifndef  EL_FILEIO_H
#define  EL_FILEIO_H

#include <filesystem>
#include "define.h"
#include "string.h"

namespace el
{
	namespace fio = std::filesystem;

	namespace el_file
	{
		/**
		 * @brief Gets the unique identifier of a path
		 * 
		 * Implementation is OS dependent. (Or at least, should be.)
		 * For binary files, use el::stream.
		 * 
		 * @warning Currently only supports Windows.
		 * @param path Full path of filesystem.
		 * @return Unique file ID (inode) in long long type
		 */
		long long identifier(fio::path path);

		/**
		 * Most basic file output function.
		 *
		 * @param filePath Directory path address.
		 * @param output String content to be saved.
		 * @return 0 if success, 1 if fail (address failure)
		 */
		 int save(strview filePath, strview output);

		/**
		 * Most basic file input function.
		 *
		 * @param filePath Directory path address.
		 * @param input Completely replaced with loaded content.
		 * @return 0 if success, 1 if fail
		 */
		 int load(const char* filePath, string& input);
	}

	namespace el_env
	{

#if _MSC_VER && !__INTEL_COMPILER
		/**
		 * Set local environment variable, not global
		 *
		 * @param name : Name of variable
		 * @param value : Value of variable
		 * @param overwrite : check for overwrite errors if true
		 *
		 * @return Errorcode, 0 if success
		 */
		 int setenv(const char* name, const char* value, int overwrite);

		/**
		 * Get local environment variable, not global
		 *
		 * @param name : Name of variable
		 * @return : Value of variable in string. Returns empty string if environment doesn't exist
		 */
		 string getenv(const char* name);
#endif
	}
}

#endif