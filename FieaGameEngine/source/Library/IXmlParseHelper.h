#pragma once

#include "XmlParseMaster.h"
#include "HashMap.h"

namespace Library
{
	/**
	 * An interface for the helpers of the parse master.
	 */
	class IXmlParseHelper
	{
	public:
		typedef XmlParseMaster::SharedData SharedData; /**< A type for the parse master's SharedData class. */

		/**
		 * The default constructor.
		 */
		IXmlParseHelper() = default;

		/**
		* The copy constructor. Deleted.
		* @param rhs	the parse helper to copy
		*/
		IXmlParseHelper(const IXmlParseHelper& rhs) = delete;

		/**
		* The assignment operator. Deleted.
		* @param rhs	the parse helper to copy
		* @return a reference to the newly copied parse helper
		*/
		IXmlParseHelper& operator=(const IXmlParseHelper& rhs) = delete;

		/**
		 * The default destructor.
		 */
		virtual ~IXmlParseHelper() = default;

		/**
		 * Initializes the helper.
		 */
		virtual void Initialize();

		/**
		 * Handles the Start callback, called from the parse master. Pure virtual.
		 * @param sharedData 	the data to store the results of the parse
		 * @param elementName	the name of the start element
		 * @param attributes	the attributes of the element
		 * @return true if the data could be handled properly, false otherwise
		 */
		virtual bool StartElementHandler(SharedData* sharedData, const std::string& elementName, const HashMap<std::string, std::string>& attributes) = 0;

		/**
		 * Handles the End callback, called from the parse master. Pure virtual.
		 * @param sharedData	the data to store the results of the parse
		 * @param elementName	the name of the end element
		 * @return true if the data could be handled properly, false otherwise
		 */
		virtual bool EndElementHandler(SharedData* sharedData, const std::string& elementName) = 0;

		/**
		 * Handles the Data callback, called from the parse master.
		 * @param sharedData	the data to store the results of the parse
		 * @param s	the character data
		 * @param len	the length of the character data
		 * @return true if the data could be handled properly, false otherwise
		 */
		virtual bool CharDataHandler(SharedData* sharedData, const std::string& s, std::uint32_t len);

		/**
		 * Clones the helper.
		 * @return a pointer to the newly copied clone
		 */
		virtual IXmlParseHelper* Clone() const = 0;
	};
}