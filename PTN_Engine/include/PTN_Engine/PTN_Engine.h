/*
 * This file is part of PTN Engine
 *
 * Copyright (c) 2017 Eduardo Valgôde
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "PTN_Engine/Utilities/Explicit.h"
#include <memory>
#include <vector>

namespace ptne
{
	class IConditionFunctor;
	class IActionFunctor;
	class PTN_EngineImp;

	using ConditionFunctorPtr = std::shared_ptr<IConditionFunctor>;
	using ActionFunctorPtr = std::shared_ptr<IActionFunctor>;

	//! Base class that implements the Petri net logic.
	/*!
	 * Base class that implements the Petri net logic.
	 * Using the pipmpl idiom.
	 * \sa PTN_EngineImp
	 */
	class DLL_PUBLIC PTN_Engine
	{
	public:

		virtual ~PTN_Engine();

	protected:

		//! Default constructor
		PTN_Engine();

		/*!
		 * Create a new transition
		 * \param activationPlaces A vector with the names of the activation places.
		 * \param activationWeights A vector with the weights of each activation place.
		 * \param destinationPlaces A vector with the names of the destination places.
		 * \param destinationWeights A vector with the weights of each destination place.
		 * \param additionalConditions A vector with functors that return bool.
		 * \param inhibitorPlaces Places that cannot have tokens to fire the transition.
		 */
		void createTransition(
			const std::vector<std::string>& activationPlaces,
			const std::vector<size_t>& activationWeights,
			const std::vector<std::string>& destinationPlaces,
			const std::vector<size_t>& destinationWeights,
			const std::vector<ConditionFunctorPtr>& additionalConditions,
			const std::vector<std::string>& inhibitorPlaces = {});

		/*!
		 * Create a new transition
		 * \param activationPlaces A vector with the names of the activation places.
		 * \param destinationPlaces A vector with the names of the destination places.
		 * \param additionalConditions A vector with functors that return bool.
		 * \param inhibitorPlaces Places that cannot have tokens to fire the transition.
		 */
		void createTransition(
			const std::vector<std::string>& activationPlaces,
			const std::vector<std::string>& destinationPlaces,
			const std::vector<ConditionFunctorPtr>& additionalConditions,
			const std::vector<std::string>& inhibitorPlaces = {});

		//! Run until it no more transitions can be fired or stop is flagged.
		void execute();

		/*!
		 * Add place a place to the net.
		 * \param name The name of the place.
		 * \param initialNumberOfTokens The number of tokens to be initialized with.
		 * \param onEnterAction The functor to be called once a token enters the place.
		 * \param onExitAction The functor to be called once a token leaves the place.
		 * \param input A flag determining if this place can have tokens added manually.
		 */
		void addPlace(
				const std::string& name,
				const size_t initialNumberOfTokens,
				ActionFunctorPtr onEnterAction,
				ActionFunctorPtr onExitAction,
				const bool input = false);

		/*!
		 * Return the number of tokens in a given place.
		 * \param place The name of the place to get the number of tokens from.
		 * \return The number of tokens present in the place.
		 */
		size_t getNumberOfTokens(const std::string& place) const;

		/*!
		 * Add a token to an input place.
		 * \param place Name of the place to be incremented.
		 */
		void incrementInputPlace(const std::string& place);

	private:

		//! Pointer to implementation of the PTN_Engine.
		std::unique_ptr<PTN_EngineImp> m_implementation;

	};

}
