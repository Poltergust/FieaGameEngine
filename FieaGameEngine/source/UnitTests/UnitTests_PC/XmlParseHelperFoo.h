#pragma once

#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"

namespace Library
{
	/**
	 * A simple helper class for the parse master; derives from the helper interface.
	 */
	class XmlParseHelperFoo : public IXmlParseHelper
	{
	public:
		/**
		 * A SharedData class that takes in integer data; derives from the parse master's SharedData class
		 */
		class SharedData : public XmlParseMaster::SharedData
		{
			/**
			 * The XmlParseHelperFoo class will need easy access to this SharedData's members.
			 */
			friend class XmlParseHelperFoo;

			RTTI_DECLARATIONS(SharedData, XmlParseMaster::SharedData)
		public:
			/**
			 * The constructor.
			 */
			SharedData();

			/**
			 * The default destructor.
			 */
			virtual ~SharedData() = default;

			/**
			 * Resets all the members in this instance.
			 */
			virtual void Reset();

			/**
			 * Clones this SharedData object.
			 * @returns a pointer to the newly created clone
			 */
			virtual SharedData* Clone() const;

			/**
			 * Gets the integer data.
			 * @returns the integer data
			 */
			int GetIntData() const;

			/**
			 * Gets the start element name.
			 * @return the start element name
			 */
			std::string GetStartElementName() const;

			/**
			 * Gets the end element name.
			 * @return the end element name
			 */
			std::string GetEndElementName() const;

			/**
			 * Gets the attribute key.
			 * @return the attribute key
			 */
			std::string GetAttributeKey() const;

			/**
			 * Gets the attribute value.
			 * @return the attribute value
			 */
			std::string GetAttributeValue() const;

			/**
			 * Gets the number of start calls.
			 * @return the number of start calls
			 */
			std::uint32_t GetNumStartCalls() const;

			/**
			 * Gets the number of end calls.
			 * @return the number of end calls
			 */
			std::uint32_t GetNumEndCalls() const;

			/**
			 * Gets the maximum depth.
			 * @return the maximum depth.
			 */
			std::uint32_t GetMaxDepth() const;

		private:
			int mIntData; /**< The integer data. */
			std::string mStartElementName; /**< The start element name. */
			std::string mEndElementName; /**< The end element name. */
			std::string mAttributeKey; /**< The attribute key. */
			std::string mAttributeValue; /**< The attribute value. */
			std::uint32_t mStartCalls; /**< The number of start calls. */
			std::uint32_t mEndCalls; /**< The number of end calls. */
			std::uint32_t mMaxDepth; /**< The maximum depth. */
		};

		/**
		 * The default constructor.
		 */
		XmlParseHelperFoo() = default;

		/**
		 * The default destructor.
		 */
		virtual ~XmlParseHelperFoo() = default;

		/**
		 * Initializes the helper.
		 */
		virtual void Initialize();

		/**
		* Handles the Start callback, called from the parse master.
		* @param sharedData 	the data to store the results of the parse; must be of type XmlParseHelperFoo::SharedData
		* @param elementName	the name of the start element
		* @param attributes	the attributes of the element
		* @return true if the data could be handled properly, false otherwise
		*/
		virtual bool StartElementHandler(XmlParseMaster::SharedData* sharedData, const std::string& elementName, const HashMap<std::string, std::string>& attributes);

		/**
		* Handles the End callback, called from the parse master.
		* @param sharedData	the data to store the results of the parse; must be of type XmlParseHelperFoo::SharedData
		* @param elementName	the name of the end element
		* @throws an exception if the start and end element names do not match
		* @return true if the data could be handled properly, false otherwise
		*/
		virtual bool EndElementHandler(XmlParseMaster::SharedData* sharedData, const std::string& elementName);

		/**
		* Handles the Data callback, called from the parse master.
		* @param sharedData	the data to store the results of the parse; must be of type XmlParseHelperFoo::SharedData
		* @param s	the character data
		* @param len	the length of the character data
		* @return true if the data could be handled properly, false otherwise
		*/
		virtual bool CharDataHandler(XmlParseMaster::SharedData* sharedData, const std::string& s, std::uint32_t len);

		/**
		 * Clones the helper.
		 * @return the pointer to the newly created clone
		 */
		virtual XmlParseHelperFoo* Clone() const;

	private:
		std::string mStringHelperData;
	};
}