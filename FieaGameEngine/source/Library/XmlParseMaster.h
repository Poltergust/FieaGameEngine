#pragma once

#include <sstream>
#include <fstream>
#include "RTTI.h"
#include "Vector.h"
#include "expat.h"

namespace Library
{
	/**
	 * Referencing the helper interface.
	 */
	class IXmlParseHelper;

	/**
	 * A class for the parse master
	 */
	class XmlParseMaster final
	{
	public:
		/**
		 * A class for shared data
		 */
		class SharedData : public RTTI
		{
			RTTI_DECLARATIONS(SharedData, RTTI)

		public:
			/**
			 * The constructor. Not directly used.
			 */
			SharedData();

			/**
			 * The default virtual destructor.
			 */
			virtual ~SharedData() = default;

			/**
			 * Resets the data members. Pure virtual.
			 */
			virtual void Reset();

			/**
			 * Clones the SharedData object to make it ready for a new file. Pure virtual.
			 * @return the newly created clone
			 */
			virtual SharedData* Clone() const = 0;

			/**
			 * Sets the parse master for this object.
			 * @param master	a pointer to the parse master
			 */
			void SetXmlParseMaster(XmlParseMaster* master);

			/**
			 * Gets the parse master pointer of this object
			 * @return a pointer to this object's parse master
			 */
			XmlParseMaster* GetXmlParseMaster() const;

			/**
			 * Increments the depth counter.
			 */
			void IncrementDepth();

			/**
			 * Decrements the depth counter.
			 * @throws an exception if depth is not at least 1
			 */
			void DecrementDepth();

			/**
			 * Gets the depth counter.
			 * @return the depth counter
			 */
			std::uint32_t Depth() const;

		private:
			XmlParseMaster* mMaster; /**< Pointer to this object's parse master. */
			std::uint32_t mDepth; /**< The depth counter. */
		};

		/**
		 * The constructor. Must take in a valid sharedData pointer.
		 * @param sharedData	a valid sharedData object
		 */
		explicit XmlParseMaster(SharedData& sharedData);

		/**
		 * The copy constructor. Deleted.
		 * @param rhs	the parse master to copy
		 */
		XmlParseMaster(const XmlParseMaster& rhs) = delete;

		/**
		 * The assignment operator. Deleted.
		 * @param rhs	the parse master to copy
		 * @return a reference to the newly copied parse master
		 */
		XmlParseMaster& operator=(const XmlParseMaster& rhs) = delete;

		/**
		 * The destructor.
		 */
		~XmlParseMaster();

		/**
		 * Resets the parser for future use.
		 */
		void ResetParser();

		/**
		 * Clones the parse master. The clone has a copy of the original's SharedData object and helpers.
		 * @return a pointer to the newly created clone
		 */
		XmlParseMaster* Clone() const;

		/**
		 * Adds a helper to the parse master for use in parsing.
		 * @param helper	the reference to the helper
		 */
		void AddHelper(IXmlParseHelper& helper);

		/**
		 * Removes a helper from the parse master.
		 * @param helper	the reference to the helper
		 * @throws an exception if the helper could not be found
		 */
		void RemoveHelper(IXmlParseHelper& helper);

		/**
		 * Parses the given string.
		 * @param s	the string to be parsed
		 * @param len	the length of the string to parse
		 * @param isFinal	a boolean telling the parser if it is done parsing or not
		 * @throws an exception if the parsing could not be completed successfully
		 */
		void Parse(const char* s, std::uint32_t len, bool isFinal);

		/**
		 * Reads in a file, then calls parse on the read-in string.
		 * @param filename	the file to read from
		 */
		void ParseFromFile(const std::string& filename);

		/**
		 * Gets the filename of what the parser is currently reading.
		 * @return the filename
		 */
		const std::string& GetFileName() const;

		/**
		 * Gets the SharedData pointer for this parse master.
		 * @return the pointer to the SharedData object
		 */
		SharedData* GetSharedData() const;

		/**
		 * Sets this parse master's SharedData pointer to another.
		 * @param sharedData	the new sharedData pointer to assign to this parse master
		 */
		void SetSharedData(SharedData* sharedData);

	private:

		/**
		 * Handles the Start callback for XML_Parse. Passes it to its helpers.
		 * @param userData	a pointer to the data that should store the results of the parse
		 * @param elementName	the name of the start element
		 * @param attributes	the attributes for this element
		 */
		static void StartElementHandler(void* userData, const XML_Char* elementName, const XML_Char** attributes);

		/**
		 * Handles the End callback for XML_Parse. Passes it to its helpers.
		 * @param userData	a pointer to the data that should store the results of the parse
		 * @param elementName	the name of the end element
		 */
		static void EndElementHandler(void* userData, const XML_Char* elementName);

		/**
		 * Handles the Data callback for XML_Parse. Passes it to its helpers.
		 * @param userData a pointer to the data the should store the results of the parse
		 * @param s	the character data
		 * @param len	the length of the character data
		 */
		static void CharDataHandler(void* userData, const XML_Char* s, std::uint32_t len);

		XML_Parser mParser; /**< The parser object for this parse master. */
		SharedData* mSharedData; /**< The pointer to this parse master's SharedData. */
		Vector<IXmlParseHelper*> mHelpers; /**< The helpers for this parse master. */
		std::string mFile; /**< The file that is being read in to this parse master. */
		bool mIsClone; /**< Tells if this parse master is a clone or not. */
	};
}