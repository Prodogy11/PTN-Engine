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

#include "gtest/gtest.h"
#include "Fixtures/FixturePetriNet.h"

TEST_F(FixturePetriNet, T1)
{
	if(!m_dispatcher)
	{
		throw std::runtime_error("No dispatcher available");
	}

	EXPECT_EQ(true, m_dispatcher->m_isWaitingPackage && m_dispatcher->m_isChannelASelected && (!m_dispatcher->m_isChannelBSelected));

	//	m_plInputWaitPackage;
	//	m_plWaitPackage;
	//	m_plChannelA;
	//	m_plChannelB;
	//	m_plSelectA;
	//	m_plSelectB;
	//	m_plPackageCounter;
	size_t expectedState[7] = {0,1,0,0,1,0,0};

	testState(expectedState);

	m_dispatcher->dispatch();
	EXPECT_EQ(true, m_dispatcher->m_isWaitingPackage && m_dispatcher->m_isChannelBSelected && (!m_dispatcher->m_isChannelASelected));

	expectedState[4] = 0; 	//	m_plSelectA;
	expectedState[5] = 1; 	//	m_plSelectB;
	expectedState[6] = 1; 	//	m_plPackageCounter;
	testState(expectedState);

	m_dispatcher->dispatch();
	EXPECT_EQ(true, m_dispatcher->m_isWaitingPackage && m_dispatcher->m_isChannelASelected && (!m_dispatcher->m_isChannelBSelected));

	expectedState[4] = 1;  	//	m_plSelectA;
	expectedState[5] = 0;  	//	m_plSelectB;
	expectedState[6] = 2;  	//	m_plPackageCounter;
	testState(expectedState);

	m_dispatcher->setResetCounter(true);
	m_dispatcher->dispatch();
	expectedState[4] = 0;  	//	m_plSelectA;
	expectedState[5] = 1;  	//	m_plSelectB;
	expectedState[6] = 0;  	//	m_plPackageCounter;
	testState(expectedState);

}
