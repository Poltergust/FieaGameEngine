#pragma once

#include <cctype>
#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"
#include "Entity.h"

namespace Library
{
	/**
	* A class for scopes within our XML parsing.
	*/
	class XmlParseHelperEntity : public IXmlParseHelper
	{

	public:
		/**
		* The default constructor.
		*/
		explicit XmlParseHelperEntity() = default;

		/**
		* The default destructor.
		*/
		virtual ~XmlParseHelperEntity() = default;

		/**
		* Initializes the helper.
		*/
		virtual void Initialize();

		/**
		* Handles the Start callback, called from the parse master.
		* @param sharedData 	the data to store the results of the parse; must be of type XmlParseHelperEntity::SharedData
		* @param elementName	the name of the start element
		* @param attributes	the attributes of the element
		* @return true if the data could be handled properly, false otherwise
		*/
		virtual bool StartElementHandler(XmlParseMaster::SharedData* sharedData, const std::string& elementName, const HashMap<std::string, std::string>& attributes);

		/**
		* Handles the End callback, called from the parse master.
		* @param sharedData	the data to store the results of the parse; must be of type XmlParseHelperEntity::SharedData
		* @param elementName	the name of the end element
		* @throws an exception if the start and end element names do not match
		* @return true if the data could be handled properly, false otherwise
		*/
		virtual bool EndElementHandler(XmlParseMaster::SharedData* sharedData, const std::string& elementName);

		/**
		* Handles the Data callback, called from the parse master.
		* @param sharedData	the data to store the results of the parse; must be of type XmlParseHelperEntity::SharedData
		* @param s	the character data
		* @param len	the length of the character data
		* @return true if the data could be handled properly, false otherwise
		*/
		virtual bool CharDataHandler(XmlParseMaster::SharedData* sharedData, const std::string& s, std::uint32_t len);

		/**
		* Clones the helper.
		* @return the pointer to the newly created clone
		*/
		virtual XmlParseHelperEntity* Clone() const;

	private:
		typedef XmlParseHelperTable::SharedData SharedData; /**< Typedef for the XmlParseHelperTable's SharedData. */
	};
}