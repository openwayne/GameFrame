﻿#pragma once
#ifndef idCE633B91_11A4_4E7F_84ECFC08322327EE
#define idCE633B91_11A4_4E7F_84ECFC08322327EE

#include "gf/Global.h"
#include "gf/EntityManager.h"
#include "gf/ResourceManager.h"
#include "gf/MessageManager.h"
//#include "gf/EntitySystemThread.h"

#include <boost/thread.hpp>

namespace gf {
    
    class EntitySystemThread;
    
    class GameFrame {
    public:
        GameFrame();
        ~GameFrame();
        
        template<class T> T* addSystem(uint8_t thread = 0);
        
        // This is what actually builds the threads (0 is the main() thread)
        // It adds them all to a thread group, and then runs them until
        // they all stop. This is designed to be the return to main(), so
        // error codes can be returned as ints.
        int run();
        
        EntityManager& entityManager();
        ResourceManager& resourceManager();
        MessageManager& messageManager();
        
    private:
        typedef boost::ptr_unordered_map<uint8_t, EntitySystemThread> EntitySystemThreads;
        EntitySystemThreads systemThreads;
        
        boost::ptr_unordered_set<boost::thread> threads;
        
        EntityManager entities;
        ResourceManager resources;
        MessageManager messages;
    };
    
    template<class T> T* GameFrame::addSystem(uint8_t thread) {
    	std::pair<EntitySystems::iterator, bool> systemPair = systemThreads.insert(std::pair<uint8_t, EntitySystemThread*>(thread, new T()));
    	if (systemPair.second) {
    		return systemPair.first;
    	} else {
    		return null_ptr;
    	}
    }

}

#endif // header
