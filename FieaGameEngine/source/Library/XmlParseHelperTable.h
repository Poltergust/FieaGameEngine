#pragma once

#include <cctype>
#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"
#include "Attributed.h"

namespace Library
{
	/**
	 * A class for scopes within our XML parsing.
	 */
	class XmlParseHelperTable : public IXmlParseHelper
	{

	public:
		/**
		 * Enumeration for parsing type. Intentionally matches up with Datum::DatumTypes.
		 */
		enum ParsingType { Unknown, Integer, Float, Vector, Matrix, Table, String, Pointer };

		/**
		 * The SharedData class; derives from XmlParseMaster's SharedData class
		 */
		class SharedData : public XmlParseMaster::SharedData
		{
			/**
			 * The XmlParseHelperTable will need easy access to this class' private members
			 */
			friend class XmlParseHelperTable;

			/**
			 * The XmlParseHelperWorld will need easy access to this class' private members
			 */
			friend class XmlParseHelperWorld;

			/**
			 * The XmlParseHelperSector will need easy access to this class' private members
			 */
			friend class XmlParseHelperSector;

			/**
			 * The XmlParseHelperEntity will need easy access to this class' private members
			 */
			friend class XmlParseHelperEntity;

			/**
			* The XmlParseHelperAction will need easy access to this class' private members
			*/
			friend class XmlParseHelperAction;

			RTTI_DECLARATIONS(SharedData, XmlParseMaster::SharedData)

		public:
			/**
			 * The constructor.
			 * @param scope an allocated scope pointer
			 */
			explicit SharedData(Scope* scope);

			/**
			 * The deleted copy constructor.
			 */
			SharedData(const SharedData& rhs) = delete;

			/**
			 * The deleted assignment operator.
			 */
			SharedData& operator=(const SharedData& rhs) = delete;

			/**
			 * The default destructor.
			 */
			virtual ~SharedData() = default;

			/**
			 * Resets all values within this instance.
			 */
			virtual void Reset();

			/**
			 * Creates a new SharedData instance.
			 * @return the new SharedData instance
			 */
			virtual SharedData* Clone() const;

			/**
			 * Gets the scope pointer.
			 * @return the scope pointer
			 */
			Scope* GetScopeData() const;

			/**
			 * Gets the grand scope.
			 * @return the grand scope
			 */
			Scope* GetGrandScope() const;

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
			 * Gets the char data.
			 * @return the char data
			 */
			std::string GetCharData() const;

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
			Scope* mScope; /**< The scope to hold data. */
			Scope* mGrandScope; /**< This scope encompasses all other scopes. */
			std::string mAttributeKey; /**< The attribute key. */
			std::string mAttributeValue; /**< The attribute value. */
			std::string mCharData; /**< The char data. */
			std::uint32_t mStartCalls; /**< The number of start calls. */
			std::uint32_t mEndCalls; /**< The number of end calls. */
			std::uint32_t mMaxDepth; /**< The maximum depth. */
		};

		/**
		 * The constructor.
		 */
		explicit XmlParseHelperTable();

		/**
		 * The default destructor.
		 */
		virtual ~XmlParseHelperTable() = default;

		/**
		* Initializes the helper.
		*/
		virtual void Initialize();

		/**
		* Handles the Start callback, called from the parse master.
		* @param sharedData 	the data to store the results of the parse; must be of type XmlParseHelperTable::SharedData
		* @param elementName	the name of the start element
		* @param attributes	the attributes of the element
		* @return true if the data could be handled properly, false otherwise
		*/
		virtual bool StartElementHandler(XmlParseMaster::SharedData* sharedData, const std::string& elementName, const HashMap<std::string, std::string>& attributes);

		/**
		* Handles the End callback, called from the parse master.
		* @param sharedData	the data to store the results of the parse; must be of type XmlParseHelperTable::SharedData
		* @param elementName	the name of the end element
		* @throws an exception if the start and end element names do not match
		* @return true if the data could be handled properly, false otherwise
		*/
		virtual bool EndElementHandler(XmlParseMaster::SharedData* sharedData, const std::string& elementName);

		/**
		* Handles the Data callback, called from the parse master.
		* @param sharedData	the data to store the results of the parse; must be of type XmlParseHelperTable::SharedData
		* @param s	the character data
		* @param len	the length of the character data
		* @return true if the data could be handled properly, false otherwise
		*/
		virtual bool CharDataHandler(XmlParseMaster::SharedData* sharedData, const std::string& s, std::uint32_t len);

		/**
		* Clones the helper.
		* @return the pointer to the newly created clone
		*/
		virtual XmlParseHelperTable* Clone() const;

	private:
		ParsingType mParsingType; /**< The parsing type. */

		/**
		 * Helper function for determining if a string is a number.
		 * @param s	the string to read
		 * @return true if the string can be represented as a number, false otherwise
		 */
		bool IsStringNumber(const std::string& s) const;
	};
}