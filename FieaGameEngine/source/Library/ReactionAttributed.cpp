#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(ReactionAttributed)

	ReactionAttributed::ReactionAttributed(std::uint32_t subtypeSize) : mSubtype(new int[subtypeSize]), mNumSubtypes(subtypeSize)
	{
		memset(mSubtype, MAXINT32, mNumSubtypes);
		EXTERNAL_ATTRIBUTE(std::string("subtype"), Datum::Integer, mNumSubtypes, mSubtype);
		Populate();
		Event<EventMessageAttributed>::Subscribe(*this);
	}

	ReactionAttributed::~ReactionAttributed()
	{
		delete[] mSubtype;
		Event<EventMessageAttributed>::Unsubscribe(*this);
	}

	int ReactionAttributed::GetSubtype(std::uint32_t index) const
	{
		if (index >= mNumSubtypes)
			throw std::exception("Index is too large.");

		return mSubtype[index];
	}

	void ReactionAttributed::SetSubtype(int subtype, std::uint32_t index)
	{
		if (index >= mNumSubtypes)
			throw std::exception("Index is too large.");

		mSubtype[index] = subtype;
	}

	void ReactionAttributed::Notify(const EventPublisher* eventPublisher)
	{
		Event<EventMessageAttributed>* e = eventPublisher->As<Event<EventMessageAttributed>>();
		if (e != nullptr)
		{
			for (std::uint32_t i = 0; i < mNumSubtypes; ++i)
			{
				if (mSubtype[i] == e->Message().GetSubtype())
				{
					Iterator iterator = e->Message().begin();
					for (std::uint32_t counterToAuxiliaryBegin = 0; counterToAuxiliaryBegin != e->Message().AuxiliaryBegin(); ++counterToAuxiliaryBegin)
					{
						++iterator;
					}

					while (iterator != e->Message().end())
					{
						AppendAuxiliaryAttribute((*iterator)->first) = (*iterator)->second;
						++iterator;
					}

					Update(*e->Message().GetWorld()->GetWorldState());
					break;
				}
			}
		}
	}
}